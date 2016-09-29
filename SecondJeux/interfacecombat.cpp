#include "interfacecombat.h"

InterfaceCombat::InterfaceCombat(QList<Hero *> futurEquipe, int NbEnnMax) :QScrollArea()
{
    //data
        systemDeCombat= new SystemCombat(futurEquipe,NbEnnMax);
        equipe=futurEquipe;
        equipeModifier=false;
        adversaire=systemDeCombat->getEquipeMonstre();
    //interface
        //conteneur global
        principal= new QWidget();
        principalLayout= new QGridLayout();
        principal->setLayout(principalLayout);
        this->setWidget(principal);
        this->setWidgetResizable(true);
        //resume de combat
        resume= new QTextEdit();
        resume->setReadOnly(true);
        resume_ScrolBar= new QScrollBar(Qt::Vertical);
        resume->setVerticalScrollBar(resume_ScrolBar);
        principalLayout->addWidget(resume,5,0,1,5);
        //conteneur des widget Ennemie
        groupeEnnemie= new QScrollArea();
        groupeEnnemie_conteneur= new QWidget();
        groupeEnnemie_LayoutConteneur= new QHBoxLayout(groupeEnnemie_conteneur);
        groupeEnnemie_LayoutConteneur->setSpacing(0);
        groupeEnnemie->setWidgetResizable(true);
        groupeEnnemie->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        groupeEnnemie->setWidget(groupeEnnemie_conteneur);
        principalLayout->addWidget(groupeEnnemie,4,0,1,5);


        //creation du predicteur tour par tour
        QScrollArea* predicteur_conteneur=new QScrollArea(this);
        predicteur_conteneur->setWidgetResizable(true);
        QWidget* predicteur_conteneurLayout= new QWidget(predicteur_conteneur);
        predicteur_conteneur->setWidget(predicteur_conteneurLayout);
        predicteur_conteneur->setMaximumWidth(80);
        principalLayout->addWidget(predicteur_conteneur,0,6,6,1);
        QVBoxLayout* predicteur_layout= new QVBoxLayout(predicteur_conteneurLayout);
        predicteur_layout->setContentsMargins(0,0,0,0);
        predicteur_layout->setSpacing(0);

        for(int i=0;i<20;i++){//nb present aussi dans prediction du system
        predictionTour << new QLabel(QString::number(i),this);
        predictionTour.at(i)->setAlignment(Qt::AlignCenter);
        predicteur_layout->addWidget(predictionTour.at(i));
        }
        //texte de la cible
        cible_texte= new QLabel("Cible:");
        principalLayout->addWidget(cible_texte,1,4);

        //creation de fenetre de magie et tech
        for (int i=0;i<5;i++){//une fenetre de magie et de tech par classe i<nb classe
            //sort [0]
            magie.push_back(new FenetreMagie());
            principalLayout->addWidget(magie[2*i],5,0,1,5);
            QObject::connect(magie[2*i],SIGNAL(affiche(FenetreMagie*)),this,SLOT(fermeAutreMagTech(FenetreMagie*)));

            //technique [1]
            magie.push_back(new FenetreMagie());
            principalLayout->addWidget(magie[(2*i)+1],5,0,1,5);

            QObject::connect(magie[(2*i)+1],SIGNAL(affiche(FenetreMagie*)),this,SLOT(fermeAutreMagTech(FenetreMagie*)));

        setConnectionAttaqueHeroClass(i);//lie les attaque du hero selon sa class
        magie[2*i]->setStyleSheet("QWidget{border-image:none;background:#555555}"
                                "QPushButton{background:#888888}");
        magie[(2*i)+1]->setStyleSheet("QWidget{border-image:none;background:#555555}"
                                "QPushButton{background:#888888}");
       }
       //creation bouton
       conteneur_BoutonAction= new QWidget(this);
       QGridLayout* layout_action= new QGridLayout(conteneur_BoutonAction);
       principalLayout->addWidget(conteneur_BoutonAction,1,0,1,4);
       QObject::connect(systemDeCombat,SIGNAL(afficheBoutonAction()),conteneur_BoutonAction,SLOT(show()));
       QObject::connect(systemDeCombat,SIGNAL(enleveBoutonAction()),conteneur_BoutonAction,SLOT(hide()));

       QPushButton* bouton_attaquePhysqiueBasic= new QPushButton("Attaque",this);
       layout_action->addWidget(bouton_attaquePhysqiueBasic,0,0);
       QObject::connect(bouton_attaquePhysqiueBasic,SIGNAL(clicked()),systemDeCombat,SLOT(actionHero_attaqueBasic()));

       QPushButton* bouton_magie= new QPushButton("Sort",this);
       layout_action->addWidget(bouton_magie,0,1);
       QObject::connect(bouton_magie,SIGNAL(clicked()),this,SLOT(showMagie()));

       QPushButton* bouton_technique= new QPushButton("Technique",this);
       layout_action->addWidget(bouton_technique,0,2);
       QObject::connect(bouton_technique,SIGNAL(clicked()),this,SLOT(showTech()));

       QPushButton* bouton_defense=new QPushButton("Defense",this);
       layout_action->addWidget(bouton_defense,0,3);
       QObject::connect(bouton_defense,SIGNAL(clicked()),systemDeCombat,SLOT(actionHero_defense()));

       //conteneur widget hero
        groupeHero= new QScrollArea();
        groupeHero->setMinimumHeight(100);
        groupeHero->setMaximumHeight(100);
        groupeEnnemie->setMinimumHeight(200);
        groupeEnnemie->setMaximumHeight(200);
        groupeHero_conteneur= new QWidget();
        groupeHero_LayoutConteneur= new QHBoxLayout(groupeHero_conteneur);
        groupeHero->setWidgetResizable(true);
        groupeHero->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        groupeHero->setWidget(groupeHero_conteneur);
        principalLayout->addWidget(groupeHero,0,0,1,5);

        //tooltip
        bouton_attaquePhysqiueBasic->setToolTip("Attaque la cible avec votre arme");
        bouton_defense->setToolTip("Se mettre en position defensive");
        bouton_magie->setToolTip("Ouvre la liste de vos Magies");
        bouton_technique->setToolTip("Ouvre la liste de vos techniques");
        cible_texte->setToolTip("La cible choisie");
        resume->clear();
        //lien system et Interface
        QObject::connect(systemDeCombat,SIGNAL(afficheTexteDansResume(QString)),this,SLOT(afficheTexteDansResume(QString)));
        QObject::connect(systemDeCombat,SIGNAL(demandeUpdateCible()),this,SLOT(updateTextCible()));
        QObject::connect(systemDeCombat,SIGNAL(finCombat()),this,SLOT(signal_FinCombat()));
        QObject::connect(systemDeCombat,SIGNAL(nbMonstreDansLeNouveauCombat(int)),this,SLOT(updateAffichageMonstre(int)));
        QObject::connect(systemDeCombat,SIGNAL(resultatPrevision(QList<QString>)),this,SLOT(updatePrediction(QList<QString>)));
        QObject::connect(systemDeCombat,SIGNAL(sauvegarde()),this,SLOT(signal_Sauvegarde()));
  //lien data Interface
        creationCiblageAdversaire(NbEnnMax);//ajoutWidgetAdversaire
        //ajout widget hero
        for (int i=0;i<equipe.size();i++){
            Hero* heroPrincipal=equipe[i];
            hero_conteneurCliquable << new QWidgetCliquable(heroPrincipal,groupeEnnemie_conteneur);
            hero_Layout << new QGridLayout(hero_conteneurCliquable[i]);
            hero_conteneurCliquable[i]->setLayout(hero_Layout[i]);
            hero_TextNom << new QLabel(heroPrincipal->getNomEntite(),hero_conteneurCliquable[i]);
            hero_barVie << new QProgressBar(hero_conteneurCliquable[i]);
            hero_barVie[i]->setTextVisible(false);
            hero_TextVie << new QLabel(QString::number(heroPrincipal->getVie()) +"/"+ QString::number(heroPrincipal->getStatBaseVie()));
            hero_barMana << new QProgressBar(hero_conteneurCliquable[i]);
            hero_barMana[i]->setTextVisible(false);
            hero_TextMana << new QLabel(QString::number(heroPrincipal->getMana()) +"/"+ QString::number(heroPrincipal->getStatBaseMana()));
            hero_TextMana[i]->setAlignment(Qt::AlignCenter);
            hero_TextVie[i]->setAlignment(Qt::AlignCenter);
            hero_Layout[i] ->addWidget(hero_TextNom[i],0,0);
            hero_Layout[i] ->addWidget(hero_barVie[i],1,0);
            hero_Layout[i] ->addWidget(hero_TextVie[i],1,0);
            hero_Layout[i] ->addWidget(hero_barMana[i],2,0);
            hero_Layout[i] ->addWidget(hero_TextMana[i],2,0);
            QObject:: connect(heroPrincipal,SIGNAL(refreshMana(int,int,Entite*)),this,SLOT(updateManaHero(int,int,Entite*)));
            QObject:: connect(heroPrincipal,SIGNAL(refreshVie(int,int,Entite*)),this,SLOT(updateVieHero(int,int,Entite*)));
            QObject:: connect(heroPrincipal,SIGNAL(refreshNom(QString,Entite*)),this,SLOT(updateNomHero(QString,Entite*)));
            QObject:: connect(hero_conteneurCliquable[i],SIGNAL(clicked(Entite*)),this,SLOT(selectionCible(Entite*)));
            QObject:: connect(heroPrincipal,SIGNAL(demandeAfficheStat(Entite*)),this,SLOT(afficheStat(Entite*)));
            groupeHero_LayoutConteneur->addWidget(hero_conteneurCliquable[i]);
                //style
            hero_barVie[i]->setMaximumHeight(12);
            hero_barMana[i]->setMaximumHeight(12);
            hero_barVie[i]->setStyleSheet("QProgressBar::chunk{background-color: #11B723;"
                                       "border-radius:3px;}"
                                       "QProgressBar{border-radius:4px;border-style:solid;border-width:1px;border-color:#999999"
                                       "}");
            hero_barMana[i]->setStyleSheet("QProgressBar::chunk{background-color: #11FAF2;"
                                                          "border-radius:3px;}"
                                                          "QProgressBar{border-radius:4px;border-style:solid;border-width:1px;border-color:#999999"
                                                          "}");
            resume->setStyleSheet("QWidget{border-image:none;background:transparent}");
            cible_texte->setStyleSheet("QWidget{border-image:none;background:transparent}");
        }
        systemDeCombat->auberge_validation();
  //style
      principal->setStyleSheet("QWidget{border-image:url(ImagePng/fond.png)};");
      this->setStyleSheet("QPushButton{border-color:#666666;border-style:outset;border-width:2px;border-radius:7px;padding-left:3px;padding-right:3px}"
                      "QPushButton::pressed{border-style:inset}"
                      );
      groupeEnnemie->setStyleSheet("QWidget{border-image:none;background:transparent;border:none}");
      groupeHero->setStyleSheet("QWidget{border-image:none;background:transparent;border:none}");
      conteneur_BoutonAction->setStyleSheet("QWidget{border-image:none;background:transparent}");
      predicteur_conteneur->setStyleSheet("QWidget{border-image:none;background:transparent}");
}

