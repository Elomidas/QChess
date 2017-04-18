#include "../include/Cavalier.h"

vector<Deplacement*> Cavalier::m_deplacements = Cavalier::InitDeplacements();

Cavalier::Cavalier()
{
    Init(_NOIR, -1, -1);
}

Cavalier::Cavalier(const Couleur c)
{
    Init(c, -1, -1);
}

Cavalier::Cavalier(const Couleur c, const int ligne, const int colonne)
{
    Init(c, ligne, colonne);
}

Cavalier::~Cavalier()
{
    Vider(m_deplacements);
}

void Cavalier::Init(const Couleur c, const int ligne, const int colonne)
{
    Piece::Init(c, ligne, colonne);
    m_caractere = (c == _BLANC) ? 'C' : 'c';
}

vector<Deplacement*> Cavalier::InitDeplacements()
{
    vector<Deplacement*> vDep;
    Deplacement * dep;
    //Droite
    dep = new Deplacement(2, -1, 1);
    vDep.push_back(dep);
    dep = new Deplacement(2, 1, 1);
    vDep.push_back(dep);
    //Gauche
    dep = new Deplacement(-2, -1, 1);
    vDep.push_back(dep);
    dep = new Deplacement(-2, 1, 1);
    vDep.push_back(dep);
    //Bas
    dep = new Deplacement(-1, 2, 1);
    vDep.push_back(dep);
    dep = new Deplacement(1, 2, 1);
    vDep.push_back(dep);
    //Haut
    dep = new Deplacement(-1, -2, 1);
    vDep.push_back(dep);
    dep = new Deplacement(1, -2, 1);
    vDep.push_back(dep);
    return vDep;
}

