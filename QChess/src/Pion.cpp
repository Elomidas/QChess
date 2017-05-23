#include "../include/Pion.h"

std::vector<const Deplacement*> Pion::m_deplacements = Pion::InitDeplacements();

Pion::Pion()
{
    Init(_NOIR, -1, -1);
}

Pion::Pion(const Couleur c)
{
    Init(c, -1, -1);
}

Pion::Pion(const Couleur c, const int ligne, const int colonne)
{
    Init(c, ligne, colonne);
}

Pion::~Pion()
{
    //
}

void Pion::Init(const Couleur c, const int ligne, const int colonne)
{
    Piece::Init(c, ligne, colonne);
    m_caractere = (c == _BLANC) ? 'P' : 'p';
}

std::vector<const Deplacement*> Pion::InitDeplacements()
{
    std::vector<const Deplacement*> vDep;
    vDep.push_back(&Deplacement::PionB);
    vDep.push_back(&Deplacement::PionH);
    return vDep;
}

const std::vector<int*> Pion::GetDeplacements(Plateau &p)
{
    std::vector<int*> vect;
    for(unsigned int i = 0; i < m_deplacements.size(); i++)
    {
        std::vector<int*> vTemp = m_deplacements[i]->GetPossibles(m_colonne, m_ligne, p, m_couleur);
        for(unsigned int j = 0; j < vTemp.size(); j++)
        {
            vect.push_back(vTemp[i]);
        }
        if(vTemp.size() > 0)
            vTemp.clear();
    }
    return vect;
}

