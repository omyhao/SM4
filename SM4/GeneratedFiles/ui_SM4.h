/********************************************************************************
** Form generated from reading UI file 'SM4.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM4_H
#define UI_SM4_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SM4Class
{
public:
    QAction *encrypt_files_Action;
    QAction *actionAll_File;
    QAction *change_loginPass_Action;
    QAction *actionb;
    QAction *exit_Action;
    QAction *decrypt_singleFile_Action;
    QAction *decrypt_allFiles_Action;
    QAction *change_key_Action;
    QAction *delete_user_actions;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *show_all_file_button;
    QLabel *label;
    QLabel *num_of_files_Lable;
    QFrame *line;
    QLineEdit *search_file_Edit;
    QPushButton *search_file_Button;
    QListWidget *all_files_ListWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;

    void setupUi(QMainWindow *SM4Class)
    {
        if (SM4Class->objectName().isEmpty())
            SM4Class->setObjectName(QStringLiteral("SM4Class"));
        SM4Class->resize(800, 600);
        SM4Class->setMinimumSize(QSize(800, 600));
        SM4Class->setMaximumSize(QSize(800, 600));
        encrypt_files_Action = new QAction(SM4Class);
        encrypt_files_Action->setObjectName(QStringLiteral("encrypt_files_Action"));
        actionAll_File = new QAction(SM4Class);
        actionAll_File->setObjectName(QStringLiteral("actionAll_File"));
        change_loginPass_Action = new QAction(SM4Class);
        change_loginPass_Action->setObjectName(QStringLiteral("change_loginPass_Action"));
        actionb = new QAction(SM4Class);
        actionb->setObjectName(QStringLiteral("actionb"));
        exit_Action = new QAction(SM4Class);
        exit_Action->setObjectName(QStringLiteral("exit_Action"));
        decrypt_singleFile_Action = new QAction(SM4Class);
        decrypt_singleFile_Action->setObjectName(QStringLiteral("decrypt_singleFile_Action"));
        decrypt_allFiles_Action = new QAction(SM4Class);
        decrypt_allFiles_Action->setObjectName(QStringLiteral("decrypt_allFiles_Action"));
        change_key_Action = new QAction(SM4Class);
        change_key_Action->setObjectName(QStringLiteral("change_key_Action"));
        delete_user_actions = new QAction(SM4Class);
        delete_user_actions->setObjectName(QStringLiteral("delete_user_actions"));
        centralWidget = new QWidget(SM4Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 801, 42));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 30, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        show_all_file_button = new QPushButton(horizontalLayoutWidget);
        show_all_file_button->setObjectName(QStringLiteral("show_all_file_button"));
        show_all_file_button->setMinimumSize(QSize(100, 30));
        show_all_file_button->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(show_all_file_button);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 30));
        label->setStyleSheet(QStringLiteral("font-size:14pt"));

        horizontalLayout->addWidget(label);

        num_of_files_Lable = new QLabel(horizontalLayoutWidget);
        num_of_files_Lable->setObjectName(QStringLiteral("num_of_files_Lable"));
        num_of_files_Lable->setMinimumSize(QSize(60, 30));
        num_of_files_Lable->setMaximumSize(QSize(60, 30));
        num_of_files_Lable->setLayoutDirection(Qt::LeftToRight);
        num_of_files_Lable->setStyleSheet(QStringLiteral("font-size:14pt;"));
        num_of_files_Lable->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        num_of_files_Lable->setMargin(0);

        horizontalLayout->addWidget(num_of_files_Lable);

        line = new QFrame(horizontalLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setMinimumSize(QSize(10, 0));
        line->setMaximumSize(QSize(16777215, 30));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        search_file_Edit = new QLineEdit(horizontalLayoutWidget);
        search_file_Edit->setObjectName(QStringLiteral("search_file_Edit"));
        search_file_Edit->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(search_file_Edit);

        search_file_Button = new QPushButton(horizontalLayoutWidget);
        search_file_Button->setObjectName(QStringLiteral("search_file_Button"));
        search_file_Button->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(search_file_Button);

        all_files_ListWidget = new QListWidget(centralWidget);
        all_files_ListWidget->setObjectName(QStringLiteral("all_files_ListWidget"));
        all_files_ListWidget->setGeometry(QRect(0, 40, 801, 541));
        all_files_ListWidget->setToolTipDuration(1);
        all_files_ListWidget->setLayoutDirection(Qt::LeftToRight);
        all_files_ListWidget->setStyleSheet(QStringLiteral("background-color:#f0f0f0;padding-left:22px;padding-right:30px;color:#696969;padding-top:22px;font-size:22pt;font-family:consolas,\"STKaiti\";"));
        all_files_ListWidget->setFrameShape(QFrame::NoFrame);
        all_files_ListWidget->setLineWidth(1);
        all_files_ListWidget->setGridSize(QSize(0, 44));
        SM4Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SM4Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        SM4Class->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(change_loginPass_Action);
        menu->addAction(delete_user_actions);
        menu->addSeparator();
        menu->addAction(exit_Action);
        menu_2->addAction(encrypt_files_Action);
        menu_2->addSeparator();
        menu_3->addAction(decrypt_singleFile_Action);
        menu_3->addSeparator();
        menu_3->addAction(decrypt_allFiles_Action);
        menu_4->addAction(change_key_Action);

        retranslateUi(SM4Class);

        QMetaObject::connectSlotsByName(SM4Class);
    } // setupUi

    void retranslateUi(QMainWindow *SM4Class)
    {
        SM4Class->setWindowTitle(QApplication::translate("SM4Class", "SM4\346\226\207\344\273\266\345\212\240\345\257\206\347\263\273\347\273\237", nullptr));
        encrypt_files_Action->setText(QApplication::translate("SM4Class", "\345\212\240\345\257\206\346\226\207\344\273\266", nullptr));
        actionAll_File->setText(QApplication::translate("SM4Class", "All File", nullptr));
        change_loginPass_Action->setText(QApplication::translate("SM4Class", "\344\277\256\346\224\271\347\231\273\345\275\225\345\257\206\347\240\201", nullptr));
        actionb->setText(QApplication::translate("SM4Class", "\351\200\200\345\207\272", nullptr));
        exit_Action->setText(QApplication::translate("SM4Class", "\351\200\200\345\207\272", nullptr));
        decrypt_singleFile_Action->setText(QApplication::translate("SM4Class", "\351\200\211\344\270\255\346\226\207\344\273\266", nullptr));
        decrypt_allFiles_Action->setText(QApplication::translate("SM4Class", "\346\211\200\346\234\211\346\226\207\344\273\266", nullptr));
        change_key_Action->setText(QApplication::translate("SM4Class", "\346\233\264\346\226\260\345\257\206\351\222\245", nullptr));
        delete_user_actions->setText(QApplication::translate("SM4Class", "\345\210\240\351\231\244\350\264\246\346\210\267", nullptr));
        show_all_file_button->setText(QApplication::translate("SM4Class", "\346\230\276\347\244\272\346\211\200\346\234\211\346\226\207\344\273\266", nullptr));
        label->setText(QApplication::translate("SM4Class", "\346\226\207\344\273\266\346\225\260:", nullptr));
        num_of_files_Lable->setText(QApplication::translate("SM4Class", "0", nullptr));
        search_file_Button->setText(QApplication::translate("SM4Class", "\346\220\234\347\264\242", nullptr));
        menu->setTitle(QApplication::translate("SM4Class", "\351\200\211\351\241\271", nullptr));
        menu_2->setTitle(QApplication::translate("SM4Class", "\345\212\240\345\257\206", nullptr));
        menu_3->setTitle(QApplication::translate("SM4Class", "\350\247\243\345\257\206", nullptr));
        menu_4->setTitle(QApplication::translate("SM4Class", "\345\257\206\351\222\245\347\256\241\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SM4Class: public Ui_SM4Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM4_H
