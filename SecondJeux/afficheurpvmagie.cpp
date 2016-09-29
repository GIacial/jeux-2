#include "afficheurpvmagie.h"

AfficheurPvMagie::AfficheurPvMagie(Entite* hero)
{
    entiteContenu=hero;
    this->setTitle(hero->getNomEntite());
    this->setStyleSheet("QGroupBox{border: 1px inset #000000}"
                                                "QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;background:transparent}");


    afficheurEquipe_layout = new QGridLayout(this);

    afficheurEquipe_Classe = new QLabel("Classe: "+hero->getNomClass(),this);
    afficheurEquipe_Classe->setAlignment(Qt::AlignLeft);

    afficheurEquipe_Vie = new QProgressBar(this);
    afficheurEquipe_Vie->setMaximum(hero->getStatBaseVie());
    afficheurEquipe_Vie->setValue(hero->getVie());
    afficheurEquipe_Vie->setMaximumHeight(11);
    afficheurEquipe_Vie->setTextVisible(false);
    afficheurEquipe_Vie->setStyleSheet("QProgressBar::chunk{background-color: #11B723;"
                                          "border-radius:3px;}"
                                          "QProgressBar{border-radius:4px;border-style:solid;border-width:1px;border-color:#999999"
                                          "}");

    afficheurEquipe_vie_texte= new QLabel(QString::number(hero->getVie())+"/"+QString::number(hero->getStatBaseVie()),this);
    afficheurEquipe_vie_texte->setAlignment(Qt::AlignCenter);

    afficheurEquipe_Mana = new QProgressBar(this);
    afficheurEquipe_Mana->setMaximum(hero->getStatBaseMana());
    afficheurEquipe_Mana->setValue(hero->getMana());
    afficheurEquipe_Mana->setMaximumHeight(11);
    afficheurEquipe_Mana->setTextVisible(false);
    afficheurEquipe_Mana->setStyleSheet("QProgressBar::chunk{background-color: #11FAF2;"
                                          "border-radius:3px;}"
                                          "QProgressBar{border-radius:4px;border-style:solid;border-width:1px;border-color:#999999"
                                          "}");

    afficheurEquipe_Mana_texte= new QLabel(QString::number(hero->getMana())+"/"+QString::number(hero->getStatBaseMana()),this);
    afficheurEquipe_Mana_texte->setAlignment(Qt::AlignCenter);

    afficheurEquipe_layout->addWidget(afficheurEquipe_Classe,0,0);
    afficheurEquipe_layout->addWidget(afficheurEquipe_Vie,1,0);
    afficheurEquipe_layout->addWidget(afficheurEquipe_vie_texte,1,0);
    afficheurEquipe_layout->addWidget(afficheurEquipe_Mana,2,0);
    afficheurEquipe_layout->addWidget(afficheurEquipe_Mana_texte,2,0);



}

void AfficheurPvMagie::mousePressEvent(QMouseEvent *){
    emit clicked(entiteContenu);
}

void AfficheurPvMagie::refresh(){
    this->setTitle(entiteContenu->getNomEntite());
    afficheurEquipe_Classe->setText("Classe: "+entiteContenu->getNomClass());
    afficheurEquipe_Vie->setMaximum(entiteContenu->getStatBaseVie());
    afficheurEquipe_vie_texte->setText(QString::number(entiteContenu->getVie())+"/"+QString::number(entiteContenu->getStatBaseVie()));
    afficheurEquipe_Vie->setValue(entiteContenu->getVie());
    afficheurEquipe_Mana->setMaximum(entiteContenu->getStatBaseMana());
    afficheurEquipe_Mana->setValue(entiteContenu->getMana());
    afficheurEquipe_Mana_texte->setText(QString::number(entiteContenu->getMana())+"/"+QString::number(entiteContenu->getStatBaseMana()));
}

void AfficheurPvMagie::setNewEntite(Entite *newEntite){
    entiteContenu=newEntite;
    refresh();
}
