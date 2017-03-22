#ifndef PIECE_H
#define PIECE_H

enum Couleur{_BLANC, _NOIR};

class Piece
{
    public:
        Piece();
        Piece(Couleur);
        virtual ~Piece();
        Couleur GetCouleur();
        void SetCouleur(Couleur c);

    protected:
        Couleur m_couleur;

    private:
};

#endif // PIECE_H
