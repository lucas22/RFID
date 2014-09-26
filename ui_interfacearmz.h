/********************************************************************************
** Form generated from reading UI file 'interfacearmz.ui'
**
** Created: Tue Jul 15 15:39:01 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEARMZ_H
#define UI_INTERFACEARMZ_H

#include <QtCore/QVariant>
#include <QtGui>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QToolBar>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_interfaceArmz
{
public:
    QAction *actionCarregarMapa;
    QAction *actionSair;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *dia;
    QLineEdit *mes;
    QLineEdit *ano;
    QLineEdit *dia_2;
    QLineEdit *mes_2;
    QLineEdit *ano_2;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *pushButton;
    QLineEdit *hora_2;
    QLineEdit *min_2;
    QLineEdit *seg_2;
    QLineEdit *min;
    QLineEdit *hora;
    QLineEdit *seg;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menuArquivo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *interfaceArmz)
    {
        if (interfaceArmz->objectName().isEmpty())
            interfaceArmz->setObjectName(QString::fromUtf8("interfaceArmz"));
        interfaceArmz->resize(422, 300);
        actionCarregarMapa = new QAction(interfaceArmz);
        actionCarregarMapa->setObjectName(QString::fromUtf8("actionCarregarMapa"));
        actionSair = new QAction(interfaceArmz);
        actionSair->setObjectName(QString::fromUtf8("actionSair"));
        centralWidget = new QWidget(interfaceArmz);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 151, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 50, 21, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 50, 31, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 50, 41, 17));
        dia = new QLineEdit(centralWidget);
        dia->setObjectName(QString::fromUtf8("dia"));
        dia->setGeometry(QRect(60, 80, 41, 27));
        dia->setMaxLength(2);
        dia->setAlignment(Qt::AlignCenter);
        mes = new QLineEdit(centralWidget);
        mes->setObjectName(QString::fromUtf8("mes"));
        mes->setGeometry(QRect(110, 80, 41, 27));
        mes->setMaxLength(2);
        mes->setAlignment(Qt::AlignCenter);
        ano = new QLineEdit(centralWidget);
        ano->setObjectName(QString::fromUtf8("ano"));
        ano->setGeometry(QRect(160, 80, 81, 27));
        ano->setMaxLength(4);
        ano->setAlignment(Qt::AlignCenter);
        dia_2 = new QLineEdit(centralWidget);
        dia_2->setObjectName(QString::fromUtf8("dia_2"));
        dia_2->setGeometry(QRect(60, 130, 41, 27));
        dia_2->setMaxLength(2);
        dia_2->setAlignment(Qt::AlignCenter);
        mes_2 = new QLineEdit(centralWidget);
        mes_2->setObjectName(QString::fromUtf8("mes_2"));
        mes_2->setGeometry(QRect(110, 130, 41, 27));
        mes_2->setMaxLength(2);
        mes_2->setAlignment(Qt::AlignCenter);
        ano_2 = new QLineEdit(centralWidget);
        ano_2->setObjectName(QString::fromUtf8("ano_2"));
        ano_2->setGeometry(QRect(160, 130, 81, 27));
        ano_2->setMaxLength(4);
        ano_2->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 70, 41, 17));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 120, 41, 17));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 180, 99, 27));
        hora_2 = new QLineEdit(centralWidget);
        hora_2->setObjectName(QString::fromUtf8("hora_2"));
        hora_2->setGeometry(QRect(260, 130, 41, 27));
        hora_2->setMaxLength(2);
        hora_2->setAlignment(Qt::AlignCenter);
        min_2 = new QLineEdit(centralWidget);
        min_2->setObjectName(QString::fromUtf8("min_2"));
        min_2->setGeometry(QRect(310, 130, 41, 27));
        min_2->setMaxLength(2);
        min_2->setAlignment(Qt::AlignCenter);
        seg_2 = new QLineEdit(centralWidget);
        seg_2->setObjectName(QString::fromUtf8("seg_2"));
        seg_2->setGeometry(QRect(360, 130, 41, 27));
        seg_2->setMaxLength(2);
        seg_2->setAlignment(Qt::AlignCenter);
        min = new QLineEdit(centralWidget);
        min->setObjectName(QString::fromUtf8("min"));
        min->setGeometry(QRect(310, 80, 41, 27));
        min->setMaxLength(2);
        min->setAlignment(Qt::AlignCenter);
        hora = new QLineEdit(centralWidget);
        hora->setObjectName(QString::fromUtf8("hora"));
        hora->setGeometry(QRect(260, 80, 41, 27));
        hora->setMaxLength(2);
        hora->setAlignment(Qt::AlignCenter);
        seg = new QLineEdit(centralWidget);
        seg->setObjectName(QString::fromUtf8("seg"));
        seg->setGeometry(QRect(360, 80, 41, 27));
        seg->setMaxLength(2);
        seg->setAlignment(Qt::AlignCenter);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(320, 50, 31, 17));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(370, 50, 31, 17));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(270, 50, 21, 17));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 210, 71, 27));
        interfaceArmz->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(interfaceArmz);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 422, 25));
        menuArquivo = new QMenu(menuBar);
        menuArquivo->setObjectName(QString::fromUtf8("menuArquivo"));
        interfaceArmz->setMenuBar(menuBar);
        mainToolBar = new QToolBar(interfaceArmz);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        interfaceArmz->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(interfaceArmz);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        interfaceArmz->setStatusBar(statusBar);
        QWidget::setTabOrder(dia, mes);
        QWidget::setTabOrder(mes, ano);
        QWidget::setTabOrder(ano, hora);
        QWidget::setTabOrder(hora, min);
        QWidget::setTabOrder(min, seg);
        QWidget::setTabOrder(seg, dia_2);
        QWidget::setTabOrder(dia_2, mes_2);
        QWidget::setTabOrder(mes_2, ano_2);
        QWidget::setTabOrder(ano_2, hora_2);
        QWidget::setTabOrder(hora_2, min_2);
        QWidget::setTabOrder(min_2, seg_2);
        QWidget::setTabOrder(seg_2, pushButton);

        menuBar->addAction(menuArquivo->menuAction());
        menuArquivo->addSeparator();
        menuArquivo->addAction(actionSair);

        retranslateUi(interfaceArmz);

        QMetaObject::connectSlotsByName(interfaceArmz);
    } // setupUi

    void retranslateUi(QMainWindow *interfaceArmz)
    {
        interfaceArmz->setWindowTitle(QApplication::translate("interfaceArmz", "interfaceArmz", 0));
        actionCarregarMapa->setText(QApplication::translate("interfaceArmz", "Carregar Mapa", 0));
        actionSair->setText(QApplication::translate("interfaceArmz", "Sair", 0));
        label->setText(QApplication::translate("interfaceArmz", "Intervalo de tempo:", 0));
        label_2->setText(QApplication::translate("interfaceArmz", "DD", 0));
        label_3->setText(QApplication::translate("interfaceArmz", "MM", 0));
        label_4->setText(QApplication::translate("interfaceArmz", "AAAA", 0));
        label_8->setText(QApplication::translate("interfaceArmz", "De:", 0));
        label_9->setText(QApplication::translate("interfaceArmz", "At\303\251:", 0));
        pushButton->setText(QApplication::translate("interfaceArmz", "Atualizar", 0));
        label_13->setText(QApplication::translate("interfaceArmz", "mm", 0));
        label_14->setText(QApplication::translate("interfaceArmz", "ss", 0));
        label_15->setText(QApplication::translate("interfaceArmz", "hh", 0));
        pushButton_2->setText(QApplication::translate("interfaceArmz", "Sair", 0));
        menuArquivo->setTitle(QApplication::translate("interfaceArmz", "Arquivo", 0));
    } // retranslateUi

};

namespace Ui {
    class interfaceArmz: public Ui_interfaceArmz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEARMZ_H
