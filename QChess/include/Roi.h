#ifndef ROI_H
#define ROI_H

#include "Piece.h"


class Roi : public Piece
{
    public:
        Roi();
        Roi(const Couleur);
        Roi(const Couleur, const int, const int);
        //Destructeurs
        virtual ~Roi();
        //Initialisation
        void Init(const Couleur, const int, const int);
        //Autres
        const std::vector<int*> GetDeplacements(Plateau&);
        void Bouge();

    protected:
        static std::vector<const Deplacement*> m_deplacements;
        //Initialisation
        static std::vector<const Deplacement*> InitDeplacements();
        bool m_roque;

    private:
};

#endif // ROI_H
