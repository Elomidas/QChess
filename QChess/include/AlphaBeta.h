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
        AlphaBeta(const Couleur couleur);
        virtual ~AlphaBeta();

        Couleur Getcouleur() { return m_couleur; }
        void Setcouleur(Couleur couleur) { std::cout << "Couleur changee : " << couleur; m_couleur = couleur; }

        double Eval(const Plateau &plateau);

        //Retourne le mouvement à faire
        //contient [2] l'index de la piece, [1] la ligne [2] la colonne
        void ABMinMax(const Plateau&, int tab[3]);
        /*
        int* ABMaxMove(Plateau* plateau, short int prof, int a, int b, int * move_env,int &index_move,Couleur couleur);
        int* ABMinMove(Plateau* plateau, short int prof, int a, int b, int * move_env,int &index_move,Couleur couleur);
        */


        double AlphaBetaMax(const Plateau&, double, double, const int, const Couleur);
        double AlphaBetaMin(const Plateau&, double, double, const int, const Couleur);
        void AlphaBetaBigMax(const Plateau&, double, double, const int, const Couleur, int tab[3]);
        void VerifAssertMove(const int*);
        int NombreMovePossible(const Plateau&, const Couleur, int&);
        void NettoieVecteur(std::vector<int*> &v);

    protected:

    private:
        Couleur m_couleur;
};

#endif // ALPHABETA_H

