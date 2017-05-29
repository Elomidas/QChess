#include "../include/Piece.h"

Piece::Piece()
{
    Init(_NOIR, -1, -1);
}

Piece::Piece(const Couleur c)
{
    Init(c, -1, -1);
}

Piece::Piece(const Couleur c, const int ligne, const int colonne)
{
    Init(c, ligne, colonne);
}

Piece::~Piece()
{
    //dtor
}

void Piece::Init(const Couleur c, const int ligne, const int colonne)
{
    SetCouleur(c);
    SetPosition(ligne, colonne);
}

const char Piece::GetChar() const
{
    return m_caractere;
}

const Couleur Piece::GetCouleur() const
{
    return m_couleur;
}

const int Piece::GetLigne() const
{
    return m_ligne;
}

const int Piece::GetColonne() const
{
    return m_colonne;
}

void Piece::SetCouleur(const Couleur c)
{
    m_couleur = c;
}

void Piece::SetLigne(const int ligne)
{
    m_ligne = ligne;
}

void Piece::SetColonne(const int colonne)
{
    m_colonne = colonne;
}

void Piece::SetPosition(const int ligne, const int colonne)
{
    SetLigne(ligne);
    SetColonne(colonne);
}

const bool Piece::Accessible(const int ligne, const int colonne, const std::vector<Deplacement*>& vect)
{
    bool test = false;
    int l = ligne - m_ligne;
    int c = colonne - m_colonne;
    for(unsigned int i(0); (i < vect.size()) && !test; i++)
    {
        Deplacement * d = vect[i];
        if(d != 0)
            test = d->Accessible(l, c);
    }
    return test;
}

const std::vector<int*> Piece::GetDeplacements(const Plateau &p) const
{
    std::cout << "Virtual" << std::endl;
    std::vector<int*> vect;
    return vect;
}





