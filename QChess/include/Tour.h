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
        //Autres
        const std::vector<int*> GetDeplacements(const Plateau&) const;

    protected:
        static std::vector<const Deplacement*> m_deplacements;
        //Initialisation
        static std::vector<const Deplacement*> InitDeplacements();

    private:
};

#endif // TOUR_H
