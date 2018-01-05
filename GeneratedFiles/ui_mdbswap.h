/********************************************************************************
** Form generated from reading UI file 'mdbswap.ui'
**
** Created: Fri Jan 5 14:14:34 2018
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MDBSWAP_H
#define UI_MDBSWAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MdbSwapClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelDbName;
    QLabel *label;
    QComboBox *comboType;
    QTabWidget *tab;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *BtnSel;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnToSqlite;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MdbSwapClass)
    {
        if (MdbSwapClass->objectName().isEmpty())
            MdbSwapClass->setObjectName(QStringLiteral("MdbSwapClass"));
        MdbSwapClass->resize(601, 400);
        centralWidget = new QWidget(MdbSwapClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelDbName = new QLabel(centralWidget);
        labelDbName->setObjectName(QStringLiteral("labelDbName"));

        horizontalLayout_2->addWidget(labelDbName);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        comboType = new QComboBox(centralWidget);
        comboType->setObjectName(QStringLiteral("comboType"));

        horizontalLayout_2->addWidget(comboType);

        horizontalLayout_2->setStretch(0, 6);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        tab = new QTabWidget(centralWidget);
        tab->setObjectName(QStringLiteral("tab"));

        verticalLayout->addWidget(tab);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        BtnSel = new QPushButton(centralWidget);
        BtnSel->setObjectName(QStringLiteral("BtnSel"));

        horizontalLayout->addWidget(BtnSel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtnToSqlite = new QPushButton(centralWidget);
        BtnToSqlite->setObjectName(QStringLiteral("BtnToSqlite"));

        horizontalLayout->addWidget(BtnToSqlite);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        MdbSwapClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MdbSwapClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 601, 23));
        MdbSwapClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MdbSwapClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MdbSwapClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MdbSwapClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MdbSwapClass->setStatusBar(statusBar);

        retranslateUi(MdbSwapClass);

        QMetaObject::connectSlotsByName(MdbSwapClass);
    } // setupUi

    void retranslateUi(QMainWindow *MdbSwapClass)
    {
        MdbSwapClass->setWindowTitle(QApplication::translate("MdbSwapClass", "\346\225\260\346\215\256\345\272\223\350\275\254\346\215\242", 0));
        labelDbName->setText(QApplication::translate("MdbSwapClass", "\345\275\223\345\211\215\346\225\260\346\215\256\345\272\223\357\274\232", 0));
        label->setText(QApplication::translate("MdbSwapClass", "\350\275\254\346\215\242\347\261\273\345\236\213\357\274\232", 0));
        BtnSel->setText(QApplication::translate("MdbSwapClass", "\351\200\211\346\213\251mdb\346\226\207\344\273\266", 0));
        BtnToSqlite->setText(QApplication::translate("MdbSwapClass", "\350\275\254\346\215\242", 0));
    } // retranslateUi

};

namespace Ui {
    class MdbSwapClass: public Ui_MdbSwapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MDBSWAP_H
