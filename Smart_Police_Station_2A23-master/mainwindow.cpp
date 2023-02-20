#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QDebug>
#include <QVector>
#include <QAbstractSocket>
#include <QInputDialog>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QDateTime>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SGSP - Username: " + user.matricule() + " is connected");
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabWidget_user->setTabEnabled(2, false);
    ui->tabWidget_user->setTabEnabled(3, false);
    ui->tabWidget_temoignage->setTabEnabled(2, false);
    ui->tabWidget_suspect->setTabEnabled(2, false);
    ui->tabWidget_enquette->setTabEnabled(2, false);


    QStandardItemModel *modele = new QStandardItemModel(1, 5);
    QStringList list;
    list << "Tâche" << "info" << "A faire..." << "A faire pour le " << "Assigée à ";
    modele->setHorizontalHeaderLabels(list);
    ui->tableView->setModel(modele);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QIcon *ico = new QIcon("search.png");
    ui->searchUser->addAction(*ico, QLineEdit::LeadingPosition);
    ui->searchUser_msg->addAction(*ico, QLineEdit::LeadingPosition);

    QObject::connect(user.Socket, SIGNAL(disconnected()), this, SLOT(deconnectedFromServer()));
    QObject::connect(user.Socket, SIGNAL(connected()), this, SLOT(connected()));
    QObject::connect(user.Socket, SIGNAL(readyRead()), this, SLOT(lectureMessage()));

    QObject::connect(user.Socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

    QTimer *timer=new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
        timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showTime()
{
    //QDateTime time=QDateTime ::currentDateTime();
   // QString time_texte=time.toString("hh : mm : ss");
    /*if((time.second() % 2)==0)
    { time_texte[3]= ' ';
        time_texte[8]= ' ';
    }*/
    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss");
    ui->label_datetime->setText(sDate);
}


bool MainWindow::attacherAgent(Agent& user, QString& matricule)
{
    QSqlQuery requeteur;
    // ceci "*" n'est pas conseillé car la position des index est indéfini
    requeteur.prepare("select "
                            "matricule, nom, prenom, login, password, mail, poste, grade, datenaiss, "
                            "ville, nompere, nommere, image, type "
                            "from AGENT where matricule = :matricule");
    requeteur.bindValue(":matricule", matricule);
    requeteur.exec();
    while(requeteur.next())
    {
        user.setMatricule(requeteur.value(0).toString());
        user.setNom(requeteur.value(1).toString());
        user.setPrenom(requeteur.value(2).toString());
        user.setLogin(requeteur.value(3).toString());
        user.setPassword(requeteur.value(4).toString());
        user.setMail(requeteur.value(5).toString());
        user.setPoste(requeteur.value(6).toString());
        user.setGrade(requeteur.value(7).toString());
        user.setDateNaiss(requeteur.value(8).toDate());
        user.setVille(requeteur.value(9).toString());
        user.setNomPere(requeteur.value(10).toString());
        user.setNomMere(requeteur.value(11).toString());
        user.setImage(requeteur.value(12).toString());
        user.setType(requeteur.value(13).toInt());
        return true;
    }
    return false;
}
                                        /* ------------ Changement de Module -------------- */

void MainWindow::on_actionUtilisateur_triggered()
{
    ui->stackedWidget->setCurrentIndex(_UTILISATEUR);
    on_userList_clicked();
    ui->table_users->setModel(user.afficherAgents());
}

void MainWindow::on_actionAcceuil_triggered()
{
    ui->stackedWidget->setCurrentIndex(_ACCEUIL);
}

                                        /* ------------ Changement d'interface Utilisateur -------------- */

void MainWindow::on_userTchat_clicked()
{
    ui->stackedWidget_user->setCurrentIndex(_TCHAT);
    if(!user.connectToMsg)
        ui->stackedWidget_msg->setCurrentIndex(0);
    else
        ui->stackedWidget_msg->setCurrentIndex(1);
    ui->userTchat->setStyleSheet("Background-color: rgba(188, 207, 195, 0.5);");
    ui->userConfig->setStyleSheet("QPushButton{Background-color: rgba(255, 255, 255, 0);}"
                            "QPushButton:hover{Background-color: rgba(188, 207, 195, 0.5);}");
    ui->userList->setStyleSheet("QPushButton{Background-color: rgba(255, 255, 255, 0);}"
                            "QPushButton:hover{Background-color: rgba(188, 207, 195, 0.5);}");
}

void MainWindow::on_userConfig_clicked()
{
    ui->stackedWidget_user->setCurrentIndex(_CONFIG);
    ui->userConfig->setStyleSheet("Background-color: rgba(188, 207, 195, 0.5);");
    ui->userTchat->setStyleSheet("QPushButton{Background-color: rgba(255, 255, 255, 0);}"
                            "QPushButton:hover{Background-color: rgba(188, 207, 195, 0.5);}");
    ui->userList->setStyleSheet("QPushButton{Background-color: rgba(255, 255, 255, 0);}"
                            "QPushButton:hover{Background-color: rgba(188, 207, 195, 0.5);}");
}

void MainWindow::on_userList_clicked()
{
    ui->stackedWidget_user->setCurrentIndex(_LISTE);
    ui->tabWidget_user->setCurrentIndex(_AFFICHER);
    ui->userList->setStyleSheet("Background-color: rgba(188, 207, 195, 0.5);");
    ui->userTchat->setStyleSheet("QPushButton{Background-color: rgba(255, 255, 255, 0);}"
                            "QPushButton:hover{Background-color: rgba(188, 207, 195, 0.5);}");
    ui->userConfig->setStyleSheet("QPushButton{Background-color: rgba(255, 255, 255, 0);}"
                            "QPushButton:hover{Background-color: rgba(188, 207, 195, 0.5);}");
}

                                        /* ------------ Associer l'agent à l'application -------------- */

void MainWindow::connect_agent(QString matricule)
{
    attacherAgent(user, matricule);
    setWindowTitle("SGSP - Username: **" + user.login() + "** is connected");
    show();
}

                                        /* ------------ Interface "Liste Utilisateurs" -------------- */

/* ****** Afficher Utilisateur ****** */

void MainWindow::on_btn_rafraichir_clicked()
{
    ui->table_users->setModel(user.afficherAgents());
}

void MainWindow::on_btn_modifier_clicked()
{
    QModelIndexList agent_select = ui->table_users->selectionModel()->selectedRows();
    if(agent_select.count() != 1)
        return;
    ui->tabWidget_user->setCurrentIndex(_MODIFIER);
    ui->tabWidget_user->setTabEnabled(_MODIFIER, true);
    // recupération de la ligne selectionné
    int ligne = 0;
    QModelIndex index = agent_select.at(0);
    ligne = index.row();
    ui->mod_matricule->setText(ui->table_users->model()->index(ligne, _MATRICULE).data().toString());
    ui->mod_login->setText(ui->table_users->model()->index(ligne, _LOGIN).data().toString());
    ui->mod_password->setText(ui->table_users->model()->index(ligne, _PASSWORD).data().toString());
    ui->mod_nom->setText(ui->table_users->model()->index(ligne, _NOM).data().toString());
    ui->mod_prenom->setText(ui->table_users->model()->index(ligne, _PRENOM).data().toString());
    ui->mod_mail->setText(ui->table_users->model()->index(ligne, _MAIL).data().toString());
    ui->mod_date->setDate(ui->table_users->model()->index(ligne, _DATENAISS).data().toDate());
    ui->mod_poste->setText(ui->table_users->model()->index(ligne, _POSTE).data().toString());
    ui->mod_grade->setText(ui->table_users->model()->index(ligne, _GRADE).data().toString());
    ui->mod_pere->setText(ui->table_users->model()->index(ligne, _NOMPERE).data().toString());
    ui->mod_mere->setText(ui->table_users->model()->index(ligne, _NOMMERE).data().toString());
    ui->mod_ville->setText(ui->table_users->model()->index(ligne, _VILLE).data().toString());
    if(ui->table_users->model()->index(ligne, _TYPE).data().toInt())
        ui->mod_type_admin->setChecked(true);
    else
        ui->mod_type_user->setChecked(true);
    ui->mod_image_text->setText(ui->table_users->model()->index(ligne, _IMAGE).data().toString());
}

void MainWindow::on_btn_supprimer_clicked()
{
    QModelIndexList agent_select = ui->table_users->selectionModel()->selectedRows();
    if(agent_select.count() == 0)
        return;

    // recupération des lignes sélectionnées
    QVector<int> ligne;
    QString usersName;
    usersName.push_back("<span style=\"font-size: 15px\">Vous êtes sur le point de supprimer les utilisateurs suivant : </span>");
    usersName.push_back("<ul style=\"font-size: 13px\">");
    for(int i(0); i<agent_select.count(); ++i)
    {
        QModelIndex index = agent_select.at(i);
        ligne.push_back(index.row());
        usersName.push_back("<li> <span style=\"font-weight: bold\">Matricule : </span>"
                        + ui->table_users->model()->index(ligne[i], _MATRICULE).data().toString()
                            + "  |  <span style=\"font-weight: bold\">Login : </span>"
                        + ui->table_users->model()->index(ligne[i], _LOGIN).data().toString()
                            + "  |  <span style=\"font-weight: bold\">Nom : </span>"
                        + ui->table_users->model()->index(ligne[i], _NOM).data().toString()
                            + "</li>");
    }
    usersName.push_back("</ul>");
    usersName.push_back("Êtes-vous sur de vouloir continuer?<br>");
    usersName.push_back(" > Si <strong>'OUI'</strong> <em> cliquez sur le bouton <strong style=\"color:red;\">Supprimer</strong></em>"
                    "<br> > Si <strong>'NON'</strong> <em> cliquez sur le bouton <strong>Annuler</strong></em>");
    QMessageBox msg;
    msg.addButton("Annuler", QMessageBox::NoRole);
    QPushButton *supp = msg.addButton("Supprimer", QMessageBox::YesRole);
    msg.setWindowTitle("Suppression d'utilisateur");
    msg.setText(usersName);
    msg.setIcon(QMessageBox::Warning);
    msg.setStyleSheet("QPushButton{border-radius: 5px; border-bottom: 5px solid #617c97;}"
                    "QPushButton:hover  {   background-color: #bccfc3  }"
                    "QPushButton:pressed   {    border-bottom: none; }");
    msg.setStyleSheet("background-color: #ddebe3; "); //#617c97;
    supp->setStyleSheet("QPushButton:hover  {   border-bottom: 5px solid rgb(159, 42, 54); "
                    "background-color: #f45;}"
                    "QPushButton:pressed   {    border-bottom: none; }");
    msg.setWindowIcon(QIcon(":/logo.png"));
    if(msg.exec())
    {
        QString matricule;
        for(int i(0); i<agent_select.count(); ++i)
        {
            matricule = ui->table_users->model()->index(ligne[i], _MATRICULE).data().toString();
            user.supprimerAgent(matricule);
        }
        on_btn_rafraichir_clicked();
    }
}

void MainWindow::on_searchUser_textChanged(const QString &arg1)
{
    QString search = arg1;
    for(int i(0); i<13; ++i)
    {
        if(ui->choix_recherche->currentIndex() == i)
            ui->table_users->setModel(user.rechercherAgent(search, i-1));
    }
}

void MainWindow::on_searchUser_returnPressed()
{
    on_searchUser_textChanged(ui->searchUser->text());
}

void MainWindow::on_choix_recherche_currentIndexChanged(int)
{
    on_searchUser_returnPressed();
}

void MainWindow::trier(int& critere, int& ordre)
{
    for(int i(0); i<13; ++i)
    {
        if(ui->choix_recherche->currentIndex() == i)
            ui->table_users->setModel(user.trierAgents(critere, ordre));
    }
}

void MainWindow::on_trie_critere_currentIndexChanged(int index)
{
    int ordre = ui->trie_critere->currentIndex();
    trier(index, ordre);
}

void MainWindow::on_trie_ordre_currentIndexChanged(int index)
{
    int critere = ui->trie_critere->currentIndex();
    trier(critere, index);
}

/* ****** Ajouter Utilisateur ****** */

void MainWindow::on_add_user_clicked()
{
    Agent newUser;
    newUser.setMatricule(ui->add_matricule->text());
    newUser.setLogin(ui->add_login->text());
    newUser.setPassword(ui->add_password->text());
    newUser.setNom(ui->add_nom->text());
    newUser.setPrenom(ui->add_prenom->text());
    newUser.setDateNaiss(ui->add_date->date());
    newUser.setPoste(ui->add_poste->text());
    newUser.setGrade(ui->add_grade->text());
    newUser.setImage(ui->add_image_text->text());
    newUser.setVille(ui->add_ville->text());
    if(ui->add_type_admin->isChecked())
        newUser.setType(1);
    else
        newUser.setType(0);
    newUser.setNomMere(ui->add_mere->text());
    newUser.setNomPere(ui->add_pere->text());
    newUser.setMail(ui->add_mail->text());
    if(!user.ajouterAgent(newUser))
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Erreur survenu lors de l'ajout d'un nouvelle utilisateur!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);;
    on_del_text_add_user_clicked();
}

