#include "sray.h"
#include <QApplication>


//Check for MS Visual C++ Compiler
#if defined _MSC_VER

    #include <algorithm>
    #define M_PI 3.141592653589793
    #define INFINITY 1e8

#endif

#define MAX_RAY_DEPTH 5

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Initializes an Object for the core Class
    sRay s;



    ///TOFIX - Output is rendered before the GUI is drawn.

    //Starts the Ray Tracing code and generates a .ppm file **before the GUI is drawn**
    s.init();

    //GUI is drawn now
    s.show();

    //Begins event loop
    return a.exec();
}
