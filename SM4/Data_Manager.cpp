#include "stdafx.h"
#include "Data_Manager.h"
#include "En_Decrypt.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <exception>
#include <iostream>
#include <QSqlDriver>
#include <QSqlRecord>
using std::get;
using std::make_tuple;
using namespace std;
Data_Manager::Data_Manager( ) :userId{0}
{
    if ( QSqlDatabase::contains( "qt_sql_default_connection" ) )
        db = QSqlDatabase::database( "qt_sql_default_connection" );
    else
        db = QSqlDatabase::addDatabase( "QMYSQL" );
    db.setHostName( "localhost" );
    db.setPort( 3306 );
    db.setDatabaseName( "sm4_filesystem" );
    db.setUserName( "root" );
    db.setPassword( "123456" );
    databeseIsOpen = db.open( );
    qDebug( ) << u8"数据库连接状态" << databeseIsOpen ;
}

bool Data_Manager::isOpen( )
{
    return databeseIsOpen;
}

void Data_Manager::closeDatabase( )
{
    db.close( );
}


Data_Manager::~Data_Manager( )
{
    if ( db.isOpen( ) || db.isValid( ) )
    {
        db.close( );
        qDebug( ) << u8"数据库关闭成功" << endl;
    }
}

bool Data_Manager::is_User_Exit( QString name )
{
    //qDebug( ) << u8"开始检查所注册用户名是否存在:" << endl;
    //qDebug( ) << u8"所查询用户名:" << name << endl;
    QSqlQuery isUserExitQuery ( db.database( )) ;
    //qDebug( ) << u8"构造QSqlQuery成功:" << endl;
    isUserExitQuery.prepare( "select * from user where user_name=:name" );
    isUserExitQuery.bindValue( ":name", name );
    //qDebug( ) << u8"绑定值结束:" << endl;
    //qDebug( ) << u8"是否支持size函数:" <<  db.driver( )->hasFeature( QSqlDriver::QuerySize );
    isUserExitQuery.exec( );
    //qDebug( ) << "query.size() :" << isUserExitQuery.size( );
    //qDebug( ) << u8"执行语句结果: " << isUserExitQuery.exec( );
    //qDebug( ) << u8"语句错误信息: " << isUserExitQuery.lastError( ).text( ) << endl;
    //isUserExitQuery.last( );
    //int result = isUserExitQuery.at( ) + 1;
    //bool result = isUserExitQuery.next( );
    //int result = isUserExitQuery.record( ).count( );
     //qDebug( ) << u8"是否存在 :" << result <<  endl;
    //qDebug( ) << u8"出错信息:" << errorMessage( ) << endl;
    /*int numOfUser =  isUserExitQuery.value(0).toInt();
    qDebug( ) << numOfUser << endl;
    bool result = numOfUser>0? false: true;*/
    return isUserExitQuery.size( )>0;
}

