#include "menuprincipal.h"

MenuPrincipal::MenuPrincipal(QList<Hero *> NouvelleEquipe, QWidget *parent) : QScrollArea(parent)
{
    equipe=NouvelleEquipe;
    equipe_memoIndicePremierHero=-1;

    menuPrincipal_conteneur= new QWidget(this);
    this->setWidget(menuPrincipal_conteneur);
    this->setWidgetResizable(true);
    menuPrincipal_conteneurLayout= new QGridLayout(menuPrincipal_conteneur);

    for (int i=0;i<equipe.size();i++){
       //creation afficheur equipe
        afficheurEquipe << new AfficheurPvMagie(equipe[i]);
        afficheurEquipe[i]->setMaximumHeight(100);
        afficheurEquipe[i]->setMaximumWidth(200);
        menuPrincipal_conteneurLayout->addWidget(afficheurEquipe[i],2*i,0,2,1);
       QObject::connect(afficheurEquipe[i],SIGNAL(clicked(Entite*)),this,SLOT(echangeHero(Entite*)));
    }


    //creation des button
    lance_CombatAlea= new QPushButton("Combat Aléatoire",menuPrincipal_conteneur);
    menuPrincipal_conteneurLayout->addWidget(lance_CombatAlea,0,1);
    QObject::connect(lance_CombatAlea,SIGNAL(clicked(bool)),this,SLOT(lanceCombatAleatoire()));

    lance_Auberge= new QPushButton("Auberge",menuPrincipal_conteneur);
    menuPrincipal_conteneurLayout->addWidget(lance_Auberge,1,1);
    QObject::connect(lance_Auberge,SIGNAL(clicked(bool)),this,SLOT(lancePassageAuberge()));

    afficheResume= new QPushButton("Resumé",menuPrincipal_conteneur);
    menuPrincipal_conteneurLayout->addWidget(afficheResume,2,1);
    QObject::connect(afficheResume,SIGNAL(clicked(bool)),this,SLOT(afficherResumer()));
}

void MenuPrincipal::lanceCombatAleatoire(){
    if(equipeEnVie()){
    emit combatAleatoire();
    }
    else{
        QMessageBox::about(this,"Aide","Il serait mieux d'aller dormir");
    }
}

void MenuPrincipal::lancePassageAuberge(){
    emit passageAuberge();
    refresh_afficheurEquipe();

}

void MenuPrincipal::echangeHero(Entite *entiteCliquer){
    if(equipe_memoIndicePremierHero<0){
        for (int i=0;i<equipe.size();i++){
            if(entiteCliquer==equipe[i]){
                equipe_memoIndicePremierHero=i;//memo de place premier hero
                afficheurEquipe[i]->setStyleSheet("QGroupBox{border: 1px outset #FF0000}"
                                                            "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;background:transparent}");
                i=equipe.size();//sorti de boucle

            }
        }
    }
    else{
        for (int i=0;i<equipe.size();i++){
            if(entiteCliquer==equipe[i]){
                //echange
                Hero* stock=equipe[equipe_memoIndicePremierHero];
                equipe[equipe_memoIndicePremierHero]=equipe[i];
                equipe[i]=stock;
                //refresh
                afficheurEquipe[i]->setNewEntite(equipe[i]);
                afficheurEquipe[equipe_memoIndicePremierHero]->setNewEntite(equipe[equipe_memoIndicePremierHero]);
                emit nouvelleConfigEquipe(equipe);
                //reset des val de memo
                afficheurEquipe[equipe_memoIndicePremierHero]->setStyleSheet("QGroupBox{border: 1px inset #000000}"
                                                                                       "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;background:transparent}");
                equipe_memoIndicePremierHero=-1;
                stock=0;
                i=equipe.size();//sorti de boucle
            }
       }
    }
}

void MenuPrincipal::refresh_afficheurEquipe(int i){
    afficheurEquipe[i]->refresh();
}

void MenuPrincipal::refresh_afficheurEquipe(){
    for (int i=0;i<equipe.size();i++){
       afficheurEquipe[i]->refresh();
    }
}

void MenuPrincipal::show(){
    refresh_afficheurEquipe();
    this->QScrollArea::show();
}

bool MenuPrincipal::equipeEnVie(){
    int total=0;
    for(int i=0;i<equipe.size();i++){
        total+=equipe[i]->getVie();
    }
    return total!=0;
}

void MenuPrincipal::afficherResumer(){
    if(equipe_memoIndicePremierHero>=0){
        QDialog* afficheur = new QDialog();
        Hero* cible = equipe[equipe_memoIndicePremierHero];
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

        //reset des val de memo
        afficheurEquipe[equipe_memoIndicePremierHero]->setStyleSheet("QGroupBox{border: 1px inset #000000}"
                                                                               "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;background:transparent}");
        equipe_memoIndicePremierHero=-1;
    }
    else{
        QMessageBox::about(this,"Aide","Choisie un hero d'abord");
    }
}
