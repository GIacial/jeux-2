#ifndef SYSTEMCOMBAT_H
#define SYSTEMCOMBAT_H

#include <QObject>
#include<c++/ctime>
#include<c++/cstdlib>
#include "ennemie.h"
#include "hero.h"
#include "fenetremagie.h"
#include"attaque.h"

class SystemCombat : public QObject
{
    Q_OBJECT
public:
    //constructeur
    explicit SystemCombat(QList<Hero*> futurEquipe, int NbEnnMax=5);
    //affectation
    void setEquipe(QList<Hero*> nouvelleEquipe);
    void nouveauCombat();//permet de lancer un nouveau combat
    void auberge_validation();//soigne les hero et remet a 1 le multiplicateur xp
    void selectionCible(Entite* cibleWidget);//permet de choisir l'ennemie clique comme cible
    //recuperation
    QList<Ennemie*> getEquipeMonstre();
    Hero* getHeroenAction();
    Entite* getCible();

signals:
    void sauvegarde();//signale que le system veut sauvegarder
    void finCombat();//signale la fin d'un combat
    void nbMonstreDansLeNouveauCombat(int nbMonstre);//signale le nb de monstre du combat du system
    void afficheTexteDansResume(QString texte);//signale que le system veut ajouter une phrase
    void resultatPrevision(QList<QString> res);//signale les prevision du system
    void demandeUpdateCible();//signale qu'on a changer de cible en interne du system
    void afficheBoutonAction();
    void enleveBoutonAction();

public slots:

    //action hero
        void actionHero_attaqueBasic();//permet de faire une attaque P de base
        void actionHero_defense();

        //magie
        void actionHero_soin();//permet de faire de petit soin
        void actionHero_soinAvance();//permet de faire des soin moyen
        void actionHero_soinPuissant();//permet de faire de grand soin
        void actionHero_soinComplet();//soigne completement
        void actionHero_rappel();//permet de reanimer a 50% de vie
        void actionHero_ressurection();//reanime toute la vie des mort
        void actionHero_bouclier();
        void actionHero_blindage();
        void actionHero_booster();
        void actionHero_deculpo();
        void actionHero_canalisationMagique();
        void actionHero_purification();
         void actionHero_flamme();//lance le sort flamme
         void actionHero_superFlamme();
         void actionHero_megaFlamme();
         void actionHero_gigaFlamme();
         void actionHero_crame();
         void actionHero_superCrame();
         void actionHero_megaCrame();
         void actionHero_gigaCrame();
         void actionHero_superBouclier();
         void actionHero_superBlindage();
         void actionHero_superBooster();
         void actionHero_omnisoin();
         void actionHero_multisoin();
         //tech
         void actionHero_frappePuissante();
         void actionHero_BriseCrane();
         void actionHero_ryuken();
         void actionHero_FrappeCirculaire();
         void actionHero_analyse();
         void actionHero_seisme();
         void actionHero_deprime();
         void actionHero_lameEmpoisonner();
         void actionHero_frappeRapide();
         void actionHero_nuagePoison();
         void actionHero_frappeAstral();
         void actionHero_lameDragon();
private:
    //variable
        Hero* heroPrincipal;//hero qui doit agir
        QList<Ennemie*> adversaire;// adversaire
        QList<Hero*>equipe;//liste hero
        Entite* cible;//cible de l'attaque
        int multiplicateurXp;//multiplie xp plus au fait de combat d'affiler
        int nbAdversaireDansCombat;//permet de savoir combien de monstre sont present dans le combat
        bool combatenCours;//permet de savoir si le combat est en cours
    //fonction
        //recuperation
        QList<Entite *> getListeCible();
        QList<Entite*> getListeHero();
        Hero* getHeroCible();//permet a l'ennemie de savoir qui attaquer
        //action
        void creationAdversaire(int nbAdversaire=1);//permet de créé des monstres
        void initialisationCible();//mets a jour la cible en fin de combat
        void finActionHero();//code a effectuer a la fin d'une attaque
        void randomEnnemie(int nbAdversaire, Ennemie *monstre);//cree et renvoi des ennemie random
        void actionEnnemie();//action des ennemie
        void celerite();//fait celerite-ajout() a toute les entite


        //calcul
        int calculXp();//calcul xp gagné
        void prediction();//predi les tour d'action
         //verification
        bool verificationEnnemieVivant()const;//verifie s'il reste un monstre en vie
        bool verificationEquipeVivant()const;//verifie s'il reste un hero vivant
        bool verificationFinCombat();//verifie si le combat est fini


};

#endif // SYSTEMCOMBAT_H
