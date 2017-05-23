#ifndef IA_H
#define IA_H
#include "Plateau.h"

class IA
{
    public:
        IA(Plateau plateau);
        virtual ~IA();

        Plateau Getplateau() { return m_plateau; }
        void Setplateau(Plateau val) { m_plateau = val; }



    protected:

    private:
        Plateau m_plateau;

};

#endif // IA_H
