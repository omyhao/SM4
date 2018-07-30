/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *user_name_LineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *password_LineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *register_Button;
    QPushButton *login_Button;
    QPushButton *exit_Button;
    QLabel *label_4;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(400, 300);
        Login->setMinimumSize(QSize(400, 300));
        Login->setMaximumSize(QSize(400, 300));
        layoutWidget = new QWidget(Login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 40, 242, 192));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(240, 0));
        label->setMaximumSize(QSize(240, 30));
        label->setStyleSheet(QStringLiteral("font-size:14pt;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 40, -1, -1);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(50, 30));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        user_name_LineEdit = new QLineEdit(layoutWidget);
        user_name_LineEdit->setObjectName(QStringLiteral("user_name_LineEdit"));
        user_name_LineEdit->setMinimumSize(QSize(170, 0));
        user_name_LineEdit->setMaximumSize(QSize(170, 30));

        horizontalLayout_3->addWidget(user_name_LineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 20, -1, -1);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(50, 30));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_3);

        password_LineEdit = new QLineEdit(layoutWidget);
        password_LineEdit->setObjectName(QStringLiteral("password_LineEdit"));
        password_LineEdit->setMinimumSize(QSize(170, 0));
        password_LineEdit->setMaximumSize(QSize(170, 30));
        password_LineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(password_LineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 20, -1, -1);
        register_Button = new QPushButton(layoutWidget);
        register_Button->setObjectName(QStringLiteral("register_Button"));

        horizontalLayout->addWidget(register_Button);

        login_Button = new QPushButton(layoutWidget);
        login_Button->setObjectName(QStringLiteral("login_Button"));
        login_Button->setMinimumSize(QSize(50, 0));
        login_Button->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(login_Button);

        exit_Button = new QPushButton(layoutWidget);
        exit_Button->setObjectName(QStringLiteral("exit_Button"));
        exit_Button->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(exit_Button);


        verticalLayout->addLayout(horizontalLayout);

        label_4 = new QLabel(Login);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 30, 151, 21));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(14);
        label_4->setFont(font);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", nullptr));
        label->setText(QApplication::translate("Login", "\346\254\242\350\277\216\344\275\277\347\224\250\346\226\207\344\273\266\345\255\230\345\202\250\345\212\240\345\257\206\347\263\273\347\273\237", nullptr));
        label_2->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_3->setText(QApplication::translate("Login", "\345\257\206\347\240\201:", nullptr));
        register_Button->setText(QApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
        login_Button->setText(QApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        exit_Button->setText(QApplication::translate("Login", "\351\200\200\345\207\272", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
