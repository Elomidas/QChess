#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "Deplacement.h"

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
        const Couleur GetCouleur() const;
        const char GetChar() const;
        const int GetLigne() const;
        const int GetColonne() const;

        //Mutateurs
        void SetCouleur(const Couleur);
        void SetLigne(const int);
        void SetColonne(const int);
        void SetPosition(const int, const int);

        //Autres
        //Retourne le liste des cases atteignables
        virtual const std::vector<int*> GetDeplacements(const Plateau&) const;
        virtual void Bouge() {};

        //Fonctions statiques
        // Retourne 'true' si la position indiquee est accessible, faux sinon
        static const bool GetDeplacement(const int, const int);

    protected:
        Couleur m_couleur;
        char m_caractere;
        int m_ligne, m_colonne;
        //Vide le tableau de deplacements passe en parametre et libere la memoire
        static void Vider(std::vector<const Deplacement*>&);
        //Regarde si une case est accessible
        const bool Accessible(const int, const int, const std::vector<Deplacement*>&);

    private:
};

#endif // PIECE_H
