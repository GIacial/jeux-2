#ifndef AFFICHEURPVMAGIE_H
#define AFFICHEURPVMAGIE_H

#include <QObject>
#include <QtWidgets>
#include"entite.h"

class AfficheurPvMagie : public QGroupBox
{
    Q_OBJECT
public:
    explicit AfficheurPvMagie( Entite* hero);
    void refresh();
    void setNewEntite(Entite* newEntite);

signals:
    void clicked(Entite*);
public slots:

protected:
    void mousePressEvent(QMouseEvent*);
private:
    Entite* entiteContenu;
    QHBoxLayout* afficheurEquipe_layoutPrincipal;
    QGridLayout* afficheurEquipe_layout;
    QLabel* afficheurEquipe_Classe;
    QProgressBar* afficheurEquipe_Vie;
    QLabel* afficheurEquipe_vie_texte;
    QProgressBar* afficheurEquipe_Mana;
    QLabel* afficheurEquipe_Mana_texte;
};

#endif // AFFICHEURPVMAGIE_H
