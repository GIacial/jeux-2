#include "entite.h"

Entite::Entite() : QObject(){

    stat_base_mana=30;
    stat_base_vie=30;
    stat_base_attaquePhysique=10;
    stat_base_defensePhysique=10;
    stat_base_attaqueMagique=10;
    stat_base_defenseMagique=10;
    stat_base_vitesse=10;
    nomEntite="Nom de la bestiolle";
    level=1;
    xp=0;

    tabStatLevelUp[0]=5;//vie
    tabStatLevelUp[1]=5;//Mana
    tabStatLevelUp[2]=4;//attaque Magique
    tabStatLevelUp[3]=4;//attaque Physique
    tabStatLevelUp[4]=2;//def mag
    tabStatLevelUp[5]=2;//def phy
    tabStatLevelUp[6]=2;//Vitesse

    mana=stat_base_mana;
    vie=stat_base_vie;
    stat_combat_attaquePhysique=stat_base_attaquePhysique;
    stat_combat_attaqueMagique=stat_base_attaqueMagique;
    stat_combat_defensePhysique=stat_base_defensePhysique;
    stat_combat_defenseMagique=stat_base_defensePhysique;
    stat_combat_vitesse=stat_base_vitesse;
    celerite=0;

}


//fonction d'action

    bool Entite::recevoirDommage(int dommage){
        vie-=dommage;
        if(vie<=0){
            vie=0;
            celerite=-1;//mets la celerité a -1 quand mort
            emit mort();
        }
        if(vie>stat_base_vie){
            vie=stat_base_vie;
        }
        emit refreshVie(vie,stat_base_vie,this);
        return vie==0;
    }

    QString Entite::infligerDommage(Entite &cible, int dommage,bool ratePossible){
        QString texte="";
        QString soin="";
        QString soin2="";

        if(isRate() && dommage>=0 && ratePossible){
            texte=nomEntite+" a raté "+cible.getNomEntite();
        }

        else{


            if(nomEntite!=cible.getNomEntite()){
                if(cible.recevoirDommage(dommage)){
                    texte+= nomEntite+" a tué "+cible.getNomEntite()+" avec "+QString::number(fabs(dommage))+" de dommage";
                }
                else{
                    soin=" a infligé ";
                    soin2=" de dommage à ";
                    if(dommage<0){
                        soin=" a soigné ";
                        soin2=" point de vie de ";
                        if(-dommage>cible.getVie()){
                            dommage=-cible.getVie();
                        }
                    }
                    texte+=nomEntite+soin+QString::number(fabs(dommage))+soin2+cible.getNomEntite();
                }
            }
            else{
                if(cible.recevoirDommage(dommage)){
                    texte+=nomEntite+" se suicide";
                }
                else{
                    soin=" se blesse de ";
                    if(dommage<0){
                        soin=" se soigne de ";
                    }
                    texte+=nomEntite+soin+QString::number(fabs(dommage))+" point de vie";
                }
            }
        }
        return texte;
    }

    QString Entite::initialisationCombat(int xpGain){
        xp+=xpGain;
        if(xp<0){
            xp=0;
        }
        QString gain=" gagne ";
        if(xpGain<0){
            gain=" perd ";
        }
        QString texte=nomEntite+gain+QString::number(xpGain)+" xp \n";
        while(xp>=getXpMax()){
            texte+=this->levelUp();
        }

        celerite=0;
        this->supprimeToutBuff();

        return texte;
    }

    void Entite::soinAuberge(){

            mana=stat_base_mana;
            vie=stat_base_vie;
            emit refreshVie(vie,stat_base_vie,this);
            emit refreshMana(mana,stat_base_mana,this);

    }

    QString Entite::levelUp(){//a modifier
        QString texte="";
        if(this->getLevel()<100){
        this->setLevel(this->getLevel()+1);


        int augmentation=tabStatLevelUp[0]+rand()%5;
        setStatBaseVie(getStatBaseVie()+augmentation);
        texte="Augmentation: Vie+"+QString::number(augmentation);

         augmentation=tabStatLevelUp[1]+rand()%5;
        setStatBaseMana(getStatBaseMana()+augmentation);
        texte+="  Mana+"+QString::number(augmentation);

         augmentation=tabStatLevelUp[2]+rand()%3;
        setStatBaseAttaqueMagique(getStatBaseAttaqueMagique()+augmentation);
        texte+="  AM+"+QString::number(augmentation);


        augmentation=tabStatLevelUp[3]+rand()%3;
        setStatBaseAttaquePhysique(getStatBaseAttaquePhysique()+augmentation);
        texte+="  AP+"+QString::number(augmentation);

        augmentation=tabStatLevelUp[4]+rand()%3;
        setStatBaseDefenseMagique(getStatBaseDefenseMagique()+augmentation);
        texte+="  DM+"+QString::number(augmentation);

        augmentation=tabStatLevelUp[5]+rand()%3;
        setStatBaseDefensePhysique(getStatBaseDefensePhysique()+augmentation);
        texte+="  DP+"+QString::number(augmentation);

        augmentation=tabStatLevelUp[6]+rand()%3;
        setStatBaseVitesse(getStatBaseVitesse()+augmentation);
        texte+="  Vitesse+"+QString::number(augmentation);

       this->soinAuberge();//reset de vie et mana
    }
        return texte;
    }

    QString Entite::attaque(Entite &cible, int coeficient, bool attaqueMagique, int coutMana, bool soin,bool RateImpossible){
        QString texte="";
        if(isCritique()){
            texte="Coup Critique!!\n";
            coeficient*=2;
            RateImpossible=true;
        }
        if(coutMana<=mana){
            if(attaqueMagique){
               texte+=infligerDommage(cible,calculDommageMagique(cible,coeficient,soin),!RateImpossible);
            }
            else{
                texte+=infligerDommage(cible,calculDommagePhysique(cible,coeficient,soin),!RateImpossible);
            }

            mana-=coutMana;
            emit refreshMana(mana,stat_base_mana,this);
        }
        else{
            texte+=nomEntite+" incante mais rien ne se passe";
        }

        return texte;
    }


    void Entite::celerite_reset(){
        celerite=0;
    }

    void Entite::celerite_ajout(){
        if(vie!=0){
            celerite+=stat_combat_vitesse;
        }
    }

    void Entite::finTour(){
        celerite_reset();
    }

    QString Entite::debutTour(){
        QString retour="";
        //decompte les buff
        for(int i=0;i<listeEtat.size();i++){
            listeEtat[i].decompte();//enleve 1 tour de durée
            if(listeEtat.at(i).getDegatTour()!=0){//si effect de degat
                this->recevoirDommage(listeEtat.at(i).getDegatTour());
                if(listeEtat.at(i).getDegatTour()>0){
                    retour+=this->nomEntite+" a subi "+QString::number(listeEtat.at(i).getDegatTour())+" de dommage a cause de "+listeEtat.at(i).getNom()+"\n";
                }
                else{
                    retour+=this->nomEntite+" a recupere "+QString::number(listeEtat.at(i).getDegatTour())+" point de vie a cause de "+listeEtat.at(i).getNom()+"\n";
                }
            }
            if(listeEtat.at(i).getNbTour()==0){
                retour+=nomEntite+" perd l'effect "+ listeEtat.at(i).getNom();
                supprimeBuff(i);
            }
        }
        return retour;
    }

 //fonction de calcul

    int Entite::calculDommagePhysique(Entite &cible, int coeficient, bool soin) const{
       return calculDommage(cible.getDefensePhysique(),this->getAttaquePhysique(),coeficient,soin);
    }

    int Entite::calculDommageMagique(Entite &cible, int coeficient, bool soin) const{
        return calculDommage(cible.getDefenseMagique(),this->getAttaqueMagique(),coeficient,soin);
    }

    int Entite::calculDommage(int cibleDef, int lanceurAtt, int coef, bool soin) const{
       /*//fonction de dommage avec exponentielle
         double puissance=(coef)*lanceurAtt;
        puissance= (double) (puissance/(250*cibleDef));
        puissance=1-exp(-puissance);*/

        double puissance = coef*(double)(pow(lanceurAtt,2)/ (25*cibleDef));

        //coef de soin ou attaque
        int coefsoin=1;
        if(soin){
            coefsoin=-1;
        }

        //int dommage=coefsoin*ceil(999*puissance);//dommage expo
        int dommage=ceil(coefsoin*puissance);

        if(dommage>999){//limitateur de dommage en critique
            dommage=999;
        }
        if(dommage<-999){//limitateur de soin en critique
            dommage=-999;
        }
        return dommage;
    }

    bool Entite::isCritique()const{
        bool critique=false;
        if(rand()%100<=5){
            critique=true;
        }
        return critique;
    }

    bool Entite::isRate()const{
        bool rate=false;
        if(rand()%100<=5){
            rate=true;
        }
        return rate;

    }

