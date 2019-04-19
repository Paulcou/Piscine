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
        std::vector<std::pair<std::vector<int>, std::pair<float, float>>> rechercheOpti(std::vector<std::pair<float, float>>);

        ///PARTIE 2
        void codePareto(SvgFile* svg);
        int rechercheCC(std::vector<int> suit);
        void dessinerGrapheChargementPareto(SvgFile* svg);
        void dessinCalculGraphePareto(SvgFile* svg);

        ///PARTIE 3
        void codeDjikstra(std::vector<int>);
        void compteurDjikstra();


        ~Graphe();

    protected:

    private:

        std::unordered_map<std::string, Sommet*> m_sommets;
        std::vector<std::pair<std::string, std::pair<std::string, std::string>>> m_aretes;

        ///juste pour dessiner
        std::vector<Arrete*> m_arretesDessin;
        std::unordered_map<std::string, Arrete*> m_arretesDessinprime1;
        float m_poid1;
        float m_poid2;
        int m_ordre;
        int m_taille;
        std::vector<std::vector<int>> m_solPossibles;
        std::pair<float, float> m_resultPrim1;
        std::pair<float, float> m_resultPrim2;
        std::vector<std::pair<float, float>> m_couts;

};

#endif // GRAPHE_H_INCLUDED