void MainWindow::on_add_image_clicked()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(),
                                                   "Images (*.png *.gif *.jpg *.jpeg)");
    ui->add_image_text->setText(fichier);
}

void MainWindow::on_del_text_add_user_clicked()
{
    ui->add_matricule->clear();
    ui->add_login->clear();
    ui->add_password->clear();
    ui->add_nom->clear();
    ui->add_prenom->clear();
    ui->add_date->clear();
    ui->add_poste->clear();
    ui->add_grade->clear();
    ui->add_image_text->clear();
    ui->add_ville->clear();
    ui->add_mere->clear();
    ui->add_pere->clear();
    ui->add_mail->clear();
}

/* ****** Modifier Utilisateur ****** */

void MainWindow::on_mod_user_clicked()
{
    Agent newUser;
    newUser.setMatricule(ui->mod_matricule->text());
    newUser.setLogin(ui->mod_login->text());
    newUser.setPassword(ui->mod_password->text());
    newUser.setNom(ui->mod_nom->text());
    newUser.setPrenom(ui->mod_prenom->text());
    newUser.setDateNaiss(ui->mod_date->date());
    newUser.setPoste(ui->mod_poste->text());
    newUser.setGrade(ui->mod_grade->text());
    newUser.setImage(ui->mod_image_text->text());
    newUser.setVille(ui->mod_ville->text());
    if(ui->mod_type_admin->isChecked())
        newUser.setType(1);
    else
        newUser.setType(0);
    newUser.setNomMere(ui->mod_mere->text());
    newUser.setNomPere(ui->mod_pere->text());
    newUser.setMail(ui->mod_mail->text());
    user.modifierAgent(newUser);
    on_del_text_mod_user_clicked();
}

