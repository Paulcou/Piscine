#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "graphe.h"
#include "math.h"

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
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");

        m_sommets.insert({id,new Sommet{id,x,y}});
    }

    int taille;
    ifs >> taille;
    m_taille = taille;
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
            throw std::runtime_error("Probleme lecture indice arete");
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
        m_arretesDessin.insert({indice, new Arrete{indice, new Sommet{id2,x1,y1}, new Sommet{id_voisin,x2, y2}, 0.0, 0.0}});
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
        for(auto item : m_arretesDessin)
        {
            if(item.first == indice2)
            {
                item.second->ajouterPoids(cout1, cout2);
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

void Graphe::codePrim(std::string id)
{
    std::vector<std::pair<Sommet*, float>> liste;
    std::unordered_set<Sommet*> marque;
    int tour = 0;
    int x;
    float poids=0;
    float poids2=0;

    std::cout<<std::endl;
    std::cout<<"Voici le tableau obtenu avec l'algorithme de Prim (cout1) en commencant par le sommet suivant : "
             <<id<<std::endl<<std::endl;
    Sommet*s0=(m_sommets.find(id))->second;
    marque.insert(s0);
    for(auto elem : s0->getVoisins())
    {
        liste.push_back({elem.first, elem.second.first}); /// cout1
    }

    while((!liste.empty())&&(tour != m_ordre-1))
    {
        std::pair<Sommet *, float> tmp;
        float a = 100;
        int index = 100;
        for(size_t i=0; i<liste.size(); ++i)
        {
            if(liste[i].second < a)
            {
                if(marque.find(liste[i].first) == marque.end())
                {
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
        std::string indice= " "; ///a modifier si on veux afficher le poids des aretes

        for(auto elem : tmp.first->getVoisins())
        {
            if(marque.find(elem.first) == marque.end())
            {
                liste.push_back({elem.first, elem.second.first});
            }
            else
            {
                if((elem.second.first == tmp.second)&&(x!=1))
                {
                    std::cout<<"pred : "<<elem.first->getId()<<", "<<std::endl;
                    indice = rechercheIndice(elem.first, tmp.first);
                    m_arretesDessinprime1.insert({indice, new Arrete{indice, elem.first, tmp.first, 0.0,0.0}}); ///elem predecesseur ///tmp en cours de traitement
                    for(auto item : m_arretesDessin)
                    {
                        if(item.first == indice)
                        {
                            (m_arretesDessinprime1.find(indice))->second->ajouterPoids(item.second->getP1(), item.second->getP2());
                            poids2+=item.second->getP2();
                        }
                    }
                    x=1;
                }
            }
        }

    }
    m_poid1 = poids;
    m_poid2 = poids2;
    std::cout<<std::endl;
    std::cout<<"Poids : "<<poids<<", "<<poids2<<std::endl;
}

void Graphe::codePrimC2(std::string id)
{
    std::vector<std::pair<Sommet*, float>> liste;
    std::unordered_set<Sommet*> marque;
    int tour = 0;
    int x;
    float poids=0;
    float poids2=0;

    std::cout<<std::endl;
    std::cout<<"Voici le tableau obtenu avec l'algorithme de Prim (cout2) en commencant par le sommet suivant : "
             <<id<<std::endl<<std::endl;
    Sommet*s0=(m_sommets.find(id))->second;
    marque.insert(s0);
    for(auto elem : s0->getVoisins())
    {
        liste.push_back({elem.first, elem.second.second});
    }

    while((!liste.empty())&&(tour != m_ordre-1))
    {
        std::pair<Sommet *, float> tmp;
        float a = 100;
        int index = 100;
        for(size_t i=0; i<liste.size(); ++i)
        {
            if(liste[i].second < a)
            {
                if(marque.find(liste[i].first) == marque.end())
                {
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
        std::string indice= " ";

        for(auto elem : tmp.first->getVoisins())
        {
            if(marque.find(elem.first) == marque.end())
            {
                liste.push_back({elem.first, elem.second.second});
            }
            else
            {
                if((elem.second.second == tmp.second)&&(x!=1))
                {
                    std::cout<<"pred : "<<elem.first->getId()<<", "<<std::endl;
                    indice = rechercheIndice(elem.first, tmp.first);
                    m_arretesDessinprime1.insert({indice, new Arrete{indice, elem.first, tmp.first, 0.0, 0.0}});
                    for(auto item : m_arretesDessin)
                    {
                        if(item.first == indice)
                        {
                            (m_arretesDessinprime1.find(indice))->second->ajouterPoids(item.second->getP1(), item.second->getP2());
                            poids2+=item.second->getP1();
                        }
                    }
                    x=1;
                }
            }

        }
    }
    m_poid1 = poids2;
    m_poid2 = poids;
    std::cout<<std::endl;
    std::cout<<"Poids : "<<poids2<<", "<<poids<<std::endl; ///on a inverse
}

void Graphe::codePareto()
{
    std::vector<std::string> liste1;

    ///Nous savons qu'il y a 2^(nbre d'ar�tes) cas possibles :
    for(int count = 1; count < pow(2,m_taille); count++)
    {
        ///On va transformer le binaire (int) en chaine de caract�re
        std::string suit="";
        for(int offset = m_taille-1; offset >= 0; offset--)
        {
            std::string s = std::to_string(((count & (1 << offset)) >> offset));
            suit += s;
        }

        ///On compte ici le nombre de 1 dans tous les cas possibles pour �liminer une certaine partie
        int counter1 = 0;
        for(char elem : suit)
        {
            if(elem == '1')
            {
                counter1 += 1;
            }
        }
        ///Nous tirons donc notre premi�re liste compos�es d'�l�ments comprenants ordre-1 ar�tes
        bool ok = true;
        if(counter1 == m_ordre-1)
        {
            std::unordered_set<std::string> marque;
            for(size_t i=0; i<suit.size(); i++)
            {
                if(suit[i] == '1')
                {
                    if( marque.find((m_arretesDessin.find(std::to_string(i)))->second->getDep()->getId()) == marque.end() )
                    {
                        marque.insert((m_arretesDessin.find(std::to_string(i)))->second->getDep()->getId());
                    }
                    if( marque.find((m_arretesDessin.find(std::to_string(i)))->second->getFin()->getId()) == marque.end() )
                    {
                        marque.insert((m_arretesDessin.find(std::to_string(i)))->second->getFin()->getId());
                    }
                }
            }
            for(int j=0; j<m_ordre; j++)
            {
                if(marque.find(std::to_string(j))==marque.end())
                {
                    ok = false;
                }
            }
            if(ok)
            {
                liste1.push_back(suit);
            }
        }
    }
    m_solPossibles = liste1;
    //std::cout<<"Liste1 size : "<<liste1.size()<<std::endl;
    /**for(auto elem : liste1)
    {
        std::cout<<elem<<std::endl;
    }**/
}

void Graphe::afficherPrime(SvgFile* svg)
{
    ///appel dessin direct

        for(auto m : m_arretesDessinprime1)
            {
                m.second->dessinerPrime(svg);
            }
        for(auto s : m_sommets)
            {
                s.second->dessinerSommetPrime(svg);
            }

            svg->addText(650, 45, "(");
            svg->addText(660, 45, m_poid1);
            svg->addText(695, 45, ";");
            svg->addText(710, 45, m_poid2);
            svg->addText(730, 45, ")");
}

std::string Graphe::rechercheIndice(Sommet*s1, Sommet*s2)
{
    for(auto elem : m_aretes)
    {
        if((s1->getId()==elem.second.first && s2->getId()==elem.second.second)||
           (s1->getId()==elem.second.second && s2->getId()==elem.second.first))
        {
            return elem.first;
        }
    }
}


///PARTIE 2
void Graphe::dessinerGrapheChargementPareto(SvgFile* svg)
{
    for(auto s : m_sommets)
        s.second->dessinerSommetChargementPareto(svg);

    for(auto a : m_arretesDessin)
        a.second->dessinerArreteChargementPareto(svg);
}

void Graphe::dessinCalculGraphePareto(SvgFile* svg)
{
    for(auto elem: m_solPossibles)
    {
        float cout1=0;
        float cout2=0;
        for(size_t i=0; i<elem.size(); i++)
        {
            if(elem[i]=='1')
            {
                cout1 += 3*m_arretesDessin.find(std::to_string(i))->second->getP1();
                cout2 += 3*m_arretesDessin.find(std::to_string(i))->second->getP2();
            }
        }
        //std::cout << "(" << cout1/5 << "," << cout2/5 << ")" << std::endl;
        ///dessin avec cout1 et cout2

        svg->addDisk(650 + cout1 , 400 - cout2, 1, "green");
    }
        svg->addLine(650, 400, 650, 50);
        svg->addLine(650, 400, 1000, 400);
        ///fleches du graphe
        svg->addLine(650, 50, 645, 55);
        svg->addLine(650, 50, 655, 55);
        svg->addLine(1000, 400, 995, 395);
        svg->addLine(1000, 400, 995, 405);
}

Graphe::~Graphe()
{
    //dtor
}
