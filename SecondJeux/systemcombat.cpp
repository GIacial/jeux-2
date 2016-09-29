#include "systemcombat.h"

#include "SystemCombat.h"

SystemCombat::SystemCombat(QList<Hero *> futurEquipe, int NbEnnMax) :QObject()
{
    equipe=futurEquipe;
    heroPrincipal=equipe[0];
    multiplicateurXp=1;

    //adversaire
    creationAdversaire(NbEnnMax);//cree les 5 adversaire (nombre max)
    nbAdversaireDansCombat=NbEnnMax;
    initialisationCible();

}
//affectation

void SystemCombat::setEquipe(QList<Hero *> nouvelleEquipe){
    equipe=nouvelleEquipe;
}
//recuperation
QList<Ennemie *> SystemCombat::getEquipeMonstre(){
    return adversaire;
}
Hero* SystemCombat::getHeroenAction(){
    return heroPrincipal;
}

Entite* SystemCombat::getCible(){
    return cible;
}

//action
void SystemCombat::creationAdversaire(int nbAdversaire){

    for(int i=0;i<nbAdversaire;i++){
        adversaire.push_back(new Ennemie());
    }
    initialisationCible();
}

void SystemCombat::randomEnnemie(int nbAdversaire,Ennemie* monstre){
    int monstre_level,monstre_vie,monstre_mana,monstre_ap,monstre_am,monstre_dp,monstre_dm,monstre_v,plus;

    if(rand()%100<=60){
       plus=(rand()%(2));
    }
    else{
       plus=-(rand()%nbAdversaire);
    }


    monstre_level=plus+heroPrincipal->getLevel();//plus au moins 5 level du joueur/nbmonstre
    if(monstre_level<=0){
        monstre_level=1;
    }

    monstre_vie=(rand()%(10*equipe.size()))+20;
    monstre_mana=(rand()%(5))+1;
    monstre_ap=(rand()%(5))+1;
    monstre_am=(rand()%(5))+1;
    monstre_dp=(rand()%(5))+1;
    monstre_dm=(rand()%(5))+1;
    monstre_v=(rand()%(5))+5;

    monstre->nouveauEnnemie(monstre_level,monstre_vie,monstre_mana,monstre_ap,monstre_am,monstre_dp,monstre_dm,monstre_v);

}

void SystemCombat::nouveauCombat(){
    int nbMonstreNextCombat=1;
    if(adversaire.size()>1){
        if(heroPrincipal->getLevel()<3 ){//limit debut
            nbMonstreNextCombat=rand()%(heroPrincipal->getLevel())+1;
        }
        else{
      nbMonstreNextCombat=rand()%(adversaire.size()-1)+1;
        }
    }

    //trouve le + haut level
    for(int i=0;i<equipe.size();i++){
        if(heroPrincipal->getLevel()<equipe[i]->getLevel()){
            heroPrincipal=equipe[i];
        }
    }

    for(int i=0;i<nbMonstreNextCombat;i++){
        randomEnnemie(nbMonstreNextCombat,adversaire[i]);
    }

    nbAdversaireDansCombat=nbMonstreNextCombat;//sauvegarde le nb ennemie de ce combat
    emit nbMonstreDansLeNouveauCombat(nbAdversaireDansCombat);

    if(nbAdversaireDansCombat==1){
           emit afficheTexteDansResume("\n"+adversaire[0]->getNomEntite()+" sort des buissons. \n");
        }
        else{
           emit afficheTexteDansResume("\n Un groupe de monstre sort des buissons \n");
            //evite les monstre avec le meme nom

            for(int i=0;i<nbMonstreNextCombat-1;i++){
                char memoire='A';
                for(int y=i+1;y<nbMonstreNextCombat;y++){
                    if(adversaire[i]->getNomEntite()==adversaire[y]->getNomEntite()){
                        adversaire[i]->setNomEntite(adversaire[i]->getNomEntite()+" "+memoire);
                        adversaire[y]->setNomEntite(adversaire[y]->getNomEntite()+" "+(memoire+1));
                        memoire++;
                    }
                }
            }
        }
    combatenCours=true;
    initialisationCible();
    prediction();
    celerite();//mets un tour de vitesse
    actionEnnemie();//lance la verification de qui doit agir en premier
    emit afficheBoutonAction();
}

