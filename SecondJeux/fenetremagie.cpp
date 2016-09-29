#include "fenetremagie.h"

FenetreMagie::FenetreMagie() :
    QScrollArea()
{
    principal= new QWidget(this);
    this->setWidget(principal);
    this->setWidgetResizable(true);
    principal_layout= new QGridLayout(principal);
    principal_layout->setSpacing(0);
    this->setVisible(false);

    QPushButton* ferme = new QPushButton("X",this);
    ferme->setGeometry(0,0,15,15);
    QObject::connect(ferme,SIGNAL(clicked()),this,SLOT(close()));

    QShortcut* ferme_raccouci= new QShortcut(Qt::Key_Escape,this);
    QObject::connect(ferme_raccouci,SIGNAL(activated()),this,SLOT(close()));

    //style
    ferme->setStyleSheet("QPushButton{border-radius:2px;border-style:outset;border-color:#666666;background:#DD2222;border-width:1px;text-align:center}");
}


//action

void FenetreMagie::creationBoutton(QString texte, QString toolTipTexte,int level){
    QPushButton* newButton=new QPushButton(texte,this);//nouveau bouton
    listeBoutton << newButton;//enregistre le nouveau button
    int taille=listeBoutton.size();
    principal_layout->addWidget(newButton,floor((taille-1)/4),(taille-1)%4);//place le bouton
    QObject::connect(newButton,SIGNAL(clicked()),this,SLOT(close()));//lie le butoon
    newButton->setToolTip(toolTipTexte);//mets le tool tip
    listeNiveau << level;//enregistre le lvl du button
}

//recup
QPushButton* FenetreMagie::getBouton(int place){
    int taille=listeBoutton.size();
    if(place<taille){
    return listeBoutton.at(place);
    }

     return 0;

}
QPushButton* FenetreMagie::getLastBouton(){
    return listeBoutton.at(listeBoutton.size()-1);
}

//slot

void FenetreMagie::show(int level){
    int taille=listeBoutton.size();
    for(int i=0;i<taille;i++){
        if(level>=listeNiveau.at(i)){
            listeBoutton.at(i)->show();
        }
        else{
            listeBoutton.at(i)->hide();
        }
    }
    emit affiche(this);
    this->QScrollArea::show();//utilise le show du parent
}
