#ifndef ENQUETTE_H
#define ENQUETTE_H

#include "QString"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include "QDateTime"


//#include <QSqlDatabase>
//#include <QtNetwork>
//#include <QDataStream>
//#include <QMessageBox>
//#include <QPushButton>

class Enquette
{
public:
    Enquette();
    Enquette(QString id_enquette, QString sujet, QDate date_debut, QString type_enquette, QString indice);

    // Getters
    QString id_enquette()const{ return Id_enquette;}
    QString sujet()const{ return Sujet;}
    QDate date_debut()const{ return Date_debut;}
    QString type_enquette()const{ return Type_enquette;}
    QString indice()const{ return Indice;}
    // Setters
    void setId_enquette(QString id_enquette){ Id_enquette = id_enquette;}
    void setSujet(QString sujet){ Sujet= sujet;}
    void setDate_debut(QDate date_debut){ Date_debut= date_debut;}
    void setType_enquette(QString type_enquette){ Type_enquette = type_enquette;}
    void setIndice(QString indice){ Indice = indice;}

    QSqlQueryModel *afficher() const;
    bool ajouter();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel* rechercherEnquette(QString,QString) const;
    QSqlQueryModel * archiver(QString,QString) const;
private:
    QString Id_enquette;
    QString Sujet, Type_enquette, Indice;
    QDate Date_debut;
};

#endif // ETUDIANT_H
