#ifndef ATTAQUE_H
#define ATTAQUE_H

#include<c++/vector>
#include"entite.h"
#include"buff.h"


class attaque
{
public:
    //base
    static QString baseAttaque(Entite& lanceur,Entite& cible,int coef=1,bool magique=false,int mana=0,bool soin=false);//attaque la cible
    static QString baseAttaqueMultiCible(Entite& lanceur,QList<Entite*> cible,int coef=1,bool magique=false,int mana=0,bool soin=false);//attaque les cible
    static QString baseAjoutBuff(Entite &lanceur,Entite &cible,buff buffAjoute,int mana=0);//ajoute un buff a la cible
    static QString baseAjoutBuffMultiCible(Entite &lanceur, QList<Entite*> cible, buff buffAjoute, int mana);
    static QString baseAttaqueBuff(Entite& lanceur,Entite& cible,buff buffAjout,int coefAttaque,int chanceBuffAct,Entite& cibleBuff ,bool magique=false,int mana=0,bool soin=false);//attaque la cible et ajoute un buff a cibleBuff
    static QString baseAttaqueBuffMultiCible(Entite& lanceur,QList<Entite*> cible,buff buffAjout,int coefAttaque,int chanceBuffAct,bool magique=false,int mana=0,bool soin=false);
    static QString baseAttaqueVolMana(Entite& lanceur,Entite& cible,int manaVol,int coef=1,bool magique=false,int mana=0);//attaque la cible et lui vole du mana
    //soin
    static QString soin(Entite& lanceur,Entite& cible);
    static QString soinAvance(Entite &lanceur, Entite &cible);
    static QString soinPuissant(Entite &lanceur,Entite &cible);
    static QString soinComplet(Entite &lanceur,Entite &cible);
    static QString rappel(Entite &lanceur,Entite &cible);
    static QString ressurection(Entite &lanceur,Entite &cible);
    static QString multisoin(Entite &lanceur,QList<Entite*> cible);
    static QString omnisoin(Entite &lanceur,QList<Entite*> cible);
    //buff
        //magie
    static QString bouclier(Entite &lanceur,Entite &cible);
    static QString blindage(Entite &lanceur,Entite &cible);
    static QString booster(Entite &lanceur,Entite &cible);
    static QString deculpo(Entite &lanceur,Entite &cible);
    static QString canalisationMagique(Entite &lanceur,Entite &cible);
    static QString purification(Entite &lanceur,Entite &cible);
    static QString superBouclier(Entite &lanceur, QList<Entite*> cible);
    static QString superBlindage(Entite &lanceur,QList<Entite*> cible);
    static QString superBooster(Entite &lanceur,QList<Entite*> cible);
        //tech
    static QString defense(Entite &lanceur);

    //attaque
        //magie
    static QString flamme(Entite& lanceur,Entite& cible);
    static QString superFlamme(Entite& lanceur,Entite& cible);
    static QString megaFlamme(Entite& lanceur,Entite& cible);
    static QString gigaFlamme(Entite& lanceur,Entite& cible);
    static QString crame(Entite& lanceur,QList<Entite*> cible);
    static QString superCrame(Entite& lanceur,QList<Entite*> cible);
    static QString megaCrame(Entite& lanceur,QList<Entite*> cible);
    static QString gigaCrame(Entite& lanceur,QList<Entite*> cible);
        //technique
    static QString frappePuissante(Entite& lanceur,Entite& cible);
    static QString briseCrane(Entite& lanceur,Entite& cible);
    static QString ryuken(Entite& lanceur,Entite& cible);
    static QString frappeCirculaire(Entite& lanceur,QList<Entite*> cible);
    static QString Seisme (Entite& lanceur,QList<Entite*> cible);
    static QString deprime(Entite& lanceur,Entite& cible);
    static QString lameEmpoisonner(Entite& lanceur,Entite& cible);
    static QString FrappeRapide(Entite& lanceur,Entite& cible);
    static QString NuagePoison(Entite& lanceur,QList<Entite*> cible);
    static QString FrappeAstral(Entite& lanceur,Entite& cible);
    static QString lameDragon(Entite& lanceur,Entite& cible);
    //autre
    static QString Analyse(Entite& lanceur,Entite& cible);
};

#endif // ATTAQUE_H
