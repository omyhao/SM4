#include "stdafx.h"
#include "SM4.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QUrl>
#include <QFile>
#include <QString>
#include <tuple>
#include <QStringList>
using std::tuple;
using std::make_tuple;
using std::get;

SM4::SM4( Data_Manager& database, QWidget *parent )
    : QMainWindow( parent ), my_Database{ database }
{
    ui.setupUi( this );

    //setWindowFlags( Qt::FramelessWindowHint );
    connect( ui.exit_Action, SIGNAL( triggered( ) ), this, SLOT( closeMainWindow( ) ) );
    connect( ui.change_loginPass_Action, SIGNAL( triggered( ) ), this, SLOT( changeLoginPassword( ) ) );
    connect( ui.encrypt_files_Action, SIGNAL( triggered( ) ), this, SLOT( encryptFiles( ) ) );
    connect( ui.decrypt_singleFile_Action, SIGNAL( triggered( ) ), this, SLOT( decryptSingleFile( ) ) );
    connect( ui.decrypt_allFiles_Action, SIGNAL( triggered( ) ), this, SLOT( decryptAllFiles( ) ) );
    connect( ui.change_key_Action, SIGNAL( triggered( ) ), this, SLOT( changeKey( ) ) );
    connect( ui.search_file_Button, SIGNAL( clicked( ) ), this, SLOT( searchFiles( ) ) );
    connect( ui.delete_user_actions, SIGNAL( triggered( ) ), this, SLOT( deleteUser( ) ) );
    connect( ui.show_all_file_button, SIGNAL( clicked( ) ), this, SLOT( showAllFile( ) ) );
    showAllFile( );
}


void SM4::showAllFile( )
{
    ui.all_files_ListWidget->clear( );
    allIdName = my_Database.get_All_FileId_Name( );
    //qDebug( ) << u8"取出数据行: " << allIdName.size( ) << endl;
    ui.num_of_files_Lable->setText( QString::number(allIdName.size( ) ));
    for ( tuple<int, QString>& single_item : allIdName  )
    {
        //qDebug( ) << u8"文件名: " << ( get<1>( single_item ) );
        ui.all_files_ListWidget->addItem((get<1>( single_item )) );
    }
}

void SM4::closeMainWindow( )
{
    this->close();
}



void SM4::changeLoginPassword( )
{
    bool isOk;
    QString new_Password = QInputDialog::getText( this, tr( u8"修改状态" ), tr( u8"请输入新的登录密码:" ), QLineEdit::Password, "", &isOk );
    if ( isOk ) {
        if ( my_Database.change_User_Password( new_Password ) )
        {
            QMessageBox::about( this, u8"修改状态", u8"修改成功" );
        }
        else
        {
            QMessageBox::about( this, u8"修改状态", u8"修改失败,请重试" );
        }
        
    }
    else
    {
        return;
    }
}

void SM4::deleteUser( )
{
    bool isOk;
    QString text = QInputDialog::getText( this, tr( u8"删除账户" ), tr( u8"输入YES来确定删除账户:" ), QLineEdit::Normal, u8"YES", &isOk );
    if ( isOk && (text==u8"YES") )
    {
        if ( my_Database.delete_User( ) )
        {
            QMessageBox::about( this, u8"状态", u8"删除账户成功" );
        }
        else {
            QMessageBox::about( this, u8"状态", u8"删除账户失败" );
        }
    }
    else
    {
        return;
    }
}

void SM4::encryptFiles( )
{
    QStringList all_names = QFileDialog::getOpenFileNames( this, u8"请选择需要加密的文件" );
    if ( all_names.size()>0 )
    {
        QList<tuple<QString, QByteArray>> all_file;
        for ( QString single_filePath : all_names )
        {
            QFileInfo single_file( single_filePath );
            /*qDebug( ) << single_file.filePath( ) << "---";
            qDebug( ) << single_file.fileName( ) << endl;*/
            QFile file( single_file.filePath( ) );
            if ( file.open(QIODevice::ReadOnly) )
            {
                QString file_name = single_file.fileName( );
                QByteArray byte_file = file.readAll( );
                all_file.push_back( std::make_tuple( file_name, byte_file ) );
            }
            /*qDebug( ) << u8"文件名  : " << single_file.fileName( ) << endl;
            qDebug( ) << u8"文件路径 : " << single_file.path( ) << endl;
            qDebug( ) << endl;*/        
            
        }
        qDebug( ) << u8"读取文件结束: " << endl;
        if ( my_Database.is_Personal_Key() )
        {
            bool isOk;
            QString text = QInputDialog::getText( this, tr( u8"提示" ), tr( u8"请输入加密密钥:" ), QLineEdit::Normal, "", &isOk );
            if ( isOk && ( !text.isEmpty( ) ) ) {
                QStringList result = text.split( "," );
                unsigned char new_key[16];
                for ( int i = 0; i < 16; i++ )
                {
                    new_key[i] = result.at( i ).toUInt( );
                }
                bool add_result = my_Database.add_File( all_file, my_Database.user_Id( ), new_key );
                if ( add_result )
                {
                    QMessageBox::about( this, u8"状态", u8"加密" + QString::number( all_names.size( ) ) + u8"个文件成功" );
                    this->showAllFile( );
                    return;
                }
                QMessageBox::about( this, u8"状态", u8"加密" + QString::number( all_names.size( ) ) + u8"个文件成功" );
                return;
            }
            else
            {
                return;
            }
            
        }
        else
        {
            unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
            bool result = my_Database.add_File( all_file, my_Database.user_Id( ), key );
            if ( reset )
            {
                QMessageBox::about( this, u8"状态", u8"加密" + QString::number( all_names.size( ) ) + u8"个文件成功" );
                this->showAllFile( );
                return;
            }
            QMessageBox::about( this, u8"状态", u8"加密" + QString::number( all_names.size( ) ) + u8"个文件成功" );
            return;
        }
        

    }
    return;    
}

