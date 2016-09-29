#include "hero.h"

Hero::Hero()
{

     //Nommez l'avatar et definir sa classe
      classe=0;
      nomClasse="Source";
      this->setNomEntite("Hero");
     setStatLevelUp();//mets les nb qui def les gain en lv up et stat de base

}


int Hero::getClasse()const{
    return classe;
}

QString Hero::getNomClass()const{
    return nomClasse;
}

void Hero::setClass(int classeAMettre){
    classe=classeAMettre;
    switch (classe) {
    case 0:nomClasse="Guerrier";
        break;
    case 1:nomClasse="Mage";
        break;
    case 2:nomClasse="Paladin";
        break;
    case 3:nomClasse="Assasin";
        break;
    case 4:nomClasse="Prêtre";
        break;
    default:nomClasse="Source";
        break;
    }
    setStatLevelUp();
}

void Hero::setStatLevelUp(){
    switch (classe) {
    case 0://guerrier
        tabStatLevelUp[0]=20;//vie au lv up
        tabStatLevelUp[1]=1;//Mana au lv up
        tabStatLevelUp[2]=0;//attaque Magique au lv up
        tabStatLevelUp[3]=10;//attaque Physique au lv up
        tabStatLevelUp[4]=2;//def mag au lv up
        tabStatLevelUp[5]=4;//def phy au lv up
        tabStatLevelUp[6]=2;//Vitesse au lv up
        setStatBaseMana(10);//mana de base
        setStatBaseVie(60);//vie de base
        setStatBaseAttaquePhysique(20);//att p de base
        setStatBaseDefensePhysique(15);//dp de base
        setStatBaseAttaqueMagique(1);//am de base
        setStatBaseDefenseMagique(5);//dm de base
        setStatBaseVitesse(10);//vitesse de base
        break;
    case 1://Mage
        tabStatLevelUp[0]=10;//vie au lv up
        tabStatLevelUp[1]=10;//Mana au lv up
        tabStatLevelUp[2]=10;//attaque Magique au lv up
        tabStatLevelUp[3]=0;//attaque Physique au lv up
        tabStatLevelUp[4]=4;//def mag au lv up
        tabStatLevelUp[5]=2;//def phy au lv up
        tabStatLevelUp[6]=2;//Vitesse au lv up
        setStatBaseMana(40);//mana de base
        setStatBaseVie(30);//vie de base
        setStatBaseAttaquePhysique(1);//att p de base
        setStatBaseDefensePhysique(5);//dp de base
        setStatBaseAttaqueMagique(20);//am de base
        setStatBaseDefenseMagique(15);//dm de base
        setStatBaseVitesse(10);//vitesse de base
        break;
    case 2://Paladin
        tabStatLevelUp[0]=19;//vie au lv up
        tabStatLevelUp[1]=5;//Mana au lv up
        tabStatLevelUp[2]=4;//attaque Magique au lv up
        tabStatLevelUp[3]=8;//attaque Physique au lv up
        tabStatLevelUp[4]=3;//def mag au lv up
        tabStatLevelUp[5]=3;//def phy au lv up
        tabStatLevelUp[6]=2;//Vitesse au lv up
        setStatBaseMana(20);//mana de base
        setStatBaseVie(50);//vie de base
        setStatBaseAttaquePhysique(15);//att p de base
        setStatBaseDefensePhysique(10);//dp de base
        setStatBaseAttaqueMagique(10);//am de base
        setStatBaseDefenseMagique(10);//dm de base
        setStatBaseVitesse(10);//vitesse de base
        break;
    case 3://assasin
        tabStatLevelUp[0]=10;//vie au lv up
        tabStatLevelUp[1]=1;//Mana au lv up
        tabStatLevelUp[2]=0;//attaque Magique au lv up
        tabStatLevelUp[3]=12;//attaque Physique au lv up
        tabStatLevelUp[4]=2;//def mag au lv up
        tabStatLevelUp[5]=2;//def phy au lv up
        tabStatLevelUp[6]=3;//Vitesse au lv up
        setStatBaseMana(10);//mana de base
        setStatBaseVie(40);//vie de base
        setStatBaseAttaquePhysique(20);//att p de base
        setStatBaseDefensePhysique(5);//dp de base
        setStatBaseAttaqueMagique(1);//am de base
        setStatBaseDefenseMagique(5);//dm de base
        setStatBaseVitesse(15);//vitesse de base
        break;
    case 4://prete
        tabStatLevelUp[0]=15;//vie au lv up
        tabStatLevelUp[1]=10;//Mana au lv up
        tabStatLevelUp[2]=10;//attaque Magique au lv up
        tabStatLevelUp[3]=0;//attaque Physique au lv up
        tabStatLevelUp[4]=3;//def mag au lv up
        tabStatLevelUp[5]=3;//def phy au lv up
        tabStatLevelUp[6]=1;//Vitesse au lv up
        setStatBaseMana(30);//mana de base
        setStatBaseVie(40);//vie de base
        setStatBaseAttaquePhysique(1);//att p de base
        setStatBaseDefensePhysique(5);//dp de base
        setStatBaseAttaqueMagique(15);//am de base
        setStatBaseDefenseMagique(10);//dm de base
        setStatBaseVitesse(8);//vitesse de base
        break;
    default://Source
        setStatBaseMana(30);//mana de base
        setStatBaseVie(40);//vie de base
        setStatBaseAttaquePhysique(10);//att p de base
        setStatBaseDefensePhysique(10);//dp de base
        setStatBaseAttaqueMagique(10);//am de base
        setStatBaseDefenseMagique(10);//dm de base
        setStatBaseVitesse(10);//vitesse de base
        break;
    }
    this->initialisationCombat();
    this->soinAuberge();
}



