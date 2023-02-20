#include "agent.h"
#include "mainwindow.h"
//#include <QMessageBox>

Agent::Agent()
{
    Matricule = "";
    Nom = "";
    Prenom = "";
    Login = "";
    Password = "";
    Mail = "";
    Poste = "";
    Grade = "";
    Ville = "";
    NomPere = "";
    NomMere = "";
    Image = "";
    Type = false;
    Socket = new QTcpSocket;

}

Agent::Agent(QString matricule, QString nom, QString prenom, QString login, QString password,
             QString mail, QString poste, QString grade, QDate dateNaiss, QString ville,
             QString nomPere, QString nomMere, QString image, bool type)
{
    Matricule = matricule;
    Nom = nom;
    Prenom = prenom;
    Login = login;
    Password = password;
    Mail = mail;
    Poste = poste;
    Grade = grade;
    DateNaiss = dateNaiss;
    Ville = ville;
    NomPere = nomPere;
    NomMere = nomMere;
    Image = image;
    Type = type;
    Socket = new QTcpSocket;
}
                                        /* ------------ CRUD -------------- */

bool Agent::bindValuesGeneral(QSqlQuery & requeteur, Agent & user)
{
    requeteur.bindValue(":matricule", user.matricule());
    requeteur.bindValue(":nom", user.nom());
    requeteur.bindValue(":prenom", user.prenom());
    requeteur.bindValue(":login", user.login());
    requeteur.bindValue(":password", user.password());
    requeteur.bindValue(":mail", user.mail());
    requeteur.bindValue(":ville", user.ville());
    requeteur.bindValue(":poste", user.poste());
    requeteur.bindValue(":grade", user.grade());
    requeteur.bindValue(":nompere", user.nomPere());
    requeteur.bindValue(":nommere", user.nomMere());
    requeteur.bindValue(":datenaiss", user.dateNaiss().toString("dd/MM/yyyy"));
    requeteur.bindValue(":type", user.type());
    requeteur.bindValue(":image", user.image());
    return requeteur.exec();
}


bool Agent::ajouterAgent(Agent & user)
{
    QSqlQuery requeteur;
    requeteur.prepare("Insert into "
                        "Agent(matricule, login, password, nom, prenom, datenaiss, mail, "
                            " type, poste, nompere, nommere, ville, image, grade) "
                        "values(:matricule, :login, :password, :nom, :prenom, :datenaiss, :mail, "
                            " :type, :poste, :nompere, :nommere, :ville, :image, :grade)");
    return bindValuesGeneral(requeteur, user);
}

void Agent::modifEntete(QSqlQueryModel* model) const
{
    model->setHeaderData(_MATRICULE, Qt::Horizontal, "Matricule");
    model->setHeaderData(_LOGIN, Qt::Horizontal, "Login");
    model->setHeaderData(_PASSWORD, Qt::Horizontal, "Password");
    model->setHeaderData(_NOM, Qt::Horizontal, "Nom");
    model->setHeaderData(_PRENOM, Qt::Horizontal, "Prenom");
    model->setHeaderData(_MAIL, Qt::Horizontal, "Mail");
    model->setHeaderData(_DATENAISS, Qt::Horizontal, "Naissance");
    model->setHeaderData(_POSTE, Qt::Horizontal, "Poste");
    model->setHeaderData(_GRADE, Qt::Horizontal, "Grade");
    model->setHeaderData(_NOMPERE, Qt::Horizontal, "Père");
    model->setHeaderData(_NOMMERE, Qt::Horizontal, "Mère");
    model->setHeaderData(_VILLE, Qt::Horizontal, "Ville");
    model->setHeaderData(_TYPE, Qt::Horizontal, "Type");
    model->setHeaderData(_IMAGE, Qt::Horizontal, "Image");
}

QSqlQueryModel* Agent::afficherAgents() const
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("Select "
                    "matricule, login, password, nom, prenom, datenaiss, "
                    "mail,  type, poste, nompere, nommere, ville, image, grade"
                    " From agent");
    modifEntete(model);
    return model;
}

