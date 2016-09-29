#include "attaque.h"

//base
QString attaque::baseAttaque(Entite &lanceur, Entite &cible, int coef, bool magique, int mana, bool soin){
    QString retour="";
    if(cible.getVie()!=0){

       retour= lanceur.attaque(cible,coef,magique,mana,soin);//cible coef magique mana soin
       lanceur.finTour();//met a 0 la celerite et decompte les buff


    }
    else{
        retour= "Impossible car "+cible.getNomEntite()+" est deja mort";
    }



    return retour;
}

QString attaque::baseAttaqueMultiCible(Entite &lanceur, QList<Entite *> cible, int coef, bool magique, int mana, bool soin){
    QString retour="";
    int taille=cible.size();
    if(lanceur.useMana(mana)){
    for(int i=0;i<taille;i++){
        if(cible[i]->getVie()!=0){
         retour+= (baseAttaque(lanceur,*cible[i],coef,magique,0,soin)+"\n");

        }
    }
    }
    else{
        retour= lanceur.getNomEntite()+" incante mais rien ne se passe";
    }

    lanceur.finTour();//met a 0 la celerite et decompte les buff

    return retour;
}


QString attaque::baseAjoutBuff(Entite &lanceur, Entite &cible, buff buffAjoute, int mana){
    QString retour="";
    if(cible.getVie()!=0){
        if(lanceur.useMana(mana)){
            retour=cible.ajoutBuff(buffAjoute);
         }
        else{
            retour= lanceur.getNomEntite()+" incante mais rien ne se passe";
        }

        lanceur.finTour();//met a 0 la celerite et decompte les buff

    }
    else{
        retour= "Impossible car "+cible.getNomEntite()+" est deja mort";
    }


    return retour;
}

QString attaque::baseAjoutBuffMultiCible(Entite &lanceur, QList<Entite *> cible, buff buffAjoute, int mana){
    QString retour="";
    if(lanceur.useMana(mana)){
    for(int i=0;i<cible.size();i++){
        if(cible[i]->getVie()!=0){
         retour+= (baseAjoutBuff(lanceur,*cible[i],buffAjoute)+"\n");

        }
    }
    }
    else{
        retour= lanceur.getNomEntite()+" incante mais rien ne se passe";
    }

    lanceur.finTour();//met a 0 la celerite et decompte les buff

    return retour;
}


QString attaque::baseAttaqueBuff(Entite &lanceur, Entite &cible,buff buffAjout ,int coefAttaque, int chanceBuffAct,Entite& cibleBuff, bool magique, int mana, bool soin){
    QString retour=baseAttaque(lanceur,cible,coefAttaque,magique,mana,soin);
    if(rand()%100<=chanceBuffAct && !(retour.contains("rien ne se passe") || retour.contains("raté")|| retour.contains("mort"))){
       retour+="\n" +cibleBuff.ajoutBuff(buffAjout);
    }
    return retour;
}

QString attaque::baseAttaqueBuffMultiCible(Entite &lanceur, QList<Entite *> cible, buff buffAjout, int coefAttaque, int chanceBuffAct, bool magique, int mana, bool soin){
QString retour="";
if(lanceur.useMana(mana)){
for(int i=0;i<cible.size();i++){
    if(cible[i]->getVie()!=0){
     retour+= (baseAttaqueBuff(lanceur,*cible[i],buffAjout,coefAttaque,chanceBuffAct,*cible[i],magique,mana,soin)+"\n");

    }
}
}
else{
    retour= lanceur.getNomEntite()+" incante mais rien ne se passe";
}

lanceur.finTour();//met a 0 la celerite et decompte les buff

return retour;
}