QString Hero::apprentissageParNiveau()const{
    QString retour="";
    switch (classe) {
    case 0://guerrier
        retour=apprendParNiveau_Guerrier();
        break;
    case 1://Mage
        retour=apprendParNiveau_Mage();
        break;
    case 2://Paladin
           retour=apprendParNiveau_Paladin();
        break;
    case 3://assasin
            retour=apprendParNiveau_Assasin();
        break;
    case 4://prete
            retour=apprendParNiveau_Prete();
        break;
    default:
        retour="Une source n'apprends pas elle créé";
        break;
    }
    return retour;
}

QString Hero::apprendParNiveau_Guerrier()const{
    QString retour="";
    switch (this->getLevel()) {
    case 5:
            retour="\n"+this->getNomEntite()+" a appris Brise-Crâne";
        break;
    case 8:
            retour="\n"+this->getNomEntite()+" a appris Frappe circulaire";
        break;
    case 10:
            retour="\n"+this->getNomEntite()+" a appris Deculpo";
        break;
    case 12:
            retour="\n"+this->getNomEntite()+" a appris Ryuken";
        break;
    case 15:
            retour="\n"+this->getNomEntite()+" a appris Déprime";
        break;
    case 25:
            retour="\n"+this->getNomEntite()+" a appris Frappe Astral";
        break;
    case 30:
            retour="\n"+this->getNomEntite()+" a appris Séisme";
        break;
    case 37:
            retour="\n"+this->getNomEntite()+" a appris Lame Dragon";
        break;
    default: retour="";
        break;
    }
    return retour;
}

