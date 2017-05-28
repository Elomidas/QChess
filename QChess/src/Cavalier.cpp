#include "../include/Cavalier.h"

std::vector<const Deplacement*> Cavalier::m_deplacements = Cavalier::InitDeplacements();

Cavalier::Cavalier()
{
    Init(_NOIR, -1, -1);
}

Cavalier::Cavalier(const Couleur c)
{
    Init(c, -1, -1);
}

Cavalier::Cavalier(const Couleur c, const int colonne, const int ligne)
{
    Init(c, colonne, ligne);
}

Cavalier::~Cavalier()
{
    //
}

void Cavalier::Init(const Couleur c, const int colonne, const int ligne)
{
    Piece::Init(c, colonne, ligne);
    m_caractere = (c == _BLANC) ? 'C' : 'c';
}

std::vector<const Deplacement*> Cavalier::InitDeplacements()
{
    std::vector<const Deplacement*> vDep;
    vDep.push_back(&Deplacement::CavalierBBD);
    vDep.push_back(&Deplacement::CavalierBBG);
    vDep.push_back(&Deplacement::CavalierHHD);
    vDep.push_back(&Deplacement::CavalierHHG);
    vDep.push_back(&Deplacement::CavalierGGB);
    vDep.push_back(&Deplacement::CavalierGGH);
    vDep.push_back(&Deplacement::CavalierDDB);
    vDep.push_back(&Deplacement::CavalierDDH);
    return vDep;
}

const std::vector<int*> Cavalier::GetDeplacements(Plateau &p)
{
    std::vector<int*> vect;
    for(unsigned int i = 0; i < m_deplacements.size(); i++)
    {
        std::vector<int*> vTemp = m_deplacements[i]->GetPossibles(m_ligne, m_colonne, p, m_couleur);
        for(unsigned int j = 0; j < vTemp.size(); j++)
        {
            vect.push_back(vTemp[j]);
        }
        if(vTemp.size() > 0)
            vTemp.clear();
    }
    return vect;
}
