#include "Plateau.h"

Plateau::Plateau()
{
    //ctor
}

Plateau::~Plateau()
{
    //dtor
}

Piece& Plateau::GetPiece(const int x, const int y)
{
    if((x >= 0)
       && (x < 8)
       && (y >= 0)
       && (y < 8))
        return m_pieces[x][y];
    return NULL;
}

const Piece& Plateau::GetPiece(const int x, const int y)
{
    if((x >= 0)
       && (x < 8)
       && (y >= 0)
       && (y < 8))
        return m_pieces[x][y];
    return NULL;
}

string ToStr()
