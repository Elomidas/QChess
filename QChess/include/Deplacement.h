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
        Deplacement(const int, const int, const int);
        Deplacement(const int, const int, const Couleur, const int, const bool, const bool, const bool = true, const bool = false);
        //Destructeur
        virtual ~Deplacement();
        //Initialisation
        void Init(const int, const int, const int, const int, const bool, const bool, const bool, const bool);
        //Fonctions de test
        const bool Accessible(const int, const int);
        //Set/Get
        int GetRepetition();
        const int X() {return m_ligne;};
        const int Y() {return m_colonne;};
        const std::vector<int*> GetPossibles(const int, const int, Plateau&, const Couleur, const bool = false) const;
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
                           PionBB,
                           PionB,
                           PionHH,
                           PionH,
                           PionBG,
                           PionBD,
                           PionHG,
                           PionHD,
                           SimpleH,
                           SimpleHD,
                           SimpleD,
                           SimpleBD,
                           SimpleB,
                           SimpleBG,
                           SimpleG,
                           SimpleHG,
                           RoqueG,
                           RoqueD;

    protected:
        //Deplacement sur les ligne et colonnes
        int m_ligne, m_colonne;
        //Nombre d'executions simultanees disponnibles (-1 = infini)
        int m_repetition;
        //Disponnibilite du deplacement selon la couleur
        bool m_couleur[2];
        //Disponnibilité selon la case visée
        bool m_libre, m_occupee, m_limitee, m_ligneVue;

    private:
};

#endif // DEPLACEMENT_H
