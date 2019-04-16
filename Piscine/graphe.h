#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"
#include "arrete.h"

class Graphe
{
    public:

        Graphe(std::string, std::string);
        void dessinerGrapheChargement(SvgFile* svg);
        void codePrim(std::string ,SvgFile* svg);
        void codePrimC2(std::string, SvgFile *svg);
        std::string rechercheIndice(Sommet*, Sommet*);
        ~Graphe();

    protected:

    private:

        std::unordered_map<std::string, Sommet*> m_sommets;
        std::vector<std::pair<std::string, std::pair<std::string, std::string>>> m_aretes;

        ///juste pour dessiner
        std::unordered_map<std::string, Arrete*> m_arretesDessin;
        int m_ordre;

};

#endif // GRAPHE_H_INCLUDED