//affectation

void InterfaceCombat::setEquipe(QList<Hero *> nouvelleEquipe){
    equipe=nouvelleEquipe;
    systemDeCombat->setEquipe(nouvelleEquipe);
    equipeModifier=true;
}

//lien
void InterfaceCombat::setConnectionAttaqueHeroClass(int numClass){
    //attaque comunne
        hero_apprend_Tech(1,numClass,"Analyse","Permet de trouver les faiblesses\nMana:5",SLOT(actionHero_analyse()));

    switch(numClass){
    case 0://Guerrier
          hero_apprend_Tech(0,numClass,"Frappe Puissante","Technique barbare qui consiste a frapper fort sur un ennemie \nMana:1",SLOT(actionHero_frappePuissante()));
          hero_apprend_Tech(5,numClass,"Brise-Crane","Frappe fort le crane de l'ennemie.Peut réduire la defense physique \nMana:0",SLOT(actionHero_BriseCrane()));
          hero_apprend_Tech(8,numClass,"Frappe Circulaire","Frappe en arc de cercle qui touche tout le monde\nMana:0",SLOT(actionHero_FrappeCirculaire()));
          hero_apprend_Magie(10,numClass,"Deculpo","Augmente l'attaque physique \nMana:25",SLOT(actionHero_deculpo()));
          hero_apprend_Tech(12,numClass,"Ryuken","Attaque magique qui vol du mana \nMana:0",SLOT(actionHero_ryuken()));
          hero_apprend_Tech(15,numClass,"Déprime","Attaque qui réduit la capacité offensive des attaques magiques\nMana:0",SLOT(actionHero_deprime()));
          hero_apprend_Tech(25,numClass,"Frappe Astral","Attaque une cible\nMana:10",SLOT(actionHero_frappeAstral()));
          hero_apprend_Tech(30,numClass,"Séisme","Fait trembler la terre\nMana:25",SLOT(actionHero_seisme()));
          hero_apprend_Tech(37,numClass,"Lame Dragon","Attaque une cible\nMana:20",SLOT(actionHero_lameDragon()));

        break;
    case 1://Mage
            hero_apprend_Magie(0,numClass,"Soin","Regenere peu de vie\nMana:5",SLOT(actionHero_soin()));
            hero_apprend_Magie(0,numClass,"Flamme","Attaque faible sur une cible \nMana:5",SLOT(actionHero_flamme()));
            hero_apprend_Magie(3,numClass,"Crame","Attaque faible sur tout les ennemie \nMana:8",SLOT(actionHero_crame()));
            hero_apprend_Magie(9,numClass,"Purification","Enleve tout les effects de la cible \nMana:10",SLOT(actionHero_purification()));
            hero_apprend_Magie(12,numClass,"Soin Avancé","Regenere la vie \nMana:15",SLOT(actionHero_soinAvance()));
            hero_apprend_Magie(17,numClass,"Bouclier","Augmente la defence physique \nMana:20",SLOT(actionHero_bouclier()));
            hero_apprend_Magie(18,numClass,"Blindage","Augmente la defence magique \nMana:30",SLOT(actionHero_blindage()));
            hero_apprend_Magie(19,numClass,"SuperFlamme","Attaque sur une cible \nMana:15",SLOT(actionHero_superFlamme()));
            hero_apprend_Magie(20,numClass,"SuperCrame","Attaque sur tout les ennemie \nMana:20",SLOT(actionHero_superCrame()));
            hero_apprend_Magie(21,numClass,"Soin Puissant","Regenere beaucoup de vie \nMana:45",SLOT(actionHero_soinPuissant()));
            hero_apprend_Magie(24,numClass,"Canalisation Magique","Augmente l'attque magique \nMana:40",SLOT(actionHero_canalisationMagique()));
            hero_apprend_Magie(25,numClass,"Booster","augmente la vitesse \nMana:50",SLOT(actionHero_booster()));
            hero_apprend_Magie(32,numClass,"MegaFlamme","Attaque puissante sur une cible Mana:25",SLOT(actionHero_megaFlamme()));
            hero_apprend_Magie(38,numClass,"MegaCrame","Attaque puissante sur tout les ennemie \nMana:35",SLOT(actionHero_megaCrame()));
            hero_apprend_Magie(43,numClass,"GigaFlamme","Attaque devastatrice sur une cible \nMana:50",SLOT(actionHero_gigaFlamme()));
            hero_apprend_Magie(50,numClass,"GigaCrame","Attaque devastatrice sur tout les ennemie \nMana:60",SLOT(actionHero_gigaCrame()));

        break;
    case 2://Paladin
          hero_apprend_Tech(0,numClass,"Frappe Puissante","Technique barbare qui consiste a frapper fort sur un ennemie \nMana:0",SLOT(actionHero_frappePuissante()));
          hero_apprend_Magie(0,numClass,"Soin","Regenere peu de vie\nMana:5",SLOT(actionHero_soin()));
          hero_apprend_Magie(9,numClass,"Purification","Enleve tout les effects de la cible \nMana:10",SLOT(actionHero_purification()));
          hero_apprend_Tech(12,numClass,"Ryuken","Attaque magique qui vol du mana \nMana:0",SLOT(actionHero_ryuken()));
          hero_apprend_Magie(13,numClass,"Crame","Attaque faible sur tout les ennemie \nMana:8",SLOT(actionHero_crame()));
          hero_apprend_Magie(14,numClass,"Soin Avancé","Regenere la vie \nMana:15",SLOT(actionHero_soinAvance()));
          hero_apprend_Magie(15,numClass,"Deculpo","Augmente l'attaque physique \nMana:25",SLOT(actionHero_deculpo()));
          hero_apprend_Tech(24,numClass,"Frappe Astral","Attaque une cible\nMana:10",SLOT(actionHero_frappeAstral()));
          hero_apprend_Magie(28,numClass,"Rappel","Reanime un mort a 50% de sa vie\nMana:100",SLOT(actionHero_rappel()));
          hero_apprend_Magie(32,numClass,"SuperCrame","Attaque sur tout les ennemie \nMana:20",SLOT(actionHero_superCrame()));
          hero_apprend_Magie(35,numClass,"Bouclier","Augmente la defence physique \nMana:20",SLOT(actionHero_bouclier()));
          hero_apprend_Tech(39,numClass,"Lame Dragon","Attaque une cible\nMana:20",SLOT(actionHero_lameDragon()));
          hero_apprend_Magie(45,numClass,"MegaCrame","Attaque puissante sur tout les ennemie \nMana:35",SLOT(actionHero_megaCrame()));

        break;
    case 3://Assasin
          hero_apprend_Tech(0,numClass,"Lame Empoisonné","Coup qui peut empoisonner sa cible \nMana:0",SLOT(actionHero_lameEmpoisonner()));
          hero_apprend_Tech(5,numClass,"Frappe Rapide","Frappe un ennemie a la vitesse de l'éclair",SLOT(actionHero_frappeRapide()));
          hero_apprend_Tech(7,numClass,"Nuage de poison","Lance un nuage de poison sur l'ennemie",SLOT(actionHero_nuagePoison()));


        break;
    case 4://Prete
        hero_apprend_Magie(0,numClass,"Soin","Regenere peu de vie\nMana:5",SLOT(actionHero_soin()));
        hero_apprend_Tech(0,numClass,"Ryuken","Attaque magique qui vol du mana \nMana:0",SLOT(actionHero_ryuken()));
        hero_apprend_Magie(9,numClass,"Purification","Enleve tout les effects de la cible \nMana:10",SLOT(actionHero_purification()));
        hero_apprend_Magie(12,numClass,"Soin Avancé","Regenere la vie \nMana:15",SLOT(actionHero_soinAvance()));
        hero_apprend_Magie(17,numClass,"Bouclier","Augmente la defence physique \nMana:20",SLOT(actionHero_bouclier()));
        hero_apprend_Magie(18,numClass,"Blindage","Augmente la defence magique \nMana:30",SLOT(actionHero_blindage()));
        hero_apprend_Magie(21,numClass,"Soin Puissant","Regenere beaucoup de vie \nMana:45",SLOT(actionHero_soinPuissant()));
        hero_apprend_Magie(23,numClass,"Booster","augmente la vitesse \nMana:50",SLOT(actionHero_booster()));
        hero_apprend_Magie(25,numClass,"Rappel","Reanime un mort a 50% de sa vie\nMana:100",SLOT(actionHero_rappel()));
        hero_apprend_Magie(29,numClass,"Multisoin","Soigne tout les alliés \nMana:150",SLOT(actionHero_multisoin()));
        hero_apprend_Magie(31,numClass,"Soin Complet","Regenere toute la vie \nMana:150",SLOT(actionHero_soinComplet()));
        hero_apprend_Magie(35,numClass,"SuperBouclier","Augmente la defence physique de tout les allié \nMana:125",SLOT(actionHero_superBouclier()));
        hero_apprend_Magie(38,numClass,"SuperBlindage","Augmente la defence magique de tout les allié \nMana:150",SLOT(actionHero_superBlindage()));
        hero_apprend_Magie(41,numClass,"Ressurection","Reanime un mort\nMana:200",SLOT(actionHero_ressurection()));
        hero_apprend_Magie(45,numClass,"SuperBooster","Augmente la vitesse de tout les allié \nMana:200",SLOT(actionHero_superBooster()));
        hero_apprend_Magie(51,numClass,"Omnisoin","Soigne tout les alliés \nMana:500",SLOT(actionHero_omnisoin()));

        break;
    default: //Source
        //boutton
            hero_apprend_Magie(0,numClass,"Soin","Regenere peu de vie\nMana:5",SLOT(actionHero_soin()));
            hero_apprend_Tech(0,numClass,"Frappe Puissante","Technique barbare qui consiste a frapper fort sur un ennemie \nMana:0",SLOT(actionHero_frappePuissante()));

        break;
    }
}

