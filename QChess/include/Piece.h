#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "Deplacement.h"

using namespace std;

class Piece
{
    public:
        //Contructeurs
        Piece();
        Piece(const Couleur);
        Piece(const Couleur, const int, const int);

        //Destructeur
        virtual ~Piece();

        //Initialisation
        void Init(const Couleur, const int, const int);

        //Accesseurs
        const Couleur GetCouleur();
        const char GetChar();
        const int GetLigne();
        const int GetColonne();

        //Mutateurs
        void SetCouleur(const Couleur);
        void SetLigne(const int);
        void SetColonne(const int);
        void SetPosition(const int, const int);

        //Fonctions statiques
        // Retourne 'true' si la position indiquee est accessible, faux sinon
        static const bool GetDeplacement(const int, const int);
        //Indique si la piece a besoin d'une ligne de vue pour se deplacer ('false' indique que la piece peut "sauter" au-dessus des autres)
        static const bool GetLigneVue();

    protected:
        Couleur m_couleur;
        char m_caractere;
        int m_ligne, m_colonne;
        //Vide le tableau de deplacements passe en parametre et libere la memoire
        static void Vider(vector<Deplacement*>&);
        //Regarde si une case est accessible
        const bool Accessible(const int, const int, const vector<Deplacement*>&);

    private:
};

#endif // PIECE_H
