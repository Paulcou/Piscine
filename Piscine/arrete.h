#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "sommet.h"
#include "SvgFile.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Arrete
{
    public:

        Arrete(std::string indice, Sommet* dep, Sommet* fin, float p1, float p2);
        void dessinerArrete(SvgFile* svg);
        void dessinerPrime(SvgFile* svg);
        ~Arrete();

    protected:

    private:

        std::vector<std::pair<Arrete*, float>> m_voisins;
        std::string m_indice; // Identifiant

        Sommet *m_dep;
        Sommet *m_fin;

        float m_x1, m_y1, m_x2, m_y2;
        float m_p1, m_p2;

};

#endif // ARRETE_H_INCLUDED