void MainWindow::on_tabWidget_user_currentChanged(int)
{
    if(ui->tabWidget_user->isTabEnabled(_MODIFIER))
        ui->tabWidget_user->setTabEnabled(_MODIFIER, false);
}

void MainWindow::on_del_text_mod_user_clicked()
{
    ui->mod_matricule->clear();
    ui->mod_login->clear();
    ui->mod_password->clear();
    ui->mod_nom->clear();
    ui->mod_prenom->clear();
    ui->mod_date->clear();
    ui->mod_poste->clear();
    ui->mod_grade->clear();
    ui->mod_image_text->clear();
    ui->mod_ville->clear();
    ui->mod_mere->clear();
    ui->mod_pere->clear();
    ui->mod_mail->clear();
}

                                        /* ------------ Interface "Tchat w-User" -------------- */

void MainWindow::on_connect_message_clicked()
{
    if(ui->password_msg->text() != user.password())
        ;
    else
    {
        // On annonce sur la fenêtre qu'on est en train de se connecter
        ui->zoneMessages->setEnabled(false);
        ui->zoneMessages->append(tr("<em>Tentative de connexion en cours...</em>"));
        QString ip = ui->serveurIP->text();
        int port = ui->serveurPort->value();
        user.connectToServer(ip, port, ui->connect_message);
    }
}

