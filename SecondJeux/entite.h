#ifndef ENTITE_H
#define ENTITE_H

#include<c++/cmath>
#include<QObject>
#include<c++/vector>
#include"buff.h"

class Entite: public QObject
{
    Q_OBJECT
public:
    //constructeur
         Entite();//constructeur de base

    //action
         //(le virtual sert a prendre la fonction surcharge des enfant au lieux de ceux ci)
      virtual  bool recevoirDommage(int dommage);//permet d'enlever de la vie a l'entite et indique si elle est morte
      virtual  QString infligerDommage(Entite &cible, int dommage , bool ratePossible);//permet d'enlever de la vie a une autre entite
      virtual  QString initialisationCombat(int xpGain=0);//permet de mettre les stat combat a la valeur des stat base
      virtual  QString attaque(Entite &cible, int coeficient=1, bool attaqueMagique=false, int coutMana=0, bool soin=false, bool RateImpossible=false);//permet d'attaquer une cible avec une attque magique ou physique
      virtual  QString levelUp();//permet de level up une entite
      virtual  void celerite_reset();//met la celereite a 0
      virtual  void celerite_ajout();//ajout stat_combat_vitesse a celerite
      virtual void soinAuberge();//remonte le vie et mana
      virtual void finTour();//calcul de fin de tour
      virtual QString debutTour();//calcul de debut de tour
      virtual bool useMana(int manaUse);//permet d'enlever du mana
      virtual QString useSoin(double coef, bool complet=false);//permet de faire des soin
      virtual void afficheStat();
      virtual QString getNomClass()const;


    //calcul de valeur
        int calculDommagePhysique(Entite &cible, int coeficient=1,bool soin=false) const;//renvoi la valeur des dommage physique a infliger a la cible
        int calculDommageMagique(Entite &cible, int coeficient=1,bool soin=false) const;//renvoi la valeur des dommage magique a infliger a la cible
        int calculDommage(int cibleDef, int lanceurAtt, int coef=1, bool soin=false) const;//calcul les dommage
        bool isCritique()const;//renvoi si coup critique ou pas
        bool isRate()const;//renvoi si le coup echoue


    //augmentation de valeur
        QString augmentAttaquePhysique(double coef);//permet de monter l'attaque physique
        QString augmentAttaqueMagique(double coef);//permet de monter l'attaque magique
        QString augmentDefensePhysique(double coef);//permet de monter la defense physique
        QString augmentDefenseMagique(double coef);//permet de monter la defense magique
        QString augmentVitesse(double coef);//permet de monter la vitesse
        QString ajoutBuff(buff nouveauBuff);//permet d'ajouter un buff
        void supprimeBuff(int caseTableau);//permet de supp un buff
        void supprimeToutBuff();//permet de supp tout les buff

    //recuperation de valeur
        int getVie() const;//permet de recup la vie actuelle de entite
        int getMana() const;//permet de recup la mana actuelle de entite
        int getStatBaseVie() const;//permet de recup la vie de base de entite
        int getStatBaseMana() const;//permet de recup le mana de base de entite
        int getStatBaseAttaquePhysique()const;//permet de recup l'attaque physique de base
        int getStatBaseAttaqueMagique()const;//permet de recup l'attaque magique de base
        int getStatBaseDefensePhysique()const;//permet de recup la defense physique de base
        int getStatBaseDefenseMagique()const;//permet de recup la defense magique de base
        int getAttaquePhysique()const;//permet de recup l'attaque physique actuelle
        int getAttaqueMagique()const;//permet de recup l'attaque magique actuelle
        int getDefensePhysique()const;//permet de recup la defense physique actuelle
        int getDefenseMagique()const;//permet de recup la defense magique actuelle
        QString getNomEntite() const;//permet de recup le nom de l'entite
        int getLevel() const;//permet de recup le level de l'entite
        int getXp() const;//permet de recup xp actuelle de l'entite
        int getXpMax() const;// permet de recup xp necessaire pour level up
        int getCelerite()const;//permet de recup le taux d'action
        int getStatBaseVitesse()const;//permet de recup la vitesse de base
        int getVitesse()const;//renvoi la vitesse de combat
        QString getResumeEtat()const;//renvoi string des buff actif
    //modificateur des valeurs
        virtual  void setNomEntite(QString nom);//permet de changer le nom de l'entite
        void setStatBaseVie(int vieDeBase);//permet de changer la vie de base
        void setStatBaseMana(int manaDeBase);//permet de changer le mana de base
        void setStatBaseAttaquePhysique(int attaquePhysiqueBase);//permet de changer l'attaque physique de base
        void setStatBaseAttaqueMagique(int attaqueMagiqueBase);//permet de changer l'attaque magique de base
        void setStatBaseDefensePhysique(int defensePhysique);//permet de changer la defense physique de base
        void setStatBaseDefenseMagique(int defenseMagique);//permet de changer la defense magique de base
        void setLevel(int NouveauLevel);//mets le level a une valeur
        void setStatBaseVitesse(int vitesseDeBase);//permet de changer la vitesse de base
        void setXp(int nouveauXp);//permet de mettre de xp a une valeur


signals:
        void refreshVie(int vieReste, int vieTotal,Entite* cetteEntite);
        void refreshMana(int ManaReste,int ManaTotal,Entite* cetteEntite);
        void refreshNom(QString nouveauNom,Entite* cetteEntite);
        void demandeAfficheStat(Entite* cetteEntite);
        void mort();

protected:
        int tabStatLevelUp[7];//contient les stat au lv up
    //stat actuel
        int vie;// vie actuelle de entite
        int mana;// mana actuelle de entite
        int stat_combat_attaquePhysique;//attaque physique actuelle
        int stat_combat_attaqueMagique;// attaque magique actuelle
        int stat_combat_defensePhysique;//defense physique actuelle
        int stat_combat_defenseMagique;//defense magique actuelle
        int stat_combat_vitesse;//vitesse actuel
        int celerite;//possibilite d'action si celerite est plus fort(taux d'action)

   //stat de base
        int stat_base_vie;// vie de base de entite
        int stat_base_mana;//mana de base de entite
        int stat_base_attaquePhysique;//attaque physique de base
        int stat_base_defensePhysique;//defense physique de base
        int stat_base_attaqueMagique;//attaque magique de base
        int stat_base_defenseMagique;//defense magique de base
        int stat_base_vitesse;//vitesse de base
        QString nomEntite;//nom de l'entite
        int level;// niveau de l'entite
        int xp;//xp actuel de l'entite

    //etat
    QList<buff> listeEtat;//liste de tout les etat

};

#endif // ENTITE_H
