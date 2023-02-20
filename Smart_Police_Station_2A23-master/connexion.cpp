#include "connexion.h"
#include "ui_connexion.h"
#include "mainwindow.h"

Connexion::Connexion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    ui->inputLogin->setFocus();
    ui->userRadio->setChecked(true);
    connect(this, SIGNAL(connect_moi(QString)), new MainWindow, SLOT(connect_agent(QString)));
}

Connexion::~Connexion()
{
    delete ui;
}

bool Connexion::creerConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_cpp");
    db.setUserName("c##montasser");
    db.setPassword("ouna0000");
    if(!db.open())
        return false;
    else
        return true;
}

bool Connexion::userExist(Agent& user)
{
    QSqlQuery requeteur;
    requeteur.prepare("Select login, password from agent");
    requeteur.exec();
    while(requeteur.next())
    {
        if(user.login() == requeteur.value(0) && user.password() == requeteur.value(1))
            return true;
    }
    return false;
}

bool Connexion::userExist(Agent& user, QString& matricule)
{
    QSqlQuery requeteur;
    requeteur.prepare("Select matricule, login, password, type from agent");
    requeteur.exec();
    while(requeteur.next())
    {
        if(user.login() == requeteur.value(1) && user.password() == requeteur.value(2)
                && user.type() == requeteur.value(3))
        {
            matricule = requeteur.value(0).toString();
            return true;
        }
    }
    return false;
}

void Connexion::on_connecter_clicked()
{
    Agent user;
    user.setLogin(ui->inputLogin->text());
    user.setPassword(ui->inputPwd->text());
    if(ui->adminRadio->isChecked())
        user.setType(1);
    else
        user.setType(0);
    QString matricule;
    if(userExist(user, matricule))
    {
        this->close();
        emit connect_moi(matricule);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("User not found"),
                              QObject::tr("Utilisateur non reconnue, veuillez réessayer!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Connexion::on_inputPwd_returnPressed()
{
    on_connecter_clicked();
}
void Connexion::on_inputLogin_returnPressed()
{
    on_connecter_clicked();
}
