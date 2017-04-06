#include "../include/Plateau.h"

Plateau::Plateau()
{
    //ctor
}

Plateau::~Plateau()
{
    for(int i = 0; i < _NB_PIECES; i++)
    {
        if(m_pieces[_BLANC][i] != 0)
            delete m_pieces[_BLANC][i];
        if(m_pieces[_NOIR][i] != 0)
            delete m_pieces[_NOIR][i];
    }
}

void Plateau::InitialiserPieces()
{
    for(int i = 0; i < _NB_PIECES; i++)
    {
        m_pieces[_BLANC][i] = 0;
        m_pieces[_NOIR][i] = 0;
    }

    //Blancs
    Couleur c = _BLANC;
    Tour* pt = new Tour(c, 0, 0);
    Fou* pf = new Fou(c, 0, 2);
    Roi* pr = new Roi(c, 0, 4);
    Cavalier* pc = new Cavalier(c, 0, 6);
    Pion* pp[8];
    for(int i = 0; i < 8; i++)
    {
        int il = (i < 4) ? 1 : 2;
        int ic = (2 - il) + (2 * (i % 4));
        pp[i] = new Pion(c, il, ic);
    }
    m_pieces[c][0] = pt;
    m_pieces[c][1] = pf;
    m_pieces[c][2] = pr;
    m_pieces[c][3] = pc;
    for(int i = 0; i < 8; i++)
        m_pieces[c][4 + i] = pp[i];

    //Noirs
    c = _NOIR;
    pt = new Tour(c, _HAUTEUR_PLATEAU - 1, _LARGEUR_PLATEAU - 1);
    pf = new Fou(c, _HAUTEUR_PLATEAU - 1, _LARGEUR_PLATEAU - 3);
    pr = new Roi(c, _HAUTEUR_PLATEAU - 1, _LARGEUR_PLATEAU - 5);
    pc = new Cavalier(c, _HAUTEUR_PLATEAU - 1, _LARGEUR_PLATEAU - 7);
    for(int i = 0; i < 8; i++)
    {
        int il = _HAUTEUR_PLATEAU - ((i < 4) ? 2 : 3);
        int ic = _LARGEUR_PLATEAU - (((i < 4) ? 2 : 1) + (2 * (i % 4)));
        pp[i] = new Pion(c, il, ic);
    }
    m_pieces[c][0] = pt;
    m_pieces[c][1] = pf;
    m_pieces[c][2] = pr;
    m_pieces[c][3] = pc;
    for(int i = 0; i < 8; i++)
        m_pieces[c][4 + i] = pp[i];
}

Piece* Plateau::GetPiece(const Couleur c, const int index)
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
            if(m_pieces[i][j] != 0)
            {
                int x = m_pieces[i][j]->GetLigne();
                int y = m_pieces[i][j]->GetColonne();
                if((x >= 0)
                   && (x < _HAUTEUR_PLATEAU)
                   && (y >= 0)
                   && (y < _LARGEUR_PLATEAU))
                    tab[x][y] = m_pieces[i][j]->GetChar();
            }
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
