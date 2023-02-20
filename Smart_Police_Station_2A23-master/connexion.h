#ifndef CONNEXION_H
#define CONNEXION_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include "agent.h"

namespace Ui {
class Connexion;
}

class MainWindow;

class Connexion : public QWidget
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);
    ~Connexion();

    bool creerConnection();
    bool userExist(Agent&);
    bool userExist(Agent&, QString& matricule);

private slots:
    void on_connecter_clicked();

    void on_inputPwd_returnPressed();

    void on_inputLogin_returnPressed();

signals:
    void connect_moi(QString);

private:
    Ui::Connexion *ui;
};

#endif // CONNEXION_H
