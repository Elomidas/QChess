#include "../include/Pion.h"

vector<Deplacement*> Pion::m_deplacements = Pion::InitDeplacements();

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
    Vider(m_deplacements);
}

void Pion::Init(const Couleur c, const int ligne, const int colonne)
{
    Piece::Init(c, ligne, colonne);
    m_caractere = (c == _BLANC) ? 'P' : 'p';
}

vector<Deplacement*> Pion::InitDeplacements()
{
    vector<Deplacement*> vDep;
    Deplacement * dep;
    //Droite
    dep = new Deplacement(1, 0, -1);
    vDep.push_back(dep);
    //Gauche
    dep = new Deplacement(-1, 0, -1);
    vDep.push_back(dep);
    //Bas
    dep = new Deplacement(0, 1, -1);
    vDep.push_back(dep);
    //Haut
    dep = new Deplacement(0, -1, -1);
    vDep.push_back(dep);
    return vDep;
}

