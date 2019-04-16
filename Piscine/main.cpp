#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};
    g.dessinerGrapheChargement(&svgout);
    g.codePrim("0");
    g.codePrimC2("0");


    return 0;
}
