#include <iostream>
#include "arrete.h"

Arrete::Arrete(Sommet dep, Sommet fin): m_dep{dep}, m_fin{fin}
{

}

 void Arrete::dessinerArrete(SvgFile* svg)
 {
     svg->addLine(m_dep.getX(), m_dep.getY(), m_fin.getX(), m_fin.getY());
 }

Arrete::~Arrete()
{
    //dtor
}
