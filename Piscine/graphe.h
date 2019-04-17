#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"
#include "arrete.h"

class Graphe
{
    public:

        Graphe(std::string, std::string);

        ///PARTIE 1
        void dessinerGrapheChargement(SvgFile* svg);
        void codePrim(std::string);
        void codePrimC2(std::string);
        void afficherPrime(SvgFile* svg);

        std::string rechercheIndice(Sommet*, Sommet*);

        ///PARTIE 2
        void codePareto();
        void dessinerGrapheChargementPareto(SvgFile* svg);
        void dessinCalculGraphePareto();


        ~Graphe();

    protected:

    private:

        std::unordered_map<std::string, Sommet*> m_sommets;
        std::vector<std::pair<std::string, std::pair<std::string, std::string>>> m_aretes;

        ///juste pour dessiner
        std::unordered_map<std::string, Arrete*> m_arretesDessin;
        std::unordered_map<std::string, Arrete*> m_arretesDessinprime1;
        float m_poid1;
        float m_poid2;
        int m_ordre;
        int m_taille;
        std::vector<std::string> m_solPossibles;

};

#endif // GRAPHE_H_INCLUDED
