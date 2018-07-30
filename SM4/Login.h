#pragma once

#include <QDialog>
#include "ui_Login.h"
#include "Data_Manager.h"
class Login : public QDialog
{
    Q_OBJECT

public:
    Login( Data_Manager& database, QWidget *parent = Q_NULLPTR );
    ~Login();

private:
    Ui::Login ui;
    Data_Manager& my_Database;

protected:
    void closeEvent( QCloseEvent *e );

private slots:
    void exitProgram( );
    void login_Method( );
    void register_Method( );

};
