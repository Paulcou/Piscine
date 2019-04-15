#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "sommet.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Arrete
{
    public:

        Arrete(Sommet dep, Sommet fin);
        void dessinerArrete(SvgFile* svg);
        ~Arrete();

    protected:

    private:

        std::vector<std::pair<Arrete*, float>> m_voisins;
        std::string m_id; // Identifiant

        Sommet m_dep;
        Sommet m_fin;

        std::string m_iddep;
        std::string m_idfin;

        double m_x1;
        double m_y1;
        double m_x2;
        double m_y2;

};

#endif // ARRETE_H_INCLUDED
