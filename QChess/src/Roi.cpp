#include "Roi.h"

std::vector<const Deplacement*> Roi::m_deplacements = Roi::InitDeplacements();

Roi::Roi()
{
    Init(_NOIR, -1, -1);
}

Roi::Roi(const Couleur c)
{
    Init(c, -1, -1);
}

Roi::Roi(const Couleur c, const int ligne, const int colonne)
{
    Init(c, ligne, colonne);
}

Roi::~Roi()
{
    //
}

void Roi::Init(const Couleur c, const int ligne, const int colonne)
{
    Piece::Init(c, ligne, colonne);
    m_caractere = (c == _BLANC) ? 'R' : 'r';
    m_roque = true;
}

void Roi::Bouge()
{
    m_roque = false;
}

std::vector<const Deplacement*> Roi::InitDeplacements()
{
    std::vector<const Deplacement*> vDep;
    vDep.push_back(&Deplacement::SimpleB);
    vDep.push_back(&Deplacement::SimpleBG);
    vDep.push_back(&Deplacement::SimpleG);
    vDep.push_back(&Deplacement::SimpleHG);
    vDep.push_back(&Deplacement::SimpleH);
    vDep.push_back(&Deplacement::SimpleHD);
    vDep.push_back(&Deplacement::SimpleD);
    vDep.push_back(&Deplacement::SimpleBD);
    vDep.push_back(&Deplacement::RoqueD);
    vDep.push_back(&Deplacement::RoqueG);
    return vDep;
}

const std::vector<int*> Roi::GetDeplacements(Plateau &p)
{
    std::vector<int*> vect;
    for(unsigned int i = 0; i < m_deplacements.size(); i++)
    {
        std::vector<int*> vTemp = m_deplacements[i]->GetPossibles(m_ligne, m_colonne, p, m_couleur, m_roque);
        for(unsigned int j = 0; j < vTemp.size(); j++)
        {
            vect.push_back(vTemp[j]);
        }
        if(vTemp.size() > 0)
            vTemp.clear();
    }
    return vect;
}























