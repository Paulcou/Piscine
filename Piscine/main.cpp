#include <iostream>
#include "graphe.h"

int main()
{
    std::cout<<"Chargement..."<< std::endl;
    /**std::string nom, weight;
    std::cout<<"choisir nom fichier"<< std::endl;
    std::cin >>nom;
    std::cout << "choisir weight fichier"<< std::endl;
    std::cin >> weight;**/

    //Graphe g{"files/"+nom+".txt", "files/"+nom+"_weights_"+weight+".txt"};
    Graphe g{"files/triville.txt", "files/triville_weights_0.txt"};
    int choix;

    do
    {
        std::cout<<"MENU"<<std::endl;
        std::cout<<"1: quitter"<<std::endl;
        std::cout<<"2: prime"<<std::endl;
        std::cout<<"3: pareto"<<std::endl;
        std::cout<<"4: dijstra"<<std::endl;
        std::cout<<"5: bonus"<<std::endl;
        std::cin >> choix;

        if(choix == 1)
            std::cout << "quitter..." << std::endl;

        else if(choix == 2)
        {
            std::cout<<"prime..."<<std::endl;
            SvgFile svgout;
            ///PARTIE 1
            svgout.addText(75, 45, "Chargement du graphe");
            svgout.addText(500, 45, "Couts totaux (prim) :");
            ///Choisir quel prime
            g.codePrim(0);
            //g.codePrimC2(0);

            ///Affichage prime
            g.dessinerGrapheChargement(&svgout);
            g.afficherPrime(&svgout);

        }

        else if(choix == 3)
        {
            std::cout<<"pareto..."<<std::endl;
            SvgFile svgout;
            ///PARTIE 2
            g.dessinerGrapheChargementPareto(&svgout);
            g.codePareto(&svgout);
            g.dessinCalculGraphePareto(&svgout);

            g.vecteurInter(&svgout);
        }

        else if(choix == 4)
        {
            std::cout<<"dijstra..."<<std::endl;
            SvgFile svgout;
            ///PARTIE 3
            g.compteurDijkstra();
            g.dessinerGrapheChargementDijkstra(&svgout);

        }

        else if(choix == 5)
        {
            std::cout<<"bonus..."<<std::endl;
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
            std::cout << "erreur..."<<std::endl;

    }
    while(choix!=1);

    return 0;
}
