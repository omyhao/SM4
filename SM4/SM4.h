#pragma once

#include <QtWidgets/QMainWindow>
#include <QSqlDatabase>
#include "ui_SM4.h"
#include "Data_Manager.h"
class SM4 : public QMainWindow
{
    Q_OBJECT

public:
    SM4( Data_Manager& database, QWidget *parent = Q_NULLPTR);

protected:
    void closeEvent( QCloseEvent *ev );
private:
    Ui::SM4Class ui;
    Data_Manager& my_Database;
    QList<tuple<int, QString>> allIdName;
    QList<tuple<QString, QByteArray>> allFile;
private slots:
    void closeMainWindow( );
    void changeLoginPassword( );
    void deleteUser( );
    void encryptFiles( );
    void decryptSingleFile( );
    void decryptAllFiles( );
    void changeKey( );
    void searchFiles( );
    void showAllFile( );
};
