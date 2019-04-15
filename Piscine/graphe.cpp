#include <fstream>
#include <iostream>
#include "graphe.h"

Graphe::Graphe(std::string nomFichier)
{
    /// Nous cherchons si le fichier est de type weight ou non.

    bool weightType;

    if (nomFichier.find('_') != std::string::npos)
        weightType = true;

    else
        weightType = false;

    if(weightType == false)
    {
        ///Lecture des sommets
        std::ifstream ifs{nomFichier};
        if (!ifs)
            throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
        int ordre;
        ifs >> ordre;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture ordre du graphe");
        std::string id;
        double x,y;

        for (int i=0; i<ordre; ++i)
        {
            ifs>>id;
            if(ifs.fail())
                throw std::runtime_error("Probleme lecture données sommet");
            ifs>>x;
            if(ifs.fail())
                throw std::runtime_error("Probleme lecture données sommet");
            ifs>>y;
            if(ifs.fail())
                throw std::runtime_error("Probleme lecture données sommet");

            m_sommets.insert({id,new Sommet{id,x,y}});
        }


        ///Lecture des arretes
        if (!ifs)
            throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
        int nbarretes;
        ifs >> nbarretes;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture ordre du graphe");

        std::string idarrete;
        std::string iddep;
        std::string idfin;
        double x1, x2, y1, y2;


        for (int i=0; i<nbarretes; ++i)
        {
            ifs>>idarrete;
            if(ifs.fail())
                throw std::runtime_error("Probleme lecture données sommet");
            ifs>>iddep;
            if(ifs.fail())
                throw std::runtime_error("Probleme lecture données sommet");
            ifs>>idfin;
            if(ifs.fail())
                throw std::runtime_error("Probleme lecture données sommet");

            for(s : m_sommets)
            {
                if(s.second->getId() == iddep)
                {
                    x1 = s.second->getX();
                    y1 = s.second->getY();
                }
                else if(s.second->getId() == idfin)
                {
                    x2 = s.second->getX();
                    y2 = s.second->getY();
                }

            }

            m_arretes.insert({idarrete, new Arrete{Sommet{iddep, x1, y1}, Sommet{idfin, x2, y2}}});

        }
    }

}

void Graphe::dessiner(SvgFile* svg)
{
    for(auto s : m_sommets)
    {
        s.second->dessinerSommet(svg);
    }

    for(auto a : m_arretes)
    {
        a.second->dessinerArrete(svg);
    }
}

Graphe::~Graphe()
{
    //dtor
}
