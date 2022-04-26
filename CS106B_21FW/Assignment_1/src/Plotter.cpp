#include "Plotter.h"
#include"strlib.h"
using namespace std;

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    /* Initially pen is up, */

    string line;
    /* pen up */
    int flag = 0;
    /* initial pen position */
    double x0 = 0, y0 = 0;
    /* dest coordiante */
    double x1 = 0, y1 = 0;

    struct PenStyle style = {1, "green"};

    for(line; getline(input, line);)
    {
        line = toLowerCase(line);

        /* first split string */
        Vector<string>data;
        data = stringSplit(line," ");

        if(startsWith(data[0],"penup") && flag == 1 )
        {
            flag = 0;
        }
        else if(startsWith(data[0],"pendown") && flag == 0)
        {
            flag = 1;
        }
        /* Move Absolute */
        else if(startsWith(data[0],"moveabs"))
        {
            x1 = stringToReal(data[1]);
            y1 = stringToReal(data[2]);

            if(flag==1)
            {
                drawLine(x0, y0, x1, y1, style);
            }

            x0 = x1;
            y0 = y1;
        }

        /* Move Relative */
        else if(startsWith(data[0],"moverel"))
        {
            x1 = stringToReal(data[1])+x0;
            y1 = stringToReal(data[2])+y0;

            if(flag==1)
            {
                drawLine(x0, y0, x1, y1, style);
            }
            x0 = x1;
            y0 = y1;
        }

        /* PenColor */
        else if(startsWith(data[0],"pencolor"))
        {
           style.color = data[1];
        }
        /* PenWidth */
        else if(startsWith(data[0],"penwidth"))
        {
           style.width = stringToReal(data[1]);
        }

    }

    return;
}
