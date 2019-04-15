#include <fstream>
#include <iostream>
#include "graphe.h"

Graphe::Graphe(std::string nomFichier){
    /// Nous cherchons si le fichier est de type weight ou non.
    bool weightType;
    if (nomFichier.find('_') != std::string::npos){
        weightType = true;
    }
    else{
        weightType = false;
    }

    /**std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>centrale; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,centrale}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    float poids;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extrémités
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        ifs>>poids; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete poids");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second, poids);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second, poids);//remove si graphe orienté
    }**/
}

Graphe::~Graphe()
{
    //dtor
}
