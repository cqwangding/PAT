/********************************************************************************
** Form generated from reading UI file 'spotscountdialog.ui'
**
** Created: Sun May 12 01:29:10 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPOTSCOUNTDIALOG_H
#define UI_SPOTSCOUNTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_spotscountDialog
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBox;
    QLabel *label;

    void setupUi(QDialog *spotscountDialog)
    {
        if (spotscountDialog->objectName().isEmpty())
            spotscountDialog->setObjectName(QString::fromUtf8("spotscountDialog"));
        spotscountDialog->resize(273, 100);
        buttonBox = new QDialogButtonBox(spotscountDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 50, 181, 32));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setAutoFillBackground(false);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        spinBox = new QSpinBox(spotscountDialog);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(210, 20, 42, 22));
        spinBox->setMinimum(1);
        spinBox->setValue(1);
        label = new QLabel(spotscountDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 201, 21));

        retranslateUi(spotscountDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), spotscountDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), spotscountDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(spotscountDialog);
    } // setupUi

    void retranslateUi(QDialog *spotscountDialog)
    {
        spotscountDialog->setWindowTitle(QApplication::translate("spotscountDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("spotscountDialog", "How many spot spaces in the line:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class spotscountDialog: public Ui_spotscountDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPOTSCOUNTDIALOG_H
