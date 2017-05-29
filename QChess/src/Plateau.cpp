#include "../include/Plateau.h"

Plateau::Plateau()
{
    InitialiserPieces();
}

Plateau::Plateau(Plateau &p)
{
    m_action = false;
    m_fini = false;
    //Blancs
    Couleur c = _BLANC;
    Piece *piece = p.GetPieceI(c, 1);
    Tour* pt = (piece == NULL) ? NULL : new Tour(c, piece->GetLigne(), piece->GetColonne());
    piece = p.GetPieceI(c, 2);
    Fou* pf = (piece == NULL) ? NULL : new Fou(c, piece->GetLigne(), piece->GetColonne());
    Roi* r = (Roi*)p.GetPieceI(c, 0);
    Roi* pr = (r == NULL) ? NULL : new Roi(c, r->GetLigne(), r->GetColonne());
    if((r != NULL) && (!r->GetRoque()))
        pr->Bouge();
    piece = p.GetPieceI(c, 3);
    Cavalier* pc = (piece == NULL) ? NULL : new Cavalier(c, piece->GetLigne(), piece->GetColonne());
    Pion* pp[8];
    for(int i = 0; i < 8; i++)
    {
        Pion* pi = (Pion*)p.GetPieceI(c, 4+i);
        pp[i] = (pi == NULL) ? NULL : new Pion(c, pi->GetLigne(), pi->GetColonne());
        if((pi != NULL) && (!pi->GetFirst()))
            pp[i]->Bouge();
    }
    m_pieces[c][0] = pr;
    m_pieces[c][1] = pt;
    m_pieces[c][2] = pf;
    m_pieces[c][3] = pc;
    for(int i = 0; i < 8; i++)
        m_pieces[c][4 + i] = pp[i];

    //Noirs
    c = _NOIR;
    piece = p.GetPieceI(c, 1);
    pt = (piece == NULL) ? NULL : new Tour(c, piece->GetLigne(), piece->GetColonne());
    piece = p.GetPieceI(c, 2);
    pf = (piece == NULL) ? NULL : new Fou(c, piece->GetLigne(), piece->GetColonne());
    r = (Roi*)p.GetPieceI(c, 0);
    pr = (r == NULL) ? NULL : new Roi(c, r->GetLigne(), r->GetColonne());
    if((r != NULL) && (!r->GetRoque()))
        pr->Bouge();
    piece = p.GetPieceI(c, 3);
    pc = (piece == NULL) ? NULL : new Cavalier(c, piece->GetLigne(), piece->GetColonne());
    for(int i = 0; i < 8; i++)
    {
        Pion* pi = (Pion*)p.GetPieceI(c, 4+i);
        pp[i] = (pi == NULL) ? NULL : new Pion(c, pi->GetLigne(), pi->GetColonne());
        if((pi != NULL) && (!pi->GetFirst()))
            pp[i]->Bouge();
    }
    m_pieces[c][0] = pr;
    m_pieces[c][1] = pt;
    m_pieces[c][2] = pf;
    m_pieces[c][3] = pc;
    for(int i = 0; i < 8; i++)
        m_pieces[c][4 + i] = pp[i];
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
        m_pieces[_BLANC][i] = NULL;
        m_pieces[_NOIR][i] = NULL;
    }
    m_action = false;
    m_fini = false;

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
    m_pieces[c][0] = pr;
    m_pieces[c][1] = pt;
    m_pieces[c][2] = pf;
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
    m_pieces[c][0] = pr;
    m_pieces[c][1] = pt;
    m_pieces[c][2] = pf;
    m_pieces[c][3] = pc;
    for(int i = 0; i < 8; i++)
        m_pieces[c][4 + i] = pp[i];
}

Piece* Plateau::GetPieceI(const Couleur c, const int index)
{
    if((0 > index) || (_NB_PIECES <= index))
    {
        std::cout << "Index out of range : " << index << std::endl;
        assert(false);
    }
    return m_pieces[c][index];
}