//action
void InterfaceCombat::creationCiblageAdversaire(int nbAdversaire){
    for(int i=0;i<nbAdversaire;i++){
    monstre_conteneurCliquable << new QWidgetCliquable(adversaire[i],groupeEnnemie_conteneur);
    monstre_Layout << new QGridLayout(monstre_conteneurCliquable[i]);
    monstre_barVie << new QProgressBar(monstre_conteneurCliquable[i]);
    monstre_barVie[i]->setTextVisible(false);
    monstre_barVie[i]->setMaximumWidth(300);
    monstre_TextNom << new QLabel(adversaire[i]->getNomEntite(),monstre_conteneurCliquable[i]);
    monstre_TextNom[i]->setAlignment(Qt::AlignCenter);
     conteneur_image<< new QLabel(monstre_conteneurCliquable[i]);
    monstre_Image <<  QPixmap("ImagePng/Inconnu.png");
    conteneur_image[i]->setAlignment(Qt::AlignCenter);

    conteneur_image[i]->setPixmap(monstre_Image[i]);
    monstre_Layout[i]->addWidget(monstre_barVie[i],0,0);
    monstre_Layout[i]->addWidget(monstre_TextNom[i],0,0);
    monstre_Layout[i]->addWidget(conteneur_image[i],1,0);
    monstre_Layout[i]->setSpacing(0);

    QObject:: connect(adversaire[i],SIGNAL(refreshVie(int,int,Entite*)),this,SLOT(updateVieMonstre(int,int,Entite*)));
    QObject:: connect(adversaire[i],SIGNAL(refreshNom(QString,Entite*)),this,SLOT(updateNomMonstre(QString,Entite*)));
    QObject:: connect(adversaire[i],SIGNAL(refreshImage(QString,Entite*)),this,SLOT(updateImageMonstre(QString,Entite*)));
    QObject:: connect(adversaire[i],SIGNAL(demandeAfficheStat(Entite*)),this,SLOT(afficheStat(Entite*)));
    QObject:: connect(monstre_conteneurCliquable[i],SIGNAL(clicked(Entite*)),this,SLOT(selectionCible(Entite*)));
    QObject:: connect(adversaire[i],SIGNAL(mort()),monstre_conteneurCliquable[i],SLOT(hide()));

    groupeEnnemie_LayoutConteneur->addWidget(monstre_conteneurCliquable[i]);
    //stylesheet
    monstre_barVie[i]->setMaximumHeight(12);
    monstre_barVie[i]->setStyleSheet("QProgressBar::chunk{background-color: #11B723;"
                                  "border-radius:3px;}"
                                  "QProgressBar{border-radius:4px;border-style:solid;border-width:1px;border-color:#999999"
                                  "}");


    }

}

