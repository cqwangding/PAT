#ifndef SPOT_H
#define SPOT_H

#include <QImage>
#include <QPoint>
#include <qmath.h>
#include <QDebug>
#include "area.h"
#include "randwithweight.h"
#include "curvefit.h"

struct particle
{
    double x;
    double xp;
    double y;
    double yp;
};

class spot
{
public:
    spot();
    ~spot();
    static double pixel;
    static double distance;
    static double hole_diameter;
    static double hole_space;
    static double spot_space;
    static double spot_intensitymin;
    static int spot_areamin;
    static QPointF center;
    void setdata(int _width, int _height, int *_data);
    void setorigin(QPoint _origin);
    void setseq(QPoint _seq);
    void getstat();
    int getvalue(QPoint p);
    int getvalue(int x, int y);
    void swap(int p1, int p2, QPoint *pdata);
    void sort(int begin, int end, QPoint *pdata);
    void swap(int p1, int p2, int *pdata);
    void sort(int begin, int end, int *pdata);
    void denoise();
    void signalmark();
    void curvefitting();
    void datacombine();
    void putdata(int _width, int _height, int *_data);
    void putdenoisedata(int _width, int _height, int *_data);
    void putfitdata(int _width, int _height, int *_fitdata);
    void putcombinedata(int _width, int _height, int *_combinedata);
    void putsignal(int _width, int _height, bool *_signal);
    void preprocess();
    particle generateparticle();
    int getweight();
    void settype(int t);
private:
    int type;
    double background;
    double average;
    int intensitymax;
    randwithweight weight;
    int intensity;
    QPoint seq;
    QPoint origin;
    int num,width,height;
    bool *signal;
    int *data,*denoisedata,*fitdata,*combinedata;
};

#endif // SPOT_H

