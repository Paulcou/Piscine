#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "graphe.h"
#include "math.h"

/// Chargement des fichiers reçus

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

    int id;
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

        m_sommmetsDijs.push_back(new Sommet{id, x,y});
    }

    int taille;
    ifs >> taille;
    m_taille = taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    int id_voisin;
    int id2;
    int indice;

    ///Pour dessin
    float x1=0, x2=0, y1=0, y2=0;

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
        m_arretesDessinBonus.push_back(new Arrete{indice, new Sommet{id2,x1,y1}, new Sommet{id_voisin,x2, y2}, 0.0, 0.0});
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

    int indice2;
    float cout1, cout2, cout3;

    if(nbre == 2)
    {
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
                if(i == indice2)
                {
                    m_arretesDessin[i]->ajouterPoids(cout1, cout2);

                }
            }
        }
    }

    if(nbre == 3)
    {
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

            ifs2 >> cout3;
            if(ifs.fail())
                throw std::runtime_error("Probleme lecture cout2 arete");

            for(auto elem : m_aretes)
            {
                if(elem.first == indice2)
                {
                    (m_sommets.find(elem.second.first))->second->ajouterVoisinBonus(m_sommets.find(elem.second.second)->second, cout1, cout2, cout3);
                    (m_sommets.find(elem.second.second))->second->ajouterVoisinBonus(m_sommets.find(elem.second.first)->second, cout1, cout2, cout3);
                }
            }
            for(size_t i=0; i<m_arretesDessinBonus.size(); i++)
            {
                if(i == indice2)
                {
                    m_arretesDessinBonus[i]->ajouterPoidsBonus(cout1, cout2, cout3);

                }
            }
        }
    }

}

/// Affiche le graphe chargé précédemment

void Graphe::dessinerGrapheChargement(SvgFile* svg)
{
    for(auto s : m_sommets)
        s.second->dessinerSommet(svg);

    for(auto a : m_arretesDessin)
        a->dessinerArrete(svg);
}


/// PARTIE 1


/// Code pour Prim avec les couts 1
/// reçoit l'id du sommet à partir duquel nous commençons l'algo

void Graphe::codePrim(int id)
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
        int indice; ///a modifier si on veux afficher le poids des aretes

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
                        if(i == indice)
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

/// Code pour Prim avec les couts 2
/// reçoit l'id du sommet à partir duquel nous commençons l'algo

void Graphe::codePrimC2(int id)
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
        int indice;

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
                        if(i == indice)
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
    /// Pour un graphe à 4 sommets, la première valeur qui comprend 3 arêtes est : pow(2, m_ordre-1) -1
    /// Par exemple, pour 4 sommets, la première sera 7 : 00111
    int depart = pow(2, m_ordre-1) -1;
    /// Pour l'arrivée nous avons également pu établir une règle basée sur une somme de puissances de 2
    /// Par exemple, pour 4 sommets, la dernière sera 28 : 11100
    int arrivee = 0;
    int n = m_taille - 1;
    while(n != (m_taille - m_ordre))
    {
        arrivee+=pow(2,n);
        n -= 1;
    }
    /// Pour le compteur ci-dessous, nous nous sommes légèrement inspiré du 3ème topic du lien suivant
    /// http://www.cplusplus.com/forum/general/15355/
    /// Au lieu de parcourir toutes les valeurs possibles, nous avons préféré partir de la valeur de départ
    /// et la remplacer à chaque tour par la valeur suivante ayant le même nombre de bits
    /// Par exemple, la prochaine valeur de 00111 est 01011.
    while(depart <= arrivee)
    {
        std::vector<int> suit;

        for(int offset = m_taille-1; offset >= 0; offset--)
        {
            suit.push_back((depart & (1 << offset)) >> offset);
        }

        /// On regarde si les arêtes du vector constituent une ou plusieurs composantes connexes

        int cc = rechercheCC(suit);
        if(cc == 1)
        {
            /// Si 1 seule composante, on l'ajoute à solutions possibles

            m_solPossibles.push_back(suit);

            /// Et on dessine le point correspondant

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
            svg->addDisk(550 + cout1, 400 - cout2, 1.5, "green");
            m_couts.push_back({cout1/3, cout2/3});
        }
        depart = snoob(depart);
    }
}

