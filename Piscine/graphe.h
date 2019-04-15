#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"

class Graphe
{
    public:

        Graphe(std::string, std::string);
        ~Graphe();

    protected:

    private:

        std::unordered_map<std::string,Sommet*> m_sommets;
        std::vector<std::pair<std::string, std::pair<std::string, std::string>>> m_aretes;

};

#endif // GRAPHE_H_INCLUDED
