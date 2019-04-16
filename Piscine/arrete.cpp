#include <iostream>
#include "arrete.h"

Arrete::Arrete(std::string indice, Sommet* dep, Sommet* fin): m_indice{indice}, m_dep{dep}, m_fin{fin}
{

}

 void Arrete::dessinerArrete(SvgFile* svg)
 {
     svg->addLine(m_dep->getX(), m_dep->getY(), m_fin->getX(), m_fin->getY());
     svg->addText((m_fin->getX() + m_dep->getX())/2 - 7, (m_fin->getY() + m_dep->getY())/2 - 5, m_indice, "green");
 }

 void Arrete::dessinerPrime(SvgFile* svg)
 {
     svg->addLine(m_dep->getX() + 500, m_dep->getY(), m_fin->getX()+ 500, m_fin->getY());
     svg->addText((m_fin->getX() + m_dep->getX())/2 - 7 + 500, (m_fin->getY() + m_dep->getY())/2 - 5, m_indice, "green");
 }

Arrete::~Arrete()
{
    //dtor
}
