#ifndef INTERFACECOMBAT_H
#define INTERFACECOMBAT_H

#include <QScrollArea>
#include<QtWidgets>
#include<c++/vector>
#include<c++/ctime>
#include<c++/cstdlib>
#include<QMessageBox>
#include "ennemie.h"
#include "hero.h"
#include "fenetremagie.h"
#include"attaque.h"
#include"systemcombat.h"
#include"qwidgetcliquable.h"

class InterfaceCombat : public QScrollArea
{
    Q_OBJECT
public:
    //constructeur
    explicit InterfaceCombat(QList<Hero*> futurEquipe, int NbEnnMax=5);
    //affectation
    void setEquipe(QList<Hero*> nouvelleEquipe);

signals:
    void sauvegarde();
    void finCombat();

public slots:
    void show();
    void hide();
    void afficheBoutonAction();
    void auberge_validation();//soigne les hero et remet a 1 le multiplicateur xp
    void nouveauCombat();//permet de lancer un nouveau combat
    void afficheStatCible();//permet d'afficher les stat de la cible
    void afficheStat(Entite* Lentite);
    void afficheTexteDansResume(QString texte);//ajoute une phrase dans le resume
    void selectionCible(Entite* cibleWidget);//permet de choisir une entite comme cible
    void showMagie();
    void showTech();
    void fermeAutreMagTech(FenetreMagie* fenetre=0);
    void netoyageResume();//netoie le resumé
    //slot de refresh
    void updateTextCible();//mets a jour le texte de la cible
    void updateAffichageMonstre(int nbMonstre);//mets/enleve les widget des monstre participant/absent au combat
    void updatePrediction(QList<QString> Textprediction);//mets a jour les prediction de tour
        //update hero
    void updateVieHero(int actuel,int max,Entite* Lentite);
    void updateManaHero(int actuel, int max,Entite* Lentite);
    void updateNomHero(QString nom,Entite* Lentite);
        //update monstre
    void updateNomMonstre(QString nom,Entite* Lentite);
    void updateVieMonstre(int actuel,int max,Entite* Lentite);
    void updateImageMonstre(QString lien , Entite* Lentite);

    //slot de signal
    void signal_FinCombat();//envoi le signal de fin de combat
    void signal_Sauvegarde();//envoi le signal de fin de combat

private:
    //variable
        //data
        QList<Ennemie*> adversaire;// adversaire
        QList<Hero*>equipe;//liste hero
        SystemCombat* systemDeCombat;
        bool equipeModifier;//permet de savoir si l'equipe a ete changer
        //interface
            //conteneur global
        QWidget* principal;//conteneur de tout
        QGridLayout* principalLayout;//Layout de principal   
        QTextEdit* resume;//resume les action des entite
        QScrollBar* resume_ScrolBar;
        QScrollArea* groupeEnnemie;//contient l'affichage des ennemie
        QWidget* groupeEnnemie_conteneur;
        QHBoxLayout* groupeEnnemie_LayoutConteneur;
        QScrollArea* groupeHero;//contient l'affichage des ennemie
        QWidget* groupeHero_conteneur;
        QHBoxLayout* groupeHero_LayoutConteneur;
        QList<FenetreMagie*> magie;//contient les fenetre de magie et technique
        QList<QLabel*> predictionTour;//contient les nom dans l'ordre d'action
        QLabel* cible_texte;//affiche le nom de la cible
        QWidget* conteneur_BoutonAction;
            //conteneur des widget Hero
        QList<QWidgetCliquable*> hero_conteneurCliquable;
        QList<QProgressBar*> hero_barVie;
        QList<QProgressBar*> hero_barMana;
        QList<QLabel*> hero_TextNom;
        QList<QLabel*> hero_TextVie;
        QList<QLabel*> hero_TextMana;
        QList<QGridLayout*> hero_Layout;
            //conteneur des widget ennemie
        QList<QWidgetCliquable*> monstre_conteneurCliquable;
        QList<QProgressBar*> monstre_barVie;
        QList<QLabel*> monstre_TextNom;
        QList<QGridLayout*> monstre_Layout;
        QList<QPixmap> monstre_Image;
        QList<QLabel*> conteneur_image;


    //fonction
        void setConnectionAttaqueHeroClass(int numClass);
        //action
        void creationCiblageAdversaire(int nbAdversaire);//lie et cree les widget des monstre au ciblage
        //lien
        void hero_apprend_Magie(int niveauApprentissage,int numHero,QString nomMagie,QString descriptionMagie,const char* slot);
        void hero_apprend_Tech(int niveauApprentissage, int numHero, QString nomTech, QString descriptionTech, const char* slot);
        //autre
        void pause(int temps);

};

#endif // INTERFACECOMBAT_H
