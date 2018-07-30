#pragma once
#ifndef EN_DECRYPT_H_
#define EN_DECRYPT_H_

#include<QString>
#include<QByteArray>

void Encrypt_String( QByteArray& source, QByteArray& result, unsigned char key[16] );
void Decrypt_String( QByteArray& source, QByteArray& result, unsigned char key[16] );
void Encrypt_ByteArray( QByteArray& source_file, QByteArray& result_file, unsigned char key[16] );
void Decrypt_ByteArray( QByteArray& source_file, QByteArray& result_file, unsigned char key[16] );


#endif // !EN_DECRYPT_H_