int Data_Manager::is_login_Success( QString name, QString password )
{
    /*unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
    qDebug( ) << u8"原始密码: " << password << endl;
    QByteArray encrypt_password;
    Encrypt_String( password.toUtf8( ), encrypt_password, key );
    qDebug( ) << u8"加密后的密码是(QByteArray形式): " << encrypt_password << endl;
    qDebug( ) << u8"开始解密:" << endl;
    qDebug( ) << u8"数据库中的密码QByteArray形式: " << encrypt_password << endl;
    Decrypt_String( encrypt_password, key );
    qDebug( ) << u8"解密后的密码是: " << QString::fromUtf8( (char*)encrypt_password.data( ) );*/

    QSqlQuery isLoginSuccessQuery( db.database( ) );
    isLoginSuccessQuery.prepare( "select * from user where user_name =:name" );
    isLoginSuccessQuery.bindValue( ":name", name );
    isLoginSuccessQuery.exec( );
    if ( isLoginSuccessQuery.size() )
    {
        unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
        //qDebug( ) << u8"找到了用户名: " << name << endl;
        //QByteArray encrypt_password;
        //Encrypt_String( password.toUtf8( ), encrypt_password, key );
        //qDebug( ) << u8"密码加密后: " << encrypt_password << endl;
        isLoginSuccessQuery.next( );
        
        QByteArray encrypted_password = isLoginSuccessQuery.value( 2 ).toByteArray();
        QByteArray result;
        //qDebug( ) << u8"数据库中密码转为QByteArray之后: " << encrypted_password << endl;
        //qDebug( ) << u8"转为QByteArray之后的长度: " << encrypted_password.length( ) << endl;
        Decrypt_String( encrypted_password, result,key );
        //qDebug( ) << u8"解压后的密码QByteArray: " << result << endl;
        QString decrypted_Password = QString::fromUtf8( (char*)result.data( ) );
        //qDebug( ) << u8"从数据库中解密得到的密码: " << decrypted_Password << endl;
        ////qDebug( ) << u8"原始密码: " << password << endl;
        //qDebug( ) << u8"解密后的密码: " << QString::fromLocal8Bit( (char*)result.data( ) ) << endl;
        if ( password == decrypted_Password )
        {
            //qDebug( ) << u8"和数据库中密码相同" << endl;
            this->isPersonalKey = isLoginSuccessQuery.value( 3 ).toInt( );
            this->userId = isLoginSuccessQuery.value( 0 ).toInt( );
            //qDebug( ) << u8"userId的地址: " << &(this->userId) << endl;
            //qDebug( ) << u8"Id: " << this->userId << " key: " << this->isPersonalKey << endl;
            ////qDebug( ) << u8"用户Id: " << userId << endl << u8"是否自定义key:" << isPersonalKey << endl;
            return this->userId;
        }        
    }
    return 0;
}

