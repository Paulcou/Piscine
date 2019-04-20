#include <iostream>
#include "arrete.h"

Arrete::Arrete(int indice, Sommet* dep, Sommet* fin, float p1, float p2)
: m_indice{indice}, m_dep{dep}, m_fin{fin}, m_p1{p1}, m_p2{p2}
{

}

void Arrete::dessinerArrete(SvgFile* svg)
{
 svg->addLine(m_dep->getX(), m_dep->getY(), m_fin->getX(), m_fin->getY());
 svg->addText((m_fin->getX() + m_dep->getX())/2 - 7, (m_fin->getY() + m_dep->getY())/2 - 5, m_indice, "green");
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 10, (m_fin->getY() + m_dep->getY())/2 - 5, m_p1, "red");
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 17.5, (m_fin->getY() + m_dep->getY())/2 - 5, ";", "red");
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 21, (m_fin->getY() + m_dep->getY())/2 - 5, m_p2, "red");

}

void Arrete::dessinerPrime(SvgFile* svg)
{
 svg->addLine(m_dep->getX() + 500, m_dep->getY(), m_fin->getX()+ 500, m_fin->getY());
 svg->addText((m_fin->getX() + m_dep->getX())/2 - 7 + 500, (m_fin->getY() + m_dep->getY())/2 - 5, m_indice, "green");
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 10 + 500, (m_fin->getY() + m_dep->getY())/2 - 5, m_p1, "red");
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 17.5 + 500, (m_fin->getY() + m_dep->getY())/2 - 5, ";", "red");
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 21 + 500, (m_fin->getY() + m_dep->getY())/2 - 5, m_p2, "red");
}

void Arrete::dessinerArreteChargementPareto(SvgFile* svg)
{
 svg->addLine(m_dep->getX(), m_dep->getY(), m_fin->getX(), m_fin->getY());
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 2, (m_fin->getY() + m_dep->getY())/2 - 5, m_p1, "red");
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 11, (m_fin->getY() + m_dep->getY())/2 - 5, ";", "red");
 svg->addText((m_fin->getX() + m_dep->getX())/2 + 16, (m_fin->getY() + m_dep->getY())/2 - 5, m_p2, "red");

}

void Arrete::dessinerArretePareto(SvgFile* svg, int decx, int decy)
{
    svg->addLine((m_dep->getX() + decx)/5, (m_dep->getY()+ decy)/5, (m_fin->getX()+decx)/5, (m_fin->getY()+ decy)/5);
}

float Arrete::getP1()
{
 return m_p1;
}

float Arrete::getP2()
{
 return m_p2;
}

void Arrete::ajouterPoids(float poids1, float poids2)
{
    m_p1 = poids1;
    m_p2 = poids2;
}

Sommet* Arrete::getDep()
{
    return m_dep;
}

Sommet* Arrete::getFin()
{
    return m_fin;
}

Arrete::~Arrete()
{
//dtor
}
