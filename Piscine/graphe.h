#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"
#include "arrete.h"
#include <queue>
#include <limits>

auto comp = [] (const std::pair<int,float> &a, const std::pair<int,float> &b)
{
    return a.second > b.second;
};

class Graphe
{
    public:

        Graphe(std::string, std::string);

        ///PARTIE 1
        void dessinerGrapheChargement(SvgFile* svg);
        void codePrim(int);
        void codePrimC2(int);
        void afficherPrime(SvgFile* svg);

        int rechercheIndice(Sommet*, Sommet*);
        std::vector<std::pair<std::vector<int>, std::pair<float, float>>> rechercheOpti(std::vector<std::pair<float, float>>);

        ///PARTIE 2
        void codePareto(SvgFile* svg);
        int rechercheCC(std::vector<int> suit);
        void dessinerGrapheChargementPareto(SvgFile* svg);
        void dessinCalculGraphePareto(SvgFile* svg);
        int snoob(int x);

        ///PARTIE 3
        void compteurDjikstra();
        void codeDjikstra(std::vector<int>);
        void dessinerGrapheChargementDjikstra(SvgFile* svg);

        ///PARTIE BONUS
        void dessinerGrapheChargementBonus(SvgFile* svg);
        void dessinCalculGrapheBonus(SvgFile* svg);
        std::vector<std::pair<std::vector<int>, std::pair<float,std::pair<float, float>>>> rechercheOptiBonus(std::vector<std::pair<float, std::pair<float, float>>> couts);
        int rechercheCCBonus(std::vector<int> suit);
        void codeBonus(SvgFile* svg);

        void dessinCalculHeuristique(SvgFile* svg);

        ~Graphe();

    protected:

    private:

        std::unordered_map<int, Sommet*> m_sommets;
        std::vector<std::pair<int, std::pair<int, int>>> m_aretes;

        ///juste pour dessiner
        std::vector<Arrete*> m_arretesDessin;
        std::unordered_map<int, Arrete*> m_arretesDessinprime1;
        float m_poid1;
        float m_poid2;
        int m_ordre;
        int m_taille;
        std::vector<std::vector<int>> m_solPossibles;
        std::pair<float, float> m_resultPrim1;
        std::pair<float, float> m_resultPrim2;
        std::vector<std::pair<float, float>> m_couts;

        ///PARTIE 3
        std::vector<Sommet*> m_sommmetsDijs;
        std::vector<std::pair<float, float>> m_poidsDji;

        ///PARTIE BONUS
        std::vector<Arrete*> m_arretesDessinBonus;
        std::vector<std::pair<float,std::pair<float, float>>> m_coutsB;

};

#endif // GRAPHE_H_INCLUDED
