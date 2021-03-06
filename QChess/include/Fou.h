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
        //Initialisation
        void Init(const Couleur, const int, const int);
        //Autre
        //Retourne le liste des cases atteignables
        const std::vector<int*> GetDeplacements(const Plateau&) const;

    protected:
        static std::vector<const Deplacement*> m_deplacements;
        //Initialisation
        static std::vector<const Deplacement*> InitDeplacements();

    private:
};

#endif // FOU_H
