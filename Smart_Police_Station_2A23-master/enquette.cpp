#include "enquette.h"

Enquette::Enquette()
{

}

Enquette::Enquette (QString id_enquette, QString sujet, QDate date_debut, QString type_enquette, QString indice)
{
    setId_enquette(id_enquette);
    setSujet(sujet);
    setDate_debut(date_debut);
    setType_enquette(type_enquette);
    setIndice(indice);

}

QSqlQueryModel *Enquette::afficher() const
{
    QSqlQuery requeteur;
    requeteur.prepare("Select id_enquette, sujet, date_debut, type_enquette, indice from Enquette");
    requeteur.exec();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(requeteur);
    model->setHeaderData(0, Qt::Horizontal, "ID Enquette");
    return model;
}

bool Enquette::ajouter()
{
    QSqlQuery requeteur;
    requeteur.prepare("INSERT INTO  Enquette(id_enquette, sujet, date_debut, type_enquette, indice) "
                      "values(:id_enquette, :sujet, :date_debut, :type_enquette, :indice)");
    requeteur.bindValue(":id_enquette", id_enquette());
    requeteur.bindValue(":sujet", sujet());
    requeteur.bindValue(":date_debut", date_debut());
    requeteur.bindValue(":type_enquette", type_enquette());
    requeteur.bindValue(":indice", indice());
    return requeteur.exec();
}

bool Enquette::supprimer(QString id_Enquette)
{
    QSqlQuery requeteur;
    requeteur.prepare("Delete from Enquette where id_Enquette = :id_Enquette");
    requeteur.bindValue(":id_Enquette", id_Enquette);
    return requeteur.exec();
}

bool Enquette::modifier()
{
    QSqlQuery requeteur;
    requeteur.prepare("Update Enquette set sujet = :sujet, date_debut = :date_debut, type_enquette = :type_enquette, indice = :indice "
                      "where id_enquette = :id_enquette");
    requeteur.bindValue(":id_enquette", id_enquette());
    requeteur.bindValue(":sujet", sujet());
    requeteur.bindValue(":date_debut", date_debut());
    requeteur.bindValue(":type_enquette", type_enquette());
    requeteur.bindValue(":indice", indice());
    return requeteur.exec();
}

QSqlQueryModel* Enquette::rechercherEnquette(QString critere, QString rech) const
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from enquette where "+critere+" like '"+rech+"%'");
    return model;
}

/*QSqlQueryModel* Agent::trierAgents(int critere, int ordre) const
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
}*/

/*QSqlQueryModel *Enquette::archiver(QString critere,QString rech) const
{

    QString sDate = QDate::currentDate().toString("dddd MMMM yyyy");
    QString date_debut = QDate::currentDate().toString("dddd MMMM yyyy") ;
    if(sDate != date_debut)
        {
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from enquette where "+critere+" like '"+rech+"%'");
    return model;}
   /* if(Today != date_debut)
    {
     QSqlQuery requeteur;

    requeteur.prepare("Select id_enquette, sujet, date_debut, type_enquette, indice from Enquette where date_debut <: Today");
    requeteur.exec();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(requeteur);
    //model->setHeaderData(0, Qt::Horizontal, "ID Enquette");
    return model;
    }*/


