#include "stdafx.h"
#include <QSqlError>
#include <QString>
#include "Login.h"
#include "MyButton.h"
#include "En_Decrypt.h"
#include <QDebug>

Login::Login( Data_Manager& database, QWidget *parent )
    : QDialog( parent ), my_Database{ database }
{
    ui.setupUi(this);

    //setWindowFlags( Qt::FramelessWindowHint );
    connect( ui.exit_Button, SIGNAL( clicked( ) ), this, SLOT( exitProgram( ) ) );
    connect( ui.login_Button, SIGNAL( clicked( ) ), this, SLOT( login_Method( ) ) );
    connect( ui.register_Button, SIGNAL( clicked( ) ), this, SLOT( register_Method( ) ));
    //可以判断数据库是否连接成功
    //QMessageBox::about( this, u8"数据库信息", QString::number(my_Database.isOpen( )) );
}

Login::~Login()
{
}

void Login::closeEvent( QCloseEvent * e )
{  
    QApplication::exit( 0 );
}

void Login::login_Method( )
{
    QString user_name = ui.user_name_LineEdit->text( );  
    QString user_password =ui.password_LineEdit->text();
    if ( user_name == "" )
    {
        QMessageBox::about( this, u8"登录信息", u8"请输入用户名" );
        ui.user_name_LineEdit->setFocus( );
        return;
    }
    if ( user_password == "" )
    {
        QMessageBox::about( this, u8"登录信息", u8"请输入密码" );
        ui.password_LineEdit->setFocus( );
        return;
    }
    if ( my_Database.is_login_Success( user_name, user_password ) )
    {
        qDebug( ) << u8"用户名密码正确" << endl;
        accept( );
        //this->close( );
    }
    else
    {
        QMessageBox::about( this, u8"登录信息", u8"用户名或密码错误，请重新输入" );
        ui.password_LineEdit->clear( );
        ui.password_LineEdit->setFocus( );
        return;
    }
}

void Login::register_Method( )
{
    QString user_name = ui.user_name_LineEdit->text( );
    QString user_password = ui.password_LineEdit->text( );
    if ( user_name == "" )
    {
        QMessageBox::about( this, u8"注册信息", u8"请输入用户名" );
        ui.user_name_LineEdit->setFocus( );
        return;
    }
    if ( user_password == "" )
    {
        QMessageBox::about( this, u8"注册信息", u8"请输入密码" );
        ui.password_LineEdit->setFocus( );
        return;
    }
    if ( my_Database.is_User_Exit( user_name ) )
    {
        QMessageBox::about( this, u8"注册信息", u8"用户名已经存在，请重新输入" );
        ui.user_name_LineEdit->clear( );
        ui.user_name_LineEdit->setFocus( );
        return;
    }
    if ( my_Database.add_User( user_name, user_password ) )
    {
        QMessageBox::about( this, u8"注册信息", u8"注册成功，请登录" );
        return;
    }
    else
    {
        QMessageBox::about( this, u8"注册信息", u8"注册失败，请重试" );
        return;
    }
}

void Login::exitProgram( )
{
    this->close( );
}
