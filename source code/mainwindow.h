#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
#include <QTimer>
#include "config.h"
#include "imageanalyse.h"
#include "spotscountdialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void putimage(QImage image);
    void putstatus(QString _s, bool _clear);
    bool eventFilter(QObject *object, QEvent *event);
    imageanalyse imanalyse;

private slots:
    void update();
    void on_loadImage_clicked();
    void on_selectRage_clicked();
    void on_dataAnalyze_clicked();
    void on_separateSpots_clicked();
    void on_getTwiss_clicked();
    void on_saveParticles_clicked();
    void on_getPhaseX_clicked();
    void on_getPhaseY_clicked();
    void on_curveFit_clicked();
    void on_signalMark_clicked();
    void on_combineData_clicked();
    void on_denoise_clicked();
    void on_ratateImage_clicked();
    void on_saveImage_clicked();
    void loadconfig(QString filename);
    void saveconfig(QString filename);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QGraphicsScene *scene;
    QImage image,selectimage,showimage;

    QPointF selectBegin, selectEnd;
    QList<QString> step;
    int mouseFlag;
    bool refresh;
    QPointF center;
    double spot_space_x, spot_space_y;
};

#endif // MAINWINDOW_H