/// Ceci est la fonction qui nous permet de trouver la valeur suivante avec le même nombre de bits
/// que la valeur passée en paramètre

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

    svg->addText(660, 45, "(");
    svg->addText(670, 45, m_poid1);
    svg->addText(705, 45, ";");
    svg->addText(720, 45, m_poid2);
    svg->addText(740, 45, ")");
}

/// rechercheIndice retourne l'indice de l'arête entre les deux sommets reçus en paramètres

int Graphe::rechercheIndice(Sommet*s1, Sommet*s2)
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

    ///On recherche la frontière de Pareto et on l'affiche
    opti=rechercheOpti(m_couts);
    m_opti = opti;

    int n = 1;
    int j = 50;
    for(auto elem : opti)
    {
        svg->addDisk(550 + 3*elem.second.first, 400 - 3*elem.second.second, 4, "red");

        if(n <9)
        {
            svg->addLine(550 + 3*elem.second.first, 400 - 3*elem.second.second, 50+j, 500);
            svg->addDisk(50+j, 500, 2);

            svg->addText(10 + j, 600, "(");
            svg->addText(20 + j, 600, elem.second.first);
            svg->addText(35+ j, 600, ",");
            svg->addText(45+ j, 600, elem.second.second);
            svg->addText(63 + j, 600, ")");


            for(auto s : m_sommets)
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
    ///Double boucle pour récupérer les solutions optimales de Pareto en comparant les couts
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

/// BFS qui retourne 1 si on trouve une seule composante connexe et 2 sinon

int Graphe::rechercheCC(std::vector<int> suit)
{
    std::vector<std::vector<int>> som(m_ordre);
    for(size_t i = 0; i<suit.size(); i++)
    {
        if(suit[i] == 1)
        {
            som[m_arretesDessin[i]->getDep()->getId()].push_back(m_arretesDessin[i]->getFin()->getId());
            som[m_arretesDessin[i]->getFin()->getId()].push_back(m_arretesDessin[i]->getDep()->getId());
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
    if(marque.size() == m_ordre)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}


/// PARTIE 3


void Graphe::compteurDijkstra()
{
    ///Sur la même base que le compteur de Pareto sauf qu'ici nous ne cherchons pas seulement les valeurs
    ///possédant m_ordre - 1 bits.
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
            m_solPossibles.push_back(suit);
            codeDijkstra(suit);
        }

    }
}

void Graphe::codeDijkstra(std::vector<int> suit)
{
    //SvgFile *svg;
    int poidstotaltout = 0;
    int poids1Graphe = 0;

    /// Nous récupérons les voisins temporaires (pour chaque combinaison binaire) des sommets sous forme de vector de vector

    std::vector<std::vector<std::pair<int,float >>> som(m_ordre);
    for(size_t i = 0; i<suit.size(); i++)
    {
        if(suit[i] == 1)
        {

            poids1Graphe+=m_arretesDessin[i]->getP1();

            som[m_arretesDessin[i]->getDep()->getId()].push_back({{m_arretesDessin[i]->getFin()->getId()},
                {m_arretesDessin[i]->getP2()}
            });

            som[m_arretesDessin[i]->getFin()->getId()].push_back({{m_arretesDessin[i]->getDep()->getId()},
                {m_arretesDessin[i]->getP2()}
            });
        }
    }
    ///Source qui a aidé a realiser dijstra: https://www.40tude.fr/blog/algorithme-de-dijkstra-en-c/?fbclid=IwAR2OIVCXB-Ld0DBj2NJ56zVaMFbeejDOcKXBsi7yP9IWojVZawGTtmDyJsI
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

            poidstot += Distance[i];

        }
        poidstotaltout += poidstot;
    }
    m_poidsDji.push_back({poids1Graphe, poidstotaltout});
}

