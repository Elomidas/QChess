#ifndef FOU_H
#define FOU_H

#include "Piece.h"


class Fou : public Piece
{
    public:
        //Constructeurs
        Fou();
        Fou(const Couleur);
        Fou(const Couleur, const int, const int);
        //Destructeur
        virtual ~Fou();
    protected:
        static vector<Deplacement*> m_deplacements;
        //Initialisation
        static vector<Deplacement*> InitDeplacements();

    private:
};

#endif // FOU_H