//fonction d'augmentation

    QString Entite::augmentAttaqueMagique(double coef){
        QString retour="";
        QString augment="augmenté";
        if(coef<1){
            augment="diminué";
        }
            stat_combat_attaqueMagique=ceil(stat_combat_attaqueMagique*coef);
            retour=nomEntite+" vois son attaque magique "+augment;

        return retour;
    }

    QString Entite::augmentAttaquePhysique(double coef){
        QString retour="";
        QString augment="augmenté";
        if(coef<1){
            augment="diminué";
        }
            stat_combat_attaquePhysique=ceil(stat_combat_attaquePhysique*coef);
            retour=nomEntite+" vois son attaque physique "+augment;


        return retour;
    }

    QString Entite::augmentDefenseMagique(double coef){
        QString retour="";
        QString augment="augmenté";
        if(coef<1){
            augment="diminué";
        }

            stat_combat_defenseMagique=ceil(stat_combat_defenseMagique*coef);
            retour=nomEntite+" vois sa defense magique "+augment;

        return retour;
    }

    QString Entite::augmentDefensePhysique(double coef){
        QString retour="";
        QString augment="augmenté";
        if(coef<1){
            augment="diminué";
        }

            stat_combat_defensePhysique=ceil(stat_combat_defensePhysique*coef);
            retour=nomEntite+" vois sa defense physique "+augment;


        return retour;
    }

    QString Entite::augmentVitesse(double coef){
        QString retour="";
        QString augment="augmenté";
        if(coef<1){
            augment="diminué";
        }
            stat_combat_vitesse=ceil(stat_combat_vitesse*coef);
            retour=nomEntite+" vois sa vitesse "+augment;


        return retour;
    }

    QString Entite::ajoutBuff(buff nouveauBuff){
        bool actif=false;
        int taille=listeEtat.size();
        QString retour="";
        for(int i=0;i<taille;i++){
            if(listeEtat[i].getNom()==nouveauBuff.getNom()){
                actif=true;
                listeEtat[i].setNbTour(nouveauBuff.getNbTour());
                i=taille;//sortir
            }

        }
        if(actif){
            retour=nomEntite+" est déjà sous l'effect de "+nouveauBuff.getNom();
        }
        else{
            listeEtat << nouveauBuff;
            retour+=nomEntite+" subi l'effect "+nouveauBuff.getNom();

            if(nouveauBuff.getCoefActif(0)){
                retour+="\n"+augmentAttaquePhysique(nouveauBuff.getCoefEffect(0));
            }
            if(nouveauBuff.getCoefActif(1)){
                retour+="\n"+augmentAttaqueMagique(nouveauBuff.getCoefEffect(1));
            }
            if(nouveauBuff.getCoefActif(2)){
                retour+="\n"+augmentDefensePhysique(nouveauBuff.getCoefEffect(2));
            }
            if(nouveauBuff.getCoefActif(3)){
               retour+="\n"+augmentDefenseMagique(nouveauBuff.getCoefEffect(3));
            }
            if(nouveauBuff.getCoefActif(4)){
               retour+="\n"+augmentVitesse(nouveauBuff.getCoefEffect(4));
            }

        }

        return retour;
    }

