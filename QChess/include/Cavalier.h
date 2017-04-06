#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"


class Cavalier : public Piece
{
    public:
        //Constructeurs
        Cavalier();
        Cavalier(const Couleur);
        Cavalier(const Couleur, const int, const int);
        //Destructeurs
        virtual ~Cavalier();
        //Initialisation
        void Init(const Couleur, const int, const int);

    protected:
        static vector<Deplacement*> m_deplacements;
        //Initialisation
        static vector<Deplacement*> InitDeplacements();
    private:
};

#endif // CAVALIER_H
