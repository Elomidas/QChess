#ifndef PIECE_H
#define PIECE_H

enum Couleur{_BLANC, _NOIR};

class Piece
{
    public:
        Piece();
        Piece(const Couleur);
        virtual ~Piece();
        Couleur GetCouleur();
        void SetCouleur(const Couleur c);

    protected:
        Couleur m_couleur;

    private:
};

#endif // PIECE_H