//完成
//addUserQuery.prepare( "insert into user (user_name, user_password) values (:user_name, :user_password)" );
bool Data_Manager::add_User( QString name, QString password )
{
    //qDebug( ) << u8"进入add_User函数" << endl;
    unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
    //qDebug( ) << u8"key值" << key << endl;
    //qDebug( ) << u8"开始加密密码" << endl;
    QByteArray password_array = password.toUtf8( );
    int size = password_array.size( );
    int change_size = ( size / 16 + 1 ) * 16;
    password_array.resize( change_size );
    QByteArray result_Password;
    Encrypt_String( password_array, result_Password, key );
    //qDebug( ) << u8"原始密码QByteArray: " << password.toLocal8Bit( ) << endl;
    //QString encrypted_Password = QString::fromUtf8( (char*)result_Password.data( ) );
    //qDebug( ) << u8"原始密码加密后:" << result_Password << endl;
    //qDebug( ) << u8"原始密码加密后的length是: " << result_Password.length() << u8" size()是: " << result_Password.size() << endl;
    //QByteArray decrypted_Password;
    //Decrypt_String( result_Password, decrypted_Password, key );
    //qDebug( ) << u8"马上解密得到ByteArray: " << decrypted_Password.data() << endl;
    //qDebug( ) << u8"解压后的length: " << decrypted_Password.length( ) << u8" size()是: " << decrypted_Password.size( ) << endl;
    //qDebug( ) << u8"再一次解密: " << endl;
    //QByteArray second_Password;
    //QByteArray decrypted_pass{result_Password};
    /*decrypted_pass.resize( result_Password.size() );
    decrypted_pass.fill( '\0' );
    for ( int i = 0; i < result_Password.size(); i++ )
    {
        decrypted_pass[i] = result_Password[i];
    }*/
    //qDebug( ) << u8"使用赋值得到的QByteArray" << decrypted_pass << endl;
    //qDebug( ) << u8"赋值得到的加密密码length: " << decrypted_pass.length( ) << u8" size()是: " << decrypted_pass.size( );
    //qDebug( ) << u8"赋值得到的加密密码的data: " << decrypted_pass.data( ) << endl;
    //Decrypt_String( decrypted_pass, second_Password, key );
    //qDebug( ) << u8"第二次解压得到的密码: " << second_Password.data() << endl;
    //qDebug( ) << u8"开始构造Query" << endl;
    QSqlQuery addUserQuery( db.database() );
    addUserQuery.prepare( "insert into user (user_name, user_password) values (:user_name, :user_password)" );
    //qDebug( ) << u8"开始绑定值" << endl;
    addUserQuery.bindValue( ":user_name", name );
    addUserQuery.bindValue( ":user_password", result_Password );
    //qDebug( ) << u8"绑定值结束" << endl;
    //qDebug( ) << u8"开始执行sql语句" << endl;
    bool result = addUserQuery.exec( );
    //qDebug( ) << u8"sql语句执行结束: " << result <<  endl;
    //qDebug( ) << u8"立马从数据库中取出来密码: ";
    /*QSqlQuery isLoginSuccessQuery( db.database( ) );
    isLoginSuccessQuery.prepare( "select * from user where user_name =:name" );
    isLoginSuccessQuery.bindValue( ":name", name );
    isLoginSuccessQuery.exec( );
    isLoginSuccessQuery.next( );*/
    /*QByteArray encrypted_password = isLoginSuccessQuery.value( 2 ).toByteArray( );*/

    /*QByteArray encrypted_password = result_Password;
    QByteArray result_pass;*/
    //qDebug( ) << u8"数据库中密码转为QByteArray之后: " << encrypted_password.data() << endl;
    //qDebug( ) << u8"转为QByteArray之后的长度: " << encrypted_password.length( ) << endl;
    //Decrypt_String( encrypted_password, result_pass, key );
    //qDebug( ) << u8"解压后的密码QByteArray: " << result_pass.data() << endl;
    /*bool isEqual{false};
    for ( int i = 0; i < result_Password.length(); i++ )
    {
        if ( result_Password.at(i) == encrypted_password.at(i) )
        {
            isEqual = true;
        }
        else
        {
            qDebug( ) << u8"位置 " << i << u8"不同" << endl;
            isEqual = false;
        }
    }*/
    //qDebug( ) << u8"存进去的QByteArray和取出来的是否相等: " << isEqual << endl;
    return result;
}
//完成
bool Data_Manager::delete_User(  )
{
    //qDebug( ) << u8"删除用户时: " << endl;
    //qDebug( ) << u8"userId的地址: " << &( this->userId ) << endl;
    //qDebug( ) << u8"当前用户id: " << this->userId << endl;
    QSqlQuery deleteUserQuery( db.database( ) );
    deleteUserQuery.prepare( "delete from user where user_id = :id_num" );
    deleteUserQuery.bindValue(":id_num",this->userId );
    bool result_user = deleteUserQuery.exec( );

    QSqlQuery deleteUserFileQuery( db.database( ) );
    deleteUserFileQuery.prepare( "delete from file where from_user_id = :id_num" );
    deleteUserFileQuery.bindValue( ":id_num", this->userId );
    bool result_file = deleteUserFileQuery.exec( );
    return result_user&&result_file;
}

//完成
bool Data_Manager::change_User_Password( QString new_Password )
{
    //qDebug( ) << u8"新的密码: " << new_Password << endl;
    //qDebug( ) << u8"数据库状态: " << db.isOpen( ) << endl;
    QSqlQuery changePasswordQuery( db.database( ) );
    changePasswordQuery.prepare( "update user set user_password = ? where user_id = ?" );
    unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
    QByteArray password_array = new_Password.toUtf8( );
    int size = password_array.size( );
    int change_size = ( size / 16 + 1 ) * 16;
    password_array.resize( change_size );
    QByteArray result;
    Encrypt_String( password_array, result, key );
    //qDebug( ) << u8"加密后的新密码: " << result.data( ) << endl;
    changePasswordQuery.addBindValue( result );
    changePasswordQuery.addBindValue( this->userId );
    bool exec_result = changePasswordQuery.exec( );
    //qDebug( ) << changePasswordQuery.lastError( ).text( ) << endl;
    return exec_result;
}

