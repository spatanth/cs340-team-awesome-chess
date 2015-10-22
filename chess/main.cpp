#include "mainwindow.h"
#include "twochessboard.h"


#include <QtGui/QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    QLabel topLevelLabel;
    QPixmap pixmap("/images.jpg");
    topLevelLabel.setPixmap(pixmap);
    mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
    mainWindow.showExpanded();

    return app.exec();
}