bool Agent::modifierAgent(Agent & user)
{
    QSqlQuery requeteur;
    requeteur.prepare("Update Agent "
                        "Set login = :login, password = :password, nom = :nom, "
                            "prenom = :prenom, datenaiss = :datenaiss, mail = :mail, type = :type, "
                            "poste = :poste, nompere = :nompere, nommere = :nommere, ville = :ville, "
                            "image = :image, grade = :grade "
                        "Where matricule = :matricule");
    return bindValuesGeneral(requeteur, user);
}

bool Agent::supprimerAgent(QString& matricule)
{
    QSqlQuery requeteur;
    requeteur.prepare("Delete from Agent where matricule = :matricule");
    requeteur.bindValue(":matricule", matricule);
    return requeteur.exec();
}

                                        /* ------------ Métier -------------- */

QSqlQueryModel* Agent::rechercherAgent(QString & recherche, int critere) const
{
    QSqlQuery requeteur;
    QString sql;
    sql = "Select "
          "matricule, login, password, nom, prenom, datenaiss, "
          "mail,  type, poste, nompere, nommere, ville, image, grade"
          " From agent ";
    switch (critere)
    {
    case -1:
        sql += "Where matricule like :recherche OR login like :recherche OR password like :recherche"
                " OR nom like :recherche OR prenom like :recherche OR mail like :recherche"
                " OR nompere like :recherche OR nommere like :recherche OR poste like :recherche"
                " OR grade like :recherche OR ville like :recherche OR datenaiss like :recherche";
        break;
    case 0: sql += "Where matricule like :recherche"; break;
    case 1: sql += "Where nom like :recherche"; break;
    case 2: sql += "Where prenom like :recherche"; break;
    case 3: sql += "Where login like :recherche"; break;
    case 4: sql += "Where password like :recherche"; break;
    case 5: sql += "Where datenaiss like :recherche"; break;
    case 6: sql += "Where mail like :recherche"; break;
    case 7: sql += "Where poste like :recherche"; break;
    case 8: sql += "Where grade like :recherche"; break;
    case 9: sql += "Where nompere like :recherche"; break;
    case 10: sql += "Where nommere like :recherche"; break;
    }
    requeteur.prepare(sql);
    requeteur.bindValue(":recherche", '%' + recherche + '%');
    QSqlQueryModel* model = new QSqlQueryModel;
    requeteur.exec(); // executer avant de le passer au model
    model->setQuery(requeteur);
    modifEntete(model);
    return model;
}

QSqlQueryModel* Agent::trierAgents(int critere, int ordre) const
{
    QSqlQuery requeteur;
    QString sql;
    sql = "Select "
          "matricule, login, password, nom, prenom, datenaiss, "
          "mail,  type, poste, nompere, nommere, ville, image, grade"
          " From agent Order by ";
    switch (critere)
    {
    case 0: sql += "matricule"; break;
    case 1: sql += "nom"; break;
    case 2: sql += "prenom"; break;
    case 3: sql += "login"; break;
    case 4: sql += "password"; break;
    case 5: sql += "datenaiss"; break;
    case 6: sql += "mail"; break;
    case 7: sql += "poste"; break;
    case 8: sql += "grade"; break;
    case 9: sql += "nompere"; break;
    case 10: sql += "nommere"; break;
    }
    if(ordre == 0)
        sql += " ASC";
    else
        sql += " DESC";
    requeteur.prepare(sql);
    requeteur.exec(); // executer avant de le passer au model
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(requeteur);
    modifEntete(model);
    return model;
}
                                        /* ------------ Connexion au serveur -------------- */

void Agent::connectToServer(QString& serveurIP, int& serveurPort, QPushButton* cnx)
{
    Socket->connectToHost(serveurIP, serveurPort); // On se connecte au serveur demandé
    cnx->setEnabled(false);
}
