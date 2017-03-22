#ifndef PIECE_H
#define PIECE_H

#include <vector>

enum Couleur{_BLANC, _NOIR};

class Piece
{
    public:
        Piece();
        Piece(const Couleur);
        virtual ~Piece();
        Couleur GetCouleur();
        void SetCouleur(const Couleur c);
        char GetChar();
        vector<int[2]> Deplacements();

    protected:
        Couleur m_couleur;

    private:
};

#endif // PIECE_H
