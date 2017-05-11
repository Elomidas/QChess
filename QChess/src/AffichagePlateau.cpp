#include "AffichagePlateau.h"
#include <iostream>

AffichagePlateau::AffichagePlateau()
{
    m_fini = false;
    m_plateau = 0;
    //Chargement des textures
    int offsets[2][5] = {{_RX, _TX, _FX, _CX, _PX}, {_RY, _TY, _FY, _CY, _PY}};
    int tailles[2][5] = {{_RL, _TL, _FL, _CL, _PL}, {_RH, _TH, _FH, _CH, _PH}};
    m_texPieces.loadFromFile("img/tpieces.png");

    for(int c(_BLANC); c <= _NOIR; c++)
    {
        int offset = (c == _BLANC) ? _OffBlanc : _OffNoir;
        for(int j(0); j < 5; j++)
        {
            //Sprite Opaque
            m_sprites[c][_opaque][j].setTexture(m_texPieces);
            m_sprites[c][_opaque][j].setTextureRect(sf::Rect<int>(offsets[1][j], offset + offsets[0][j], tailles[0][j], tailles[1][j]));
            m_sprites[c][_opaque][j].scale(_RATIO, _RATIO);

            //Sprite semi transparent
            m_sprites[c][_semi_transparent][j].setTexture(m_texPieces);
            m_sprites[c][_semi_transparent][j].setTextureRect(sf::Rect<int>(offsets[1][j], offset + offsets[0][j], tailles[0][j], tailles[1][j]));
            m_sprites[c][_semi_transparent][j].scale(_RATIO, _RATIO);
            int modif = (c == _BLANC) ? 200 : 255;
            int alpha = (c == _BLANC) ? 255 : 200;
            m_sprites[c][_semi_transparent][j].setColor(sf::Color(modif, modif, modif, alpha));
        }
    }
    //Fond
    m_tPlateau.loadFromFile("img/plateau.jpg");
    m_sPlateau.setTexture(m_tPlateau);
    std::cout << "OK" << std::endl;
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
                    posSouris[0] = sf::Mouse::getPosition().x - m_fenetre.getPosition().x - 8;
                    posSouris[1] = sf::Mouse::getPosition().y - m_fenetre.getPosition().y - 30;
                    break;

                default :
                    break;
            }
        }
        sf::Vector2i pos = GetPiece(posSouris[0], posSouris[1], tailles);
        //std::cout << "c : " << pos.x << ", i : " << pos.y << std::endl;
        Rafraichir(pos);
        sf::sleep(sf::milliseconds(20));
    }
}

