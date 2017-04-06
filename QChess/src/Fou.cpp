#include "../include/Fou.h"

vector<Deplacement*> Fou::m_deplacements = Fou::InitDeplacements();

Fou::Fou() : Piece();
{
    //ctor
}

Fou::Fou(const Couleur c) : Piece(c)
{
    //ctor
}

Fou::Fou(const Couleur c, const int ligne, const int colonne) : Piece(c, ligne, colonne)
{
    //ctor
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
