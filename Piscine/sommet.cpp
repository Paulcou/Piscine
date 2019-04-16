#include <iostream>
#include "sommet.h"

Sommet::Sommet(std::string id, float x, float y): m_id{id}, m_x{x}, m_y{y}
{
}
void Sommet::ajouterVoisin(Sommet *voisin, float cout1, float cout2)
{
    m_voisins.push_back({voisin, {cout1, cout2}});
}

void Sommet::dessinerSommet(SvgFile* svg)
{
    svg->addDisk(m_x, m_y, 5);
    svg->addText(m_x - 18, m_y - 9, m_id, "purple");
}

void Sommet::dessinerSommetPrime(SvgFile* svg)
{
    svg->addDisk(m_x + 500, m_y, 5);
    svg->addText(m_x - 18 + 500, m_y - 9, m_id, "purple");
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

std::vector<std::pair<Sommet*, std::pair<float, float>>> Sommet::getVoisins(){
    return m_voisins;
}

Sommet::~Sommet()
{
    //dtor
}