void SM4::decryptSingleFile( )
{
    //下标从-1开始计算的
    //qDebug( ) << u8"下标位置: " << ui.all_files_ListWidget->currentIndex( ).row( ) << endl;
    if ( ui.all_files_ListWidget->currentIndex().row()>-1 )
    {
        int index = ui.all_files_ListWidget->currentIndex( ).row( );
        int file_id = get<0>(allIdName.at( index ));
        QList<int> all_id; 
        all_id.push_back( file_id );
        if ( my_Database.is_Personal_Key() )
        {
            bool isOk;
            QString text = QInputDialog::getText( this, tr( u8"提示" ), tr( u8"请输入加密密钥:" ), QLineEdit::Normal, "", &isOk );
            if ( isOk && ( !text.isEmpty( ) ) ) {
                QStringList result = text.split( "," );
                unsigned char new_key[16];
                for ( int i = 0; i < 16; i++ )
                {
                    new_key[i] = result.at( i ).toUInt( );
                }
                allFile = my_Database.decrypt_File( all_id, new_key );
                qDebug( ) << u8"要解压的文件个数: " << allFile.size( ) << endl;
                QString file_path = QFileDialog::getSaveFileName( this, u8"保存文件", "./" + ( get<0>( allFile.at( 0 ) ) ), QString( ), nullptr, QFileDialog::ShowDirsOnly );
                if ( file_path == u8"" )
                {
                    return;
                }
                qDebug( ) << u8"保存路径" << file_path << endl;
                QFileInfo result_file{ file_path };
                QFile output_file( result_file.filePath( ) );
                if ( output_file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
                {
                    qDebug( ) << u8"开始输出信息" << endl;
                    output_file.write( get<1>( allFile.at( 0 ) ) );
                    qDebug( ) << u8"输出信息结束" << endl;
                }
                output_file.close( );
                showAllFile( );
            }
            else
            {
                return;
            }
        }
        else
        {
            unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
            allFile = my_Database.decrypt_File( all_id, key );
            qDebug( ) << u8"要解压的文件个数: " << allFile.size( ) << endl;
            QString file_path = QFileDialog::getSaveFileName( this, u8"保存文件", "./" + ( get<0>( allFile.at( 0 ) ) ), QString( ), nullptr, QFileDialog::ShowDirsOnly );
            if ( file_path == u8"" )
            {
                return;
            }
            qDebug( ) << u8"保存路径" << file_path << endl;
            QFileInfo result{ file_path };
            QFile output_file( result.filePath( ) );
            if ( output_file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
            {
                qDebug( ) << u8"开始输出信息" << endl;
                output_file.write( get<1>( allFile.at( 0 ) ) );
                /*QDataStream out( &output_file );
                out.setVersion( QDataStream::Qt_5_10 );
                out << ( get<1>( allFile.at( 0 ) ));
                output_file.close( );*/
                qDebug( ) << u8"输出信息结束" << endl;
            }
            output_file.close( );
            showAllFile( );
            //qDebug( ) << u8"文件id: " << file_id << endl;
        }
        
        
    }
    else
    {
        QMessageBox::about( this, u8"提示", u8"未选中任何文件" );
    }
    
}

void SM4::decryptAllFiles( )
{

    if ( ui.all_files_ListWidget->count()>0 )
    {
        QString file_path = QFileDialog::getExistingDirectory( this, u8"请选择文件保存路径...", "./" );
        if ( file_path.isEmpty() )
        {
            return;
        }
        else
        {
            if ( my_Database.is_Personal_Key() )
            {
                bool isOk;
                QString text = QInputDialog::getText( this, tr( u8"提示" ), tr( u8"请输入解密密钥:" ), QLineEdit::Normal, "", &isOk );
                if ( isOk && ( !text.isEmpty( ) ) ) {
                    QStringList result = text.split( "," );
                    unsigned char new_key[16];
                    for ( int i = 0; i<16; i++ )
                    {
                         new_key[i] = result.at( i ).toUInt( )  ;
                    }
                    qDebug( ) << u8"选择的文件路径: " << file_path << endl;
                    QList<int> all_id;
                    for ( auto& single : allIdName )
                    {
                        all_id.push_back( get<0>( single ) );
                    }
                    //unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
                    allFile = my_Database.decrypt_File( all_id, new_key );
                    qDebug( ) << u8"要解压的文件个数: " << allFile.size( ) << endl;
                    for ( auto& single_file : allFile )
                    {
                        QFileInfo  result{ file_path + "/" + get<0>( single_file ) };
                        qDebug( ) << result.filePath( ) << endl;
                        QFile output_file( result.filePath( ) );
                        if ( output_file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
                        {
                            qDebug( ) << u8"开始输出信息" << endl;
                            output_file.write( get<1>( single_file ) );
                            qDebug( ) << u8"输出信息结束" << endl;
                        }
                        output_file.close( );
                    }
                }
                else
                {
                    return;
                }
            }
            //不是自定义key，则使用原始key
            else
            {
                qDebug( ) << u8"选择的文件路径: " << file_path << endl;
                QList<int> all_id;
                for ( auto& single : allIdName )
                {
                    all_id.push_back( get<0>( single ) );
                }
                unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
                allFile = my_Database.decrypt_File( all_id, key );
                qDebug( ) << u8"要解压的文件个数: " << allFile.size( ) << endl;
                for ( auto& single_file : allFile )
                {
                    QFileInfo  result{ file_path + "/" + get<0>( single_file ) };
                    qDebug( ) << result.filePath( ) << endl;
                    QFile output_file( result.filePath( ) );
                    if ( output_file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
                    {
                        qDebug( ) << u8"开始输出信息" << endl;
                        output_file.write( get<1>( single_file ) );
                        qDebug( ) << u8"输出信息结束" << endl;
                    }
                    output_file.close( );
                }
            }
            
        }     
        showAllFile( );
    }
    else
    {
        QMessageBox::about( this, u8"提示", u8"没有文件进行解密");
    }
   
}

void SM4::changeKey( )
{
    if ( my_Database.is_Personal_Key() )//是自定义key，所以需要用户输入原始key，和新的key。
    {
        bool preOk, newOk;
        QString preText = QInputDialog::getText( this, tr( u8"提示" ), tr( u8"请输入旧的加密密钥:" ), QLineEdit::Normal, "", &preOk );
        QString newText = QInputDialog::getText( this, tr( u8"提示" ), tr( u8"请输入新的加密密钥:" ), QLineEdit::Normal, "", &newOk );
        QStringList pre_num = preText.split( "," );
        QStringList now_num = newText.split( "," );
        if ( preOk && newOk && !(preText.isEmpty()) && !(newText.isEmpty()) )
        {
            unsigned char old_key[16], new_key[16];
            for ( int i = 0; i<16; i++ )
            {
                old_key[i] = pre_num.at( i ).toUInt( );
                new_key[i] = now_num.at( i ).toUInt( );
            }
            if ( my_Database.update_File_Key( old_key, new_key ) )
            {
                QMessageBox::about( this, u8"提示", u8"更新秘钥成功" );
                return;
            }
            else
            {
                QMessageBox::about( this, u8"提示", u8"更新秘钥失败" );
                return;
            }
            
        }
    } 
    else//不是自定义key，所以直接用原始key来解密即可
    {
        bool isOk;
        QString text = QInputDialog::getText( this, tr( u8"修改密钥" ), tr( u8"请输入新的加密密钥:" ), QLineEdit::Normal, "", &isOk );
        if ( isOk && ( !text.isEmpty( ) ) ) {
            qDebug( ) << u8"新的秘钥: " << text << endl;
            QStringList result = text.split( "," );
            unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
            unsigned char new_key[16];
            for ( int i = 0; i<16; i++ )
            {
                qDebug( ) << key[i] << u8"  " << ( new_key[i] = result.at( i ).toUInt( ) ) << endl;
            }
            if ( my_Database.update_File_Key( key, new_key ) )
            {
                QMessageBox::about( this, u8"提示", u8"更新秘钥成功" );
                return;
            }
            else
            {
                QMessageBox::about( this, u8"提示", u8"更新秘钥失败" );
                return;
            }
        }
    }
}

void SM4::searchFiles( )
{
    QString search_Name = ui.search_file_Edit->text();
    ui.all_files_ListWidget->clear( );
    allIdName = my_Database.search_File_By_Name( search_Name );
    if ( allIdName.size()!=0 )
    {
        qDebug( ) << u8"共搜到文件: " << allIdName.size( ) << endl;
        ui.num_of_files_Lable->setText( QString::number( allIdName.size( ) ) );
        for ( tuple<int, QString>& single_item : allIdName )
        {
            qDebug( ) << u8"文件名: " << ( get<1>( single_item ) );
            ui.all_files_ListWidget->addItem( ( get<1>( single_item ) ) );
        }
    }
    else
    {
        QMessageBox::about( this, u8"状态", u8"未搜到相关文件" );
        return;
    }  
}

void SM4::closeEvent( QCloseEvent * ev )
{
    //关闭数据库连接

    if ( QMessageBox::information( this, u8"提示", u8"确定进行关闭吗？", QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
    {
        my_Database.closeDatabase( );
        ev->accept( );
        QApplication::exit( 0 );
    }
    else
    {
        ev->ignore( );
    }
}