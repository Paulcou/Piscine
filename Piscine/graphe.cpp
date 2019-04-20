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

        m_sommmetsDijs.push_back(new Sommet{id, x,y});
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
        for(size_t i=0; i<m_arretesDessin.size(); i++)
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
                    for(size_t i=0; i<m_arretesDessin.size(); i++)
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
                    for(size_t i=0; i<m_arretesDessin.size(); i++)
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

void Graphe::codePareto(SvgFile* svg)
{
    ///Nous savons qu'il y a 2^(nbre d'ar�tes) cas possibles :
    int depart = pow(2, m_ordre-1) -1;
    int arrivee = 0;
    int n = m_taille - 1;
    while(n != (m_taille - m_ordre))
    {
        arrivee+=pow(2,n);
        n -= 1;
    }
    while(depart <= arrivee)
    {
        std::vector<int> suit;

        for(int offset = m_taille-1; offset >= 0; offset--)
        {
            suit.push_back((depart & (1 << offset)) >> offset);
        }
        /**for(auto elem : suit)
                    std::cout<<elem;
                std::cout<<std::endl;**/

        int cc = rechercheCC(suit);
        if(cc == 1)
        {
            m_solPossibles.push_back(suit);
            /*for(auto elem : suit)
                std::cout<<elem;
            std::cout<<std::endl;*/
            float cout1=0;
            float cout2=0;
            for(size_t i=0; i<suit.size(); i++)
            {
                if(suit[i]==1)
                {
                    cout1 += 3*m_arretesDessin[i]->getP1();
                    cout2 += 3*m_arretesDessin[i]->getP2();
                }
            }
            svg->addDisk(550 + cout1, 400 - cout2, 1.25, "green");
            m_couts.push_back({cout1/3, cout2/3});
        }
        depart = snoob(depart);
    }
}

int Graphe::snoob(int x)
{
    ///Source : https://www.geeksforgeeks.org/next-higher-number-with-same-number-of-set-bits/
    int rightOne;
    int nextHigherOneBit;
    int rightOnesPattern;

    int next = 0;

    if(x)
    {

        // right most set bit
        rightOne = x & -(signed)x;

        // reset the pattern and set next higher bit
        // left part of x will be here
        nextHigherOneBit = x + rightOne;

        // nextHigherOneBit is now part [D] of the above explanation.

        // isolate the pattern
        rightOnesPattern = x ^ nextHigherOneBit;

        // right adjust pattern
        rightOnesPattern = (rightOnesPattern)/rightOne;

        // correction factor
        rightOnesPattern >>= 2;

        // rightOnesPattern is now part [A] of the above explanation.

        // integrate new pattern (Add [D] and [A])
        next = nextHigherOneBit | rightOnesPattern;
    }

    return next;
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
    svg->addText(530, 40, "Cout 2");
    svg->addText(915, 405, "Cout 1");
}

void Graphe::dessinCalculGraphePareto(SvgFile* svg)
{
    std::vector<std::pair<std::vector<int>, std::pair<float, float>>> opti;

    ///On recherche la fronti�re de Pareto et on l'affiche
    opti=rechercheOpti(m_couts);

    int n = 1;
    int j = 50;
    for(auto elem : opti)
    {
        svg->addDisk(550 + 3*elem.second.first, 400 - 3*elem.second.second, 2, "red");

        if(n <9)
        {
            svg->addLine(550 + 3*elem.second.first, 400 - 3*elem.second.second, 50+j, 500);
            svg->addDisk(50+j, 500, 2);

            svg->addText(10 + j, 600, "(");
            svg->addText(20 + j, 600, elem.second.first);
            svg->addText(35+ j, 600, ",");
            svg->addText(45+ j, 600, elem.second.second);
            svg->addText(63 + j, 600, ")");


            for(s : m_sommets)
            {
                s.second->dessinerPareto(svg, (0+j)*5, 500*5);
            }

            for(size_t i=0; i<elem.first.size(); i++)
            {
                if(elem.first[i]==1)
                {
                    m_arretesDessin[i]->dessinerArretePareto(svg, j*5, 500*5);
                }
            }
        }
        j+=100;
        n+=1;
    }
    svg->addText(50, 670, "Nombre de solutions : ");
    svg->addText(220, 670, opti.size());
}

