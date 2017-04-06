#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"

class Tour : public Piece
{
    public:
        //Constructeurs
        Tour();
        Tour(const Couleur);
        Tour(const Couleur, const int, const int);
        //Destructeurs
        virtual ~Tour();
        //Initialisation
        void Init(const Couleur, const int, const int);

    protected:
        static vector<Deplacement*> m_deplacements;
        //Initialisation
        static vector<Deplacement*> InitDeplacements();

    private:
};

#endif // TOUR_H
