#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QWebEngineView>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{

    ui->setupUi(this);
    TimerReceiveIR = new QTimer(this);



    connect(TimerReceiveIR, &QTimer::timeout, this, &MainWindow::display_irArD);
    connect(TimerReceiveIR, &QTimer::timeout, this, &MainWindow::display_irAvD);
    connect(TimerReceiveIR, &QTimer::timeout, this, &MainWindow::display_irArG);
    connect(TimerReceiveIR, &QTimer::timeout, this, &MainWindow::display_irAvG);

    //

    TimerReceiveIR->start(100);
    robot = new MyRobot(this);
    connect(robot, SIGNAL(updateUI(QByteArray)),this,SLOT(update()));

    //
    connect(robot,SIGNAL(updateUI(QByteArray)), this, SLOT(odometrie_g()));
    connect(robot, SIGNAL(updateUI(QByteArray)), this, SLOT(odometrie_d()));

    //
    xbox = new QGamepad();
    connect(xbox, SIGNAL(axisLeftXChanged(double)), this, SLOT(move_xbox()));
    connect(xbox, SIGNAL(axisLeftYChanged(double)), this, SLOT(move_xbox()));
    connect(xbox, SIGNAL(buttonBChanged(bool)), this, SLOT(stop()));


    manager = new QNetworkAccessManager();
    //Vue de la webcam du robot (independant du robot)
    view = new QWebEngineView();
    view->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    view->show();

    this->ui->camera->addWidget(view);


}

void MainWindow::update()
{
    QByteArray data = robot->DataReceived;
    maj_batterie(data);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

//UTILISATION DU CLAVIER

//Lorsque l'on appuie sur une touche, Ã§a va affectuer une des fonctions
void MainWindow::keyPressEvent(QKeyEvent* key_robot){
    switch(key_robot->key()){
    case Qt::Key_Z :    //Avancer
        robot->set_etat(1);
        break;
    case Qt::Key_Q :    //Gauche
        robot->set_etat(2);
        break;
    case Qt::Key_D :    //Droite
        robot->set_etat(3);
        break;
    case Qt::Key_S :    //Reculer
        robot->set_etat(4);
        break;
    case Qt::Key_R :    //Stop
        robot->set_etat(5);
        break;
    case Qt::Key_W :    //Filtre Gris
        cam_filtre(1);
        break;
    case Qt::Key_X :    //Filtre
        cam_filtre(2);
        break;
    case Qt::Key_C :
        cam_filtre(3);
        break;
    case Qt::Key_V :
        cam_filtre(4);
        break;
    case Qt::Key_B :
        cam_filtre(5);
        break;
    case Qt::Key_H :
        cam_filtre(6);
        break;
    case Qt::Key_J :
        cam_filtre(7);
        break;
    case Qt::Key_N :
        cam_reset();
        break;
    }
}

//Lorsque l'on relache, on s'arrete
void MainWindow::keyReleaseEvent(QKeyEvent* key_robot){
    robot->set_etat(5);
}

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
//MOUVEMENT CAMERA
void MainWindow::on_haut_camera_pressed()
{
    cam_haut();
}

void MainWindow::on_gauche_camera_pressed()
{
    cam_gauche();
}

void MainWindow::on_droite_camera_pressed()
{
    cam_droite();
}

void MainWindow::on_bas_camera_pressed()
{
    cam_bas();
}

void MainWindow::cam_haut()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200"));
    manager->get(request);
}
void MainWindow::cam_bas()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200"));
    manager->get(request);

}
void MainWindow::cam_gauche()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200"));
    manager->get(request);
}
void MainWindow::cam_droite()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200"));
    manager->get(request);
}
//Affichage Batterie

void MainWindow::maj_batterie(QByteArray data){    //A tester


      //Recupération de la valeur du robot
    unsigned char batterie = (data[2]);
    int valeur = (int)batterie;
    //Passage en pourcentage
    valeur = (valeur*100)/130;
    QString bat_string = QString::number(valeur);

    //Verification de l'état de la batterie : en marche, plus de batterie ou normal
    if(((unsigned int) valeur <= 100) && ((unsigned int) valeur > 0)){  //Normal
        ui->barre_batterie->setValue(valeur); //Si marche pas : test avec (int)robot->DataReceived[2]
        ui->titre_batterie->setText("Batterie : " + bat_string + "%");

    }
    else if(((unsigned int) valeur > 100)){ //En charge
        ui->barre_batterie->setValue(100);
        ui->titre_batterie->setText("Plus de batterie");

    }
    else{   //Plus de batterie
        ui->barre_batterie->setValue(0);

    }



}

void MainWindow::display_irArD()
{
    int ir=robot->get_irArD();
    ui->irArD->display(ir);

}

void MainWindow::display_irAvD()
{
    int ir=robot->get_irAvD();
    ui->irAvD->display(ir);



}

void MainWindow::display_irArG()
{
    int ir=robot->get_irArG();
    ui->irArG->display(ir);


}

void MainWindow::display_irAvG()
{
    int ir=robot->get_irAvG();
    ui->irAvG->display(ir);

}