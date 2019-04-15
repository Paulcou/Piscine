#include <fstream>
#include <iostream>
#include <vector>
#include "graphe.h"

Graphe::Graphe(std::string nomFichier, std::string nomFichier2){
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    std::string id;
    float x, y;

    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }

    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    std::string id_voisin;
    std::string id2;
    std::string indice;
    for (int i=0; i<taille; ++i){
        ifs>>indice; if(ifs.fail()) throw std::runtime_error("Probleme lecture ineice arete");
        ifs>>id2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        (m_aretes.push_back({indice,{id2, id_voisin}}));
    }

    std::ifstream ifs2{nomFichier2};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier2 );

    int taille2;
    int nbre;
    ifs2 >> taille2;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe2");
    ifs2 >> nbre;

    std::string indice2;
    float cout1, cout2;

    for(int j=0; j<taille2; j++){
        ifs2 >> indice2; if(ifs.fail()) throw std::runtime_error("Probleme lecture indice2 arete");
        ifs2 >> cout1; if(ifs.fail()) throw std::runtime_error("Probleme lecture cout1 arete");
        ifs2 >> cout2; if(ifs.fail()) throw std::runtime_error("Probleme lecture cout2 arete");
        for(auto elem : m_aretes){
            if(elem.first == indice2){
                (m_sommets.find(elem.second.first))->second->ajouterVoisin(m_sommets.find(elem.second.second)->second, cout1, cout2);
                (m_sommets.find(elem.second.second))->second->ajouterVoisin(m_sommets.find(elem.second.first)->second, cout1, cout2);
            }
        }
    }
}

Graphe::~Graphe()
{
    //dtor
}
