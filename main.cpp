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
    sRay s;

    s.init();
    s.show();

    return a.exec();
}