void SystemCombat::initialisationCible(){
    cible=adversaire[0];
    demandeUpdateCible();
}

void SystemCombat::finActionHero(){
    emit enleveBoutonAction();
    if(heroPrincipal->getCelerite()<=0){
        celerite();//ajoute de la celerite a tout le monde
        heroPrincipal->celerite_reset();


            if(!verificationFinCombat()){//si toutes les cible sont mortes apres l'attaque
                actionEnnemie();
            }
    }

    if(combatenCours){
        emit afficheBoutonAction();
    }
}

void SystemCombat::actionEnnemie(){
    bool CombatActif=true;
    int indicePlusRapide=0;
    for(int i=0;i<nbAdversaireDansCombat;i++){//determine le + rapide
        if(adversaire[indicePlusRapide]->getCelerite()<adversaire[i]->getCelerite()){
            indicePlusRapide=i;
        }
    }

    for(int i=0;i<equipe.size();i++){//determine hero plus rapide
        if(heroPrincipal->getCelerite()<equipe[i]->getCelerite()){
            heroPrincipal=equipe[i];
        }
    }

    if(adversaire[indicePlusRapide]->getCelerite()>heroPrincipal->getCelerite()){
        do{

        //action ennemie
            emit afficheTexteDansResume(adversaire[indicePlusRapide]->debutTour());
            emit afficheTexteDansResume(adversaire[indicePlusRapide]->actionIA(*getHeroCible()));
            celerite();
            adversaire[indicePlusRapide]->finTour();
            //verif defaite
           CombatActif=!verificationFinCombat();
        //determine le + rapide pour le prochain tour

            for(int i=0;i<nbAdversaireDansCombat;i++){//determine le + rapide
                if(adversaire[indicePlusRapide]->getCelerite()<adversaire[i]->getCelerite()){
                    indicePlusRapide=i;
                }
            }
            for(int i=0;i<equipe.size();i++){//determine hero plus rapide
                if(heroPrincipal->getCelerite()<equipe[i]->getCelerite()){
                    heroPrincipal=equipe[i];
                }
            }

        }while(adversaire[indicePlusRapide]->getCelerite()>heroPrincipal->getCelerite() && CombatActif);
    }
        if(CombatActif){
        verificationFinCombat();//verifi si ennemie mort avec un buff qui inflige des degat
        emit afficheTexteDansResume("------------------------------------------------------------");
        emit afficheTexteDansResume( heroPrincipal->debutTour());
        prediction();}

}

void SystemCombat::prediction(){
    QList<int> tab_celerite;
    QList<QString> predictionTour;
            for(int i=0;i<equipe.size();i++){
            tab_celerite << equipe[i]->getCelerite();
            }

            for(int i=0;i<nbAdversaireDansCombat;i++){//entre le celerite initial
                tab_celerite << adversaire[i]->getCelerite();
            }

            int indicePlusRapide=0;

            for(int i=0;i<tab_celerite.size();i++){//determine le + rapide tout les adversaire +hero
                if(tab_celerite[indicePlusRapide]<tab_celerite[i]){
                    indicePlusRapide=i;
                 }
            }
            //imcristion des tour d'action + calcul
            for(int y=0;y<20;y++){
                if(indicePlusRapide<equipe.size()){//mets le nom du + rapide
                    predictionTour <<(equipe.at(indicePlusRapide)->getNomEntite());
                }
                else{
                    predictionTour <<(adversaire[indicePlusRapide-equipe.size()+1]->getNomEntite());
                }
                //augment les celerite
                for(int i=0;i<equipe.size();i++){
                    if(equipe[i]->getVie()!=0){
                        tab_celerite[i]+=equipe[i]->getVitesse();
                    }
                }
                for(int i=0;i<nbAdversaireDansCombat;i++){//augment d'un tour la celerite
                    if(adversaire[i]->getVie()!=0){
                        tab_celerite[i+equipe.size()]+=adversaire[i]->getVitesse();
                    }
                }


                tab_celerite[indicePlusRapide]=0;//met a 0 la celerite de celui qui a ete mis

                for(int i=0;i<tab_celerite.size();i++){//determine le + rapide tout les adversaire +hero
                    if(tab_celerite[indicePlusRapide]<tab_celerite[i]){
                        indicePlusRapide=i;
                     }
                }

            }
            emit resultatPrevision(predictionTour);
}

