#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));//permet d'avoir un vrai aléatoire
    MainWindow w;
    w.show();


    return a.exec();
}

/*
 Amelioration



  */

