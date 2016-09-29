#include "ennemie.h"

Ennemie::Ennemie(int level, int baseVie, int baseMana, int baseAP, int baseAM, int baseDP, int baseDM, int baseVitesse, QString nom, bool Magicien)
{
    affiniteMagie=Magicien;
    this->setStatBaseVie(baseVie);
    this->setStatBaseMana(baseMana);
    this->setStatBaseAttaquePhysique(baseAP);
    this->setStatBaseAttaqueMagique(baseAM);
    this->setStatBaseDefenseMagique(baseDM);
    this->setStatBaseDefensePhysique(baseDP);
    this->setStatBaseVitesse(baseVitesse);
    this->setLevel(level);
    xpWhenVaincu=1;

    //mise en place de nom
    if(nom=="Monstre"){
       this->Entite::setNomEntite(randomNom());

    }
    else{
        this->Entite::setNomEntite(nom);
    }
    this->initialisationCombat();
    this->soinAuberge();

}


//action

    QString Ennemie::actionIA(Entite &cible){
        QString retour="";
        if(this->getVie()!=0){
                if(affiniteMagie){//ennemie magique
                    if(this->getVie()<=((double)(this->getStatBaseVie())/2) &&this->getMana()>=5 && rand()%100<=25){//si inf 50%vie max il se soigne
                       retour= technique_soin(*this);
                    }
                    else{
                        if(rand()%100<=20){
                            retour= randomSort(cible);
                        }
                        else{
                            retour= attaque::baseAttaque(*this,cible);
                        }
                    }
                }
                else{//ennemie non magique
                    if(rand()%100<=15){
                        retour= randomTech(cible);
                    }
                    else{
                        retour= attaque::baseAttaque(*this,cible);
                    }
                }
            }

        return retour;
    }

    //technique de monstre
    QString Ennemie::randomSort(Entite &cible){
        QString retour="";

        if(this->getNomEntite().contains("Goutelette")){
   //ia de Goutelette
            if(rand()%100<75 && this->getMana()>=5){
                retour=technique_Flamme(cible);
            }
            else{
                retour=attaque::defense(*this);
            }
        }
        else{
            if(this->getNomEntite().contains("Goute")){
   //ia de Goute
                if(rand()%100<85 && this->getMana()>=5){
                    retour=technique_Flamme(cible);
                }
                else{
                    retour=attaque::booster(*this,*this);
                }
            }
            else{if(this->getNomEntite().contains("Monte-Goutelette")){
  //ia de Monte-Goutelette
                    if(rand()%100<55 && this->getMana()>=5){
                        retour=technique_Flamme(cible);
                    }
                    else{
                        retour=attaque::bouclier(*this,*this);
                    }
                }
                else{
  //ia par default
               retour=attaque::defense(*this);
                }
            }
        }

        return retour;
    }

    QString Ennemie::randomTech(Entite &cible){
        QString retour="";
        if(this->getNomEntite().contains("Taupier")){
//ia de taupier
            retour=attaque::frappePuissante(*this,cible);
        }
        else{
            if(this->getNomEntite().contains("Taupelle")){
 //ia de taupelle
                if(rand()%100<70){
                  retour=attaque::frappePuissante(*this,cible);
                }
                else{
                   retour=attaque::defense(*this);
                }
            }
            else{
 //ia par default
               retour=attaque::defense(*this);
            }
        }
        return retour;
    }



    QString Ennemie::technique_soin(Entite &cible){
       QString retour="";
       if(this->getMana()>=150 && this->getLevel()>=25){
          retour=attaque::soinComplet(*this,cible);

       }
       else{
           if(this->getMana()>=45 && this->getLevel()>=15){
               retour= attaque::soinPuissant(*this,cible);
           }
           else{
               if(this->getMana()>=15 && this->getLevel()>=5){
                   retour= attaque::soinAvance(*this,cible);
               }
               else{
                   retour= attaque::soin(*this,cible);
               }
           }
       }

       return retour;
    }

    QString Ennemie::technique_Flamme(Entite &cible){
        QString retour="";
        if(this->getMana()>=50 && this->getLevel()>=50){
           retour=attaque::gigaFlamme (*this,cible);

        }
        else{
            if(this->getMana()>=25 && this->getLevel()>=35){
                retour= attaque::megaFlamme(*this,cible);
            }
            else{
                if(this->getMana()>=15 && this->getLevel()>=22){
                    retour= attaque::superFlamme(*this,cible);
                }
                else{
                    retour= attaque::flamme(*this,cible);
                }
            }
        }

        return retour;
    }

