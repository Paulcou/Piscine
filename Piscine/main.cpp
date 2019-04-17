#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};
    svgout.addText(75, 45, "Chargement du graphe");
    svgout.addText(500, 45, "Couts totaux (prim) :");


    ///modifier ici pour gerer l'affiche
    g.dessinerGrapheChargement(&svgout);
    //g.codePrim("0");
    //g.codePrimC2("0");
    g.codePareto();

    ///Affichage prime
    //g.afficherPrime(&svgout);


    return 0;
}
