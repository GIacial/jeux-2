#include "qwidgetcliquable.h"

QWidgetCliquable::QWidgetCliquable(Entite* entiteLier,QWidget *parent) :
    QWidget(parent)
{
    entiteContenu=entiteLier;
}

void QWidgetCliquable::mousePressEvent(QMouseEvent *){
    emit clicked(entiteContenu);
    emit clicked();
}

Entite* QWidgetCliquable::getEntiteLier(){
    return entiteContenu;
}
