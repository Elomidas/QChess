#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "Piece.h"
#include "Plateau.h"

#define _NB_PIECES  12
#define    _PROF    5

class AlphaBeta
{
    public:
        AlphaBeta();
        AlphaBeta(Plateau &plateau, Couleur couleur);
        virtual ~AlphaBeta();

        Plateau Getplateau() { return m_plateau; }
        void Setplateau(Plateau val) { m_plateau = val; }

        Couleur Getcouleur() { return m_couleur; }
        void Setcouleur(Couleur couleur) { std::cout << "Couleur changee : " << couleur; m_couleur = couleur; }

        int Eval(Plateau * plateau, Couleur couleur);

        //Retourne le mouvement à faire
        //contient [2] l'index de la piece, [1] la ligne [2] la colonne
        int* ABMinMax(Plateau plateau);
        int* ABMaxMove(Plateau* plateau, short int prof, int a, int b, int * move_env,Couleur couleur);
        int* ABMinMove(Plateau* plateau, short int prof, int a, int b, int * move_env,Couleur couleur);

        void VerifAssertMove(int* move);
    protected:

    private:
        Plateau m_plateau;
        Couleur m_couleur;
        bool m_gagne;
};

#endif // ALPHABETA_H
