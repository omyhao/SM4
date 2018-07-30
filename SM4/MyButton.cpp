#include "stdafx.h"
#include "MyButton.h"

MyButton::MyButton(QWidget *parent)
    : QPushButton(parent)
{
}

MyButton::~MyButton()
{
}

void MyButton::mouseReleaseEvent( QMouseEvent * ev )
{
    if ( Qt::LeftButton == ev->button( ) )
    {

        emit clicked( );

    }
    else if ( Qt::RightButton == ev->button( ) )
    {
        if ( this->text() == u8"µÇÂ¼")
        {
            this->setText( u8"×¢²á" );
        }
        else
        {
            this->setText( u8"µÇÂ¼" );
        }
    }
}
