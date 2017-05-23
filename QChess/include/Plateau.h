#ifndef PLATEAU_H
#define PLATEAU_H

#include <string>
#include <assert.h>

#include "Roi.h"
#include "Fou.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Pion.h"

//Nombre de piece jouee pour chaque joueur
#define _NB_PIECES  12
//Largeur et hauteur du plateau
#define _LARGEUR_PLATEAU    8
#define _HAUTEUR_PLATEAU    8
//Index du roi dans le tableau de pieces
#define _INDEX_ROI  0

class Plateau
{
    public:
        //Constructeur
        Plateau();
        //Destructeur
        virtual ~Plateau();
        //Initialisation
        void InitialiserPieces();
        //Accesseur
        Piece* GetPiece(const Couleur, const int);
        Piece* GetPiece(const int, const int);
        bool Libre(const int, const int) const;
        //Mutateur
        bool Bouger(const Couleur, const int, const int, const int);
        bool Bouger(Piece*, const int, const int);
        //Affichage
        std::string ToStr();

    protected:
        Piece* m_pieces[2][_NB_PIECES];
        void SetPiece(Piece*, Piece*);

    private:
};

#endif // PLATEAU_H
