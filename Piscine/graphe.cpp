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
        m_arretesDessin.push_back(new Arrete{indice, new Sommet{id2,x1,y1}, new Sommet{id_voisin,x2, y2}, 0.0, 0.0});
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
        for(int i=0; i<m_arretesDessin.size(); i++)
        {
            if(std::to_string(i) == indice2)
            {
                m_arretesDessin[i]->ajouterPoids(cout1, cout2);
            }
        }
    }
}

void Graphe::dessinerGrapheChargement(SvgFile* svg)
{
    for(auto s : m_sommets)
        s.second->dessinerSommet(svg);

    for(auto a : m_arretesDessin)
        a->dessinerArrete(svg);
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
                    for(int i=0; i<m_arretesDessin.size(); i++)
                    {
                        if(std::to_string(i) == indice)
                        {
                            (m_arretesDessinprime1.find(indice))->second->ajouterPoids(m_arretesDessin[i]->getP1(), m_arretesDessin[i]->getP2());
                            poids2+=m_arretesDessin[i]->getP2();
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
    m_resultPrim1 = {poids, poids2};
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
                    for(int i=0; i<m_arretesDessin.size(); i++)
                    {
                        if(std::to_string(i) == indice)
                        {
                            (m_arretesDessinprime1.find(indice))->second->ajouterPoids(m_arretesDessin[i]->getP1(), m_arretesDessin[i]->getP2());
                            poids2+=m_arretesDessin[i]->getP1();
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
    m_resultPrim2 = {poids2, poids};
}

void Graphe::codePareto()
{
    std::vector<std::string> liste1;

    ///Nous savons qu'il y a 2^(nbre d'arêtes) cas possibles :
    int depart = pow(2, m_ordre-1) -1;
    int arrivee = 1;
    int n = m_taille - 1;
    while(n != (m_taille-m_ordre))
    {
        arrivee+=pow(2,n);
        n -= 1;
    }
    for(int count = depart; count < arrivee; count++)
    {
        ///On va transformer le binaire (int) en chaine de caractère
        std::string suit="";
        for(int offset = m_taille-1; offset >= 0; offset--)
        {
            std::string s = std::to_string(((count & (1 << offset)) >> offset));
            suit += s;
        }
        //std::cout<<suit<<std::endl;

        ///On compte ici le nombre de 1 dans tous les cas possibles pour éliminer une certaine partie
        int counter1 = 0;
        for(char elem : suit)
        {
            if(elem == '1')
            {
                counter1 += 1;
            }
        }
        ///Nous tirons donc notre première liste composées d'éléments comprenants ordre-1 arêtes
        bool ok = true;
        if(counter1 == m_ordre-1)
        {
            std::unordered_set<std::string> marque;
            for(size_t i=0; i<suit.size(); i++)
            {
                if(suit[i] == '1')
                {
                    if( marque.find((m_arretesDessin[i]->getDep()->getId())) == marque.end() )
                    {
                        marque.insert((m_arretesDessin[i]->getDep()->getId()));
                    }
                    if( marque.find((m_arretesDessin[i]->getFin()->getId())) == marque.end() )
                    {
                        marque.insert((m_arretesDessin[i]->getFin()->getId()));
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
        a->dessinerArreteChargementPareto(svg);
}

void Graphe::dessinCalculGraphePareto(SvgFile* svg)
{

    ///pointilles
    for(int i = 550; i < 900; i += 30)
        for(int j = 70; j < 430; j += 30)
        {
            svg->addLine(i-5, j, i + 5, j, "grey");
            svg->addLine(i, j-5, i, j+5, "grey");
        }

    svg->addLine(550, 400, 550, 50);
    svg->addLine(550, 400, 900, 400);
    ///fleches du graphe
    svg->addLine(550, 50, 545, 55);
    svg->addLine(550, 50, 555, 55);
    svg->addLine(900, 400, 895, 395);
    svg->addLine(900, 400, 895, 405);

    int grad = -10;
    for(int i = 550; i < 900; i +=30)
    {
        svg->addLine(i, 400, i, 405);
        svg->addText(i - 5, 420, grad + 10);
        grad+=10;
    }
    int grad2 = 100;
    for(int i = 70; i < 420; i +=30)
    {
        svg->addLine(545, i, 550, i);
        svg->addText(515, i + 5, grad2 +10);
        grad2-=10;
    }
    ///Text
    svg->addText(565, 50, "Cout 2");
    svg->addText(915, 405, "Cout 1");

    ///on affiche avant puis points
    std::vector<std::pair<float, float>> couts;
    std::vector<std::pair<std::string, std::pair<float, float>>> opti;
    for(int j=0; j<m_solPossibles.size(); j++)
    {
        float cout1=0;
        float cout2=0;
        std::string elem = m_solPossibles[j];
        for(size_t i=0; i<elem.size(); i++)
        {
            if(elem[i]=='1')
            {
                cout1 += 3*m_arretesDessin[i]->getP1();
                cout2 += 3*m_arretesDessin[i]->getP2();
            }
        }

        svg->addDisk(550 + cout1, 400 - cout2, 1.25, "green");

        couts.push_back({cout1/3, cout2/3});
    }

    ///On recherche la frontière de Pareto et on l'affiche
    opti=rechercheOpti(couts);
    std::cout<<"opti"<<std::endl;
    for(auto elem : opti)
    {
        std::cout<<elem.second.first<<" , "<<elem.second.second<<std::endl;
        std::cout<<elem.first<<std::endl;
        svg->addDisk(550 + 3*elem.second.first, 400 - 3*elem.second.second, 2, "red");

        std::string item;
        item = elem.first;
        for(int i=0; i<item.size(); i++)
        {
            if(item[i]=='1')
            {
                for(int j = 0; j<1000; j+=100)
                {

                   for(s : m_sommets)
                    {
                        s.second->dessinerPareto(svg, (0+j)*5, 500*5);
                    }
                    ///tu récupères l'arete d'indice 1 avec m_arreteDessin[i]

                    m_arretesDessin[i]->dessinerArretePrime(svg, (0+j)*5, 500*5);
                }


            }
        }

    }
}

std::vector<std::pair<std::string, std::pair<float, float>>> Graphe::rechercheOpti(std::vector<std::pair<float, float>> couts)
{
    std::vector<std::pair<std::string, std::pair<float, float>>> opti;
    std::vector<std::pair<float, float>> coutsComparaison;
    coutsComparaison = couts;

    for(int i = 0; i<couts.size(); i++)
    {
        bool ok = true;
        for(auto item : coutsComparaison)
        {
            if(couts[i]!=item)
            {
                if((item.first <= couts[i].first)&&(item.second <= couts[i].second))
                {
                    ok = false;
                }
            }
        }
        if(ok)
        {
            opti.push_back({m_solPossibles[i],couts[i]});
        }
    }

    return opti;
}

Graphe::~Graphe()
{
    //dtor
}
