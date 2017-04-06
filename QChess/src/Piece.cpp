#include "Piece.h"

Piece::Piece() : m_couleur(_NOIR)
{
    //ctor
}

Piece::Piece(const Couleur c) : m_couleur(c)
{
    //ctor
}

Piece::~Piece()
{
    //dtor
}

Couleur Piece::GetCouleur()
{
    return m_couleur;
}

void Piece::SetCouleur(const Couleur c)
{
    m_couleur = c;
}

char Piece::GetChar()
{
    return '?';
}

vector<int[2]> Piece::Deplacements()
{
    //
}
