#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"

class Graphe
{
    public:

        Graphe(std::string);
        ~Graphe();

    protected:

    private:

        std::unordered_map<std::string,Sommet*> m_sommets;

};

#endif // GRAPHE_H_INCLUDED
