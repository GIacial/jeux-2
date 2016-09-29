#ifndef ENNEMIE_H
#define ENNEMIE_H

#include"entite.h"
#include"attaque.h"

class Ennemie : public Entite
{
    Q_OBJECT
public:
    Ennemie(int level=1, int baseVie=10, int baseMana=10, int baseAP=1, int baseAM=1, int baseDP=1, int baseDM=1, int baseVitesse=1, QString nom="Monstre", bool Magicien=false);

    //action
    QString actionIA(Entite& cible);//permet a l'ennemie de choisir son action
    QString randomSort(Entite& cible);//choisi aleatoirement un sort
    QString randomTech(Entite& cible);//choisi sort alea
    QString randomNom();//permet de donner un nom aleatoire
    QString randomNom(int numEnnemie);//permet de faire une enneie du num indiquer
    void nouveauEnnemie(int level=1, int baseVie=10, int baseMana=10, int baseAP=1, int baseAM=1, int baseDP=1, int baseDM=1, int baseVitesse=1);//permet de modifier un ennemie pour le changer en un autre

    //technique des monstre
    QString technique_soin(Entite& cible);//permet a l'ennemie de lancer le sort soin
    QString technique_Flamme(Entite &cible);

    //recuperation
    int getXpWhenVaincu()const;//permet de svoir combien xp on gagne en le tuant

signals:
             void refreshImage(QString lienImage,Entite* cetteEntite);
private:
    bool affiniteMagie;
    int xpWhenVaincu;
};

#endif // ENNEMIE_H
