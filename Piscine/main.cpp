#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/cubetown.txt", "files/cubetown_weights_0.txt"};

    ///PARTIE 1
    //svgout.addText(75, 45, "Chargement du graphe");
    //svgout.addText(500, 45, "Couts totaux (prim) :");


    ///modifier ici pour gerer l'affiche
    g.dessinerGrapheChargement(&svgout);
    //g.codePrim("0");
    //g.codePrimC2("0");

    ///Affichage prime
    //g.afficherPrime(&svgout);

    ///PARTIE 2
    g.codePareto();
    //g.dessinerGrapheChargementPareto(&svgout);



    return 0;
}
