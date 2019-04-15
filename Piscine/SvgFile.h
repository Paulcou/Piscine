#ifndef SVGFILE_H
#define SVGFILE_H

#include <string>
#include <fstream>
#include <set>

constexpr char defcol[] = "black";

class SvgFile
{
    public:
        SvgFile(std::string _filename = "output.svg", int _width=1000, int _height=800);
        ~SvgFile();

        void addDisk(double x, double y, double r, std::string color=defcol);
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);
        void addEllipse(double x, double y, double rx, double ry, double opacity , std::string color= defcol);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);

        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);

        void addRect(double x1, double y1, double largeur, double hauteur, std::string colorFill=defcol,
                      double opacite = 1);
        void addRect2(double x1, double y1, double x2, double y2,
                       double x3, double y3,
                       double x4, double y4, std::string colorFill=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        SvgFile(const SvgFile&) = delete;
        SvgFile& operator=(const SvgFile&) = delete;

        static bool s_verbose;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};


#endif // SVGFILE_H
