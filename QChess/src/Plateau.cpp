#include "../include/Plateau.h"

Plateau::Plateau()
{
    //ctor
}

Plateau::~Plateau()
{
    //dtor
}

void Plateau::InitialiserPieces()
{
    //Blancs
    Tour tBl(_BLANC, 0, 0);
    Fou fBl(_BLANC, 0, 2);
    Roi rBl(_BLANC, 0, 4);
    Cavalier cBl(_BLANC, 0, 6);
    Pion pBl[8];
    for(int i = 0; i < 8; i++)
    {
        int l = (i < 4) ? 1 : 2;
        int c = (2 - l) + (i % 4);
        pBl[i].SetPosition(l, c);
        pBl[i].SetCouleur(_BLANC);
    }
    m_pieces[_BLANC][0] = tBl;
    m_pieces[_BLANC][1] = fBl;
    m_pieces[_BLANC][2] = rBl;
    m_pieces[_BLANC][3] = cBl;
    for(int i = 0; i < 8; i++)
        m_pieces[4 + i] = pBl[i];
}

Piece& Plateau::GetPiece(const Couleur c, const int index)
{
    assert(0 <= index);
    assert(_NB_PIECES > index);
    return m_pieces[c][index];
}

bool Plateau::Bouger(const Couleur couleur, const int index, const int newLigne, const int newColonne)
{
    //
}

string Plateau::ToStr()
{
    string str("");
    char tab[_HAUTEUR_PLATEAU][_LARGEUR_PLATEAU];

    //Initialisation
    for(int i(0); i < _HAUTEUR_PLATEAU; i++)
    {
        for(int j(0); j < _LARGEUR_PLATEAU; j++)
            tab[i][j] = ' ';
    }

    //On ajoute les pieces
    for(int i(0); i < 2; i++)
    {
        for(int j(0); j < _NB_PIECES; j++)
        {
            int x = m_pieces[i][j].GetLigne();
            int y = m_pieces[i][j].GetColonne();
            if((x >= 0)
               && (x < _HAUTEUR_PLATEAU)
               && (y >= 0)
               && (y < _LARGEUR_PLATEAU))
                tab[x][y] = m_pieces[x][y].GetChar();
        }
    }

    //On cree str a partir du tableau de caracteres
    for(int i(0); i < _HAUTEUR_PLATEAU; i++)
    {
        for(int j(0); j < _LARGEUR_PLATEAU; j++)
            str += tab[i][j];
        str += '\n';
    }
    return str;
}
