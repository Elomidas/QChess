#ifndef PLATEAU_H
#define PLATEAU_H

#include <string>

#include "Roi.h"
#include "Reine.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Pion.h"

class Plateau
{
    public:
        Plateau();
        virtual ~Plateau();
        Piece& GetPiece(const int x, const int y);
        const Piece& GetPiece(const int x, const int y);
        string ToStr();
        bool Bouger(const int dx, const int dy, const int ax, const int ay);

    protected:
        Piece m_pieces[8][8];

    private:
};

#endif // PLATEAU_H
