#include "Deplacement.h"
#include "Plateau.h"

Deplacement::Deplacement()
{
    Init(0, 0, -1, 1);
}

Deplacement::Deplacement(const int ligne, const int colonne)
{
    Init(ligne, colonne, -1, 1);
}

Deplacement::Deplacement(const int ligne, const int colonne, const Couleur couleur)
{
    Init(ligne, colonne, couleur, 1);
}

Deplacement::Deplacement(const int ligne, const int colonne, const int repetition)
{
    Init(ligne, colonne, -1, repetition);
}

Deplacement::Deplacement(const int ligne, const int colonne, const Couleur couleur, const int repetition)
{
    Init(ligne, colonne, couleur, repetition);
}

Deplacement::~Deplacement()
{
    //dtor
}

void Deplacement::Init(const int ligne, const int colonne, const int couleur, const int repetition)
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
const std::vector<int*> Deplacement::GetPossibles(const int px, const int py, Plateau &p, const Couleur couleur) const
{
    std::vector<int*> vect;
    if(m_couleur[couleur])
    {
        bool continuer = true;
        int ite = 0;
        while(continuer)
        {
            ite++;
            if(ite > m_repetition)
                continuer = false;
            else
            {
                int y = (ite * px) + m_colonne;
                int x = (ite * py) + m_ligne;
                int tab[2] = {x, y};
                if((x >= 8)
                   || (x < 0)
                   || (y >= 8)
                   || (y < 0))
                    continuer = false;
                else
                {
                    if(p.Libre(x, y))
                        vect.push_back(tab);
                    else
                    {
                        Piece *pt = p.GetPiece(x, y);
                        if((pt != NULL) && (pt->GetCouleur() != couleur))
                            vect.push_back(tab);
                        continuer = false;
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
Deplacement Deplacement::PionB = Deplacement(0, -1, _BLANC, 2);
Deplacement Deplacement::PionH = Deplacement(0, 1, _NOIR, 2);
Deplacement Deplacement::SimpleH = Deplacement(0, -1, 1);
Deplacement Deplacement::SimpleHD = Deplacement(1, -1, 1);
Deplacement Deplacement::SimpleD = Deplacement(1, 0, 1);
Deplacement Deplacement::SimpleBD = Deplacement(1, 1, 1);
Deplacement Deplacement::SimpleB = Deplacement(0, 1, 1);
Deplacement Deplacement::SimpleBG = Deplacement(-1, 1, 1);
Deplacement Deplacement::SimpleG = Deplacement(-1, 0, 1);
Deplacement Deplacement::SimpleHG = Deplacement(-1, -1, 1);
