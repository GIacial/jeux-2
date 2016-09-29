#ifndef FENETREMAGIE_H
#define FENETREMAGIE_H

#include <QScrollArea>
#include<QtWidgets>
#include<c++/vector>
#include<c++/cmath>

class FenetreMagie : public QScrollArea
{
    Q_OBJECT
public:
     FenetreMagie();
    //  action
    void creationBoutton(QString texte,QString toolTipTexte="",int level=0);
    //recup
    QPushButton* getBouton(int place);//permet de recup le bouton x
    QPushButton* getLastBouton();//permet de recup le dernier butoon

signals:
    void affiche(FenetreMagie*);
public slots:
    void show(int level);
private:
    QGridLayout* principal_layout;//layout principal
    QWidget* principal;
    QList<QPushButton*> listeBoutton;//liste des bouton
    QList<int>listeNiveau;//liste de lv associe au button

};

#endif // FENETREMAGIE_H
