#ifndef QWIDGETCLIQUABLE_H
#define QWIDGETCLIQUABLE_H

#include <QWidget>
#include <entite.h>

class QWidgetCliquable : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetCliquable(Entite* entiteLier,QWidget *parent = 0);
    Entite* getEntiteLier();


signals:
    void clicked(Entite*);
    void clicked();
public slots:

protected:
    void mousePressEvent(QMouseEvent*);
private:
    Entite* entiteContenu;
};

#endif // QWIDGETCLIQUABLE_H
