#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include "sommet.h"
#include "SvgFile.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Arrete
{
public:

    Arrete(int indice, Sommet* dep, Sommet* fin, float p1, float p2);
    Arrete(int indice, Sommet* dep, Sommet* fin, float p1, float p2, float p3);
    void dessinerArrete(SvgFile* svg);
    void dessinerPrime(SvgFile* svg);
    void dessinerArreteChargementPareto(SvgFile* svg);
    void dessinerArretePareto(SvgFile* svg, int decx, int decy);

    void dessinerArreteChargementBonus(SvgFile* svg);

    float getP1();
    float getP2();
    float getP3();
    void ajouterPoids(float, float);
    void ajouterPoidsBonus(float, float, float);
    Sommet* getDep();
    Sommet* getFin();
    ~Arrete();

protected:

private:

    std::vector<std::pair<Arrete*, float>> m_voisins;
    int m_indice; // Identifiant

    Sommet *m_dep;
    Sommet *m_fin;

    float m_x1, m_y1, m_x2, m_y2;
    float m_p1, m_p2, m_p3;

};

#endif // ARRETE_H_INCLUDED