/// Tout ce qui est du chargement lorsque nous appliquons Dijkstra

void Graphe::dessinerGrapheChargementDijkstra(SvgFile* svg)
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

    /// Nous recherchons les solutions optimales et nous les affichons

    opti = rechercheOpti(m_poidsDji);

    int n = 1;
    int j = 50;
    for(auto elem : opti)
    {
        svg->addDisk(550 + 3*elem.second.first, 400 - 0.15*elem.second.second, 2, "red");

    /// Nous avons décidé de n'afficher que 8 des solutions trouvées sous forme de graphe (en dessous)
        if(n<9)
        {
            svg->addLine(550 + 3*elem.second.first, 400 - 0.15*elem.second.second, 50+j, 500);
            svg->addDisk(50+j, 500, 2);

            svg->addText(15 + j, 600, elem.second.first);
            svg->addText(36+ j, 600, ";");
            svg->addText(50+ j, 600, elem.second.second);

            for(auto s : m_sommets)
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


///PARTIE BONUS


/// Affichage du Cube pour le représentation 3D due à 3 couts différents

void Graphe::dessinerGrapheChargementBonus(SvgFile* svg)
{
    for(auto s : m_sommets)
        s.second->dessinerSommetChargementPareto(svg);

    for(auto a : m_arretesDessinBonus)
        a->dessinerArreteChargementBonus(svg);

    ///CUBE
    svg->addLine(550, 400, 550, 25);///cout2
    svg->addLine(550, 400, 950, 400); ///cout 1
    svg->addLine(550, 400, 400, 550);///cout 3
    svg->addLine(425, 525, 775, 525);
    svg->addLine(425, 525, 425, 175);
    svg->addLine(425, 175, 550, 50);
    svg->addLine(775, 525, 900, 400);
    svg->addLine(775, 525, 775, 175);
    svg->addLine(775, 175, 425, 175);
    svg->addLine(775, 175, 900, 50);
    svg->addLine(550, 50, 900, 50);
    svg->addLine(900, 400, 900, 50);

    ///Text
    svg->addText(560, 40, "Cout 2");
    svg->addText(915, 415, "Cout 1");
    svg->addText(425, 550, "Cout 3");
}

/// Même compteur que pour Pareto 2D mais cette fois avec 3 couts

void Graphe::codeBonus(SvgFile* svg)
{
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

        int cc = rechercheCCBonus(suit);
        if(cc == 1)
        {
            m_solPossibles.push_back(suit);

            float cout1=0;
            float cout2=0;
            float cout3=0;
            for(size_t i=0; i<suit.size(); i++)
            {
                if(suit[i]==1)
                {
                    cout1 += 3*m_arretesDessinBonus[i]->getP1();
                    cout2 += 3*m_arretesDessinBonus[i]->getP2();
                    cout3 += 3*m_arretesDessinBonus[i]->getP3();
                }
            }
            svg->addDisk(550 + cout1 - cout3, 400 - cout2 + cout3, 1.25, "green");
            m_coutsB.push_back({cout1/3, {cout2/3, cout3/3}});
        }
        depart = snoob(depart);
    }
}

/// Affichage de la frontière de Pareto en 3D pour 3 couts

void Graphe::dessinCalculGrapheBonus(SvgFile* svg)
{
    std::vector<std::pair<std::vector<int>, std::pair<float, std::pair<float, float>>>> opti;

    ///On recherche la frontière de Pareto et on l'affiche
    opti=rechercheOptiBonus(m_coutsB);

    int n = 1;
    int j = 50;
    for(auto elem : opti)
    {
        svg->addDisk(550 + 3*elem.second.first - 3*elem.second.second.second,
                     400 - 3*elem.second.second.first + 3*elem.second.second.second,
                      2, "red");
    /// Nous avons décidé de n'afficher que 8 des solutions trouvées sous forme de graphe (en dessous)
        if(n <9)
        {
            svg->addLine(550 + 3*elem.second.first - 3*elem.second.second.second,
                          400 - 3*elem.second.second.first + 3*elem.second.second.second,
                          50+j, 600);
            svg->addDisk(50+j, 600, 2);

            svg->addText(10 + j, 700, "(");
            svg->addText(20 + j, 700, elem.second.first);
            svg->addText(35+ j, 700, ",");
            svg->addText(45+ j, 700, elem.second.second.first);
            svg->addText(60+ j, 700, ",");
            svg->addText(75+ j, 700, elem.second.second.second);
            svg->addText(93 + j, 700, ")");


            for(auto s : m_sommets)
            {
                s.second->dessinerPareto(svg, (0+j)*5, 600*5);
            }

            for(size_t i=0; i<elem.first.size(); i++)
            {
                if(elem.first[i]==1)
                {
                    m_arretesDessinBonus[i]->dessinerArretePareto(svg, j*5, 600*5);
                }
            }
        }
        j+=150;
        n+=1;
    }
    svg->addText(50, 770, "Nombre de solutions : ");
    svg->addText(220, 770, opti.size());
}

/// Recherche des extremums de Pareto pour 3 couts

std::vector<std::pair<std::vector<int>, std::pair<float,std::pair<float, float>>>> Graphe::rechercheOptiBonus(std::vector<std::pair<float, std::pair<float, float>>> couts)
{
    std::vector<std::pair<std::vector<int>, std::pair<float,std::pair<float, float>>>> opti;
    std::vector<std::pair<float,std::pair<float, float>>> coutsComparaison;
    coutsComparaison = couts;

    for(size_t i = 0; i<couts.size(); i++)
    {
        bool ok = true;
        for(auto item : coutsComparaison)
        {
            if(couts[i]!=item)
            {
                if((item.first <= couts[i].first)&&(item.second.first <= couts[i].second.first)&&(item.second.second <= couts[i].second.second))
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

///BFS pour trouver si il y a une ou plusieurs composantes connexes comme pour Pareto

int Graphe::rechercheCCBonus(std::vector<int> suit)
{
    std::vector<std::vector<int>> som(m_ordre);
    for(size_t i = 0; i<suit.size(); i++)
    {
        if(suit[i] == 1)
        {
            som[m_arretesDessinBonus[i]->getDep()->getId()].push_back(m_arretesDessinBonus[i]->getFin()->getId());
            som[m_arretesDessinBonus[i]->getFin()->getId()].push_back(m_arretesDessinBonus[i]->getDep()->getId());
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
    if(marque.size() == m_ordre)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

///La fonction dessinCalculHeuristique calcule et affiche la valeur la plus proche de l'origine

void Graphe::dessinCalculHeuristique(SvgFile* svg)
{
    float moyenne = 1000;
    std::pair<float, float> couts;
    std::vector<int> pPetite;
    for(size_t i=0; i<m_couts.size(); i++)
    {
        if((m_couts[i].first + m_couts[i].second)/2 < moyenne)
        {
            moyenne = (m_couts[i].first + m_couts[i].second)/2;
            couts = {m_couts[i].first, m_couts[i].second};
            pPetite = m_solPossibles[i];
        }
    }

    svg->addDisk(550 + 3*couts.first, 400 - 3*couts.second, 2.5, "blue");

    for(size_t j = 0; j<pPetite.size(); j++)
    {
        if(pPetite[j] == 1)
        {
            m_arretesDessin[j]->dessinerArretePareto(svg, 3200, 2550);
        }
    }

    for(auto s : m_sommets)
    {
        s.second->dessinerPareto(svg, 3200, 2550);
    }

    svg->addLine(550 + 3*couts.first, 400 - 3*couts.second, 685, 500);
    svg->addDisk(685, 500, 2);

    svg->addText(655, 620, "(");
    svg->addText(665, 620, couts.first);
    svg->addText(680, 620, ",");
    svg->addText(690, 620, couts.second);
    svg->addText(708, 620, ")");
}

///La prochaine fonction est pour l'extension "Interpoler les vecteurs solutions extrêmes"

void Graphe::vecteurInter(SvgFile* svg)
{
    std::vector<std::pair<std::vector<int>, std::pair<float, float>>> optiComp;
    std::unordered_map<float, std::vector<int>> inter;
    optiComp = m_opti;

    ///Nous déterminons les vector intermédiaires en comparant les solutions optimales de Pareto entre elles.
    for(size_t i = 0; i<m_opti.size(); i++)
    {
        for(size_t j = 0; j<optiComp.size(); j++)
        {
            if(i!=j)
            {
                std::vector<int> tmp;
                for(size_t k = 0; k<m_opti[i].first.size(); k++)
                {
                    if(((m_opti[i].first)[k] == (optiComp[j].first)[k]))
                    {
                        tmp.push_back((m_opti[i].first)[k]);
                    }
                    else
                    {
                        tmp.push_back(2);
                    }
                }
                if(inter.find(m_opti[i].second.first + optiComp[j].second.first)==inter.end())
                {
                    inter.insert({m_opti[i].second.first + optiComp[j].second.first, tmp});
                }
            }
        }
    }

    std::vector<std::vector<int>> solutions;

    ///Pour chaque vector intermédiaire
    for(auto elem : inter)
    {
        int compteur2 = 0;
        std::vector<std::vector<int>> combinaisons;

        ///On compte le nombre de 2 (X dans l'énoncé)
        for(auto item : elem.second)
        {
            if(item==2)
            {
                compteur2 +=1;
            }

        }

        ///Nous créeons en conséquence un nombre de possibilités correspondantes
        ///Par exemple, compteur = 3, on aura (000, 001,...,111)
        int arrivee = pow(2, compteur2);
        int count = 0;
        while(count!=arrivee)
        {
            std::vector<int> suit;
            for(int offset = (compteur2-1); offset >= 0; offset--)
            {
                suit.push_back((count & (1 << offset)) >> offset);
            }
            combinaisons.push_back(suit);
            count++;
        }

        ///Nous changeons les 2 par ces combinaisons et envoyons toutes les possibilités si elles sont
        ///acceptables dans un vector.

        for(size_t i = 0; i<combinaisons.size(); i++)
        {
            int j = 0;
            std::vector<int> suit;
            for(auto item : elem.second)
            {
                if(item==2)
                {
                    suit.push_back((combinaisons[i])[j]);
                    j += 1;
                }
                else
                {
                    suit.push_back(item);
                }
            }

            int compteur1 = 0;
            for(auto x : suit)
            {
                if(x==1)
                {
                    compteur1+=1;
                }
            }
            if(compteur1==m_ordre-1)
            {
                solutions.push_back(suit);
            }

        }
    }

    ///Nous stockons ici les couts des solutions retenues
    std::vector<std::pair<float, float>> couts;

    for(auto elem : solutions)
    {
        float poids1=0;
        float poids2=0;
        for(size_t i = 0; i<elem.size(); i++)
        {
            if(elem[i] == 1)
            {
                poids1 += m_arretesDessin[i]->getP1();
                poids2 += m_arretesDessin[i]->getP2();
            }
        }
        couts.push_back({poids1, poids2});
    }

    ///Puis nous affichons le résultat
    for(auto elem : couts)
    {
        svg->addDisk(550 + 3*elem.first, 400 - 3*elem.second, 1.6, "yellow");
    }
}


Graphe::~Graphe()
{
    //dtor
}
