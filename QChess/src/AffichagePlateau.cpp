#include "AffichagePlateau.h"
#include <iostream>
AffichagePlateau::AffichagePlateau()
{
    m_fini = false;
    m_plateau = 0;
    for(int c(_BLANC); c <= _NOIR; c++)
    {
        int offset = (c == _BLANC) ? _OffBlanc : _OffNoir;
        //Chargement des textures
        m_textures[c][0].loadFromFile("img/pieces.png", sf::IntRect(_RY, _RX + offset, _RL, _RH));
        m_textures[c][1].loadFromFile("img/pieces.png", sf::IntRect(_TY, _TX + offset, _TL, _TH));
        m_textures[c][2].loadFromFile("img/pieces.png", sf::IntRect(_FY, _FX + offset, _FL, _FH));
        m_textures[c][3].loadFromFile("img/pieces.png", sf::IntRect(_CY, _CX + offset, _CL, _CH));
        m_textures[c][4].loadFromFile("img/pieces.png", sf::IntRect(_PY, _PX + offset, _PL, _PH));
        for(int j(0); j < 5; j++)
        {
            //Sprite Opaque
            m_sprites[c][_opaque][j].setTexture(m_textures[c][j]);
            m_sprites[c][_opaque][j].scale(0.4, 0.4);

            //Sprite semi transparent
            m_sprites[c][_semi_transparent][j].setTexture(m_textures[c][j]);
            m_sprites[c][_semi_transparent][j].scale(0.6, 0.6);
            m_sprites[c][_semi_transparent][j].setColor(sf::Color(255, 255, 255, 128));
        }
    }
    //Fond
    m_tPlateau.loadFromFile("img/plateau.jpg");
    m_sPlateau.setTexture(m_tPlateau);
}

AffichagePlateau::~AffichagePlateau()
{
    //dtor
}

void AffichagePlateau::SetPlateau(Plateau * plateau)
{
    m_plateau = plateau;
    m_fenetre.create(sf::VideoMode(_LARGEUR_FENETRE, _HAUTEUR_FENETRE), _NOM_FENETRE);
}

bool AffichagePlateau::Rafraichir()
{
    if(m_plateau == 0)
        return false;
    //Affichage
    m_fenetre.clear();
    //Affichage du fond
    m_fenetre.draw(m_sPlateau);
    //Affichage des pièces
    for(int c = _BLANC; c <= _NOIR; c++)
    {
        for(int i = 0; i < _NB_PIECES; i++)
        {
            std::cout << c << ", " << i << std::endl;
            Piece *p = m_plateau->GetPiece((Couleur)c, i);
            if(p != 0)
            {
                int h, l;
                sf::Texture t = GetTexture(p->GetChar(), h, l);
                sf::Sprite s(t);
                s.setScale(0.6, 0.6);
                int px = p->GetLigne() * _TAILLE_CASE;
                int py = p->GetColonne() * _TAILLE_CASE;
                int dx = (_TAILLE_CASE - h) / 2;
                int dy = (_TAILLE_CASE - l) / 2;
                std::cout << p->GetChar() << " : " << px << " + " << dx << ", " << py << " + " << dy << std::endl;
                s.setPosition(py + dy, px + dx);
                m_fenetre.draw(s);
            }
        }
    }
    m_fenetre.display();
    return true;
}

void AffichagePlateau::Event()
{
    while (m_fenetre.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (m_fenetre.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
            {
                m_fini = true;
                m_fenetre.close();
            }
        }
        sf::sleep(sf::milliseconds(20));
        Rafraichir();
    }
}

sf::Texture& AffichagePlateau::GetTexture(const char c, int &h, int &l)
{
    switch(c)
    {
        case 'R':
            h = 0.6 * _RH;
            l = 0.6 * _RL;
            return m_textures[_BLANC][0];
        case 'r':
            h = 0.6 * _RH;
            l = 0.6 * _RL;
            return m_textures[_NOIR][0];
        case 'T':
            h = 0.6 * _TH;
            l = 0.6 * _TL;
            return m_textures[_BLANC][1];
        case 't':
            h = 0.6 * _TH;
            l = 0.6 * _TL;
            return m_textures[_NOIR][1];
        case 'F':
            h = 0.6 * _FH;
            l = 0.6 * _FL;
            return m_textures[_BLANC][2];
        case 'f':
            h = 0.6 * _FH;
            l = 0.6 * _FL;
            return m_textures[_NOIR][2];
        case 'C':
            h = 0.6 * _CH;
            l = 0.6 * _CL;
            return m_textures[_BLANC][3];
        case 'c':
            h = 0.6 * _CH;
            l = 0.6 * _CL;
            return m_textures[_NOIR][3];
        case 'P':
            h = 0.6 * _PH;
            l = 0.6 * _PL;
            return m_textures[_BLANC][4];
        default:
            h = 0.6 * _PH;
            l = 0.6 * _PL;
            return m_textures[_NOIR][4];

    }
}