//autre fonction

    QString Ennemie::randomNom(){
        return randomNom(rand()%5);
    }

    QString Ennemie::randomNom(int numEnnemie){
        QString retour="";
        switch(numEnnemie){//don de nom
        case 0:retour="Taupier";
            affiniteMagie=false;
            tabStatLevelUp[0]=10;//vie au lv up
            tabStatLevelUp[1]=1;//Mana au lv up
            tabStatLevelUp[2]=1;//attaque Magique au lv up
            tabStatLevelUp[3]=3;//attaque Physique au lv up
            tabStatLevelUp[4]=3;//def mag au lv up
            tabStatLevelUp[5]=3;//def phy au lv up
            tabStatLevelUp[6]=1;//Vitesse au lv up
            xpWhenVaincu=3;//xp gagne en le tuant
                break;
        case 1:retour="Goutelette";
            affiniteMagie=true;
            tabStatLevelUp[0]=4;//vie au lv up
            tabStatLevelUp[1]=2;//Mana au lv up
            tabStatLevelUp[2]=1;//attaque Magique au lv up
            tabStatLevelUp[3]=3;//attaque Physique au lv up
            tabStatLevelUp[4]=1;//def mag au lv up
            tabStatLevelUp[5]=1;//def phy au lv up
            tabStatLevelUp[6]=2;//Vitesse au lv up
            xpWhenVaincu=2;//xp gagne en le tuant
                break;
        case 2:retour="Goute";
            affiniteMagie=true;
            tabStatLevelUp[0]=6;//vie au lv up
            tabStatLevelUp[1]=3;//Mana au lv up
            tabStatLevelUp[2]=3;//attaque Magique au lv up
            tabStatLevelUp[3]=2;//attaque Physique au lv up
            tabStatLevelUp[4]=3;//def mag au lv up
            tabStatLevelUp[5]=3;//def phy au lv up
            tabStatLevelUp[6]=2;//Vitesse au lv up
            xpWhenVaincu=4;//xp gagne en le tuant
            break;
        case 3:retour="Monte-Goutelette";
            affiniteMagie=true;
            tabStatLevelUp[0]=10;//vie au lv up
            tabStatLevelUp[1]=5;//Mana au lv up
            tabStatLevelUp[2]=1;//attaque Magique au lv up
            tabStatLevelUp[3]=7;//attaque Physique au lv up
            tabStatLevelUp[4]=3;//def mag au lv up
            tabStatLevelUp[5]=4;//def phy au lv up
            tabStatLevelUp[6]=3;//Vitesse au lv up
            xpWhenVaincu=6;//xp gagne en le tuant
            break;
        case 4:retour="Taupelle";
            affiniteMagie=false;
            tabStatLevelUp[0]=2;//vie au lv up
            tabStatLevelUp[1]=4;//Mana au lv up
            tabStatLevelUp[2]=1;//attaque Magique au lv up
            tabStatLevelUp[3]=9;//attaque Physique au lv up
            tabStatLevelUp[4]=1;//def mag au lv up
            tabStatLevelUp[5]=5;//def phy au lv up
            tabStatLevelUp[6]=2;//Vitesse au lv up
            xpWhenVaincu=3;//xp gagne en le tuant
            break;
        default:retour="Source";
            affiniteMagie=rand()%100<50;
            tabStatLevelUp[0]=7;//vie au lv up
            tabStatLevelUp[1]=5;//Mana au lv up
            tabStatLevelUp[2]=4;//attaque Magique au lv up
            tabStatLevelUp[3]=4;//attaque Physique au lv up
            tabStatLevelUp[4]=3;//def mag au lv up
            tabStatLevelUp[5]=3;//def phy au lv up
            tabStatLevelUp[6]=2;//Vitesse au lv up
            xpWhenVaincu=1;//xp gagne en le tuant
            break;
        }
       emit refreshImage("ImagePng/"+retour+".png",this);
        return retour;
    }

    void Ennemie::nouveauEnnemie(int level, int baseVie, int baseMana, int baseAP, int baseAM, int baseDP, int baseDM, int baseVitesse){
        this->setStatBaseVie(baseVie);
        this->setStatBaseMana(baseMana);
        this->setStatBaseAttaquePhysique(baseAP);
        this->setStatBaseAttaqueMagique(baseAM);
        this->setStatBaseDefensePhysique(baseDP);
        this->setStatBaseDefenseMagique(baseDM);
        this->setStatBaseVitesse(baseVitesse);
        this->setLevel(1);
        this->Entite::setNomEntite(this->randomNom());//donne le nom + affinite magie

        for(int i=1;i<level;i++){
            this->levelUp();
        }

        this->initialisationCombat();//reset les buff et les stat
        this->soinAuberge();


    }

//recuperation


int Ennemie::getXpWhenVaincu()const{
    return xpWhenVaincu;
}



