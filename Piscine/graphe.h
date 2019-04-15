#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"
#include "arrete.h"
#include "SvgFile.h"

class Graphe
{
    public:

        Graphe(std::string);
        void dessiner(SvgFile* svg);

        ~Graphe();

    protected:

    private:

        std::unordered_map<std::string, Sommet*> m_sommets;
        std::unordered_map<std::string, Arrete*> m_arretes;

};

#endif // GRAPHE_H_INCLUDED
