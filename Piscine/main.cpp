#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/triville.txt", "files/triville_weights_0.txt"};

    ///modifier ici pour gerer l'affiche
    g.dessinerGrapheChargement(&svgout);
    //g.codePrim("0", &svgout);
    g.codePrimC2("0", &svgout);


    return 0;
}
