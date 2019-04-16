#include <fstream>
#include <iostream>
#include <vector>
#include "graphe.h"

Graphe::Graphe(std::string nomFichier, std::string nomFichier2)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    m_ordre = ordre;

    std::string id;
    float x, y;

    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");

        m_sommets.insert({id,new Sommet{id,x,y}});
    }

    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    std::string id_voisin;
    std::string id2;
    std::string indice;

    ///Pour dessin
    float x1, x2, y1, y2;

    for (int i=0; i<taille; ++i)
    {
        ifs>>indice;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture ineice arete");
        ifs>>id2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");

        (m_aretes.push_back({indice,{id2, id_voisin}}));

        ///Dessin direct du graphe avec classe aretes
        for(auto d : m_sommets)
        {
            if(d.second->getId() == id2)
            {
                x1 = d.second->getX();
                y1 = d.second->getY();
            }
            else if(d.second->getId() == id_voisin)
            {
                x2 = d.second->getX();
                y2 = d.second->getY();
            }
        }
        m_arretesDessin.insert({indice, new Arrete{indice, Sommet{id2,x1,y1}, Sommet{id_voisin,x2, y2}}});
        ///

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

    for(int j=0; j<taille2; j++)
    {
        ifs2 >> indice2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture indice2 arete");
        ifs2 >> cout1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture cout1 arete");
        ifs2 >> cout2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture cout2 arete");

        for(auto elem : m_aretes)
        {
            if(elem.first == indice2)
            {
                (m_sommets.find(elem.second.first))->second->ajouterVoisin(m_sommets.find(elem.second.second)->second, cout1, cout2);
                (m_sommets.find(elem.second.second))->second->ajouterVoisin(m_sommets.find(elem.second.first)->second, cout1, cout2);
            }
        }
    }
}

void Graphe::dessinerGrapheChargement(SvgFile* svg)
{
    for(auto s : m_sommets)
        s.second->dessinerSommet(svg);

    for(auto a : m_arretesDessin)
        a.second->dessinerArrete(svg);
}

void Graphe::codePrim(std::string id){
    std::vector<std::pair<Sommet*, float>> liste;
    std::unordered_set<Sommet*> marque;
    int tour = 0;
    int x;
    float poids=0;

    std::cout<<std::endl;
    std::cout<<"Voici le tableau obtenu avec l'algorithme de Prim en commençant par le sommet suivant : "
             <<id<<std::endl<<std::endl;
    Sommet*s0=(m_sommets.find(id))->second;
    marque.insert(s0);
    for(auto elem : s0->getVoisins()){
        liste.push_back({elem.first, elem.second.first}); /// cout1
    }

    while((!liste.empty())&&(tour != m_ordre-1)){
        std::pair<Sommet *, float> tmp;
        float a = 100;
        int index = 100;
        for(int i=0; i<liste.size(); ++i){
            if(liste[i].second < a){
                if(marque.find(liste[i].first) == marque.end()){
                    a = liste[i].second;
                    tmp = liste[i];
                    index = i;
                }
            }
        }

        std::cout<<tmp.first->getId()<<"("<<tmp.second<<"), ";

        liste.erase(liste.begin()+index);
        marque.insert(tmp.first);
        tour+=1;
        poids+=tmp.second;

        x=0;
        for(auto elem : tmp.first->getVoisins()){
            if(marque.find(elem.first) == marque.end()){
                liste.push_back({elem.first, elem.second.first});
            }else{
                if((elem.second.first == tmp.second)&&(x!=1)){
                    std::cout<<"pred : "<<elem.first->getId()<<", "<<std::endl;
                    x=1;
                }
            }
        }
    }
    std::cout<<std::endl;
    std::cout<<"Poids : "<<poids<<std::endl;
}

Graphe::~Graphe()
{
    //dtor
}
