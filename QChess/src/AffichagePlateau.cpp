#include "AffichagePlateau.h"
#include <iostream>

AffichagePlateau::AffichagePlateau()
{
    m_fini = false;
    m_plateau = 0;
    for(int c(_BLANC); c <= _NOIR; c++)
    {
        int offset = (c == _BLANC) ? _OffBlanc : _OffNoir;
        int offsets[2][5] = {{_RX, _TX, _FX, _CX, _PX}, {_RY, _TY, _FY, _CY, _PY}};
        int tailles[2][5] = {{_RL, _TL, _FL, _CL, _PL}, {_RH, _TH, _FH, _CH, _PH}};
        //Chargement des textures
        m_texPieces.loadFromFile("img/pieces.png");
        for(int j(0); j < 5; j++)
        {
            //Sprite Opaque
            m_sprites[c][_opaque][j].setTexture(m_texPieces);
            m_sprites[c][_opaque][j].setTextureRect(sf::Rect<int>(offsets[1][j], offset + offsets[0][j], tailles[0][j], tailles[1][j]));
            m_sprites[c][_opaque][j].scale(_RATIO, _RATIO);

            //Sprite semi transparent
            m_sprites[c][_semi_transparent][j].setTexture(m_texPieces);
            m_sprites[c][_semi_transparent][j].setTextureRect(sf::Rect<int>(offsets[0][j], offset + offsets[1][j], tailles[0][j], tailles[1][j]));
            m_sprites[c][_semi_transparent][j].scale(_RATIO, _RATIO);
            int modif = (c == _BLANC) ? 0 : 255;
            m_sprites[c][_semi_transparent][j].setColor(sf::Color(modif, modif, modif, 192));
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
    sf::Vector2i pos(-1, -1);
    return Rafraichir(pos);
}

bool AffichagePlateau::Rafraichir(const sf::Vector2i &pos)
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
            Piece *p = m_plateau->GetPiece((Couleur)c, i);
            if(p != 0)
            {
                int h, l;
                sf::Sprite s;
                s = GetSprite(p->GetChar(), h, l, (c == pos.x) && (i == pos.y));
                int px = p->GetLigne() * _TAILLE_CASE;
                int py = p->GetColonne() * _TAILLE_CASE;
                int dx = (_TAILLE_CASE - h) / 2;
                int dy = (_TAILLE_CASE - l) / 2;
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
    int posSouris[2] = {0, 0};
    int offsets[2][5] = {{_RX, _TX, _FX, _CX, _PX}, {_RY, _TY, _FY, _CY, _PY}};
    int tailles[2][5] = {{_RL, _TL, _FL, _CL, _PL}, {_RH, _TH, _FH, _CH, _PH}};
    while (m_fenetre.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (m_fenetre.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed :
                    // évènement "fermeture demandée" : on ferme la fenêtre
                    m_fini = true;
                    m_fenetre.close();
                    break;

                case sf::Event::MouseMoved :
                    posSouris[0] = sf::Mouse::getPosition().x;
                    posSouris[1] = sf::Mouse::getPosition().y;
                    break;

                default :
                    break;
            }
        }
        sf::Vector2i pos = GetPiece(posSouris[0], posSouris[1], tailles);
        std::cout << pos.x << ", " << pos.y << std::endl;
        Rafraichir(pos);
        sf::sleep(sf::milliseconds(20));
    }
}

sf::Sprite& AffichagePlateau::GetSprite(const char c, int &h, int &l, const bool transparent)
{
    switch(c)
    {
        case 'R':
            h = _RATIO * _RH;
            l = _RATIO * _RL;
            return m_sprites[_BLANC][transparent][0];
        case 'r':
            h = _RATIO * _RH;
            l = _RATIO * _RL;
            return m_sprites[_NOIR][transparent][0];
        case 'T':
            h = _RATIO * _TH;
            l = _RATIO * _TL;
            return m_sprites[_BLANC][transparent][1];
        case 't':
            h = _RATIO * _TH;
            l = _RATIO * _TL;
            return m_sprites[_NOIR][transparent][1];
        case 'F':
            h = _RATIO * _FH;
            l = _RATIO * _FL;
            return m_sprites[_BLANC][transparent][2];
        case 'f':
            h = _RATIO * _FH;
            l = _RATIO * _FL;
            return m_sprites[_NOIR][transparent][2];
        case 'C':
            h = _RATIO * _CH;
            l = _RATIO * _CL;
            return m_sprites[_BLANC][transparent][3];
        case 'c':
            h = _RATIO * _CH;
            l = _RATIO * _CL;
            return m_sprites[_NOIR][transparent][3];
        case 'P':
            h = _RATIO * _PH;
            l = _RATIO * _PL;
            return m_sprites[_BLANC][transparent][4];
        default:
            h = _RATIO * _PH;
            l = _RATIO * _PL;
            return m_sprites[_NOIR][transparent][4];
    }
}

sf::Vector2i AffichagePlateau::GetPiece(const int &x, const int &y, const int tailles[2][5])
{
    sf::Vector2i pos(-1, -1);
    for(int c(_BLANC); c <= _NOIR; c++)
    {
        for(int i(0); i < _NB_PIECES; i++)
        {
            //Position de la case occuppée par la piece
            int px = m_plateau->GetPiece((Couleur)c, i)->GetColonne() * _TAILLE_CASE;
            int py = m_plateau->GetPiece((Couleur)c, i)->GetLigne() * _TAILLE_CASE;
            //Ecarts de position dus à la taille de la piece
            int ex = (_TAILLE_CASE - (tailles[1][i] * _RATIO)) / 2;
            int ey = (_TAILLE_CASE - (tailles[0][i] * _RATIO)) / 2;
            if((x >= (px + ex))
               && (y >= (py + ey))
               && (x < (px + _TAILLE_CASE - ex))
               && (y < (py + _TAILLE_CASE - ey)))
            {
                std::cout << "Enter " << std::endl;
                if(Contains(c, i, y - (py + ey), x - (px + ex)))
                {
                    pos.x = c;
                    pos.y = i;
                }
                return pos;
            }
        }
    }
    return pos;
}

bool AffichagePlateau::Contains(const int &couleur, const int &piece, const int &x, const int &y)
{
    sf::Image im = m_sprites[couleur][0][piece].getTexture()->copyToImage();
    int px = x / _RATIO;
    int py = y / _RATIO;
    return (im.getPixel(px, py).a != 0);
}