void InterfaceCombat::nouveauCombat(){
    systemDeCombat->nouveauCombat();
}



//slot
void InterfaceCombat::afficheTexteDansResume(QString texte){
    if(texte!=""){
        resume->setText(resume->toPlainText()+texte+"\n");
        resume_ScrolBar->setValue(resume_ScrolBar->maximum());
    }
    fermeAutreMagTech();//ferme toute les fenettre
}

void InterfaceCombat::selectionCible(Entite *cibleWidget){

      systemDeCombat->selectionCible( cibleWidget);

}


void InterfaceCombat::showMagie(){

            magie[2*systemDeCombat->getHeroenAction()->getClasse()]->show(systemDeCombat->getHeroenAction()->getLevel());

}

void InterfaceCombat::showTech(){

            magie[(2*systemDeCombat->getHeroenAction()->getClasse())+1]->show(systemDeCombat->getHeroenAction()->getLevel());

}

void InterfaceCombat::fermeAutreMagTech(FenetreMagie *fenetre){
    for(int i=0;i<magie.size();i++ ){
        if(magie[i]!=fenetre){
            magie[i]->hide();
        }
    }
}

void InterfaceCombat::netoyageResume(){
    resume->clear();
}

void InterfaceCombat::afficheStat(Entite *Lentite){
    QDialog* afficheur = new QDialog();
    Entite* cible = Lentite;
    afficheur->setWindowTitle("Stat de "+cible->getNomEntite());
    QVBoxLayout* layoutScroll= new QVBoxLayout(afficheur);
    QScrollArea* scroll= new QScrollArea(afficheur);
    scroll->setWidgetResizable(true);
    afficheur->setLayout(layoutScroll);
    layoutScroll->addWidget(scroll);
    QWidget* conteneur= new QWidget(afficheur);
    QGridLayout* layoutConteneur= new QGridLayout(conteneur);
    conteneur->setLayout(layoutConteneur);
    scroll->setWidget(conteneur);
    QLabel* texteVie= new QLabel("Vie: "+QString::number(cible->getVie())+"/"+QString::number(cible->getStatBaseVie()),afficheur);
    QLabel* texteMana= new QLabel("Mana: "+QString::number(cible->getMana())+"/"+QString::number(cible->getStatBaseMana()),afficheur);
    QLabel* texteAttaqueP= new QLabel("Attaque Physique: "+QString::number(cible->getAttaquePhysique())+"/"+QString::number(cible->getStatBaseAttaquePhysique()),afficheur);
    QLabel* texteAttaqueM= new QLabel("Attaque Magique: "+QString::number(cible->getAttaqueMagique())+"/"+QString::number(cible->getStatBaseAttaqueMagique()),afficheur);
    QLabel* texteDefenseP= new QLabel("Defense Physique: "+QString::number(cible->getDefensePhysique())+"/"+QString::number(cible->getStatBaseDefensePhysique()),afficheur);
    QLabel* texteDefenseM= new QLabel("Defense Magique: "+QString::number(cible->getDefenseMagique())+"/"+QString::number(cible->getStatBaseDefenseMagique()),afficheur);
    QLabel* texteLevel= new QLabel("Niveau: "+QString::number(cible->getLevel()),afficheur);
    QLabel* texteVitesse= new QLabel("Vitesse: "+QString::number(cible->getVitesse())+"/"+QString::number(cible->getStatBaseVitesse()),afficheur);

    QString resume=cible->getResumeEtat();
    if(resume!=""){
    QTextEdit* resumeEtat=new QTextEdit(afficheur);
    resumeEtat->setText(resume);
    resumeEtat->setReadOnly(true);

    layoutConteneur->addWidget(resumeEtat,8,0,1,2);
    }

    layoutConteneur->addWidget(texteLevel,0,0);
    layoutConteneur->addWidget(texteVie,1,1);
    layoutConteneur->addWidget(texteMana,2,1);
    layoutConteneur->addWidget(texteAttaqueP,3,1);
    layoutConteneur->addWidget(texteAttaqueM,4,1);
    layoutConteneur->addWidget(texteDefenseP,5,1);
    layoutConteneur->addWidget(texteDefenseM,6,1);
    layoutConteneur->addWidget(texteVitesse,7,1);


    if(afficheur->exec()){}
    cible=0;
    delete afficheur;
}

