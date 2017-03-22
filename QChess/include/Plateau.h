#ifndef PLATEAU_H
#define PLATEAU_H

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

    protected:
        Piece m_pieces[8][8];

    private:
};

#endif // PLATEAU_H