// si nous sommes connecté
void MainWindow::connected()
{
    // create a QDataStream operating on the socket
    QDataStream clientStream(user.Socket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // creation du Json que nous voulons envoyer
    QJsonObject message;
    message["type"] = QStringLiteral("login");
    message["username"] = user.login();
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
    user.connectToMsg = true;
    // préparation de l'interface de connexion
    ui->connect_message->setEnabled(true);
    ui->stackedWidget_msg->setCurrentIndex(1);
    ui->pseudo->setText(user.login());
    ui->pseudo->setEnabled(false);
    ui->zoneMessages->setEnabled(true);
    ui->zoneMessages->setReadOnly(true);
    QString login = user.login();
    msgUser.afficherListUtilisateur(ui->userList_msg, login);
    ui->zoneMessages->append("<em style = \"text-align: right;\">You are connected</em>");
    ui->userRecepteur->setText(ui->userList_msg->item(0)->text());
}

void MainWindow::on_userList_msg_itemClicked(QListWidgetItem *item)
{
    ui->userRecepteur->setText(item->data(Qt::DisplayRole).toString());
    // create a QDataStream operating on the socket
    QDataStream clientStream(user.Socket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("changeUser");
    message[QStringLiteral("sender")] = user.login();
    message[QStringLiteral("receiver")] = ui->userRecepteur->text();
    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
    ui->zoneMessages->clear();
}

void MainWindow::on_searchUser_msg_textChanged(const QString &arg1)
{
    QString search = arg1, login = user.login();
    Message msg;
    ui->userList_msg->clear();
    msg.rechercherUtilisateurInList(ui->userList_msg, search, login);
}

void MainWindow::on_envoyer_msg_clicked()
{
    Message msg;
    msg.setContent(ui->text_msg->toPlainText());
    msg.setLoginAgent(user.login());
    msg.setDateEnvoie(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));
    msg.userReseach = "";
    msg.context = 0;
    if(ui->userRecepteur->text() != "Tout le monde")
    {
        msg.userReseach = ui->userRecepteur->text();
        msg.context = 1;
    }
    if(!msg.sendMessage(msg, user)) return;
    // now we add the message to the list
    // set the alignment for the message
    ui->zoneMessages->append(msg.dateEnvoie() + " : <strong style=\"color: blue\"> <em> MOI</em></strong>");
    ui->zoneMessages->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->zoneMessages->append("<span style=\"color: blue; text-align: right;\">" + msg.content() + "</span>");
    if(ui->userRecepteur->text() != "Tout le monde")
        ui->zoneMessages->append("<span style=\"color: blue; text-align: right;\">~~~~ <i>Message envoyé à : </i>"
                        + tr("%1").arg(msg.userReseach) + "~~~~</span>");
    // clear the content of the message editor
    ui->text_msg->clear();
}


void MainWindow::deconnectedFromServer()
{
    // Si l'on perd la connection avec le serveur
    QMessageBox::critical(nullptr, QObject::tr("Disconnected"),
                          QObject::tr("The host terminated the connection!!!\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    user.Socket->abort();
    ui->stackedWidget_msg->setCurrentIndex(0);
    ui->zoneMessages->append("<span style = \"text-align: center\"> "
                             "******************************************* </span>");
    ui->userList_msg->clear();
    ui->usersConnected->clear();
    lastUserName.clear();
    user.connectToMsg = false;
}

void MainWindow::error(QAbstractSocket::SocketError socketError)
{
    // show a message to the user that informs of what kind of error occurred
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return; // handled by disconnectedFromServer
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("The host refused the connection!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("The proxy refused the connection!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Could not find the proxy\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Could not find the server!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("You don't have permissions to execute this operation!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Too many connections opened!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Operation timed out!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Proxy timed out!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Unable to reach the network\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("An unknown error occure!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Operation not supported!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Your proxy requires authentication!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Proxy comunication failed!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Operation failed!!! Please try again\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    default:
        Q_UNREACHABLE();
    }
    ui->connect_message->setEnabled(true);
}

void MainWindow::lectureMessage()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(user.Socket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // start an infinite loop
    for (;;) {
        // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // we try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonDoc.isObject()) // and is a JSON object
                    jsonRecu(jsonDoc.object()); // parse the JSON
            }
            // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }
    }
}

void MainWindow::messageRecu(Message & msg)
{
    // we display a line containing the username only if it's different from the last username we displayed
    if (user.login() != msg.loginAgent()) {
        ui->zoneMessages->append("<strong>" + msg.loginAgent() + "</strong> : " + msg.dateEnvoie());
        ui->zoneMessages->setAlignment(Qt::AlignLeft);
        ui->zoneMessages->append(msg.content());
    } else {
            ui->zoneMessages->append("<em style = \" text-align: center;\"> ````id :" + msg.id() + "````</em>  ---- "
                                 + msg.dateEnvoie() + " : <strong style=\"color: blue\"> <em> MOI</em></strong>");
            ui->zoneMessages->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            ui->zoneMessages->append("<span style=\"color: blue; text-align: right;\">" + msg.content() + "</span>");
            if(ui->userRecepteur->text() != "Tout le monde")
                ui->zoneMessages->append("<span style=\"color: blue; text-align: right;\">~~~~ <i>Message envoyé à : </i>"
                                + tr("%1").arg(msg.userReseach) + "~~~~</span>");
    }
}

void MainWindow::utilisateurParti(const QString &username)
{
    // set the color for the text
    ui->zoneMessages->setTextColor(Qt::red);
    // store in the model the message to comunicate a user left
    ui->zoneMessages->append(tr("%1 A quitter le Chat").arg(username));
    // set the alignment for the text
    ui->zoneMessages->setAlignment(Qt::AlignCenter);
}

void MainWindow::utilisateurArriver(const QString &username)
{
    ui->zoneMessages->setTextColor(Qt::darkCyan);
    ui->zoneMessages->append(tr("%1 A rejoins le Chat").arg(username));
    ui->zoneMessages->setAlignment(Qt::AlignCenter);
    ui->zoneMessages->setTextColor(Qt::black);
}

void MainWindow::jsonRecu(const QJsonObject &docObj)
{
    Message msg;
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return; // message sans type just ignored
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0)  //It's a login message
    {
        QJsonArray userList = docObj[QLatin1String("userList")].toArray();
        for(int i(0); i<userList.size(); ++i)
        {
            if(userList[i].toString() != user.login())
                msg.usersConnect.append(userList[i].toString());
        }
        msg.fillListUserConnect(ui->usersConnected, msg.usersConnect);
    } else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) //It's a chat message
    {
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        const QJsonValue senderVal = docObj.value(QLatin1String("sender")); // celui qui e envoyer le msg
        const QJsonValue dateVal = docObj.value(QLatin1String("date"));
        const QJsonValue receiver = docObj.value(QLatin1String("receiver")); // celiu à qui le msg à été envoyé
        const QJsonValue id_msg = docObj.value(QLatin1String("id_msg"));
        if (textVal.isNull() || !textVal.isString())
            return; // the text field was invalid so we ignore
        if (senderVal.isNull() || !senderVal.isString())
            return; // the sender field was invalid so we ignore
        msg.setContent(textVal.toString());
        msg.setLoginAgent(senderVal.toString());
        msg.setDateEnvoie(dateVal.toString());
        msg.userReseach = receiver.toString();
        msg.setID(id_msg.toString());
        // we notify a new message was received via the messageReceived signal
        messageRecu(msg);
    } else if (typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0) { // A user joined the chat
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the new user via the userJoined signal
        utilisateurArriver(usernameVal.toString());
        int newRow = ui->usersConnected->count();
        ui->usersConnected->insertItem(newRow, tr("%1").arg(usernameVal.toString()));

    } else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) { // A user left the chat
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the user disconnection the userLeft signal
        utilisateurParti(usernameVal.toString());
        for(int i(0); i < ui->usersConnected->count(); ++i)
        {
            if(usernameVal.toString() == ui->usersConnected->item(i)->text())
                //ui->usersConnected->removeItemWidget(ui->usersConnected->item(i));
                delete(ui->usersConnected->item(i));
        }
    }
}

