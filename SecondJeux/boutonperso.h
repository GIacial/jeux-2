#ifndef BOUTONPERSO_H
#define BOUTONPERSO_H

#include <QWidget>
#include<QtWidgets>
#include<QPushButton>
#include<QIcon>
#include"hero.h"

class BoutonPerso : public QPushButton
{
    Q_OBJECT

public:
    explicit BoutonPerso(QString texte,QWidget *parent=0);

signals:
    void clickedGetLevel(int);
private:
  void mousePressEvent(QMouseEvent *);//savoir quand clicquer desus
  void mouseReleaseEvent(QMouseEvent *);//savoir quand relager

};

#endif // BOUTONPERSO_H