void InterfaceCombat::afficheStatCible(){
   afficheStat(systemDeCombat->getCible());
}


void InterfaceCombat::auberge_validation(){
   afficheTexteDansResume( "Merci d'etre passé à notre auberge");
   systemDeCombat->auberge_validation();
}

//lien
void InterfaceCombat::hero_apprend_Magie(int niveauApprentissage, int numClass, QString nomMagie, QString descriptionMagie, const char *slot){
    magie[2*numClass]->creationBoutton(nomMagie,descriptionMagie,niveauApprentissage);
    QObject::connect(magie[2*numClass]->getLastBouton() ,SIGNAL(clicked()),systemDeCombat,slot);
}

void InterfaceCombat::hero_apprend_Tech(int niveauApprentissage, int numClass, QString nomTech, QString descriptionTech, const char *slot) {
    magie[(2*numClass)+1]->creationBoutton(nomTech,descriptionTech,niveauApprentissage);
    QObject::connect(magie[(2*numClass)+1]->getLastBouton(),SIGNAL(clicked()),systemDeCombat,slot);
}

void InterfaceCombat::show(){
    if(equipeModifier){
        for(int i=0;i<equipe.size();i++){
            for (int y=0; y<equipe.size();y++){
                if(equipe[i]==hero_conteneurCliquable[y]->getEntiteLier()){
                    groupeHero_LayoutConteneur->addWidget(hero_conteneurCliquable[y],i);
                }
            }

        }
        equipeModifier=false;
    }
    this->QScrollArea::show();
}

