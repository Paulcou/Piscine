#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:

        Sommet(std::string, float, float);
        void ajouterVoisin(Sommet*, float, float);

        double getX();
        double getY();
        std::string getId();

        ~Sommet();

    protected:

    private:

        std::vector<std::pair<Sommet*, std::pair<float, float>>> m_voisins;

        std::string m_id; // Identifiant
        float m_x;
        float m_y;

};

#endif // SOMMET_H_INCLUDED
