#include "Deplacement.h"
#include "Plateau.h"

Deplacement::Deplacement(const int ligne, const int colonne, const int repetition)
{
    Init(ligne, colonne, -1, repetition, false, false, true, false);
}

Deplacement::Deplacement(const int ligne, const int colonne, const Couleur couleur, const int repetition, const bool libre, const bool pion, const bool limitee, const bool ligneVue)
{
    Init(ligne, colonne, couleur, repetition, libre, pion, limitee, ligneVue);
}

Deplacement::~Deplacement()
{
    //dtor
}

void Deplacement::Init(const int ligne, const int colonne, const int couleur, const int repetition, const bool libre, const bool pion, const bool limitee, const bool ligneVue)
{
    m_ligne = ligne;
    m_colonne = colonne;
    if(couleur != -1)
    {
        m_couleur[1 - couleur] = false;
        m_couleur[couleur] = true;
    }
    else m_couleur[0] = m_couleur[1] = true;
    m_repetition = repetition;
    m_occupee = pion;
    m_libre= libre;
    m_limitee = limitee;
    m_ligneVue = ligneVue;
}

const bool Deplacement::Accessible(const int ligne, const int colonne)
{
    //On verifie qu'on bouge sur les axes voulus
    if(((m_ligne == 0) && (ligne != 0))
       || ((m_colonne == 0) && (colonne != 0)))
        return false;
    //On verifie que l'on va dans la bonne direction
    if(((m_ligne * ligne) < 0)
       || ((m_colonne * colonne) < 0))
        return false;
    //On verifie "le reste"
    if(((ligne % m_ligne) != 0)
       || ((colonne % m_colonne) != 0))
        return false;
    //Nombre de deplacements verticaux
    int v = ligne / m_ligne;
    if((m_repetition != -1) && (v > m_repetition))
        return false;
    //Nombre de deplacements verticaux
    int h = colonne / m_colonne;
    if((m_repetition != -1) && (h > m_repetition))
        return false;
    //On verifie le bon nombre de deplacements
    if(v != h)
        return false;
    return true;
}

//x ligne, y colonne
const std::vector<int*> Deplacement::GetPossibles(const int ligne, const int colonne, Plateau &p, const Couleur couleur, const bool limite) const
{
    std::vector<int*> vect;
    if(m_couleur[couleur] && (m_limitee || limite))
    {
        bool continuer = true;
        int ite = 0;
        while(continuer)
        {
            ite++;
            if((m_repetition > 0) && (ite > m_repetition))
                continuer = false;
            else
            {
                //Nouvelle ligne
                int dLig = (ite * m_colonne) + ligne;
                //Nouvelle colonne
                int dCol = (ite * m_ligne) + m_colonne;
                //On vérifie que l'on reste sur le plateau
                if((dCol >= 8)
                   || (dCol < 0)
                   || (dLig >= 8)
                   || (dLig < 0))
                    continuer = false;

                else if(m_ligneVue)
                {
                    //On s'assure de respecter la ligne de vue
                    //Càd qu'il n'y ait aucune pièce entre le point de départ et celui d'arrivée
                    //On ne regarde que les pièces sur la ligne car ce cas ne concerne que le roi qui roque
                    int mod = (m_ligne > 0) ? 1 : -1;
                    for(int i = (((ite - 1) * m_ligne) + colonne);
                        (i != (dCol + mod)) && continuer;
                        i += mod)
                    {
                        if(!p.Libre(dLig, i + mod))
                            continuer = false;
                    }
                }
                if(continuer)
                {
                    bool enreg = false;
                    if(p.Libre(dLig, dCol) && (!m_occupee))
                        enreg = true;
                    else
                    {
                        Piece *pt = p.GetPiece(dLig, dCol);
                        if((pt != NULL) && (!m_libre) && (pt->GetCouleur() != couleur))
                            enreg = true;;
                        continuer = false;
                    }
                    if(enreg)
                    {
                        int* ntab = new int[2];
                        ntab[0] = dLig;
                        ntab[1] = dCol;
                        vect.push_back(ntab);
                    }
                }
            }
        }
    }
    return vect;
}

Deplacement Deplacement::LigneH = Deplacement(0, -1, -1);
Deplacement Deplacement::LigneB = Deplacement(0, 1, -1);
Deplacement Deplacement::LigneD = Deplacement(1, 0, -1);
Deplacement Deplacement::LigneG = Deplacement(-1, 0, -1);
Deplacement Deplacement::DiagoHD = Deplacement(1, -1, -1);
Deplacement Deplacement::DiagoBD = Deplacement(1, 1, -1);
Deplacement Deplacement::DiagoBG = Deplacement(-1, 1, -1);
Deplacement Deplacement::DiagoHG = Deplacement(-1, -1, -1);
Deplacement Deplacement::CavalierHHG = Deplacement(-1, -2, 1);
Deplacement Deplacement::CavalierHHD = Deplacement(1, -2, 1);
Deplacement Deplacement::CavalierBBG = Deplacement(-1, 2, 1);
Deplacement Deplacement::CavalierBBD = Deplacement(1, 2, 1);
Deplacement Deplacement::CavalierGGH = Deplacement(-2, -1, 1);
Deplacement Deplacement::CavalierGGB = Deplacement(-2, 1, 1);
Deplacement Deplacement::CavalierDDH = Deplacement(2, -1, 1);
Deplacement Deplacement::CavalierDDB = Deplacement(2, 1, 1);
Deplacement Deplacement::PionBB = Deplacement(0, 1, _BLANC, 2, true, false, false);
Deplacement Deplacement::PionB = Deplacement(0, 1, _BLANC, 1, true, false, true);
Deplacement Deplacement::PionHH = Deplacement(0, -1, _NOIR, 2, true, false, false);
Deplacement Deplacement::PionH = Deplacement(0, -1, _NOIR, 1, true, false, true);
Deplacement Deplacement::PionBG = Deplacement(-1, 1, _BLANC, 1, false, true);
Deplacement Deplacement::PionBD = Deplacement(1, 1, _BLANC, 1, false, true);
Deplacement Deplacement::PionHG = Deplacement(-1, -1, _NOIR, 1, false, true);
Deplacement Deplacement::PionHD = Deplacement(1, -1, _NOIR, 1, false, true);
Deplacement Deplacement::SimpleH = Deplacement(0, -1, 1);
Deplacement Deplacement::SimpleHD = Deplacement(1, -1, 1);
Deplacement Deplacement::SimpleD = Deplacement(1, 0, 1);
Deplacement Deplacement::SimpleBD = Deplacement(1, 1, 1);
Deplacement Deplacement::SimpleB = Deplacement(0, 1, 1);
Deplacement Deplacement::SimpleBG = Deplacement(-1, 1, 1);
Deplacement Deplacement::SimpleG = Deplacement(-1, 0, 1);
Deplacement Deplacement::SimpleHG = Deplacement(-1, -1, 1);
Deplacement Deplacement::RoqueG = Deplacement(-2, 0, _BLANC, 1, true, false, false, true);
Deplacement Deplacement::RoqueD = Deplacement(2, 0, _NOIR, 1, true, false, false, true);
