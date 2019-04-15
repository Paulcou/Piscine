#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include "SvgFile.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:

        Sommet(std::string id, double x, double y);
        void ajouterVoisin(Sommet*, float);
        void dessinerSommet(SvgFile* svg);

        double getX();
        double getY();
        std::string getId();
        ~Sommet();

    protected:

    private:

        std::vector<std::pair<Sommet*, float>> m_voisins;
        std::string m_id; // Identifiant
        double m_x;
        double m_y;

};

#endif // SOMMET_H_INCLUDED
