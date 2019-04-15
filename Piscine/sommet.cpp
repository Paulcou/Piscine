#include <iostream>
#include "sommet.h"

Sommet::Sommet(std::string id):m_id{id}
{
}
void Sommet::ajouterVoisin(Sommet* voisin, float poids)
{
    m_voisins.push_back({voisin, poids});
}

Sommet::~Sommet()
{
    //dtor
}