void MainWindow::on_disconnect_msg_clicked()
{
    user.Socket->disconnectFromHost();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->zoneMessages->clear();
}

void MainWindow::on_effacer_msg_clicked()
{
    ui->text_msg->clear();
}

void MainWindow::on_password_msg_returnPressed()
{
    on_connect_message_clicked();
}

void MainWindow::on_supprimer_msg_clicked()
{
    bool ok = false;
    QString id = QInputDialog::getText(this, "Supprimer un message", "Veuillez saisir l'id du message ?", QLineEdit::Normal, QString(), &ok);
    QString login = user.login();
    if (ok && !id.isEmpty())
        msgUser.supprimerMessage(id, user.Socket, login);
}

void MainWindow::on_actionEnquette_triggered()
{

    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidget_enquette->setCurrentIndex(1);
    ui->tableView_temoignage->setModel(temoignage.afficher());
    ui->stackedWidget_enquette->setCurrentIndex(1);
    ui->tableView_enquette->setModel(enquette.afficher());
    ui->stackedWidget_enquette->setCurrentIndex(1);
    ui->tableView_suspect->setModel(suspect.afficher());
     //ui->tableView_enquette->setModel(enquette.archiver());
    //ui->stackedWidget_enquette->setCurrentIndex(1);
}



void MainWindow::on_pushButtonmodifier_clicked()
{
    int row=ui->tableView_temoignage->selectionModel()->currentIndex().row();
    QString id=ui->tableView_temoignage->model()->index(0,row).data().toString();
    ui->tabWidget_temoignage->setCurrentIndex(2);
    ui->tabWidget_temoignage->setTabEnabled(2, true);
   /* QModelIndexList temoign_select = ui->tableView_temoignage->selectionModel()->selectedRows();
    if(temoign_select.count() != 1)
        return;
    ui->tabWidget_temoignage->setCurrentIndex(2);
    ui->tabWidget_temoignage->setTabEnabled(2, true);
    // recupération de la ligne selectionné
    int ligne = 0;
    QModelIndex index = temoign_select.at(0);
    ligne = index.row();
    ui->lineEdit_10->setEnabled(false);
    ui->lineEdit_9->setEnabled(false);
    //ui->lineEdit_9->setText(ui->tableView_temoignage->model()->index(ligne, 0).data().toString());
    //ui->lineEdit_10->setText(ui->tableView_temoignage->model()->index(ligne, 1).data().toString());
    ui->lineEdit_11->setText(ui->tableView_temoignage->model()->index(ligne, 1).data().toString());
    ui->textEdit_3->setText(ui->tableView_temoignage->model()->index(ligne, 2).data().toString());*/
    ui->lineEdit_9->setEnabled(false);

    ui->lineEdit_9->setText(ui->tableView_temoignage->model()->index(row, 3).data().toString());
    ui->lineEdit_10->setText(ui->tableView_temoignage->model()->index(row, 0).data().toString());
    ui->lineEdit_11->setText(ui->tableView_temoignage->model()->index(row, 1).data().toString());
    ui->textEdit_3->setText(ui->tableView_temoignage->model()->index(row, 2).data().toString());

}

