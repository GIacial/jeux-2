#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    creationEquipe();//charge ou cree une equipe
    //mise en place
    conteneurCentralWidget= new QWidget(this);
    conteneurCentralWidget_Layout= new QGridLayout(conteneurCentralWidget);
    interfaceCombat= new InterfaceCombat(equipe,equipe.size()*5);
    conteneurCentralWidget_Layout->addWidget(interfaceCombat);
    interfaceCombat->hide();

    menuPrincipal= new MenuPrincipal(equipe,conteneurCentralWidget);
    conteneurCentralWidget_Layout->addWidget(menuPrincipal);
    this->setCentralWidget(conteneurCentralWidget);

    //lien
    QObject::connect(interfaceCombat,SIGNAL(sauvegarde()),this,SLOT(sauvegarde()));
    QObject::connect(interfaceCombat,SIGNAL(finCombat()),this,SLOT(MenuPrincipalToInterfaceCombat()));
    QObject::connect(menuPrincipal,SIGNAL(combatAleatoire()),this,SLOT(MenuPrincipalToInterfaceCombat()));
    QObject::connect(menuPrincipal,SIGNAL(passageAuberge()),interfaceCombat,SLOT(auberge_validation()));
    QObject::connect(menuPrincipal,SIGNAL(nouvelleConfigEquipe(QList<Hero*>)),this,SLOT(nouvelleConfigEquipeHero(QList<Hero*>)));


    //fabrication menu
    QMenu* menuOutils= new QMenu("Outils");
    menuBar()->addMenu(menuOutils);
    QMenu* menuDebug= new QMenu("DebugTool");
    menuBar()->addMenu(menuDebug);

    //les action
        QAction* netoyage= new QAction("Netoyage Résumé",this);
        menuOutils->addAction(netoyage);
        QObject::connect(netoyage,SIGNAL(triggered()),interfaceCombat,SLOT(netoyageResume()));
        //debug
        QAction* afficheStatCible= new QAction("Stat cible",this);
        menuDebug->addAction(afficheStatCible);
        QObject::connect(afficheStatCible,SIGNAL(triggered()),interfaceCombat,SLOT(afficheStatCible()));

        QAction* heroLvlMax = new QAction("Hero lvl:100",this);
        menuDebug->addAction(heroLvlMax);
        QObject::connect(heroLvlMax,SIGNAL(triggered()),this,SLOT(heroToLvlMax()));

        QAction* nouveauCombat= new QAction("Nouveau Combat",this);
        menuDebug->addAction(nouveauCombat);
        QObject::connect(nouveauCombat,SIGNAL(triggered()),interfaceCombat,SLOT(nouveauCombat()));

        QAction* AfficheBoutonAction= new QAction("Afficher les boutons",this);
        menuDebug->addAction(AfficheBoutonAction);
        QObject::connect(AfficheBoutonAction,SIGNAL(triggered()),interfaceCombat,SLOT(afficheBoutonAction()));


    //taille
        this->setGeometry(QApplication::desktop()->screenGeometry().width()/5//recup la largeur de l'ecran
                          ,QApplication::desktop()->screenGeometry().height()/5
                          ,QApplication::desktop()->screenGeometry().width()*0.5,
                          QApplication::desktop()->screenGeometry().height()*0.75);
        //style
           // setStyleSheet("QObject{background:#FFFFFF;}"
                         // "QPushButton{border: 1px solid #000000;border-radius:7px}");//border: 3px solid #000000 pour bordure

}

void MainWindow::selectNbHeroMonstre(){
    QDialog* option_conteneur= new QDialog(this);
        QVBoxLayout* option_layout= new QVBoxLayout(option_conteneur);
        QLabel* option_nbHero_text= new QLabel("Nombre de hero",option_conteneur);
        option_layout->addWidget(option_nbHero_text);
        QSpinBox* option_nbHero= new QSpinBox(option_conteneur);
        option_nbHero->setMinimum(1);
        option_nbHero->setValue(1);
        option_layout->addWidget(option_nbHero);
        QPushButton* close = new QPushButton("ok",option_conteneur);
        option_layout->addWidget(close);
        QObject::connect(close,SIGNAL(clicked()),option_conteneur,SLOT(close()));
        option_conteneur->setMinimumSize(200,100);
        if(option_conteneur->exec()){}
         nbHero=option_nbHero->value();


        delete option_conteneur;
}

void MainWindow::MenuPrincipalToInterfaceCombat(){
    if(menuPrincipal->isHidden()){
            QTimer* timer= new QTimer(this);
            QObject::connect(timer,SIGNAL(timeout()),interfaceCombat,SLOT(hide()));//cache interfaceCombat
            QObject::connect(timer,SIGNAL(timeout()),menuPrincipal,SLOT(show()));//cache interfaceCombat
            QObject::connect(timer,SIGNAL(timeout()),timer,SLOT(deleteLater()));//delete timer
            timer->setSingleShot(true);
            timer->start(2000);
    }
    else{

        menuPrincipal->hide();
        interfaceCombat->nouveauCombat();
        interfaceCombat->show();

    }
}

