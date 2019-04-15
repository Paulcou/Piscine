#include <iostream>
#include "sommet.h"

Sommet::Sommet(std::string id, float x, float y):m_id{id}, m_x{x}, m_y{y}
{
}
void Sommet::ajouterVoisin(Sommet *voisin, float cout1, float cout2)
{
    m_voisins.push_back({voisin, {cout1, cout2}});
}

Sommet::~Sommet()
{
    //dtor
}
