#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/cubetown.txt"};
    g.dessiner(&svgout);
    return 0;
}
