#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/triville.txt"};
    g.dessiner(&svgout);
    return 0;
}
