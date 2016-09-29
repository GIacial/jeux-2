#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QScrollArea>
#include<QtWidgets>
#include"hero.h"
#include "afficheurpvmagie.h"

class MenuPrincipal : public QScrollArea
{
    Q_OBJECT
public:
    explicit MenuPrincipal(QList<Hero*> NouvelleEquipe, QWidget *parent = 0);

signals:
    void combatAleatoire();
    void passageAuberge();
    void nouvelleConfigEquipe(QList<Hero*>);
public slots:
    void show();
private slots:
    void lanceCombatAleatoire();
    void lancePassageAuberge();
    void echangeHero(Entite* entiteCliquer);
    void afficherResumer();
private:
    QWidget* menuPrincipal_conteneur;
    QGridLayout* menuPrincipal_conteneurLayout;
    QPushButton* lance_CombatAlea;
    QPushButton* lance_Auberge;
    QPushButton* afficheResume;
    QList<Hero*> equipe;
    int equipe_memoIndicePremierHero;
    //afficheur hero
    QList<AfficheurPvMagie*> afficheurEquipe;
    //fonction
    void refresh_afficheurEquipe(int i);
    void refresh_afficheurEquipe();
    bool equipeEnVie();
};

#endif // MENUPRINCIPAL_H
