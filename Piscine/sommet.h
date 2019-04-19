#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include "SvgFile.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:

        Sommet(std::string, float, float);
        Sommet(int id2, float, float);
        void ajouterVoisin(Sommet*, float, float);

        void dessinerSommet(SvgFile* svg);
        void dessinerSommetPrime(SvgFile* svg);
        void dessinerSommetChargementPareto(SvgFile* svg);
        void dessinerPareto(SvgFile* svg, int decx, int decy);

        double getX();
        double getY();
        std::string getId();
        int getIdInt();
        std::vector<std::pair<Sommet*, std::pair<float, float>>> getVoisins();


        ~Sommet();

    protected:

    private:

        std::vector<std::pair<Sommet*, std::pair<float, float>>> m_voisins;

        std::string m_id; // Identifiant
        int m_id2;
        float m_x;
        float m_y;

};

#endif // SOMMET_H_INCLUDED
