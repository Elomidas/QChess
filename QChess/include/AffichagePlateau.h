#ifndef AFFICHAGEPLATEAU_H
#define AFFICHAGEPLATEAU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Plateau.h"

//Taille d'une case du plateau
#define _TAILLE_CASE    80

//Ratio entre la taille des sprite et celle des textures
#define _RATIO  0.6

//Dimensions de la fenêtre de jeu
#define _LARGEUR_FENETRE    8 * _TAILLE_CASE
#define _HAUTEUR_FENETRE    8 * _TAILLE_CASE

//Nom de la fenêtre de jeu
#define _NOM_FENETRE    "QChess"

//Offset de couleur
#define _OffNoir   156
#define _OffBlanc  357

//Taille des pièces
//Roi
#define _RH 119
#define _RL 112
//Tour
#define _TH 106
#define _TL 93
//Fou
#define _FH 127
#define _FL 119
//Cavalier
#define _CH 107
#define _CL 111
//Pion
#define _PH 107
#define _PL 80

//Position des pièces
//Roi
#define _RX 2
#define _RY 0
//Tour
#define _TX 15
#define _TY 484
//Fou
#define _FX 0
#define _FY 706
//Cavalier
#define _CX 14
#define _CY 947
//Pion
#define _PX 14
#define _PY 1199

class AffichagePlateau
{
    public:
        bool m_fini;
        //Constructeur
        AffichagePlateau();
        //Destructeur
        virtual ~AffichagePlateau();
        //Accesseurs
        //Mutateurs
        void SetPlateau(Plateau*);
        //Autres fonctions
        bool Rafraichir();
        bool Rafraichir(const sf::Vector2i&);
        void Event();


    protected:
        enum{_opaque, _semi_transparent};
        enum{_roi, _tour, _fou, _cavalier, _pion};
        //Retourne la texture d'une piece
        sf::Sprite& GetSprite(const char, int&, int&, const bool);
        bool Contains(const int&, const int&, const int&, const int&);
        sf::Vector2i GetPiece(const int&, const int &, const int[2][5]);
        //Fenêtre
        sf::RenderWindow m_fenetre;
        //Elements graphiques
        sf::Texture m_textures[2][5];
        sf::Texture m_texPieces;
        sf::Sprite m_sprites[2][2][5];
        sf::Texture m_tPlateau;
        sf::Sprite m_sPlateau;
        //Plateau de référence
        Plateau * m_plateau;

    private:
};

#endif // AFFICHAGEPLATEAU_H
