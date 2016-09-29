#ifndef BUFF_H
#define BUFF_H

#include<QString>

class buff
{
public:
    buff(QString nomEffect,double coefAp=-1,double coefAm=-1,double coefDp=-1,double coefDm=-1,double coefV=-1,int nbTourEffect=-1,int degatTour=0);
    /*
                                          nbTour -1=infini
                  0=aP                  0=fini
                  1=am                  x=nbtour restant
                  2=dp
                  3=dm
                  4=v
    */
    int decompte();//enleve un tour
//recup
    QString getNom()const;
    double getCoefEffect(int statCible)const;
    int getNbTour()const;
    QString getNbTourText()const;
    int getDegatTour()const;
    bool getCoefActif(int statCible)const;
    void setNbTour(int nombreTour);
    void setCoefEffect(int coefficentEffect,int statCible);
private:
    QString nom;
    double effect[5];//coef de l'effect
    int nbTour;
    int degatParTour;

};

class BuffPredefini{
 public:
    static buff getBuffBouclier();
    static buff getBuffBlindage();
    static buff getBuffBooster();
    static buff getBuffDeculpo();
    static buff getBuffCanalisationMagique();
    static buff getBuffDefense();
    static buff getForceDivine();
    static buff getBuffPoison(QString nom, int nbTour, int dommageTour);
};


#endif // BUFF_H
