#include <QtMath>
#include <QtWidgets>
#include <iostream>
#include <fstream>

#include "ball.h"
#include "constants.h"
#include "obstacle.h"
#include "inkballscene.h"
#include "inkballview.h"
#include "mainmenuwindow.h"

using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainMenuWindow mainmenu;
    mainmenu.show();
    return app.exec();
}
