#include "suspect.h"

Suspect::Suspect()
{

}

Suspect::Suspect (int id_suspect,QString id_enquette, QString id_citoyen , QString description)
{
    setId_suspect(id_suspect);
    setId_enquette(id_enquette);
    setId_citoyen(id_citoyen);
    setDescription(description);

}

QSqlQueryModel *Suspect::afficher() const
{
    QSqlQuery requeteur;
    requeteur.prepare("Select * from Suspect");
    requeteur.exec();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(requeteur);
    model->setHeaderData(0, Qt::Horizontal, "ID Suspect");
    return model;
}

bool Suspect::ajouter()
{
    QSqlQuery requeteur;
    requeteur.prepare("INSERT INTO  Suspect(id_suspect, id_enquette, id_citoyen, description) "
                      "values( :id_suspect, :id_enquette, :id_citoyen, :description)");
     requeteur.bindValue(":id_suspect", id_suspect());
    requeteur.bindValue(":id_enquette", id_enquette());
    requeteur.bindValue(":id_citoyen", id_citoyen());
    requeteur.bindValue(":description", description());

    return requeteur.exec();
}

bool Suspect::supprimer(int id_suspect)
{
    QSqlQuery requeteur;
    requeteur.prepare("Delete from Suspect where id_suspect = :id_suspect");
    requeteur.bindValue(":id_suspect", id_suspect);
    return requeteur.exec();
}

bool Suspect::modifier()
{
    QSqlQuery requeteur;
    requeteur.prepare("Update Suspect set description = :description where id_suspect = :id_suspect");
    requeteur.bindValue(":id_suspect", Id_suspect);
    requeteur.bindValue(":description", description());

    return requeteur.exec();
}
