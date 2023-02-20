#ifndef MESSAGE_H
#define MESSAGE_H

#include <QListWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QTcpSocket>

class Agent;

class Message
{

public:
    explicit Message();
    ~Message();
    QVector<QString> usersConnect;
    QString userReseach;
    int context;

    // getters et setters
    QString content(){ return Content;}
    QString loginAgent(){ return LoginAgent;}
    QString id(){ return ID;}
    QString dateEnvoie(){ return DateEnvoie;}
    int etat(){ return Etat;}

    void setID(QString id){ ID = id;}
    void setContent(QString content){ Content = content;}
    void setLoginAgent(QString loginAgent){ LoginAgent = loginAgent;}
    void setDateEnvoie(QString date){ DateEnvoie = date;}
    void setEtat(int etat){ Etat = etat;}

    bool afficherListUtilisateur(QListWidget*, QString&) const;
    bool rechercherUtilisateurInList(QListWidget*, QString&, QString&) const;
    void fillListUserConnect(QListWidget * , QVector<QString>& ) const;
    bool sendMessage(Message& msg, Agent& user);
    bool supprimerMessage(QString& , QTcpSocket*, QString&);


private:
    QString ID;
    QString Content, LoginAgent;
    QString DateEnvoie;
    int Etat;

};

#endif // MESSAGE_H
