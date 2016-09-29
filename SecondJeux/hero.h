#ifndef HERO_H
#define HERO_H

#include "entite.h"



class Hero : public Entite
{
    Q_OBJECT
public:
    //constructeur
    Hero();

    //recup
    int getClasse()const;//recup la classe
    virtual QString getNomClass()const;
    //modif
    void setClass(int classeAMettre);

private:

    int classe;
    QString nomClasse;

    //fonction

    void setStatLevelUp();//met les stat des level up et stat de base
    //calcul texte
    QString apprentissageParNiveau()const;//permet de savoir quand le hero apprend quelquchose
    QString apprendParNiveau_Guerrier()const;
    QString apprendParNiveau_Mage()const;
    QString apprendParNiveau_Paladin()const;
    QString apprendParNiveau_Assasin()const;
    QString apprendParNiveau_Prete()const;

};

#endif // HERO_H
