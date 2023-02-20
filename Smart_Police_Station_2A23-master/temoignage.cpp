#include "temoignage.h"

Temoignage::Temoignage()
{

}

Temoignage::Temoignage (QString id_t, QString nom_t, QString contenu, QString id_citoyen)
{
    setId_t(id_t);
    setNom_t(nom_t);
    setContenu(contenu);
    setId_citoyen(id_citoyen);
}

QSqlQueryModel *Temoignage::afficher() const
{
    QSqlQuery requeteur;
    requeteur.prepare("Select * from Temoignage");
    requeteur.exec();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(requeteur);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    return model;
}

bool Temoignage::ajouter()
{
    QSqlQuery requeteur;
    requeteur.prepare("Insert Into Temoignage( id_citoyen, id_t, nom_t, contenu) values( :id_citoyen, :id_t, :nom_t, :contenu)");
    requeteur.bindValue(":id_citoyen", id_citoyen());
    requeteur.bindValue(":id_t", id_t());
    requeteur.bindValue(":nom_t", nom_t());
    requeteur.bindValue(":contenu", contenu());
    return requeteur.exec();
}

bool Temoignage::supprimer(QString id_t)
{
    QSqlQuery requeteur;
    requeteur.prepare("Delete from Temoignage where id_t = :id_t");
    requeteur.bindValue(":id_t", id_t);
    return requeteur.exec();
}

bool Temoignage::modifier()
{
    QSqlQuery requeteur;
    requeteur.prepare("Update Temoignage set nom_t = :nom_t, contenu = :contenu where id_t = :id_t");
    requeteur.bindValue(":id_t", id_t());
    requeteur.bindValue(":nom_t", nom_t());
    requeteur.bindValue(":contenu", contenu());
    return requeteur.exec();
}

QSqlQueryModel* Temoignage::trier(QString critere,QString ordre)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from temoignage order by "+critere+" "+ordre+"");
    return model;
}
