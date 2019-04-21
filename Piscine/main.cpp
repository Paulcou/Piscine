#include <iostream>
#include "graphe.h"

int main()
{
    std::cout<<"Chargement..."<< std::endl;
    /**std::string nom, weight;
    std::cout<<"choisir nom fichier"<< std::endl;
    std::cin >>nom;
    std::cout << "choisir weight fichier"<< std::endl;
    std::cin >> weight;

    //Graphe g{"files/"+nom+".txt", "files/"+nom+"_weights_"+weight+".txt"};**/
    Graphe g{"files/triville.txt", "files/triville_weights_0.txt"};
    int choix;

    std::cout<<std::endl;
    std::cout<<"  MENU  "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"1: Quitter"<<std::endl;
    std::cout<<"2: Prim"<<std::endl;
    std::cout<<"3: Pareto"<<std::endl;
    std::cout<<"4: Dijkstra"<<std::endl;
    std::cout<<"5: Bonus"<<std::endl;
    std::cin >> choix;

    if(choix == 1)
        std::cout << "Quitter..." << std::endl;

    else if(choix == 2)
    {
        std::cout<<"Prim..."<<std::endl;
        SvgFile svgout;
        ///PARTIE 1
        svgout.addText(75, 45, "Chargement du graphe");
        svgout.addText(500, 45, "Couts totaux (Prim) :");
        ///Choisir quel prime
        g.codePrim(0);
        //g.codePrimC2(0);

        ///Affichage prime
        g.dessinerGrapheChargement(&svgout);
        g.afficherPrime(&svgout);

    }

    else if(choix == 3)
    {
        std::cout<<"Pareto..."<<std::endl;
        SvgFile svgout;
        ///PARTIE 2
        g.dessinerGrapheChargementPareto(&svgout);
        g.codePareto(&svgout);
        g.dessinCalculGraphePareto(&svgout);

        //g.vecteurInter(&svgout);
    }

    else if(choix == 4)
    {
        std::cout<<"Dijkstra..."<<std::endl;
        SvgFile svgout;
        ///PARTIE 3
        g.compteurDijkstra();
        g.dessinerGrapheChargementDijkstra(&svgout);

    }

    else if(choix == 5)
    {
        std::cout<<"Bonus..."<<std::endl;
        SvgFile svgout;
        ///PARTIE BONUS
        g.dessinerGrapheChargementBonus(&svgout);
        g.codeBonus(&svgout);
        g.dessinCalculGrapheBonus(&svgout);


        ///Plus petite moyenne
        //g.dessinerGrapheChargementPareto(&svgout);
        //g.codePareto(&svgout);
        //g.dessinCalculHeuristique(&svgout);

    }
    else
        std::cout << "Erreur..."<<std::endl;

    return 0;
}