void SystemCombat::celerite(){
    for(int i=0;i<equipe.size();i++){
            equipe[i]->celerite_ajout();

    }
    for(int i=0;i<nbAdversaireDansCombat;i++){
            adversaire[i]->celerite_ajout();

    }

}


//action hero
    void SystemCombat::actionHero_attaqueBasic(){
        emit afficheTexteDansResume( attaque::baseAttaque(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_defense(){
       emit afficheTexteDansResume( attaque::defense(*heroPrincipal));
        finActionHero();
    }

//magie blanche
    void SystemCombat::actionHero_soin(){
      emit afficheTexteDansResume( attaque::soin(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_soinAvance(){
      emit afficheTexteDansResume( attaque::soinAvance(*heroPrincipal,*cible));
       finActionHero();
    }

    void SystemCombat::actionHero_soinPuissant(){
        emit afficheTexteDansResume(attaque::soinPuissant(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_soinComplet(){
        emit afficheTexteDansResume(attaque::soinComplet(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_rappel(){
        emit afficheTexteDansResume(attaque::rappel(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_ressurection(){
        emit afficheTexteDansResume(attaque::ressurection(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_bouclier(){
        emit afficheTexteDansResume(attaque::bouclier(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_blindage(){
        emit afficheTexteDansResume(attaque::blindage(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_booster(){
        emit afficheTexteDansResume(attaque::booster(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_deculpo(){
        emit afficheTexteDansResume(attaque::deculpo(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_canalisationMagique(){
        emit afficheTexteDansResume(attaque::canalisationMagique(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_purification(){
        emit afficheTexteDansResume(attaque::purification(*heroPrincipal,*cible));
        finActionHero();
    }

//magie noire
    void SystemCombat::actionHero_flamme(){
       emit afficheTexteDansResume( attaque::flamme(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_superFlamme(){
       emit afficheTexteDansResume( attaque::superFlamme(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_megaFlamme(){
       emit afficheTexteDansResume( attaque::megaFlamme(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_gigaFlamme(){
        emit afficheTexteDansResume(attaque::gigaFlamme(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_crame(){
        emit afficheTexteDansResume(attaque::crame(*heroPrincipal,getListeCible()));
        finActionHero();
    }

    void SystemCombat::actionHero_superCrame(){
        emit afficheTexteDansResume(attaque::superCrame(*heroPrincipal,getListeCible()));
        finActionHero();
    }

    void SystemCombat::actionHero_megaCrame(){
        emit afficheTexteDansResume(attaque::megaCrame(*heroPrincipal,getListeCible()));
        finActionHero();
    }

    void SystemCombat::actionHero_gigaCrame(){
        emit afficheTexteDansResume(attaque::gigaCrame(*heroPrincipal,getListeCible()));
        finActionHero();
    }

    void SystemCombat::actionHero_superBouclier(){
        emit afficheTexteDansResume(attaque::superBouclier(*heroPrincipal,getListeHero()));
        finActionHero();
    }

    void SystemCombat::actionHero_superBlindage(){
        emit afficheTexteDansResume(attaque::superBlindage(*heroPrincipal,getListeHero()));
        finActionHero();
    }

    void SystemCombat::actionHero_superBooster(){
        emit afficheTexteDansResume(attaque::superBooster(*heroPrincipal,getListeHero()));
        finActionHero();
    }

    void SystemCombat::actionHero_omnisoin(){
        emit afficheTexteDansResume(attaque::omnisoin(*heroPrincipal,getListeHero()));
        finActionHero();
    }

    void SystemCombat::actionHero_multisoin(){
        emit afficheTexteDansResume(attaque::multisoin(*heroPrincipal,getListeHero()));
        finActionHero();
    }

    //tech
    void SystemCombat::actionHero_frappePuissante(){
        emit afficheTexteDansResume(attaque::frappePuissante(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_BriseCrane(){
        emit afficheTexteDansResume(attaque::briseCrane(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_ryuken(){
        emit afficheTexteDansResume(attaque::ryuken(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_FrappeCirculaire(){
        emit afficheTexteDansResume(attaque::frappeCirculaire(*heroPrincipal,getListeCible()));
        finActionHero();
    }

    void SystemCombat::actionHero_analyse(){
        emit afficheTexteDansResume(attaque::Analyse(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_seisme(){
        emit afficheTexteDansResume(attaque::Seisme(*heroPrincipal,getListeCible()));
        finActionHero();
    }

    void SystemCombat::actionHero_deprime(){
        emit afficheTexteDansResume(attaque::deprime(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_lameEmpoisonner(){
        emit afficheTexteDansResume(attaque::lameEmpoisonner(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_frappeRapide(){
        emit afficheTexteDansResume(attaque::FrappeRapide(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_nuagePoison(){
        emit afficheTexteDansResume(attaque::NuagePoison(*heroPrincipal,getListeCible()));
        finActionHero();
    }

    void SystemCombat::actionHero_frappeAstral(){
        emit afficheTexteDansResume(attaque::FrappeAstral(*heroPrincipal,*cible));
        finActionHero();
    }

    void SystemCombat::actionHero_lameDragon(){
        emit afficheTexteDansResume(attaque::lameDragon(*heroPrincipal,*cible));
        finActionHero();
    }



    //calcul
    int SystemCombat::calculXp(){//a modifier
        int taille=nbAdversaireDansCombat;
        int xp=0;
        for(int i=0;i<taille;i++){
            if(adversaire[i]->getVie()==0){
                xp+=(multiplicateurXp+adversaire[i]->getXpWhenVaincu());
            }
        }
        return xp;
    }



//verification

    bool SystemCombat::verificationEnnemieVivant()const{

        int vieTotal=0;
        for(int i=0;i<nbAdversaireDansCombat ;i++){
            vieTotal+=adversaire[i]->getVie();
        }
        return vieTotal>0;
    }

    bool SystemCombat::verificationEquipeVivant()const{

        int vieTotal=0;
        for(int i=0;i<equipe.size();i++){
            vieTotal+=equipe[i]->getVie();
        }
        return vieTotal>0;
    }

    bool SystemCombat::verificationFinCombat(){
        bool combatFini=false;
        if( (!verificationEquipeVivant()) && combatenCours){
            emit afficheTexteDansResume("Defaite");
            int xpGagne=-multiplicateurXp;
            for(int i=0;i<equipe.size();i++){
            emit afficheTexteDansResume( equipe[i]->initialisationCombat(xpGagne));//enleve les changement de status du hero et mets xp
            }
            multiplicateurXp=1;
            emit sauvegarde();
            emit finCombat();//signale la fin du combat
            combatenCours=false;
            combatFini=true;//combat n'est plus actif plus de calcul de tour

        }
        else{
            if((!verificationEnnemieVivant()) && combatenCours){//si toutes les cible sont mortes apres l'attaque
               emit afficheTexteDansResume("Victoire");
                int xpGagne=calculXp();
                for(int i=0;i<equipe.size();i++){
                emit afficheTexteDansResume( equipe[i]->initialisationCombat(xpGagne));//enleve les changement de status du hero et mets xp
                }
                multiplicateurXp++;
                 emit sauvegarde();//suavegarde la progression
                 emit finCombat();//signale la fin du combat
                combatenCours=false;//evite le spam de gain xp
                 combatFini=true;//combat n'est plus actif plus de calcul de tour

            }
        }
        return combatFini;
    }

void SystemCombat::selectionCible(Entite *cibleWidget){
             cible=cibleWidget;
             emit demandeUpdateCible();
}


//validation slot

void SystemCombat::auberge_validation(){
   emit afficheTexteDansResume( "Merci d'etre passé à notre auberge");
   for(int i=0;i<equipe.size();i++){
   equipe[i]->soinAuberge();
   }
    multiplicateurXp=1;
}


//recuperation


QList<Entite*> SystemCombat::getListeCible(){
    QList<Entite*> listeCible;

    for (int i=0;i<nbAdversaireDansCombat;i++){
        listeCible << adversaire[i];
    }

    return listeCible;
}

QList<Entite*> SystemCombat::getListeHero(){
    QList<Entite*> listeCible;

    for (int i=0;i<equipe.size();i++){
        listeCible << equipe[i];
    }

    return listeCible;
}


Hero* SystemCombat::getHeroCible(){
    Hero* retour=heroPrincipal;
    for (int i=0;i<equipe.size();i++){
        if(equipe[i]->getVie()>0){
            if(retour->getVie()>0){
                if(rand()%100<40){
                    retour=equipe[i];
                    i=equipe.size();
                }
            }
            else{
            retour=equipe[i];
            }
        }
    }
    return retour;
}

