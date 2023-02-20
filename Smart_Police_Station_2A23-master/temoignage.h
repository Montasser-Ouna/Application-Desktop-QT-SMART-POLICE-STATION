#ifndef ETUDIANT_H
#define ETUDIANT_H

#include "QString"
#include "QSqlQuery"
#include "QSqlQueryModel"

class Temoignage
{
public:
    Temoignage();
    Temoignage(QString, QString, QString, QString);

    // Getters
    QString id_t()const{ return Id_t;}
    QString nom_t()const{ return Nom_t;}
    QString contenu()const{ return Contenu;}
    QString id_citoyen()const{ return Id_citoyen;}
    // Setters
    void setId_t(QString id_t){ Id_t = id_t;}
    void setNom_t(QString nom_t){ Nom_t= nom_t;}
    void setContenu(QString contenu){ Contenu = contenu;}
    void setId_citoyen(QString id_citoyen){ Id_citoyen = id_citoyen;}

    QSqlQueryModel *afficher() const;
    bool ajouter();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel *trier(QString,QString);
private:

    QString Id_t, Id_citoyen, Nom_t, Contenu;
};

#endif // ETUDIANT_H
