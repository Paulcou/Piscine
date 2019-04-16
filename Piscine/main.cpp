#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/cubetown.txt", "files/cubetown_weights_0.txt"};

    ///modifier ici pour gerer l'affiche
    g.dessinerGrapheChargement(&svgout);
    g.codePrim("0");
    //g.codePrimC2("0");

    ///Affichage prime
    g.afficherPrime(&svgout);


    return 0;
}
