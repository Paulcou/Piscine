#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:

        Sommet(std::string);
        void ajouterVoisin(Sommet*, float);
        ~Sommet();

    protected:

    private:

        std::vector<std::pair<Sommet*, float>> m_voisins;

        std::string m_id; // Identifiant

};

#endif // SOMMET_H_INCLUDED
