#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"
#include "Plateau.h"


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
        //Autres
        //Retourne le liste des cases atteignables
        const std::vector<int*> GetDeplacements(const Plateau&) const;

    protected:
        static std::vector<const Deplacement*> m_deplacements;
        //Initialisation
        static std::vector<const Deplacement*> InitDeplacements();
    private:
};

#endif // CAVALIER_H
