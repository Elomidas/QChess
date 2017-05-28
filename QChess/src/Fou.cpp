#include "../include/Fou.h"

std::vector<const Deplacement*> Fou::m_deplacements = Fou::InitDeplacements();

Fou::Fou()
{
    Init(_NOIR, -1, -1);
}

Fou::Fou(const Couleur c)
{
    Init(c, -1, -1);
}

Fou::Fou(const Couleur c, const int ligne, const int colonne)
{
    Init(c, ligne, colonne);
}

Fou::~Fou()
{
    //dtor
}

void Fou::Init(const Couleur c, const int ligne, const int colonne)
{
    Piece::Init(c, ligne, colonne);
    m_caractere = (c == _BLANC) ? 'F' : 'f';
}

std::vector<const Deplacement*> Fou::InitDeplacements()
{
    std::vector<const Deplacement*> vDep;
    vDep.push_back(&Deplacement::DiagoBD);
    vDep.push_back(&Deplacement::DiagoBG);
    vDep.push_back(&Deplacement::DiagoHD);
    vDep.push_back(&Deplacement::DiagoHG);
    return vDep;
}

const std::vector<int*> Fou::GetDeplacements(Plateau &p)
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
