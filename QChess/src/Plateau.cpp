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

bool Plateau::Bouger(const int dx, const int dy, const int ax, const int ay)
{
    if((dx < 0)
       || (dx > 7)
       || (dy < 0)
       || (dy > 7)
       || (m_pieces[dx][dy] == NULL))
        return false;

}

string Plateau::ToStr()
{
    string str("");
    for(int i(0); i < 8; i++)
    {
        for(int j(0); j < 8; j++)
        {
            if(m_pieces[i][j] != NULL)
                str += m_pieces[i][j].GetChar();
            else str += ' ';
        }
        str += '\n';
    }
    return str;
}
