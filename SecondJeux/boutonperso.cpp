#include "boutonperso.h"


BoutonPerso::BoutonPerso(QString texte, QWidget* parent)
{
    this->setText(texte);
    this->setParent(parent);
}


void BoutonPerso::mousePressEvent(QMouseEvent *){
  emit clicked();
  this->setStyleSheet("BoutonPerso{border-style:inset}");
}

void BoutonPerso::mouseReleaseEvent(QMouseEvent *){
    this->setStyleSheet("BoutonPerso{border-style:outset}");
}
