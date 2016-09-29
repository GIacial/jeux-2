#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfacecombat.h"
#include "menuprincipal.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void sauvegarde();
    void MenuPrincipalToInterfaceCombat();
    void nouvelleConfigEquipeHero(QList<Hero *> nouvelleEquipe);
    //debug slot
    void heroToLvlMax();//permet de mettre le hero au niveau max
private:
    QWidget* conteneurCentralWidget;
    QGridLayout* conteneurCentralWidget_Layout;
    InterfaceCombat* interfaceCombat;
    MenuPrincipal* menuPrincipal;
    int nbHero;
    QList<Hero*> equipe;
    QString NomEquipe;
    //fonction
    void selectNbHeroMonstre();
    //gestion de fichier
    void chargement();
    void creationEquipe();
    bool heroExistDeja(int i) const;


};

#endif // MAINWINDOW_H
