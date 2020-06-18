/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun May 12 03:12:36 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *loadImage;
    QPushButton *selectRage;
    QPushButton *separateSpots;
    QPushButton *separateSpots_2;
    QPushButton *ratateImage;
    QGroupBox *groupBox_2;
    QPushButton *signalMark;
    QPushButton *curveFit;
    QPushButton *combineData;
    QPushButton *denoise;
    QGroupBox *groupBox_3;
    QPushButton *dataAnalyze;
    QPushButton *getTwiss;
    QPushButton *getPhaseX;
    QPushButton *getPhaseY;
    QGroupBox *groupBox_4;
    QPushButton *saveParticles;
    QPushButton *saveImage;
    QGroupBox *groupBox_5;
    QGraphicsView *graphicsView;
    QGroupBox *groupBox_6;
    QTextEdit *Status;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(925, 495);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 231, 121));
        loadImage = new QPushButton(groupBox);
        loadImage->setObjectName(QString::fromUtf8("loadImage"));
        loadImage->setGeometry(QRect(10, 20, 101, 23));
        selectRage = new QPushButton(groupBox);
        selectRage->setObjectName(QString::fromUtf8("selectRage"));
        selectRage->setGeometry(QRect(120, 20, 101, 23));
        separateSpots = new QPushButton(groupBox);
        separateSpots->setObjectName(QString::fromUtf8("separateSpots"));
        separateSpots->setGeometry(QRect(120, 50, 101, 23));
        separateSpots_2 = new QPushButton(groupBox);
        separateSpots_2->setObjectName(QString::fromUtf8("separateSpots_2"));
        separateSpots_2->setGeometry(QRect(10, 80, 101, 23));
        ratateImage = new QPushButton(groupBox);
        ratateImage->setObjectName(QString::fromUtf8("ratateImage"));
        ratateImage->setGeometry(QRect(10, 50, 101, 23));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 140, 231, 91));
        signalMark = new QPushButton(groupBox_2);
        signalMark->setObjectName(QString::fromUtf8("signalMark"));
        signalMark->setGeometry(QRect(10, 20, 101, 23));
        curveFit = new QPushButton(groupBox_2);
        curveFit->setObjectName(QString::fromUtf8("curveFit"));
        curveFit->setGeometry(QRect(10, 50, 101, 23));
        combineData = new QPushButton(groupBox_2);
        combineData->setObjectName(QString::fromUtf8("combineData"));
        combineData->setGeometry(QRect(120, 50, 101, 23));
        denoise = new QPushButton(groupBox_2);
        denoise->setObjectName(QString::fromUtf8("denoise"));
        denoise->setGeometry(QRect(120, 20, 101, 23));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 240, 231, 91));
        dataAnalyze = new QPushButton(groupBox_3);
        dataAnalyze->setObjectName(QString::fromUtf8("dataAnalyze"));
        dataAnalyze->setGeometry(QRect(10, 20, 101, 23));
        getTwiss = new QPushButton(groupBox_3);
        getTwiss->setObjectName(QString::fromUtf8("getTwiss"));
        getTwiss->setGeometry(QRect(120, 20, 101, 23));
        getPhaseX = new QPushButton(groupBox_3);
        getPhaseX->setObjectName(QString::fromUtf8("getPhaseX"));
        getPhaseX->setGeometry(QRect(10, 50, 101, 23));
        getPhaseY = new QPushButton(groupBox_3);
        getPhaseY->setObjectName(QString::fromUtf8("getPhaseY"));
        getPhaseY->setGeometry(QRect(120, 50, 101, 23));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 340, 231, 91));
        saveParticles = new QPushButton(groupBox_4);
        saveParticles->setObjectName(QString::fromUtf8("saveParticles"));
        saveParticles->setGeometry(QRect(10, 20, 101, 23));
        saveImage = new QPushButton(groupBox_4);
        saveImage->setObjectName(QString::fromUtf8("saveImage"));
        saveImage->setGeometry(QRect(120, 20, 101, 23));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(250, 10, 421, 431));
        graphicsView = new QGraphicsView(groupBox_5);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 20, 400, 400));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(680, 10, 221, 431));
        Status = new QTextEdit(groupBox_6);
        Status->setObjectName(QString::fromUtf8("Status"));
        Status->setGeometry(QRect(20, 20, 200, 401));
        Status->setReadOnly(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 925, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Pepper-Pot Analysis Tool", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Image Load", 0, QApplication::UnicodeUTF8));
        loadImage->setText(QApplication::translate("MainWindow", "Load Image", 0, QApplication::UnicodeUTF8));
        selectRage->setText(QApplication::translate("MainWindow", "Select Range", 0, QApplication::UnicodeUTF8));
        separateSpots->setText(QApplication::translate("MainWindow", "Separate Spots", 0, QApplication::UnicodeUTF8));
        separateSpots_2->setText(QApplication::translate("MainWindow", "Auto Separate", 0, QApplication::UnicodeUTF8));
        ratateImage->setText(QApplication::translate("MainWindow", "Rotate Image", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Denoise", 0, QApplication::UnicodeUTF8));
        signalMark->setText(QApplication::translate("MainWindow", "Signal mark", 0, QApplication::UnicodeUTF8));
        curveFit->setText(QApplication::translate("MainWindow", "Curve fit", 0, QApplication::UnicodeUTF8));
        combineData->setText(QApplication::translate("MainWindow", "Combine data", 0, QApplication::UnicodeUTF8));
        denoise->setText(QApplication::translate("MainWindow", "Denoise", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Data analyse", 0, QApplication::UnicodeUTF8));
        dataAnalyze->setText(QApplication::translate("MainWindow", "Data Analyze", 0, QApplication::UnicodeUTF8));
        getTwiss->setText(QApplication::translate("MainWindow", "Get Twiss Para", 0, QApplication::UnicodeUTF8));
        getPhaseX->setText(QApplication::translate("MainWindow", "Get X-X'", 0, QApplication::UnicodeUTF8));
        getPhaseY->setText(QApplication::translate("MainWindow", "Get Y-Y'", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Save data", 0, QApplication::UnicodeUTF8));
        saveParticles->setText(QApplication::translate("MainWindow", "Save Particles", 0, QApplication::UnicodeUTF8));
        saveImage->setText(QApplication::translate("MainWindow", "Save Image", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Image", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "GroupBox", 0, QApplication::UnicodeUTF8));
        Status->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">PAT 2.0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">code maintained by Ding Wang</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">wangd@nscl.msu.edu</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