void InterfaceCombat::hide(){
    netoyageResume();
    this->QScrollArea::hide();
}

void InterfaceCombat::updateTextCible(){
    cible_texte->setText("Cible:"+systemDeCombat->getCible()->getNomEntite());
}

void InterfaceCombat::signal_FinCombat(){
    emit finCombat();
}

void InterfaceCombat::signal_Sauvegarde(){
    emit sauvegarde();
}

void InterfaceCombat::updateAffichageMonstre(int nbMonstre){
    for(int i=0;i<adversaire.size();i++){
        if(i<nbMonstre){
            monstre_conteneurCliquable[i]->show();
        }
        else{
             monstre_conteneurCliquable[i]->hide();
        }
    }
}

void InterfaceCombat::updatePrediction(QList<QString> Textprediction){
    for (int i=0;i<predictionTour.size();i++){
        bool ennemie=true;
        predictionTour[i]->setText(Textprediction[i]);
        for (int j=0;j<equipe.size();j++){
            if(Textprediction[i]==equipe[j]->getNomEntite()){
                ennemie=false;
                j=equipe.size();
            }
        }
        if(ennemie){
            predictionTour[i]->setStyleSheet("background: #FF0000;border-bottom-style: solid;border-bottom-width:1px;border-bottom-color:#000000");
        }
        else{
           predictionTour[i]->setStyleSheet("background: #3CBEE8;border-bottom-style: solid;border-bottom-width:1px;border-bottom-color:#000000");
        }
    }
}

