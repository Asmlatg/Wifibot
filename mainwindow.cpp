#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{

    ui->setupUi(this);
    TimerReceiveIR = new QTimer(this);


}



MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

/

//Fonctions reliees aux boutons :
void MainWindow::connexion()
{
   robot->doConnect();
}

void MainWindow::avancer()
{
    robot->set_etat(1);

}

void MainWindow::gauche()
{
     robot->set_etat(2);
}

void MainWindow::droite()
{
     robot->set_etat(3);
}

void MainWindow::reculer()
{
     robot->set_etat(4);
}

void MainWindow::stop()
{
     robot->set_etat(5);
}

void MainWindow::hgauche()
{
     robot->set_etat(6);
}

void MainWindow::bgauche()
{
     robot->set_etat(7);
}

void MainWindow::hdroite()
{
     robot->set_etat(8);
}

void MainWindow::bdroite()
{
     robot->set_etat(9);
}


//MOUVEMENT INTERFACE
void MainWindow::on_Gauche_pressed()
{
    gauche();
}

void MainWindow::on_avancer_pressed()
{
    avancer();
}

void MainWindow::on_droite_pressed()
{
    droite();
}

void MainWindow::on_reculer_pressed()
{
    reculer();
}

void MainWindow::on_hgauche_pressed()
{
    hgauche();
}

void MainWindow::on_hdroite_pressed()
{
    hdroite();
}

void MainWindow::on_bgauche_pressed()
{
    bgauche();
}

void MainWindow::on_bdroite_pressed()
{
    bdroite();
}

void MainWindow::on_connexion_clicked()
{
    connexion();
}

void MainWindow::on_avancer_released()
{
    stop();
}

void MainWindow::on_hdroite_released()
{
    stop();
}

void MainWindow::on_droite_released()
{
    stop();
}

void MainWindow::on_bdroite_released()
{
    stop();
}

void MainWindow::on_reculer_released()
{
    stop();
}

void MainWindow::on_bgauche_released()
{
    stop();
}

void MainWindow::on_Gauche_released()
{
    stop();
}

void MainWindow::on_hgauche_released()
{
    stop();
}



//CHANGEMENT VITESSE ET AFFICHAGE
void MainWindow::on_slide_vitesse_valueChanged(int value)
{
    //Change la vitesse du robot
    robot->set_vitesse(value);
    //Affiche la vitesse et le pourcentage sur l'interface
    int vit = robot->get_vitesse();
    QString vit_string = QString::number(vit);
    double pourcentage = ((vit-120)*100/120);
    QString pourcentage_string = QString::number(pourcentage);
    ui->titre_vitesse->setText(vit_string + " (" + pourcentage_string + "%)");

}














