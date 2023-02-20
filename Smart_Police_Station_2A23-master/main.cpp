#include "connexion.h"
#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion db;
    if(!db.creerConnection())
        QMessageBox::critical(nullptr, "Database is not open", "Connection failled: \n"
                                "we cannot open a database\n Click cancel to quit", QMessageBox::Cancel);
    else
    {
        db.show();
        MainWindow window;
        return a.exec();
    }

    return -1;
}
