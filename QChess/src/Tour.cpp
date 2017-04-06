#include "../include/Tour.h"

vector<Deplacement*> Tour::m_deplacements = Tour::InitDeplacements();

Tour::Tour() : Piece()
{
    //ctor
}

Tour::Tour(const Couleur c) : Piece(c)
{
    //ctor
}

Tour::Tour(const Couleur c, const int ligne, const int colonne) : Piece(c, ligne, colonne)
{
    //ctor
}

Tour::~Tour()
{
    Vider(m_deplacements);
}

void Tour::Init(const Couleur c, const int ligne, const int colonne)
{
    Piece::Init(c, ligne, colonne);
    m_caractere = (c == _BLANC) ? 'T' : 't';
}

vector<Deplacement*> Tour::InitDeplacements()
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

