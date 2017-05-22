#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include <vector>
#include <iostream>

struct Plateau;

enum Couleur{_BLANC, _NOIR};

class Deplacement
{
    public:
        //Constructeurs
        Deplacement();
        Deplacement(const int, const int);
        Deplacement(const int, const int, const Couleur);
        Deplacement(const int, const int, const int);
        Deplacement(const int, const int, const Couleur, const int);
        //Destructeur
        virtual ~Deplacement();
        //Initialisation
        void Init(const int, const int, const int, const int);
        //Fonctions de test
        const bool Accessible(const int, const int);
        //Set/Get
        int GetRepetition();
        const int X() {return m_ligne;};
        const int Y() {return m_colonne;};
        const std::vector<int*> GetPossibles(const int, const int, Plateau&, const Couleur) const;
        //Déplacements
        static Deplacement LigneH,
                           LigneB,
                           LigneG,
                           LigneD,
                           DiagoHD,
                           DiagoBD,
                           DiagoBG,
                           DiagoHG,
                           CavalierHHG,
                           CavalierHHD,
                           CavalierBBG,
                           CavalierBBD,
                           CavalierGGH,
                           CavalierGGB,
                           CavalierDDH,
                           CavalierDDB,
                           PionB,
                           PionH,
                           SimpleH,
                           SimpleHD,
                           SimpleD,
                           SimpleBD,
                           SimpleB,
                           SimpleBG,
                           SimpleG,
                           SimpleHG;

    protected:
        //Deplacement sur les ligne et colonnes
        int m_ligne, m_colonne;
        //Nombre d'executions simultanees disponnibles (-1 = infini)
        int m_repetition;
        //Disponnibilite du deplacement selon la couleur
        bool m_couleur[2];

    private:
};

#endif // DEPLACEMENT_H
