#include "stdafx.h"
#include "SM4.h"
#include "Login.h"
#include <QtWidgets/QApplication>
#include "Data_Manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Data_Manager my_Database{ };
    //QApplication::setQuitOnLastWindowClosed( false );
    Login loginWindow(my_Database);
    if ( loginWindow.exec( ) == QDialog::Rejected )
    {
        a.exit( 0 );
        return 0;
    }
    else
    {
        SM4 w(my_Database);
        w.show( );
        return a.exec( );
    }
}
