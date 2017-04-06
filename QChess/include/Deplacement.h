#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

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
