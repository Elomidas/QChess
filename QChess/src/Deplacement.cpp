#include "Deplacement.h"

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