QString attaque::baseAttaqueVolMana(Entite &lanceur, Entite &cible, int manaVol, int coef, bool magique, int mana){
    QString retour=baseAttaque(lanceur,cible,coef,magique,mana);
    if(!(retour.contains("rien ne se passe") || retour.contains("raté")|| retour.contains("mort"))){
        if(cible.useMana(manaVol)){
        lanceur.useMana(-manaVol);
        retour+="\n" +lanceur.getNomEntite()+" vole "+QString::number(manaVol)+" de mana à "+cible.getNomEntite();
        }
        else{
           retour+="\n" +lanceur.getNomEntite()+" ne peut plus voler du mana à "+cible.getNomEntite();
        }
    }
    return retour;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//soin
QString attaque::soin(Entite &lanceur, Entite &cible){
       return lanceur.getNomEntite()+" utilise le sort Soin\n"+baseAttaque(lanceur,cible,5,true,5,true);//cible coef magique mana soin
}

QString attaque::soinAvance(Entite &lanceur, Entite &cible){
     return lanceur.getNomEntite()+" utilise le sort Soin Avancé\n"+baseAttaque(lanceur,cible,9,true,15,true);
}

QString attaque::soinPuissant(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise le sort Soin Puissant\n"+baseAttaque(lanceur,cible,18,true,45,true);
}

QString attaque::soinComplet(Entite &lanceur, Entite &cible){
    QString retour=lanceur.getNomEntite()+" utilise le sort Soin Complet\n";
    if(cible.getVie()!=0){
        if(lanceur.useMana(150)){
            retour+=cible.useSoin(0,true);
        }
        else{
            retour+= lanceur.getNomEntite()+" incante mais rien ne se passe";
        }
        lanceur.finTour();
    }
    else{
        retour= "Impossible car "+cible.getNomEntite()+" est deja mort";
    }

    return retour;
}

QString attaque::rappel(Entite &lanceur, Entite &cible){
    QString retour= lanceur.getNomEntite()+" utilise Rappel\n";
    if(cible.getVie()==0){
        if(lanceur.useMana(100)){
            retour+=cible.useSoin(0.5);
        }
        else{
            retour+= lanceur.getNomEntite()+" incante mais rien ne se passe";
        }
    }
    else{
        retour+="Impossible de réanimer quelqu'un si il est vivant";
    }
        lanceur.finTour();
    return retour;
}

QString attaque::ressurection(Entite &lanceur, Entite &cible){
    QString retour= lanceur.getNomEntite()+" utilise Ressurection\n";
    if(cible.getVie()==0){
        if(lanceur.useMana(200)){
            retour+=cible.useSoin(0,true);
        }
        else{
            retour+= lanceur.getNomEntite()+" incante mais rien ne se passe";
        }
    }
    else{
        retour+="Impossible de réanimer quelqu'un si il est vivant";
    }
        lanceur.finTour();
    return retour;
}

QString attaque::multisoin(Entite &lanceur, QList<Entite *> cible){
    return lanceur.getNomEntite()+" utilise le sort Multisoin\n"+baseAttaqueMultiCible(lanceur,cible,10,true,150,true);
}

QString attaque::omnisoin(Entite &lanceur, QList<Entite *> cible){
    QString retour=lanceur.getNomEntite()+" utilise le sort Omnisoin\n";

        if(lanceur.useMana(500)){
            for (int i=0; i<cible.size();i++){
                if(cible[i]->getVie()!=0){
                    retour+=cible[i]->useSoin(0,true)+"\n";
                }
                else{
                    retour= "Impossible car "+cible[i]->getNomEntite()+" est deja mort";
                }
            }
        }
        else{
            retour+= lanceur.getNomEntite()+" incante mais rien ne se passe";
        }
        lanceur.finTour();

    return retour;
}

//buff
    //magie
QString attaque::bouclier(Entite &lanceur, Entite &cible){

    return lanceur.getNomEntite()+" utilise le sort Bouclier\n"+baseAjoutBuff(lanceur,cible,BuffPredefini::getBuffBouclier(),20) ;
}

QString attaque::blindage(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise le sort Blindage\n"+baseAjoutBuff(lanceur,cible,BuffPredefini::getBuffBlindage(),30) ;
}

QString attaque::booster(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise le sort Booster\n"+baseAjoutBuff(lanceur,cible,BuffPredefini::getBuffBooster(),50);
}

QString attaque::deculpo(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise le sort Deculpo\n"+baseAjoutBuff(lanceur,cible,BuffPredefini::getBuffDeculpo(),25);
}

QString attaque::canalisationMagique(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise le sort Canalisation Magique\n"+baseAjoutBuff(lanceur,cible,BuffPredefini::getBuffCanalisationMagique(),40);
}

QString attaque::purification(Entite &lanceur, Entite &cible){
    QString retour=lanceur.getNomEntite()+" utilise le sort Purification\n";
    if(cible.getVie()!=0){
        if(lanceur.useMana(10)){
            cible.supprimeToutBuff();
            retour+=cible.getNomEntite()+" perd tout ses effects";
        }
        else{
            retour+= lanceur.getNomEntite()+" incante mais rien ne se passe";
        }
        lanceur.finTour();
    }
    else{
        retour= "Impossible car "+cible.getNomEntite()+" est deja mort";
    }

    return retour;
}
    //tech
QString attaque::defense(Entite &lanceur){
    return lanceur.getNomEntite()+" se met en defense\n"+baseAjoutBuff(lanceur,lanceur,BuffPredefini::getBuffDefense());
}

QString attaque::superBouclier(Entite &lanceur, QList<Entite *> cible){
    return lanceur.getNomEntite()+" lance SuperBouclier\n"+baseAjoutBuffMultiCible(lanceur,cible,BuffPredefini::getBuffBouclier(),125);
}

QString attaque::superBlindage(Entite &lanceur, QList<Entite *> cible){
    return lanceur.getNomEntite()+" lance SuperBlindage\n"+baseAjoutBuffMultiCible(lanceur,cible,BuffPredefini::getBuffBlindage(),150);
}

QString attaque::superBooster(Entite &lanceur, QList<Entite *> cible){
    return lanceur.getNomEntite()+" lance SuperBooster\n"+baseAjoutBuffMultiCible(lanceur,cible,BuffPredefini::getBuffBooster(),200);
}

//attaque
    //magie
QString attaque::flamme(Entite &lanceur, Entite &cible){
      return lanceur.getNomEntite()+" utilise le sort Flamme\n"+baseAttaque(lanceur,cible,3,true,5);
}

QString attaque::superFlamme(Entite &lanceur, Entite &cible){
      return lanceur.getNomEntite()+" utilise le sort SuperFlamme\n"+baseAttaque(lanceur,cible,6,true,15);
}

QString attaque::megaFlamme(Entite &lanceur, Entite &cible){
      return lanceur.getNomEntite()+" utilise le sort MegaFlamme\n"+baseAttaque(lanceur,cible,12,true,25);
}

QString attaque::gigaFlamme(Entite &lanceur, Entite &cible){
      return lanceur.getNomEntite()+" utilise le sort GigaFlamme\n"+baseAttaque(lanceur,cible,14,true,50);
}

QString attaque::crame(Entite &lanceur, QList<Entite *> cible){
   return lanceur.getNomEntite()+" utilise le sort Crame\n"+baseAttaqueMultiCible(lanceur,cible,2,true,8);
}

QString attaque::superCrame(Entite &lanceur, QList<Entite *> cible){
   return lanceur.getNomEntite()+" utilise le sort SuperCrame\n"+baseAttaqueMultiCible(lanceur,cible,4,true,20);
}

QString attaque::megaCrame(Entite &lanceur, QList<Entite *> cible){
   return lanceur.getNomEntite()+" utilise le sort MegaCrame\n"+baseAttaqueMultiCible(lanceur,cible,8,true,35);
}

QString attaque::gigaCrame(Entite &lanceur, QList<Entite *> cible){
   return lanceur.getNomEntite()+" utilise le sort GigaCrame\n"+baseAttaqueMultiCible(lanceur,cible,12,true,60);
}

QString attaque::frappePuissante(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise la frappe Puissante\n"+baseAttaque(lanceur,cible,2,false,1);
}

QString attaque::briseCrane(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise Brise-Crane\n"+baseAttaqueBuff(lanceur,cible,buff ("Brise-Crane",-1,-1,0.8,-1,-1,3),3,75,cible);
}

QString attaque::ryuken(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise ryuken\n"+baseAttaqueVolMana(lanceur,cible,ceil((double)lanceur.calculDommageMagique(cible)/2),2,true);
}

QString attaque::frappeCirculaire(Entite &lanceur, QList<Entite *> cible){
    return lanceur.getNomEntite()+" frappe en arc de cercle\n"+baseAttaqueMultiCible(lanceur,cible,2);
}

QString attaque::Seisme(Entite &lanceur, QList<Entite *> cible){
    return lanceur.getNomEntite()+" provoque un séisme\n"+baseAttaqueMultiCible(lanceur,cible,4,false,25);
}

QString attaque::Analyse(Entite &lanceur, Entite &cible){
    QString retour=lanceur.getNomEntite()+" analyse "+cible.getNomEntite()+"\n";
    if(cible.getVie()!=0){
        if(lanceur.useMana(5)){
            cible.afficheStat();
        }
        else{
            retour+= lanceur.getNomEntite()+" incante mais rien ne se passe";
        }
        lanceur.finTour();
    }
    else{
        retour= cible.getNomEntite()+" est deja mort";
    }

    return retour;
}

QString attaque::deprime(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise deprime\n"+baseAttaqueBuff(lanceur,cible,buff("Déprime",-1,0.5,-1,-1,-1,3),2,80,cible);
}

QString attaque::lameEmpoisonner(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" frappe avec sa lame empoisonné\n"+baseAttaqueBuff(lanceur,cible,BuffPredefini::getBuffPoison("Poison",3,2+(cible.getStatBaseVie()/200)),1,75,cible );
}

QString attaque::FrappeRapide(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" frappe à la vitesse de l'éclair\n"+baseAttaqueBuff(lanceur,cible,buff("Rapidité",-1,-1,-1,-1,1.5,1),2,95,lanceur );
}

QString attaque::NuagePoison(Entite &lanceur, QList<Entite *> cible){
    return lanceur.getNomEntite()+" lance un nuage de poison\n"+baseAttaqueBuffMultiCible(lanceur,cible,BuffPredefini::getBuffPoison("Poison",3,10),1,50);
}

QString attaque::FrappeAstral(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise la frappe Astral\n"+baseAttaque(lanceur,cible,7,false,10);
}

QString attaque::lameDragon(Entite &lanceur, Entite &cible){
    return lanceur.getNomEntite()+" utilise la lame Dragon\n"+baseAttaque(lanceur,cible,10,false,20);
}
