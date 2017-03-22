#include "Piece.h"

Piece::Piece() : m_couleur(_NOIR)
{
    //ctor
}

Piece::Piece(Couleur c) : m_couleur(c)
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

void Piece::SetCouleur(Couleur c)
{

}
