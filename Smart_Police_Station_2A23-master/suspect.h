#ifndef SUSPECT_H
#define SUSPECT_H

#include "QString"
#include "QSqlQuery"
#include "QSqlQueryModel"

class Suspect
{
public:
    Suspect();
    Suspect(int, QString, QString, QString);

    // Getters
    int id_suspect()const{ return Id_suspect;}
    QString id_enquette()const{ return Id_enquette;}
    QString id_citoyen()const{ return Id_citoyen;}
    QString description()const{ return Description;}

    // Setters
    void setId_suspect(int id_suspect){ Id_suspect = id_suspect;}
    void setId_enquette(QString id_enquette){ Id_enquette = id_enquette;}
    void setId_citoyen(QString id_citoyen){ Id_citoyen = id_citoyen;}
    void setDescription(QString description){ Description = description;}


    QSqlQueryModel *afficher() const;
    bool ajouter();
    bool supprimer(int id_suspect);
    bool modifier();
private:

    int Id_suspect;
    QString Id_enquette,Id_citoyen,Description;
};

#endif // ETUDIANT_H