void Entite::supprimeBuff(int caseTableau){
    if(listeEtat.size()!=0){
        augmentAttaquePhysique((double)1/listeEtat.at(caseTableau).getCoefEffect(0));
        augmentAttaqueMagique((double)1/listeEtat.at(caseTableau).getCoefEffect(1));
        augmentDefensePhysique((double)1/listeEtat.at(caseTableau).getCoefEffect(2));
        augmentDefenseMagique((double)1/listeEtat.at(caseTableau).getCoefEffect(3));
        augmentVitesse((double)1/listeEtat.at(caseTableau).getCoefEffect(4));

        }

       listeEtat[caseTableau]=listeEtat[listeEtat.size()-1];
       listeEtat.pop_back();

      if(listeEtat.size()==0){
          stat_combat_attaqueMagique=stat_base_attaqueMagique;
          stat_combat_attaquePhysique=stat_base_attaquePhysique;
          stat_combat_defenseMagique=stat_base_defenseMagique;
          stat_combat_defensePhysique=stat_base_defensePhysique;
          stat_combat_vitesse=stat_base_vitesse;
      }

}

void Entite::supprimeToutBuff(){
    stat_combat_attaqueMagique=stat_base_attaqueMagique;
    stat_combat_attaquePhysique=stat_base_attaquePhysique;
    stat_combat_defenseMagique=stat_base_defenseMagique;
    stat_combat_defensePhysique=stat_base_defensePhysique;
    stat_combat_vitesse=stat_base_vitesse;

        listeEtat=QList<buff>();

}