bool Data_Manager::is_Personal_Key( )
{
    return isPersonalKey;
}

int Data_Manager::user_Id( )
{
    return this->userId;
}

bool Data_Manager::add_File( QList<tuple<QString, QByteArray>>& file, int user_Id, unsigned char key[16] )
{
    //qDebug( ) << u8"共有文件数: " << file.size( ) << endl;
    QVariantList file_Names, user_Ids,different_size, encrypted_Files;
    for ( tuple<QString, QByteArray>& single_File : file )
    {
        QByteArray source_file( get<1>( single_File ) );
        qDebug( ) << u8"原始文件的长度: " << source_file.size( ) << endl;
        qDebug( ) << u8"原始文件内容: " << source_file.data( ) << endl;
        QByteArray encrypted_File;
        int new_size = ( (get<1>( single_File ).size( )) / 16 + 1 ) * 16;
        int different = new_size - (get<1>( single_File ) .size( ));
        source_file.resize( new_size );
        qDebug( ) << u8"原始文件长度修改为: " << new_size << endl;
        Encrypt_ByteArray(source_file , encrypted_File, key );
        qDebug( ) << u8"加密后的文件内容: " <<encrypted_File.data( ) << endl;
        //绑定顺序file_name, from_user_id, different_size,  file
        file_Names<< get<0>( single_File );
        user_Ids<< user_Id ;
        different_size << different;
        encrypted_Files<< encrypted_File ;   
    }
    QSqlQuery addFileQuery( db.database( ) );
    addFileQuery.prepare( "insert into file (file_name, from_user_id, different_size, file ) values(?,?,?,?)" );
    addFileQuery.addBindValue( file_Names );
    addFileQuery.addBindValue( user_Ids );
    addFileQuery.addBindValue( different_size );
    addFileQuery.addBindValue( encrypted_Files );
    bool result = addFileQuery.execBatch( );
    qDebug( ) << u8"出错信息: " << addFileQuery.lastError().text() << endl;
    return result;
}

QList<tuple<QString, QByteArray>> Data_Manager::decrypt_File( QList<int> file_Id, unsigned char key[16] )
{
    qDebug( ) << u8"所有file id: " << endl;
    for ( int id: file_Id )
    {
        qDebug( ) << id ;
    }
    qDebug( ) << endl;
    QSqlQuery decryptFileQuery(db.database());
    QSqlQuery deleteFileQuery( db.database( ) );
    decryptFileQuery.prepare( "select file_name, different_size, file from file where file_id = ?" );
    deleteFileQuery.prepare( "delete from file where file_id = ?" );
    //" select file_name, file from file where file_id = ?"
    QList<tuple<QString, QByteArray>> result;
    for ( int single_Id: file_Id )
    { 
        decryptFileQuery.bindValue( 0, single_Id );
        decryptFileQuery.exec( );
        if ( decryptFileQuery.next( ) )
        {
            QByteArray decrypt_Array;
            Decrypt_ByteArray( decryptFileQuery.value( 2 ).toByteArray( ), decrypt_Array,key );
            qDebug( ) << u8"解密后的size: " << decrypt_Array.size( ) << endl;
            qDebug( ) << u8"解密后的文件内容: " << decrypt_Array.data( ) << endl;
            int different_size = decryptFileQuery.value( 1 ).toInt( );
            int result_size = decrypt_Array.size( ) - different_size;
            decrypt_Array.resize( result_size );
            qDebug( ) << u8"截断后的size: " << result_size << endl;
            qDebug( ) << u8"最终的文件内容: " << decrypt_Array.data( ) << endl;
            result.push_back( make_tuple( decryptFileQuery.value( 0 ).toString( ), decrypt_Array ) );
            deleteFileQuery.bindValue( 0, single_Id );
            deleteFileQuery.exec( );
        }
        else
        {
            result.clear( );
            return result;
        }
    } 
    return result;
}

