#include "AffichagePlateau.h"

AffichagePlateau::AffichagePlateau()
{
    m_fini = false;
    m_plateau = 0;
    m_pointee = -1;
    m_cliquee = -1;
    m_dep = NULL;
    /*m_gui[_BLANC] = */m_gui[_NOIR] = true;
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
    //Carre bleu
    m_tBleu.loadFromFile("img/case.png");
    m_sBleu.setTexture(m_tBleu);
    m_sBleu.setColor(sf::Color(0, 162, 232, 150));
    //Fond
    m_tPlateau.loadFromFile("img/plateau.jpg");
    m_sPlateau.setTexture(m_tPlateau);



    std::cout << "Init OK" << std::endl << std::endl;
}

AffichagePlateau::~AffichagePlateau()
{
    DelDep();
}

void AffichagePlateau::DelDep()
{
    if(m_dep != NULL)
    {
        for(unsigned int i = 0; i < m_dep->size(); i++)
            delete (*m_dep)[i];
        m_dep = NULL;
    }
}

void AffichagePlateau::SetDep(const std::vector<int*> vect)
{
    DelDep();
    m_dep = new std::vector<int*>();
    for(unsigned int i = 0; i < vect.size(); i++)
        m_dep->push_back(vect[i]);
}

void AffichagePlateau::SetPlateau(Plateau * plateau)
{
    m_plateau = plateau;
    m_fenetre.create(sf::VideoMode(_LARGEUR_FENETRE, _HAUTEUR_FENETRE), _NOM_FENETRE);
}

void AffichagePlateau::SetCouleur(Couleur joueur)
{
    m_joueur = joueur;
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
            Piece *p = m_plateau->GetPiece((Couleur)c, i);
            if(p != 0)
            {
                int h, l;
                sf::Sprite s;
                //Si la souris est sur le pion et que c'est le tour du joueur, on affiche le sprite modifié
                s = GetSprite(p->GetChar(), h, l, (c == m_joueur) && (m_pointee == i));
                int py = p->GetLigne() * _TAILLE_CASE;
                int px = p->GetColonne() * _TAILLE_CASE;
                int dx = (_TAILLE_CASE - h) / 2;
                int dy = (_TAILLE_CASE - l) / 2;
                s.setPosition(py + dy, px + dx);
                m_fenetre.draw(s);
            }
        }
    }
    if((m_cliquee != -1) && (m_dep != NULL))
    {
        //Affichage des cases possibles
        for(unsigned int i = 0; i < m_dep->size(); i++)
        {
            m_sBleu.setPosition((*m_dep)[i][0] * _TAILLE_CASE, (*m_dep)[i][1] * _TAILLE_CASE);
            m_fenetre.draw(m_sBleu);
        }
    }
    m_fenetre.display();
    return true;
}

void AffichagePlateau::Event()
{
    int x = -1, y = -1;
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

                case sf::Event::MouseButtonReleased :
                    //Clic de la souris
                    //On ne traite l'action que si le joueur a la main
                    if(m_gui[m_joueur])
                    {
                        x = posSouris[0] / _TAILLE_CASE;
                        y = posSouris[1] / _TAILLE_CASE;
                        if(DepOK(x, y))
                        {
                            m_plateau->Bouger(m_joueur, m_cliquee, x, y);
                            m_pointee = -1;
                            m_cliquee = -1;
                            DelDep();
                        }
                        else
                        {
                            m_cliquee = m_pointee;
                            if(m_pointee != -1)
                                SetDep(m_plateau->GetPiece(m_joueur, m_pointee)->GetDeplacements(*m_plateau));
                            else DelDep();
                        }
                    }

                    break;

                default :
                    break;
            }
        }
        if(m_plateau->GetAction())
        {
            m_joueur = Couleur(_NOIR - m_joueur);
            m_plateau->Reset();
        }
        GetPiece(posSouris[0], posSouris[1], tailles);
        Rafraichir();
        sf::sleep(sf::milliseconds(20));
    }
}

bool AffichagePlateau::DepOK(const int x, const int y)
{
    if(m_dep == NULL)
        return false;
    for(unsigned int i = 0; i < m_dep->size(); i++)
    {
        if((x == (*m_dep)[i][0]) && (y == (*m_dep)[i][1]))
            return true;
    }
    return false;
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

void AffichagePlateau::GetPiece(const int &x, const int &y, const int tailles[2][5])
{
    m_pointee = -1;
    if(m_gui[m_joueur])
    {
        for(int i(0); i < _NB_PIECES; i++)
        {
            int index = (i < 4) ? i : 4;
            Piece *p = m_plateau->GetPiece((Couleur)m_joueur, i);
            if(p != NULL)
            {
                //Position de la case occuppée par la piece
                int px = m_plateau->GetPiece((Couleur)m_joueur, i)->GetLigne() * _TAILLE_CASE;
                int py = m_plateau->GetPiece((Couleur)m_joueur, i)->GetColonne() * _TAILLE_CASE;
                //Ecarts de position dus à la taille de la piece
                int ex = (_TAILLE_CASE - (tailles[0][index] * _RATIO)) / 2;
                int ey = (_TAILLE_CASE - (tailles[1][index] * _RATIO)) / 2;
                //Calcul des limites de la pièce
                int xmin = px + ex;
                int xmax = px + _TAILLE_CASE - ex;
                int ymin = py + ey;
                int ymax = py + _TAILLE_CASE - ey;
                if((x > xmin)
                   && (x <= xmax)
                   && (y > ymin)
                   && (y <= ymax))
                {
                    if(Contains(m_joueur, i, x - xmin, y - ymin))
                        m_pointee = i;
                    return;
                }
            }
        }
    }
}

bool AffichagePlateau::Contains(const int &couleur, const int &piece, const int &x, const int &y)
{
    int index = (piece < 4) ? piece : 4;
    sf::Rect<int> rect = m_sprites[couleur][0][index].getTextureRect();
    sf::Image im = m_sprites[couleur][0][index].getTexture()->copyToImage();
    int px = (x / _RATIO) + rect.left;
    int py = (y / _RATIO) + rect.top;
    bool b = (im.getPixel(px, py).a != 0);
    return b;
}