std::vector<std::pair<std::vector<int>, std::pair<float, float>>> Graphe::rechercheOpti(std::vector<std::pair<float, float>> couts)
{
    std::vector<std::pair<std::vector<int>, std::pair<float, float>>> opti;
    std::vector<std::pair<float, float>> coutsComparaison;
    coutsComparaison = couts;

    for(size_t i = 0; i<couts.size(); i++)
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

int Graphe::rechercheCC(std::vector<int> suit)
{
    std::vector<std::vector<int>> som(m_ordre);
    for(size_t i = 0; i<suit.size(); i++)
    {
        if(suit[i] == 1)
        {
            som[m_arretesDessin[i]->getDep()->getIdInt()].push_back(m_arretesDessin[i]->getFin()->getIdInt());
            som[m_arretesDessin[i]->getFin()->getIdInt()].push_back(m_arretesDessin[i]->getDep()->getIdInt());
        }
    }
    std::queue<int> file;
    std::unordered_set<int> marque;

    file.push(0);
    marque.insert(0);
    while(!file.empty())
    {
        int s = file.front();
        file.pop();
        for(auto elem : som[s])
        {
            if ( marque.find(elem) == marque.end() )
            {
                file.push(elem);
                marque.insert(elem);
            }
        }
    }
    if(marque.size()==m_ordre)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
void Graphe::compteurDjikstra()
{
    int depart = pow(2, m_ordre-1) -1;
    int arrivee = pow(2, m_taille);
    for(int count = depart; count < arrivee; count++)
    {
        std::vector<int> suit;
        for(int offset = m_taille-1; offset >= 0; offset--)
        {
            suit.push_back((count & (1 << offset)) >> offset);
        }

        int cc = rechercheCC(suit);
        if(cc == 1)
        {
            /*for(auto elem : suit)
            {
                std::cout<<elem;
            }*/
            m_solPossibles.push_back(suit);
            //std::cout<<std::endl;
            codeDjikstra(suit);

        }

    }
}

void Graphe::codeDjikstra(std::vector<int> suit)
{
    //SvgFile *svg;
    int poidstotaltout = 0;
    int poids1Graphe = 0;

    std::vector<std::vector<std::pair<int,float >>> som(m_ordre);
    for(size_t i = 0; i<suit.size(); i++)
    {
        if(suit[i] == 1)
        {

            poids1Graphe+=m_arretesDessin[i]->getP1();

            som[m_arretesDessin[i]->getDep()->getIdInt()].push_back({{m_arretesDessin[i]->getFin()->getIdInt()},
                                                                    {m_arretesDessin[i]->getP2()}});

            som[m_arretesDessin[i]->getFin()->getIdInt()].push_back({{m_arretesDessin[i]->getDep()->getIdInt()},
                                                                    {m_arretesDessin[i]->getP2()}});
        }
    }

    for(int starNode = 0; starNode < m_ordre; ++starNode)
    {
        std::vector<int> Distance(m_ordre, std::numeric_limits<int>::max());

        Distance[starNode] = 0;
        std::vector<int> Parents(m_ordre, -1);

        std::priority_queue<std::pair<int,float>, std::vector<std::pair<int,float>>, decltype(comp)> Q(comp);
        Q.push(std::make_pair(starNode, 0));

        while (!Q.empty())
        {
            int v = Q.top().first;
            float w = Q.top().second;
            Q.pop();

            if (w <= Distance[v])
            {
                // It can be removed, however, it avoid duplicated work

                for (const auto& i : som[v])
                {
                    auto v2 = i.first;
                    auto w2 = i.second;

                    if (Distance[v] + w2 < Distance[v2])
                    {
                        Distance[v2] = Distance[v] + w2;
                        Parents[v2] = v;
                        Q.push(std::make_pair(v2, Distance[v2]));
                    }
                }
            }
        }
        int poidstot=0;
        for (auto i = 0; i != m_ordre; ++i)
        {

            if(Distance[i]> 20000)
                Distance[i] = 0;

            //std::cout << "\nPath from node " << starNode << " to node " << i << " cost " << Distance[i] << std::endl;
            poidstot += Distance[i];

            //std::cout << i;
            /*for (auto p = Parents[i]; p != -1; p = Parents[p])
                std::cout << " <- " << p;

            std::cout << std::endl;*/

        }
        //std::cout << "poidstot" << poidstot<< std::endl << std::endl;
        poidstotaltout += poidstot;
    }
    //std::cout<<"total poids 1:"<< poids1Graphe<<std::endl;
    //std::cout << "poidstotaltoutgraphe :" << poidstotaltout << std::endl;
    m_poidsDji.push_back({poids1Graphe, poidstotaltout});
    //svg->addDisk(550 + poids1Graphe, 400 - 4*poidstotaltout, 1.25, "green");

}

void Graphe::dessinerGrapheChargementDjikstra(SvgFile* svg)
{
    for(auto s : m_sommets)
        s.second->dessinerSommetChargementPareto(svg);

    for(auto a : m_arretesDessin)
        a->dessinerArreteChargementPareto(svg);

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
        svg->addText(515, i + 5, (grad2 +2100));
        grad2-=200;
    }
    ///Text
    svg->addText(485, 40, "Somme des Dijkstra");
    svg->addText(915, 405, "Poids 1 total");

    for(auto elem : m_poidsDji)
    {
        svg->addDisk(550 + 3*elem.first, 400 - 0.15*elem.second, 1, "green");
    }
    std::vector<std::pair<std::vector<int>, std::pair<float, float>>> opti;

    opti = rechercheOpti(m_poidsDji);

    int n = 1;
    int j = 50;
    for(auto elem : opti)
    {
        svg->addDisk(550 + 3*elem.second.first, 400 - 0.15*elem.second.second, 2, "red");
        //svg->addText(540 + 3*elem.second.first, 412 - 0.15*elem.second.second, n, "black");
        if(n<9)
        {
            svg->addLine(550 + 3*elem.second.first, 400 - 0.15*elem.second.second, 50+j, 500);
            svg->addDisk(50+j, 500, 2);

            //svg->addText(0 + j, 600, n);
            svg->addText(15 + j, 600, elem.second.first);
            svg->addText(36+ j, 600, ";");
            svg->addText(50+ j, 600, elem.second.second);

            for(s : m_sommets)
            {
                s.second->dessinerPareto(svg, (0+j)*5, 500*5);
            }

            for(size_t i=0; i<elem.first.size(); i++)
            {
                if(elem.first[i]==1)
                {
                    m_arretesDessin[i]->dessinerArretePareto(svg, j*5, 500*5);
                }
            }
        }
        j+=100;
        n+=1;
    }

    svg->addText(50, 670, "Nombre de solutions : ");
    svg->addText(220, 670, opti.size());

}

Graphe::~Graphe()
{
    //dtor
}