QList<tuple<int, QString>> Data_Manager::get_All_FileId_Name( )
{
    QSqlQuery getAllFileIdNameQuery( db.database( ) );
    getAllFileIdNameQuery.prepare( "select file_id, file_name from file where from_user_id =:id_num" );
    getAllFileIdNameQuery.bindValue( ":id_num", this->userId );
    getAllFileIdNameQuery.exec( );
    QList<tuple<int, QString>> result;
    while ( getAllFileIdNameQuery.next() )
    {
        result.push_back( make_tuple( getAllFileIdNameQuery.value( 0 ).toInt( ),
                                      getAllFileIdNameQuery.value( 1 ).toString( )
        ) );
    }
    return result;
}

QList<tuple<int, QString>> Data_Manager::search_File_By_Name( QString name )
{
    qDebug( ) << u8"模糊查询的名字: " << name << endl;
    //"select file_id,file_name from file where from_user_id = ? and file_name like '%?%'"
    QSqlQuery searchFileByNameQuery( db.database( ) );
    searchFileByNameQuery.prepare( "select file_id,file_name from file where from_user_id =:id_num and file_name like :search_name" );
    searchFileByNameQuery.bindValue( ":id_num", this->userId );
    searchFileByNameQuery.bindValue( ":search_name", "%"+name+"%" );
    searchFileByNameQuery.exec( );
    QList<tuple<int, QString>> result;
    while ( searchFileByNameQuery.next() )
    {
        result.push_back( make_tuple( searchFileByNameQuery.value( 0 ).toInt( ),
                                      searchFileByNameQuery.value( 1 ).toString( )
        ) );
    }
    return result;
}


bool Data_Manager::update_File_Key(unsigned char previouskey[16], unsigned char new_key[16] )
{
    QSqlQuery updateFileKeyQuery(db.database()), getAllFileIdByteArrayQuery(db.database());
    updateFileKeyQuery.prepare( "update file set file = ? where file_id = ?" );
    getAllFileIdByteArrayQuery.prepare( "select file_id, file from file where from_user_id = ?" );
    QList<tuple<int, QByteArray>> result;
    getAllFileIdByteArrayQuery.bindValue( 0, this->userId );
    getAllFileIdByteArrayQuery.exec( );
    while ( getAllFileIdByteArrayQuery.next( ) )
    {
        result.push_back( make_tuple( getAllFileIdByteArrayQuery.value( 0 ).toInt( ),
                                      getAllFileIdByteArrayQuery.value( 1 ).toByteArray( )
        ) );
    }
    QList<QByteArray> result_file;
    for ( tuple<int, QByteArray>& single : result )
    {
        //这里注意，要重新改
        QByteArray middle;
        Decrypt_ByteArray( get<1>( single ), middle, previouskey );
        QByteArray new_file;
        Encrypt_ByteArray( middle,  new_file, new_key );
        result_file.push_back( new_file );
    }
    QVariantList all_File_Ids, all_Files;
    for ( int i = 0; i < result.size(); i++ )
    {
        all_File_Ids << get<0>( result.at(i) );
        all_Files <<  result_file.at(i) ;
    }
    updateFileKeyQuery.addBindValue( all_Files );
    updateFileKeyQuery.addBindValue( all_File_Ids );
    updateFileKeyQuery.execBatch( );

    QSqlQuery update_key_status( db.database( ) );
    update_key_status.prepare( "update user set user_key = ? where user_id = ?" );
    update_key_status.bindValue( 0, 1 );
    update_key_status.bindValue( 1, this->userId );
    if ( update_key_status.exec() )
    {
        return this->isPersonalKey = true;
    }
    return false;
}