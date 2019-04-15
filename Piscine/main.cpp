#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/manhattan.txt", "files/manhattan_weights_0.txt"};
    g.dessinerGrapheChargement(&svgout);


    return 0;
}
