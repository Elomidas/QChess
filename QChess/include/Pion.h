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
        //Autres
        const std::vector<int*> GetDeplacements(Plateau&);
        void Bouge();

    protected:
        static std::vector<const Deplacement*> m_deplacements;
        //Initialisation
        static std::vector<const Deplacement*> InitDeplacements();
        bool m_first;

    private:
};

#endif // PION_H
