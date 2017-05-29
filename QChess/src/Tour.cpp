#include "../include/Tour.h"

std::vector<const Deplacement*> Tour::m_deplacements = Tour::InitDeplacements();

Tour::Tour()
{
    Init(_NOIR, -1, -1);
}

Tour::Tour(const Couleur c)
{
    Init(c, -1, -1);
}

Tour::Tour(const Couleur c, const int ligne, const int colonne)
{
    Init(c, ligne, colonne);
}

Tour::~Tour()
{
    //
}

void Tour::Init(const Couleur c, const int ligne, const int colonne)
{
    Piece::Init(c, ligne, colonne);
    m_caractere = (c == _BLANC) ? 'T' : 't';
}

std::vector<const Deplacement*> Tour::InitDeplacements()
{
    std::vector<const Deplacement*> vDep;
    vDep.push_back(&Deplacement::LigneB);
    vDep.push_back(&Deplacement::LigneG);
    vDep.push_back(&Deplacement::LigneH);
    vDep.push_back(&Deplacement::LigneD);
    return vDep;
}

const std::vector<int*> Tour::GetDeplacements(const Plateau &p) const
{
    std::vector<int*> vect;
    for(unsigned int i = 0; i < m_deplacements.size(); i++)
    {
        std::vector<int*> vTemp = m_deplacements[i]->GetPossibles(m_ligne, m_colonne, p, m_couleur);
        for(unsigned int j = 0; j < vTemp.size(); j++)
            vect.push_back(vTemp[j]);
        if(vTemp.size() > 0)
            vTemp.clear();
    }
    return vect;
}

