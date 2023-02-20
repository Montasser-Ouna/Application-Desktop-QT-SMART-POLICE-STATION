#include "message.h"
#include "agent.h"
#include <QJsonObject>
#include <QJsonDocument>

Message::Message()
{
}

Message::~Message()
{
}

bool Message::afficherListUtilisateur(QListWidget * list, QString& exclude) const
{
    QSqlQuery requeteur;
    QString sql;
    sql = "Select "
          "matricule, login"
          " From agent ";
    requeteur.prepare(sql);
    if(requeteur.exec())
    {
        list->insertItem(0, "Tout le monde");
        list->item(0)->setForeground(Qt::blue);
        int i=1;
        while(requeteur.next() && ++i)
        {
            if(requeteur.value(1).toString() != exclude)
                list->insertItem(i, requeteur.value(1).toString());
        }
        return true;
    }
    else
        return false;
}

bool Message::rechercherUtilisateurInList(QListWidget * list, QString& search, QString& exclude) const
{
    QSqlQuery requeteur;
    QString sql;
    sql = "Select "
          "matricule, login"
          " From agent Where login like :login";
    requeteur.prepare(sql);
    requeteur.bindValue(":login", '%' + search + '%');
    if(requeteur.exec())
    {
        list->insertItem(0, "Tout le monde");
        list->item(0)->setForeground(Qt::blue);
        int i=1;
        while(requeteur.next() && ++i)
        {
            if(requeteur.value(1).toString() != exclude)
                list->insertItem(i, requeteur.value(1).toString());
        }
        return true;
    }
    else
        return false;
}

void Message::fillListUserConnect(QListWidget * list, QVector<QString>& userList) const
{
    for(int i(0); i<userList.size(); ++i)
        list->insertItem(i, userList[i]);
}

bool Message::sendMessage(Message& msg, Agent& user)
{
    if (msg.content().isEmpty())
        return false; // We don't send empty messages
    if(msg.content() == "")
        return false;
    int i(0), cpt(msg.content().size() - 1);
    while (cpt && msg.content()[--cpt] == ' ') { ++i;}
    if(i+1 == msg.content().size())
        return false;
    // create a QDataStream operating on the socket
    QDataStream clientStream(user.Socket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("text")] = msg.content();
    message[QStringLiteral("sender")] = user.login();
    message[QStringLiteral("date")] = msg.dateEnvoie();
    message[QStringLiteral("receiver")] = msg.userReseach;
    message[QStringLiteral("context")] = msg.context;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
    return true;
}

bool Message::supprimerMessage(QString& id, QTcpSocket* socket, QString& login)
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(socket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("supp_msg");
    message[QStringLiteral("id_msg")] = id;
    message[QStringLiteral("sender")] = login;
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
    return true;
}
