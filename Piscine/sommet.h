#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include "SvgFile.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:

        Sommet(int, float, float);
        void ajouterVoisin(Sommet*, float, float);

        void dessinerSommet(SvgFile* svg);
        void dessinerSommetPrime(SvgFile* svg);
        void dessinerSommetChargementPareto(SvgFile* svg);

        double getX();
        double getY();
        int getId();
        std::vector<std::pair<Sommet*, std::pair<float, float>>> getVoisins();

        ~Sommet();

    protected:

    private:

        std::vector<std::pair<Sommet*, std::pair<float, float>>> m_voisins;

        int m_id; // Identifiant
        float m_x;
        float m_y;

};

#endif // SOMMET_H_INCLUDED