void MainWindow::sauvegarde(){

    QFile fichier ("save/"+NomEquipe+".sav");

        if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::warning(this, "ERREUR", "Attention, votre progression n'a pas pu être sauvegardé !");//affiche une erreur
        }
        else{
            QTextStream save(&fichier);
            Hero*  heroPrincipal;
            //sauvegarde des variable pas Hero
            save<<nbHero<<"\n";
            for(int i=0;i<equipe.size();i++){
                heroPrincipal=equipe[i];


          //mettre les truc a sauvegarder des hero ici
               save<< heroPrincipal->getNomEntite()<<"\n";
               save<<heroPrincipal->getClasse()<<"\n";
               save << heroPrincipal->getLevel() << "\n";
               save << heroPrincipal->getXp()  << "\n";

               save << heroPrincipal->getStatBaseVie() << "\n";
               save << heroPrincipal->getStatBaseMana() << "\n";
               save << heroPrincipal->getStatBaseAttaquePhysique() << "\n";
               save << heroPrincipal->getStatBaseAttaqueMagique()  << "\n";
               save << heroPrincipal->getStatBaseDefensePhysique()  << "\n";
               save << heroPrincipal->getStatBaseDefenseMagique()  << "\n";
               save << heroPrincipal->getStatBaseVitesse()  << "\n";

            }
          //fin de la sauvegarde
          fichier.close();
        }

}

void MainWindow::chargement(){
    QFile save ("save/"+NomEquipe+".sav");

        if(!save.open(QIODevice::ReadOnly | QIODevice::Text)){
          QMessageBox::warning(this, "ERREUR : "+NomEquipe, "Attention, votre progression n'a pas pu être chargé !");//affiche une erreur
        }
        else{
            QTextStream lecture(&save);
            lecture.seek(0);
            nbHero=lecture.readLine().toInt();

            Hero*  heroPrincipal;
            for (int i=0;i<nbHero;i++){//creation des Hero
                 heroPrincipal = new Hero();
                equipe << heroPrincipal;

            //chargement des hero

            heroPrincipal->setNomEntite(lecture.readLine());
            heroPrincipal->setClass(lecture.readLine().toInt());
            heroPrincipal->setLevel(lecture.readLine().toInt());
            heroPrincipal->setXp(lecture.readLine().toInt());

            heroPrincipal->setStatBaseVie(lecture.readLine().toInt());
            heroPrincipal->setStatBaseMana(lecture.readLine().toInt());
            heroPrincipal->setStatBaseAttaquePhysique(lecture.readLine().toInt());
            heroPrincipal->setStatBaseAttaqueMagique(lecture.readLine().toInt());
            heroPrincipal->setStatBaseDefensePhysique(lecture.readLine().toInt());
            heroPrincipal->setStatBaseDefenseMagique(lecture.readLine().toInt());
            heroPrincipal->setStatBaseVitesse(lecture.readLine().toInt());

            //refresh les widget
            heroPrincipal->soinAuberge();
            heroPrincipal->initialisationCombat();
            }
          //fin chargement
          save.close();
        }
}

void MainWindow::creationEquipe(){
    NomEquipe=QInputDialog::getText(this,"Nom de votre Equipe","Comment ce nommes votre équipe",QLineEdit::Normal);
    QFile test ("save/"+NomEquipe+".sav");
    if(test.exists()){
        chargement();
    }
    else{
        selectNbHeroMonstre();//select des nombre hero et ennemie
        for (int i=0;i<nbHero;i++){//creation des Hero
            Hero* heroPrincipal = new Hero();
            equipe << heroPrincipal;
            }
        //creation de la fenetre de demande
            QDialog* fenetreDemande= new QDialog();

            QComboBox* demandeClasse= new QComboBox(fenetreDemande);
            demandeClasse->addItem("Guerrier");
            demandeClasse->addItem("Mage");
            demandeClasse->addItem("Paladin");
            demandeClasse->addItem("Assasin");
            demandeClasse->addItem("Prêtre");
            //demandeClasse->addItem("Source");
            QLineEdit* demandeNom= new QLineEdit(fenetreDemande);
            QVBoxLayout* layoutDemande= new QVBoxLayout(fenetreDemande);
            QLabel* nommezVotreAvatar=new QLabel("Nommez votre Avatar",fenetreDemande);
            QPushButton* fermetureDemande= new QPushButton("OK",fenetreDemande);
            QObject::connect(fermetureDemande,SIGNAL(clicked()),fenetreDemande,SLOT(close()));
            layoutDemande->addWidget(new QLabel("Choissisez votre classe",fenetreDemande));
            layoutDemande->addWidget(demandeClasse);
            layoutDemande->addWidget(nommezVotreAvatar);
            layoutDemande->addWidget(demandeNom);
            layoutDemande->addWidget(fermetureDemande);

        for(int i=0;i<equipe.size();i++){
            do{
                //mets les valeur deja existante
                demandeClasse->setCurrentIndex(equipe[i]->getClasse());
                demandeNom->setText(equipe[i]->getNomEntite());
                fenetreDemande->setWindowTitle("Hero n°"+QString::number(i+1));
                //affichage
                if(fenetreDemande->exec()){}//demande de nommer le hero
                //sauvegarde des info
                equipe[i]->setNomEntite(demandeNom->text());
                equipe[i]->setClass(demandeClasse->currentIndex());
            }while(heroExistDeja(i));
        }
        //supression fenetre
        delete fenetreDemande;
    }
}

bool MainWindow::heroExistDeja(int i) const{
    bool existe=false;
    for(int j=0;j<equipe.size();j++){
        if(!(j==i)){
           existe= existe || (equipe[i]->getNomClass()==equipe[j]->getNomClass() && equipe[j]->getNomEntite()==equipe[i]->getNomEntite());//verif si meme classe et meme nom
           //true=si existe ou meme est vrai
           //false si meme est faux
        }
    }
    return existe;
}

void MainWindow::nouvelleConfigEquipeHero(QList<Hero*> nouvelleEquipe){
    equipe=nouvelleEquipe;
    interfaceCombat->setEquipe(nouvelleEquipe);
}


void MainWindow::heroToLvlMax(){
    for(int i=0;i<equipe.size();i++){
    if(equipe[i]->getLevel()<100){
        int nbLevelUp=100-equipe[i]->getLevel();
        for(int y=1;y<=nbLevelUp;y++){
            equipe[i]->levelUp();
        }
    }
    }
}
