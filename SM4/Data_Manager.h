#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QByteArray>
#include <QList>
#include <QFile>
#include <tuple>
using std::tuple;
class Data_Manager
{
public:
    Data_Manager( );
    bool isOpen( );
    void closeDatabase( );
    ~Data_Manager( );
    
    //     0: 用户不存在
    // 其他值: 用户id
    bool is_User_Exit(QString name );
    int is_login_Success( QString name, QString password );
    bool add_User( QString name, QString password );
    bool delete_User( );
    bool change_User_Password( QString new_Password );
    bool is_Personal_Key( );
    int user_Id( );


    bool add_File( QList<tuple<QString, QByteArray>>& file, int user_Id, unsigned char key[16] );
    QList<tuple<QString, QByteArray>> decrypt_File( QList<int> file_Id, unsigned char key[16] );

    QList<tuple<int, QString>> get_All_FileId_Name();
    QList<tuple<int, QString>> search_File_By_Name( QString name );
    bool update_File_Key( unsigned char previouskey[16], unsigned char new_key[16] );

private:
    QSqlDatabase db;
    bool databeseIsOpen, isPersonalKey;
    int userId;
};