sf::Sprite& AffichagePlateau::GetSprite(const char c, int &h, int &l, const bool transparent)
{
    if(transparent)
        std::cout << c << ", " << transparent << std::endl;
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
    // x -> largeur : tailles[0]
    // y -> hauteur : tailles[1]
    sf::Vector2i pos(-1, -1);
    for(int c(_BLANC); c <= _NOIR; c++)
    {
        for(int i(0); i < _NB_PIECES; i++)
        {
            int index = (i < 4) ? i : 4;
            //Position de la case occuppée par la piece
            int px = m_plateau->GetPiece((Couleur)c, i)->GetColonne() * _TAILLE_CASE;
            int py = m_plateau->GetPiece((Couleur)c, i)->GetLigne() * _TAILLE_CASE;
            //Ecarts de position dus à la taille de la piece
            int ex = (_TAILLE_CASE - (tailles[0][index] * _RATIO)) / 2;
            int ey = (_TAILLE_CASE - (tailles[1][index] * _RATIO)) / 2;
            //Calcul des limites de la pièce
            int xmin = px + ex;
            int xmax = px + _TAILLE_CASE - ex;
            int ymin = py + ey;
            int ymax = py + _TAILLE_CASE - ey;
            /*
            std::cout << "Piece " << i << std::endl
                      << "-> " << xmin << " & " << xmax << std::endl
                      << "-> " << ymin << " & " << ymax << std::endl << std::endl;
            */
            if((x > xmin)
               && (x <= xmax)
               && (y > ymin)
               && (y <= ymax))
            {
                if(Contains(c, i, x - xmin, y - ymin))
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
    std::cout << "Test 1" << std::endl;
    int index = (piece < 4) ? piece : 4;
    sf::Rect<int> rect = m_sprites[couleur][0][index].getTextureRect();
    sf::Image im = m_sprites[couleur][0][index].getTexture()->copyToImage();
    std::cout << "Test 2" << std::endl;
    int px = (x / _RATIO) + rect.left;
    int py = (y / _RATIO) + rect.top;
    std::cout << "Test 3" << std::endl;
    bool b = (im.getPixel(px, py).a != 0);
    std::cout << "Test 4" << std::endl;
    return b;
}

#define _H 1280
/*
bool AffichagePlateau::Test(int i, int j, int *tab)
{
    //1 -> transparent
    //2 -> noir
    //0 -> blanc
    std::cout << i << ", " << j << std::endl;
    if(tab[(j * _H) + i] != 0)
        return;
    if(m_imPieces.getPixel(i, j).a != 0)
    {
        tab[(j * _H) + i] = 2;
        return;
    }
    tab[(j * _H) + i] = 1;
    if(i > 0)
        Test(i-1, j, tab);
    if(i < 1279)
        Test(i+1, j, tab);
    if(j > 0)
        Test(i, j-1, tab);
    if(j < 639)
        Test(i, j+1, tab);
}*/
/*
void AffichagePlateau::Parcours(int* tab)
{
    //1 -> transparent
    //2 -> noir
    //0 -> blanc

    //Parcours de haut en bas, de gauche à droite
    for(int i = 0; i < _H; i++)
    {
        for(int j = 0; j < 640; j++)
        {
            if((i == 0)
               || (i == (_H - 1))
               || (j == 0)
               || (j == (639)))
                tab[i + (_H * j)] = 1;
            else if(m_imPieces.getPixel(i, j).a != 0)
                tab[i + (_H * j)] = 2;
            else if(((tab[(i - 1) + (_H * j)]) == 1)
                    || ((tab[i + (_H * (j - 1))]) == 1))
                tab[i + (_H * j)] = 1;
        }
    }

    //Parcours de bas en haut, de droite à gauche
    for(int i = (_H - 1); i >= 0; i--)
    {
        for(int j = 639; j >= 0; j--)
        {
            if(tab[i + (_H * j)] != 0);
            else if((i == 0)
               || (i == (_H - 1))
               || (j == 0)
               || (j == (639)))
                tab[i + (_H * j)] = 1;
            else if(m_imPieces.getPixel(i, j).a >= 128)
                tab[i + (_H * j)] = 2;
            else if(((tab[(i + 1) + (_H * j)]) == 1)
                    || ((tab[i + (_H * (j + 1))]) == 1))
                tab[i + (_H * j)] = 1;
        }
    }
}

void AffichagePlateau::DelAlpha()
{
    std::cout << "1" << std::endl;
    m_imPieces = m_texPieces.copyToImage();
    int *tab = new int[_H * 640];
    for(int i = 0; i < _H; i++)
    {
        for(int j = 0; j < 640; j++)
            tab[(j * _H) + i] = 0;
    }

    std::cout << "2" << std::endl;

    //Test(0, 0, tab);
    Parcours(tab);

    std::cout << "3" << std::endl;

    sf::Color c;
    for(int i = 0; i < _H; i++)
    {
        for(int j = 0; j < 640; j++)
        {
            if((tab[(j * _H) + i] == 0))
            {
                std::cout << "Modif " << i << ", " << j << std::endl;
                c = m_imPieces.getPixel(i, j);
                int rgb = (c.a <= 128) ? 255 : 0;
                c.r = c.b = c.g = rgb;
                c.a = 255;
                m_imPieces.setPixel(i, j, c);
            }
        }
    }

    delete tab;
    std::cout << "4" << std::endl;

    m_imPieces.saveToFile("img/tpieces.png");
}
*/

sf::Image AffichagePlateau::GetPion()
{
    int r = _TAILLE_CASE / _RATIO;
    sf::Image im;
    im.create(r, r);

    for(int i = 0; i < (_TAILLE_CASE / _RATIO); i++)
    {
        for(int j = 0; j < (_TAILLE_CASE / _RATIO); j++)
        {
            /*
            double d = sqrt(pow(i - (_TAILLE_CASE / (_RATIO * 2.0)), j - (_TAILLE_CASE / (_RATIO * 2.0))));
            if(d <= (_RAYON_PION * _RATIO))
                im.setPixel(i, j, _COULEUR_PION);
            else if(d <= ((_RAYON_PION + _BORDURE_PION) / _RATIO))
                im.setPixel(i, j, _COULEUR_BORDURE);
            else*/
                im.setPixel(i, j, sf::Color::Transparent);
        }
    }
    return im;

}