void InterfaceCombat:: updateImageMonstre(QString lien, Entite *Lentite){
    for (int i=0;i<adversaire.size();i++){
        if(Lentite==adversaire[i]){
            if(!monstre_Image[i].load(lien)){
                monstre_Image[i].load("ImagePng/Inconnu.png");
            }
            conteneur_image[i]->setPixmap(monstre_Image[i]);
        }
    }
}

void InterfaceCombat:: updateManaHero(int actuel, int max, Entite *Lentite){
    for (int i=0; i<equipe.size();i++){
        if(Lentite==equipe[i]){
            hero_barMana[i]->setMaximum(max);
            hero_barMana[i]->setValue(actuel);
            hero_TextMana[i]->setText(QString::number(actuel)+"/"+QString::number(max));
            hero_TextMana[i]->update();

        }
    }
}

void InterfaceCombat:: updateNomHero(QString nom, Entite *Lentite){
    for (int i=0; i<equipe.size();i++){
        if(Lentite==equipe[i]){
            hero_TextNom[i]->setText(nom);
        }
    }
}

void InterfaceCombat::updateNomMonstre(QString nom, Entite *Lentite){
    for (int i=0;i<adversaire.size();i++){
        if(Lentite==adversaire[i]){
            monstre_TextNom[i]->setText(nom);
        }
    }
}

void InterfaceCombat::updateVieHero(int actuel, int max, Entite *Lentite){
    for (int i=0; i<equipe.size();i++){
        if(Lentite==equipe[i]){
            hero_barVie[i]->setMaximum(max);
            hero_barVie[i]->setValue(actuel);
            hero_TextVie[i]->setText(QString::number(actuel)+"/"+QString::number(max));
            hero_barVie[i]->update();
        }
    }
}

void InterfaceCombat::updateVieMonstre(int actuel, int max, Entite *Lentite){
    for (int i=0;i<adversaire.size();i++){
        if(Lentite==adversaire[i]){
            monstre_barVie[i]->setMaximum(max);
            monstre_barVie[i]->setValue(actuel);
            monstre_barVie[i]->update();//force la mise a jour
        }
    }
}

void InterfaceCombat::afficheBoutonAction(){
    conteneur_BoutonAction->show();
}