QString Hero::apprendParNiveau_Mage()const{
    QString retour="";
    switch (this->getLevel()) {
    case 3:
            retour="\n"+this->getNomEntite()+" a appris Crame";
        break;
    case 9:
            retour="\n"+this->getNomEntite()+" a appris Purification";
        break;
    case 12:
            retour="\n"+this->getNomEntite()+" a appris Soin Avancé";
        break;
    case 17:
            retour="\n"+this->getNomEntite()+" a appris Bouclier";
        break;
    case 18:
            retour="\n"+this->getNomEntite()+" a appris Blindage";
        break;
    case 19:
            retour="\n"+this->getNomEntite()+" a appris SuperFlamme";
        break;
    case 20:
            retour="\n"+this->getNomEntite()+" a appris SuperCrame";
        break;
    case 21:
            retour="\n"+this->getNomEntite()+" a appris Soin Puissant";
        break;
    case 24:
            retour="\n"+this->getNomEntite()+" a appris Canalisation Magique";
        break;
    case 25:
            retour="\n"+this->getNomEntite()+" a appris Booster";
        break;
    case 32:
            retour="\n"+this->getNomEntite()+" a appris MegaFlamme";
        break;
    case 38:
            retour="\n"+this->getNomEntite()+" a appris MegaCrame";
        break;
    case 43:
            retour="\n"+this->getNomEntite()+" a appris GigaFlamme";
        break;
    case 50:
            retour="\n"+this->getNomEntite()+" a appris GigaCramme";
        break;
    default: retour="";
        break;
    }
    return retour;
}

QString Hero::apprendParNiveau_Paladin()const{
    QString retour="";
    switch (this->getLevel()) {
    case 9:
            retour="\n"+this->getNomEntite()+" a appris Purification";
        break;
    case 12:
            retour="\n"+this->getNomEntite()+" a appris Ryuken";
        break;
    case 13:
            retour="\n"+this->getNomEntite()+" a appris Crame";
        break;
    case 14:
            retour="\n"+this->getNomEntite()+" a appris Soin Avancé";
        break;
    case 15:
            retour="\n"+this->getNomEntite()+" a appris Deculpo";
        break;
    case 24:
            retour="\n"+this->getNomEntite()+" a appris Frappe Astral";
        break;
    case 28:
            retour="\n"+this->getNomEntite()+" a appris Rappel";
        break;
    case 32:
            retour="\n"+this->getNomEntite()+" a appris SuperCrame";
        break;
    case 35:
            retour="\n"+this->getNomEntite()+" a appris Bouclier";
        break;
    case 39:
            retour="\n"+this->getNomEntite()+" a appris Lame Dragon";
        break;
    case 45:
            retour="\n"+this->getNomEntite()+" a appris MegaCrame";
        break;
    default: retour="";
        break;
    }
    return retour;
}

QString Hero::apprendParNiveau_Assasin()const{
    QString retour="";
    switch (this->getLevel()) {
    case 5:
            retour="\n"+this->getNomEntite()+" a appris Frappe Rapide";
        break;
    case 7:
            retour="\n"+this->getNomEntite()+" a appris Nuage de poison";
        break;
    default: retour="";
        break;
    }
    return retour;
}

QString Hero::apprendParNiveau_Prete()const{
    QString retour="";
    switch (this->getLevel()) {
    case 9:
            retour="\n"+this->getNomEntite()+" a appris Purification";
        break;
    case 12:
            retour="\n"+this->getNomEntite()+" a appris Soin Avancé";
        break;
    case 17:
            retour="\n"+this->getNomEntite()+" a appris Bouclier";
        break;
    case 18:
            retour="\n"+this->getNomEntite()+" a appris Blindage";
        break;
    case 21:
            retour="\n"+this->getNomEntite()+" a appris Soin Puissant";
        break;
    case 23:
            retour="\n"+this->getNomEntite()+" a appris Booster";
        break;
    case 25:
            retour="\n"+this->getNomEntite()+" a appris Rappel";
        break;
    case 31:
            retour="\n"+this->getNomEntite()+" a appris Soin Complet";
        break;
    case 35:
            retour="\n"+this->getNomEntite()+" a appris SuperBouclier";
        break;
    case 38:
            retour="\n"+this->getNomEntite()+" a appris SuperBlindage";
        break;
    case 41:
            retour="\n"+this->getNomEntite()+" a appris Ressurection";
        break;
    case 45:
            retour="\n"+this->getNomEntite()+" a appris SuperBooster";
        break;
    case 51:
            retour="\n"+this->getNomEntite()+" a appris Omnisoin";
        break;
    default: retour="";
        break;
    }
    return retour;
}
