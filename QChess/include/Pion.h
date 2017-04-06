#ifndef PION_H
#define PION_H

#include "Piece.h"


class Pion : public Piece
{
    public:
        //Constructeurs
        Pion();
        Pion(const Couleur);
        Pion(const Couleur, const int, const int);
        //Destructeurs
        virtual ~Pion();
        //Initialisation
        void Init(const Couleur, const int, const int);

    protected:
        static vector<Deplacement*> m_deplacements;
        //Initialisation
        static vector<Deplacement*> InitDeplacements();

    private:
};

#endif // PION_H
