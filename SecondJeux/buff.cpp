#include "buff.h"

buff::buff(QString nomEffect, double coefAp, double coefAm, double coefDp, double coefDm, double coefV, int nbTourEffect, int degatTour)
{
    nom=nomEffect;
    effect[0]=coefAp;
    effect[1]=coefAm;
    effect[2]=coefDp;
    effect[3]=coefDm;
    effect[4]=coefV;
    nbTour=nbTourEffect;
    degatParTour=degatTour;
}

int buff::decompte(){
    if(nbTour!=-1){
        nbTour--;
    }
    return nbTour;
}

//recup

QString buff::getNom()const{
    return nom;
}

double buff::getCoefEffect(int statCible)const{
    double retour=1;//return 1 si negatif
    if(effect[statCible]>0){
       retour= effect[statCible];
    }
    return retour;
}

bool buff::getCoefActif(int statCible) const{
    return effect[statCible]>0;
}

int buff::getNbTour()const{
    return nbTour;
}

QString buff::getNbTourText()const{
    QString retour="";
    if(nbTour==-1){
        retour="Aucune durée";
    }
    else{
        retour="Reste encore "+QString::number(nbTour)+" tour";
    }
    return retour;
}

int buff::getDegatTour()const{
    return degatParTour;
}

void buff::setNbTour(int nombreTour){
    nbTour=nombreTour;
}

void buff::setCoefEffect(int coefficentEffect, int statCible){
    effect[statCible]=coefficentEffect;
}

//buff predefini

buff BuffPredefini::getBuffBouclier(){
    return buff("Bouclier",-1,-1,2);
}

buff BuffPredefini::getBuffBlindage(){
    return buff("Blindage",-1,-1,-1,2);
}

buff BuffPredefini::getBuffBooster(){
    return buff("Booster",-1,-1,-1,-1,2);
}

buff BuffPredefini::getBuffDeculpo(){
    return buff("Deculpo",2);
}

buff BuffPredefini::getBuffCanalisationMagique(){
    return buff("Canalisation Magique",-1,2);
}

buff BuffPredefini::getBuffDefense(){
    return buff("Defense",-1,-1,2,-1,-1,1);
}

buff BuffPredefini::getForceDivine(){
    return buff("Force Divine",2,2,2,2,2);
}

buff BuffPredefini::getBuffPoison(QString nom,int nbTour, int dommageTour){
    return buff(nom,-1,-1,-1,-1,-1,nbTour,dommageTour);
}
