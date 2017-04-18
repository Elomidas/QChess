#include "Roi.h"

vector<Deplacement*> Roi::m_deplacements = Roi::InitDeplacements();

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
    Vider(m_deplacements);
}

void Roi::Init(const Couleur c, const int ligne, const int colonne)
{
    Piece::Init(c, ligne, colonne);
    m_caractere = (c == _BLANC) ? 'R' : 'r';
}

vector<Deplacement*> Roi::InitDeplacements()
{
    vector<Deplacement*> vDep;
    Deplacement * dep;
    //Droite
    dep = new Deplacement(1, 0, 1);
    vDep.push_back(dep);
    //Gauche
    dep = new Deplacement(-1, 0, 1);
    vDep.push_back(dep);
    //Bas
    dep = new Deplacement(0, 1, 1);
    vDep.push_back(dep);
    //Haut
    dep = new Deplacement(0, -1, 1);
    vDep.push_back(dep);
    //Haut Gauche
    dep = new Deplacement(-1, -1, 1);
    vDep.push_back(dep);
    //Haut Droite
    dep = new Deplacement(1, -1, 1);
    vDep.push_back(dep);
    //Bas Gauche
    dep = new Deplacement(-1, 1, 1);
    vDep.push_back(dep);
    //Bas Droite
    dep = new Deplacement(1, 1, 1);
    vDep.push_back(dep);
    return vDep;
}