Piece* Plateau::GetPiece(const int ligne, const int colonne)
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < _NB_PIECES; j++)
        {
            if((m_pieces[i][j] != NULL)
                && (m_pieces[i][j]->GetLigne() == ligne)
                && (m_pieces[i][j]->GetColonne() == colonne))
            {
                return m_pieces[i][j];
            }
        }
    }
    return NULL;
}

void Plateau::GetPieces(Piece* tab[2][_NB_PIECES])
{
    for(int i = 0; i < _NB_PIECES; i++)
    {
        tab[0][i] = m_pieces[0][i];
        tab[1][i] = m_pieces[1][i];
    }
}

bool Plateau::Bouger(const Couleur couleur, const int index, const int ligne, const int colonne)
{
    return Bouger(GetPieceI(couleur, index), ligne, colonne);
}

//Bouge une pièce aux coordonnées indiquées
bool Plateau::Bouger(Piece *p, const int ligne, const int colonne)
{
    if(p == NULL)
    {
        std::cout << "Piece NULL" << std::endl;
        return false;
    }
    if((ligne < 0) || (ligne > 7))
    {
        std::cout << "Ligne incorrecte : " << ligne << std::endl;
        return false;
    }
    if((colonne < 0) || (colonne > 7))
    {
        std::cout << "Colonne incorrecte : " << colonne << std::endl;
        return false;
    }
    char c = p->GetChar();
    bool roque[2] = {false, false};
    //Cas du roque d'un roi
    if((c == 'R')
       && (((Roi*)p)->GetRoque())
       && (colonne == 2)
       && (ligne == 0))
            roque[_BLANC] = true;
    else if((c == 'r')
       && (((Roi*)p)->GetRoque())
       && (colonne == 5)
       && (ligne == 7))
            roque[_NOIR] = true;
    Piece *np = GetPiece(ligne, colonne);
    if(np != NULL)
    {
        //Si le roi est pris, c'est la fin de la partie
        //Si la tour est prise, on empêche le roque
        if(np == m_pieces[np->GetCouleur()][0])
            m_fini = true;
        else if(np == m_pieces[np->GetCouleur()][1])
            m_pieces[np->GetCouleur()][0]->Bouge();
        SetPiece(np, NULL);
    }
    p->SetPosition(ligne, colonne);
    p->Bouge();
    //std::cout << "Bouger 5" << std::endl;
    //std::cout << "Couleur : " << p->GetCouleur() << std::endl;
    //Si c'est la tour qui a été bougée, on empêche le roi de roquer
    if((c == 't') || (c == 'T'))
        ((Roi*)(m_pieces[p->GetCouleur()][0]))->Bouge();
    //std::cout << "Bouger 6" << std::endl;
    //Si un roi vient de faire un roque, on déplace la tour
    if(roque[_BLANC])
        Bouger(m_pieces[_BLANC][1], 0, 3);
    else if(roque[_NOIR])
        Bouger(m_pieces[_NOIR][1], 7, 4);
    m_action = true;
    //std::cout << "Bouger 7" << std::endl;
    return true;
}

void Plateau::SetPiece(Piece *oldP, Piece *newP)
{
    bool b = true;
    for(int i = 0; b && (i < 2); i++)
    {
        for(int j = 0; b && (j < _NB_PIECES); j++)
        {
            if(m_pieces[i][j] == oldP)
            {
                delete m_pieces[i][j];
                m_pieces[i][j] = newP;
                b = false;
            }
        }
    }
}

std::string Plateau::ToStr()
{
    std::string str("");
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

//x ligne, y colonne
bool Plateau::Libre(const int ligne, const int colonne) const
{
    if((ligne < 0)
       || (ligne > 7)
       || (colonne < 0)
       || (colonne > 7))
        return false;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < _NB_PIECES; j++)
        {
            Piece* p = m_pieces[i][j];
            if((p != NULL)
               && (p->GetLigne() == ligne)
               && (p->GetColonne() == colonne))
               return false;
        }
    }
    return true;
}