void MainWindow::on_pushButtonajouter_clicked()
{
    Temoignage temoignage;
    temoignage.setId_t(ui->lineEdit_2->text());
    temoignage.setId_citoyen(ui->lineEdit->text());
    temoignage.setNom_t(ui->lineEdit_3->text());
    temoignage.setContenu(ui->textEdit->toPlainText().toUtf8());
    if(!temoignage.ajouter())
        QMessageBox::critical(nullptr, QObject::tr("Echec d'ajout"), QObject::tr("temoignage n'a pas été ajouté à "
                                "la base de données\n Click to cancel to quit"), QMessageBox::Cancel);
    ui->lineEdit_2->clear();
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->textEdit->clear();
}

void MainWindow::on_pushButtonsupprimer_clicked()
{
   // int row=ui->tableView_temoignage->selectionModel()->currentIndex().row();
    //QString id=ui->tableView_temoignage->model()->index(0,row).data().toString();

    QModelIndexList temoign_select = ui->tableView_temoignage->selectionModel()->selectedRows();
    if(temoign_select.count() != 1)
        return;
    // recupération de la ligne selectionné
    int ligne = 0;
    QModelIndex index;
    Temoignage temoign;
    for(int i =0; i < temoign_select.count(); ++i)
    {
        index = temoign_select.at(i);
        ligne = index.row();
     QString t=ui->tableView_temoignage->model()->index(ligne, 0).data().toString();
        temoign.supprimer(t);
    }
   // temoignage.supprimer(id);
    on_btn_actualiserTmg_clicked();
}

void MainWindow::on_pushButton_7_clicked()
{

     Temoignage temoignage;

       temoignage.setId_citoyen(ui->lineEdit_9->text());
       temoignage.setId_t(ui->lineEdit_10->text());
       temoignage.setNom_t(ui->lineEdit_11->text());
       temoignage.setContenu(ui->textEdit_3->toPlainText().toUtf8());

       if(!temoignage.modifier())
           QMessageBox::critical(nullptr, QObject::tr("Echec de la modification"), QObject::tr("temoignage n'a pas été modifié dans "
                                   "la base de données\n Click to cancel to quit"), QMessageBox::Cancel);

       ui->lineEdit_10->clear();
       ui->lineEdit_11->clear();
       ui->textEdit_3->clear();
       ui->lineEdit_9->clear();


       ui->tabWidget_suspect->setCurrentIndex(2);
       ui->tabWidget_suspect->setTabEnabled(2, false);

    on_btn_actualiserTmg_clicked();
}

void MainWindow::on_btn_actualiserTmg_clicked()
{
    Temoignage temoign;
    ui->tableView_temoignage->setModel(temoign.afficher());
}

void MainWindow::on_pushButton_suspect_clicked()
{
    ui->stackedWidget_enquette->setCurrentIndex(2);
}

void MainWindow::on_pushButton_enquette_2_clicked()
{
    ui->stackedWidget_enquette->setCurrentIndex(1);
}

void MainWindow::on_pushButton_temoin_clicked()
{
    ui->stackedWidget_enquette->setCurrentIndex(0);
}


/*void MainWindow::doTask(int &number)
{
 qDebug() <<"starting " <<number;
 int max =  10;
 for(int i = 0 ;i<max;i++)
 {
     QThread::currentThread()->msleep(500);
     qDebug() << "Processing" <<number <<" . " << i << " of" << max;
 }
 qDebug() << "stopped" <<number;
}*/