//fonction demodification de variable

    void Entite::setNomEntite(QString nom){
        nomEntite=nom;
        emit refreshNom(nom,this);
    }

    void Entite::setStatBaseVie(int vieDeBase){
        stat_base_vie=vieDeBase;
    }

    void Entite::setStatBaseMana(int manaDeBase){
        stat_base_mana=manaDeBase;
    }

    void Entite::setStatBaseAttaquePhysique(int attaquePhysiqueBase){
        stat_base_attaquePhysique=attaquePhysiqueBase;
    }

    void Entite::setStatBaseAttaqueMagique(int attaqueMagiqueBase){
        stat_base_attaqueMagique=attaqueMagiqueBase;
    }

    void Entite::setStatBaseDefensePhysique(int defensePhysique){
        stat_base_defensePhysique=defensePhysique;
    }

    void Entite::setStatBaseDefenseMagique(int defenseMagique){
        stat_base_defenseMagique=defenseMagique;
    }

    void Entite::setLevel(int NouveauLevel){//mets le level
        level=NouveauLevel;
    }

    void Entite::setXp(int nouveauXp){
        xp=nouveauXp;
    }

    void Entite::setStatBaseVitesse(int vitesseDeBase){
        stat_base_vitesse=vitesseDeBase;
    }

    bool Entite::useMana(int manaUse){
        bool manaSuffissant=false;
        if(mana>=manaUse){
            mana-=manaUse;
            manaSuffissant=true;
            if(mana>=stat_base_mana){
                mana=stat_base_mana;
            }
            emit refreshMana(mana,stat_base_mana,this);
        }
        return manaSuffissant;
    }

    QString Entite::useSoin(double coef, bool complet){
        if(complet){
            vie=stat_base_vie;
             return nomEntite+" recupere toute sa vie";
        }
        else{
            int soin= stat_base_vie*coef;
            if(vie+soin>stat_base_vie){
                vie=stat_base_vie;
                return nomEntite+" recupere toute sa vie";
            }
            else{
             vie+=soin;
             return nomEntite+" recupere "+QString::number(soin)+" de vie";
            }
        }
        emit refreshVie(vie,stat_base_vie,this);
    }

//fonction de recuperation

int Entite::getMana() const{
    return mana;
}

int Entite::getVie() const{
    return vie;
}

int Entite::getStatBaseMana() const{
    return stat_base_mana;
}

int Entite::getStatBaseVie() const{
    return stat_base_vie;
}

int Entite::getStatBaseAttaqueMagique()const{
    return stat_base_attaqueMagique;
}

int Entite::getStatBaseAttaquePhysique()const{
    return stat_base_attaquePhysique;
}

int Entite::getStatBaseDefenseMagique()const{
    return stat_base_defenseMagique;
}

int Entite::getStatBaseDefensePhysique()const{
    return stat_base_defensePhysique;
}

int Entite::getAttaqueMagique()const{
    return stat_combat_attaqueMagique;
}

int Entite::getAttaquePhysique()const{
    return stat_combat_attaquePhysique;
}

int Entite::getDefenseMagique()const{
    return stat_combat_defenseMagique;
}

int Entite::getDefensePhysique()const{
    return stat_combat_defensePhysique;
}

QString Entite::getNomEntite()const{

    return nomEntite;
}

int Entite::getLevel()const{
    return level;
}

int Entite::getXp()const{
    return xp;
}

int Entite::getXpMax()const{
    return 10*pow(level,2)+6*level-10;
}

int Entite::getCelerite()const{
    int retour=-1;
    if(vie>0){
        retour=celerite;
    }
    return retour;
}

int Entite::getStatBaseVitesse()const{
    return stat_base_vitesse;
}

int Entite::getVitesse()const{
    return stat_combat_vitesse;
}

QString Entite::getResumeEtat()const{
    QString retour="";
    if(listeEtat.size()!=0){
        for(int i=0;i<listeEtat.size();i++){
            retour+= listeEtat[i].getNom()+" "+listeEtat[i].getNbTourText()+"\n";
        }
    }
    return retour;

}

void Entite::afficheStat(){
    emit demandeAfficheStat(this);
}

QString Entite::getNomClass()const{
    return "Aucune Classe";
}
