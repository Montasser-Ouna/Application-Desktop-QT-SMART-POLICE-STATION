#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QListWidgetItem>
#include <QProgressDialog>
//#include <QtConcurrent>

#include <QThread>
#include <QFutureWatcher>
#include <QMessageBox>
#include "temoignage.h"
#include "enquette.h"
#include "agent.h"
#include "message.h"
#include "suspect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Agent user;
    Message msgUser;
    QString lastUserName;
    Temoignage temoignage;
    Enquette enquette;
    Suspect suspect;

//    static void doTask(int &number);

    bool attacherAgent(Agent&, QString&);
    void messageRecu(Message & msg);
    void utilisateurParti(const QString &);
    void utilisateurArriver(const QString &);
    void jsonRecu(const QJsonObject &docObj);

private slots:
    void on_actionUtilisateur_triggered();
    void on_actionAcceuil_triggered();
    void on_userTchat_clicked();
    void on_userConfig_clicked();
    void on_userList_clicked();
    void on_add_image_clicked();
    void on_add_user_clicked();
    void on_del_text_add_user_clicked();
    void on_btn_rafraichir_clicked();
    void on_btn_modifier_clicked();
    void on_btn_supprimer_clicked();
    void on_tabWidget_user_currentChanged(int index);
    void on_del_text_mod_user_clicked();
    void on_mod_user_clicked();
    void on_searchUser_textChanged(const QString &arg1);
    void on_searchUser_returnPressed();
    void on_trie_critere_currentIndexChanged(int index);
    void on_trie_ordre_currentIndexChanged(int index);
    void on_choix_recherche_currentIndexChanged(int index);
    void on_connect_message_clicked();
    void on_userList_msg_itemClicked(QListWidgetItem *item);
    void on_searchUser_msg_textChanged(const QString &arg1);
    void on_disconnect_msg_clicked();
    void on_pushButton_11_clicked();
    void on_effacer_msg_clicked();
    void on_password_msg_returnPressed();
    void on_envoyer_msg_clicked();
    void on_supprimer_msg_clicked();

    void connect_agent(QString);
    void trier(int& , int&);
    void deconnectedFromServer();
    void error(QAbstractSocket::SocketError);
    void connected();
    void lectureMessage();

    void on_actionEnquette_triggered();
    void showTime();

   /* void on_searchUser_cursorPositionChanged(int arg1, int arg2);

    void on_trie_critere_activated(const QString &arg1);

    void on_tabWidget_2_currentChanged(int index);

    void on_stackedWidget_user_currentChanged(int arg1);

    void on_stackedWidget_widgetRemoved(int index);
*/

    void on_pushButtonmodifier_clicked();

    void on_pushButtonajouter_clicked();

    void on_pushButtonsupprimer_clicked();

    void on_pushButton_7_clicked();

    void on_btn_actualiserTmg_clicked();

    void on_pushButton_suspect_clicked();


    void on_pushButton_enquette_2_clicked();

    void on_pushButton_temoin_clicked();

    void on_pushButton_ajouterenquette_clicked();



    void on_pushButton_ajoususpect_clicked();

    void on_pushButton_6_clicked();

    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_10_clicked();

    void on_lineEdit_15_textChanged(const QString &arg1);

    void on_pushButton_16_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_supprimersuspect_clicked();

    //void on_lineEdit_12_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();


    void on_pushButton_13_clicked();




//
    //void on_pushButton_12_clicked(bool checked);

    void on_pushButton_13_toggled(bool checked);

signals:
    void open_message();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