void MainWindow::on_pushButton_ajouterenquette_clicked()
{

    Enquette enquette;
    enquette.setId_enquette(ui->lineEdit_13->text());
    enquette.setSujet(ui->textEdit_5->toPlainText());
    enquette.setDate_debut(ui->dateEdit->date());
    enquette.setType_enquette(ui->comboBox_5->currentText());
    enquette.setIndice(ui->toolButon_text->text());

    if(enquette.ajouter())
    {
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                                notifier->show();
                                notifier->showMessage("Enquéte ajouté","Success",QSystemTrayIcon::Information,10000);

                               /* QVector<int> vector;
                                for(int i = 0 ; i<ui->spinBoxx->value();i++)
                                {
                                    vector.append(i);
                                }
                               QProgressDialog pdialog;
                               pdialog.setLabelText("Processing");
                               QFutureWatcher<void> watcher;


                              connect(&pdialog,SIGNAL(canceled()), &watcher, SLOT(cancel()));
                               connect(&watcher,SIGNAL(finished()), &pdialog, SLOT(reset()));
                               connect(&watcher,SIGNAL(progressRangeChanged(int,int)), &pdialog, SLOT(setRange(int,int)));
                               connect(&watcher,SIGNAL(progressValueChanged(int)), &pdialog, SLOT(setValue(int)));

                             watcher.setFuture(QtConcurrent::map(vector,&MainWindow::doTask));
                            // pdialog.exec();
                            watcher.waitForFinished();
                             if(watcher.isRunning())
                             {
                                 qDebug() << "canceled";
                                 QMessageBox::critical(this,"canceled","you clicked cancel");

                             }
                             else {
                                 qDebug() << "finished";
                                 QMessageBox::information(this,"finished","archiver");
                             }*/

                }
    else
    {   QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
         notifier->show();
         notifier->showMessage("Enquéte non ajouté","Failed",QSystemTrayIcon::Critical,10000);
}

    ui->lineEdit_13->clear();
    ui->textEdit_5->clear();
    ui->dateEdit->clear();
    ui->comboBox_5->clear();
    ui->toolButon_text->clear();
    //ui->spinBoxx->clear();

}




void MainWindow::on_pushButton_ajoususpect_clicked()
{
    Suspect suspect;
    suspect.setId_suspect(ui->lineEdit_17->text().toInt());
    suspect.setId_enquette(ui->lineEdit_5->text());
    suspect.setId_citoyen(ui->lineEdit_6->text());
    suspect.setDescription(ui->textEdit_2->toPlainText().toUtf8());

    if(!suspect.ajouter())
        QMessageBox::critical(nullptr, QObject::tr("Echec d'ajout"), QObject::tr("Suspect n'a pas été ajouté à "
                                "la base de données\n Click to cancel to quit"), QMessageBox::Cancel);
    ui->lineEdit_17->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->textEdit_2->clear();



}

void MainWindow::on_pushButton_6_clicked()
{
    QModelIndexList enquette_select = ui->tableView_enquette->selectionModel()->selectedRows();
    if(enquette_select.count() != 1)
        return;
    ui->tabWidget_enquette->setCurrentIndex(2);
    ui->tabWidget_enquette->setTabEnabled(2, true);
    // recupération de la ligne selectionné
    int ligne = 0;
    QModelIndex index = enquette_select.at(0);
    ligne = index.row();
    ui->lineEdit_14->setEnabled(false);
    ui->lineEdit_14->setText(ui->tableView_enquette->model()->index(ligne, 0).data().toString());
    ui->textEdit_6->setText(ui->tableView_enquette->model()->index(ligne, 1).data().toString());
    ui->dateEdit_2->setDate(ui->tableView_enquette->model()->index(ligne, 2).data().toDate());
    ui->comboBox_6->setCurrentText(ui->tableView_enquette->model()->index(ligne, 3).data().toString());
    ui->toolButton_text_2->setText(ui->tableView_enquette->model()->index(ligne, 4).data().toString());
}

void MainWindow::on_toolButton_clicked()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(),
                                                   "Images (*.png *.gif *.jpg *.jpeg)");
    ui->toolButon_text->setText(fichier);
}

void MainWindow::on_pushButton_clicked()
{
    Enquette enquette;
        enquette.setId_enquette(ui->lineEdit_14->text());
        enquette.setSujet(ui->textEdit_6->toPlainText().toUtf8());
        enquette.setDate_debut(ui->dateEdit_2->date());
        enquette.setType_enquette(ui->comboBox_6->currentText());
        enquette.setIndice(ui->toolButton_text_2->text());
        if(!enquette.modifier())
            QMessageBox::critical(nullptr, QObject::tr("Echec de la modification"), QObject::tr("enquette n'a pas été modifié dans "
                                    "la base de données\n Click to cancel to quit"), QMessageBox::Cancel);
        ui->lineEdit_14->clear();
        ui->textEdit_6->clear();
        ui->dateEdit_2->clear();
        ui->comboBox_6->clear();
         ui->comboBox_6->clear();

        ui->tabWidget_enquette->setCurrentIndex(1);
        ui->tabWidget_enquette->setTabEnabled(2, false);
        on_pushButton_15_clicked();

}

void MainWindow::on_pushButton_15_clicked()
{
    ui->tableView_enquette->setModel(enquette.afficher());
}

void MainWindow::on_pushButton_10_clicked()
{
    QModelIndexList enquette_select = ui->tableView_enquette->selectionModel()->selectedRows();
    if(enquette_select.count() == 0)
        return;
    // recupération de la ligne selectionné
    int ligne = 0;
    QModelIndex index;
    for(int i =0; i < enquette_select.count(); ++i)
    {
        index = enquette_select.at(i);
        ligne = index.row();
        enquette.supprimer(ui->tableView_enquette->model()->index(ligne, 0).data().toString());
    }
    on_pushButton_15_clicked();
}

