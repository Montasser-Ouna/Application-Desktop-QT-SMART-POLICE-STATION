#ifndef AGENT_H
#define AGENT_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QtNetwork>
#include <QDataStream>
#include <QMessageBox>
#include <QPushButton>

#include "message.h"

enum {_MATRICULE, _LOGIN, _PASSWORD, _NOM, _PRENOM, _DATENAISS,
      _MAIL, _TYPE, _POSTE, _NOMPERE, _NOMMERE, _VILLE, _IMAGE, _GRADE};

enum {_ACCEUIL, _UTILISATEUR, _DOSSIER};

enum {_LISTE, _TCHAT, _CONFIG};

enum {_AFFICHER, _AJOUTER, _MODIFIER};

class Agent
{
public:
    Agent();
    Agent(QString matricule, QString nom, QString prenom, QString login,
          QString password, QString mail, QString poste, QString grade,
          QDate dateNaiss, QString ville, QString nomPere, QString nomMere,
          QString image, bool type);

    bool connectToMsg = false;
    QTcpSocket *Socket; // Représente le serveur

    QString matricule(){ return Matricule;}
    QString nom(){ return Nom;}
    QString prenom(){ return Prenom;}
    QString login(){ return Login;}
    QString password(){ return Password;}
    QString mail(){ return Mail;}
    QString poste(){ return Poste;}
    QString grade(){ return Grade;}
    QDate dateNaiss(){ return DateNaiss;}
    QString ville(){ return Ville;}
    QString nomPere(){ return NomPere;}
    QString nomMere(){ return NomMere;}
    QString image(){ return Image;}
    bool type(){ return Type;}

    void setMatricule(QString matricule){ Matricule = matricule;}
    void setNom(QString nom){ Nom = nom;}
    void setPrenom(QString prenom){ Prenom = prenom;}
    void setLogin(QString login){ Login = login;}
    void setPassword(QString password){ Password = password;}
    void setMail(QString mail){ Mail = mail;}
    void setPoste(QString poste){ Poste = poste;}
    void setGrade(QString grade){ Grade = grade;}
    void setDateNaiss(QDate dateNaiss){ DateNaiss = dateNaiss;}
    void setNomPere(QString nomPere){ NomPere = nomPere;}
    void setNomMere(QString nomMere){ NomMere = nomMere;}
    void setImage(QString image){ Image = image;}
    void setVille(QString ville){ Ville = ville;}
    void setType(bool type){ Type = type;}

    // CRUD de l'entite Agent
    bool ajouterAgent(Agent&);
    QSqlQueryModel* afficherAgents()const;
    bool modifierAgent(Agent&);
    bool supprimerAgent(QString&);

    // Metiers et autres fonctions
    bool bindValuesGeneral(QSqlQuery&, Agent&);
    QSqlQueryModel* rechercherAgent(QString&, int critere = -1) const;
    void modifEntete(QSqlQueryModel*) const;
    QSqlQueryModel* trierAgents(int critere = 0, int ordre = 0) const;

    // fonction de communication avec le serveur
    void connectToServer(QString&, int&, QPushButton* cnx = nullptr);
    bool sendMessage(Message&, QString);

private:
    QString Matricule, Nom, Prenom, Login, Password;
    QString Mail, Poste, Grade, Ville;
    QString NomPere, NomMere, Image;
    bool Type;
    QDate DateNaiss;
};

#endif // AGENT_H
