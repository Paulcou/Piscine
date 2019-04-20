#include <iostream>
#include "graphe.h"

int main()
{
    SvgFile svgout;

    Graphe g{"files/triville.txt", "files/triville_weights_0.txt"};

    ///PARTIE 1

    /// # Choisir quel prime
    //g.codePrim(0);
    //g.codePrimC2(0);

    /// # Affichage prime
    //g.dessinerGrapheChargement(&svgout);
    //g.afficherPrime(&svgout);
    //svgout.addText(75, 45, "Chargement du graphe");
    //svgout.addText(500, 45, "Couts totaux (prim) :");

    ///PARTIE 2
    g.dessinerGrapheChargementPareto(&svgout);
    g.codePareto(&svgout);
    g.dessinCalculGraphePareto(&svgout);

    ///PARTIE 3
    /**g.compteurDjikstra();
    g.dessinerGrapheChargementDjikstra(&svgout);
    **/

    ///PARTIE BONUS

    /// # Heuristique
    //g.dessinCalculHeuristique(&svgout);

    return 0;
}