void MainWindow::on_lineEdit_15_textChanged(const QString &arg1)
{
    /*QString search = arg1;
    for(int i(0); i<3; ++i)
    {*/
        //if(ui->comboBox_7->currentIndex() == i)
            ui->tableView_enquette->setModel(enquette.rechercherEnquette(ui->comboBox_7->currentText(),ui->lineEdit_15->text()));
   // }
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->tableView_suspect->setModel(suspect.afficher());
}

void MainWindow::on_pushButton_4_clicked()
{
    //QModelIndexList suspect_select = ui->tableView_suspect->selectionModel()->selectedRows();
    int row=ui->tableView_suspect->selectionModel()->currentIndex().row();
    QString id=ui->tableView_suspect->model()->index(0,row).data().toString();
    /*if(suspect_select.count() != 1)
        return;*/
    ui->tabWidget_suspect->setCurrentIndex(2);
    ui->tabWidget_suspect->setTabEnabled(2, true);
    // recupération de la ligne selectionné
    /*int ligne = 0;
    QModelIndex index = suspect_select.at(0);
    ligne = index.row();*/
    ui->lineEdit_16->setEnabled(false);
    ui->lineEdit_16->setText(ui->tableView_suspect->model()->index(row, 0).data().toString());
    ui->lineEdit_7->setText(ui->tableView_suspect->model()->index(row, 1).data().toString());
    ui->lineEdit_8->setText(ui->tableView_suspect->model()->index(row, 2).data().toString());
    ui->textEdit_4->setText(ui->tableView_suspect->model()->index(row, 3).data().toString());

}

void MainWindow::on_pushButton_2_clicked()
{
     Suspect suspect;
     suspect.setId_suspect(ui->lineEdit_16->text().toInt());
        suspect.setId_enquette(ui->lineEdit_7->text());
        suspect.setId_citoyen(ui->lineEdit_8->text());
        suspect.setDescription(ui->textEdit_4->toPlainText().toUtf8());

        if(!suspect.modifier())
            QMessageBox::critical(nullptr, QObject::tr("Echec de la modification"), QObject::tr("enquette n'a pas été modifié dans "
                                    "la base de données\n Click to cancel to quit"), QMessageBox::Cancel);
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
        ui->textEdit_4->clear();
        ui->lineEdit_16->clear();


        ui->tabWidget_suspect->setCurrentIndex(2);
        ui->tabWidget_suspect->setTabEnabled(2, false);
        on_pushButton_16_clicked();
}

void MainWindow::on_pushButton_supprimersuspect_clicked()
{
    int row=ui->tableView_suspect->selectionModel()->currentIndex().row();
    int id=ui->tableView_suspect->model()->index(0,row).data().toInt();
    /*if(suspect_select.count() == 0)
        return;*/
    // recupération de la ligne selectionné
   /* int ligne = 0;
    QModelIndex index;
    for(int i =0; i < suspect_select.count(); ++i)
    {
        index = suspect_select.at(i);
        ligne = index.row();
        suspect.supprimer(ui->tableView_suspect->model()->index(ligne, 0).data().toInt());
    }*/
    suspect.supprimer(id);
    on_pushButton_16_clicked();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableView_temoignage->setModel(temoignage.trier(ui->comboBox->currentText(),ui->comboBox_2->currentText()));
}


void MainWindow::on_pushButton_13_clicked()
{

    QString strStream;
                    QTextStream out(&strStream);


                    const int rowCount = ui->tableView_enquette->model()->rowCount();
                    const int columnCount = ui->tableView_enquette->model()->columnCount();

                    out <<  "<html>\n"
                        "<head>\n"

                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%60 les postes</title>\n").arg("poste")
                        <<  "</head>\n"
                        "<body bgcolor=#ffffff link=#5000A0>\n"
                        "<table border=1 cellspacing=0 cellpadding=2>\n";
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (! ui->tableView_enquette->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView_enquette->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    for (int row = 0; row < rowCount; row++) {
                        out << "<tr>";
                        for (int column = 0; column < columnCount; column++) {
                            if (!ui->tableView_enquette->isColumnHidden(column)) {
                                QString data = ui->tableView_enquette->model()->data(ui->tableView_enquette->model()->index(row, column)).toString().simplified();
                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                            }
                        }
                        out << "</tr>\n";
                    }
                    out <<  "</table>\n"
                        "</body>\n"
                        "</html>\n";

                    QTextDocument *document = new QTextDocument();
                    document->setHtml(strStream);

                    QPrinter printer;

                    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                    if (dialog->exec() == QDialog::Accepted) {
                        document->print(&printer);
                    }

                    delete document;
}
/*
void MainWindow::on_pushButton_12_clicked()
{
   Enquette enquette;
     ui->tableView_enquette->setModel(enquette.archiver());
}





void MainWindow::on_pushButton_12_clicked(bool checked)
{
    Enquette enquette;
  ui->tableView_enquette->setModel(enquette.archiver(ui->dateEdit->text(),ui->label_datetime->text()));
}*/

