#include "../include/Fou.h"

vector<Deplacement*> Fou::m_deplacements = Fou::InitDeplacements();

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

vector<Deplacement*> Fou::InitDeplacements()
{
    vector<Deplacement*> vDep;
    Deplacement * dep;
    //Haut Droite
    dep = new Deplacement(1, -1, -1);
    vDep.push_back(dep);
    //Haut Gauche
    dep = new Deplacement(-1, -1, -1);
    vDep.push_back(dep);
    //Bas Droite
    dep = new Deplacement(1, 1, -1);
    vDep.push_back(dep);
    //Bas Gauche
    dep = new Deplacement(-1, 1, -1);
    vDep.push_back(dep);
    return vDep;
}
