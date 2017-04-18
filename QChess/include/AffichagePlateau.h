#ifndef AFFICHAGEPLATEAU_H
#define AFFICHAGEPLATEAU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Plateau.h"

//Taille d'une case du plateau
#define _TAILLE_CASE    80

//Dimensions de la fenêtre de jeu
#define _LARGEUR_FENETRE    8 * _TAILLE_CASE
#define _HAUTEUR_FENETRE    8 * _TAILLE_CASE

//Nom de la fenêtre de jeu
#define _NOM_FENETRE    "QChess"

//Offset de couleur
#define _OffBlanc   156
#define _OffNoir    357

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
        void Event();


    protected:
        enum{_opaque, _semi_transparent};
        enum{_roi, _tour, _fou, _cavalier, _pion};
        //Retourne la texture d'une piece
        sf::Texture& GetTexture(const char, int&, int&);
        //Fenêtre
        sf::RenderWindow m_fenetre;
        //Elements graphiques
        sf::Texture m_textures[2][5];
        sf::Sprite m_sprites[2][2][5];
        sf::Texture m_tPlateau;
        sf::Sprite m_sPlateau;
        //Plateau de référence
        Plateau * m_plateau;

    private:
};

#endif // AFFICHAGEPLATEAU_H
