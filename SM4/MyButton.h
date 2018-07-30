#pragma once

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT

public:
    MyButton(QWidget *parent);
    ~MyButton();

protected:
    void mouseReleaseEvent( QMouseEvent *ev );

};
