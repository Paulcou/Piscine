#include <iostream>
#include "sommet.h"

Sommet::Sommet(std::string id, double x, double y): m_id{id}, m_x{x},m_y{y}
{
}

void Sommet::ajouterVoisin(Sommet* voisin, float poids)
{
    m_voisins.push_back({voisin, poids});
}

void Sommet::dessinerSommet(SvgFile* svg)
{
    svg->addDisk(m_x, m_y, 5);
}

double Sommet::getX()
{
    return m_x;
}
double Sommet::getY()
{
    return m_y;
}
std::string Sommet::getId()
{
   return m_id;
}

Sommet::~Sommet()
{
    //dtor
}
