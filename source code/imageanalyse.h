#ifndef IMAGEANALYSE_H
#define IMAGEANALYSE_H

#include <QImage>
#include <QColor>
#include <QList>
#include <QPainter>
#include "spot.h"
#include <fstream>

using namespace std;

class imageanalyse
{
public:
    static int spot_num,spot_x_min, spot_x_max, spot_y_min, spot_y_max;
    static int particle_num;
    static double emittance_x, alpha_x, beta_x, gama_x, emittance_y, alpha_y, beta_y, gama_y;
    imageanalyse();
    ~imageanalyse();
    void loadimage(QImage image);
    int* getdata(int x, int y, int w, int h);
    QImage getimage();
    QImage getdenoiseimage();
    QImage getsignalimage();
    QImage getfitimage();
    QImage getcombineimage();
    void setgridshow(bool flag);
    int getwidth();
    int getheight();
    void getallspots();
    void signalmark();
    void keepnoise();
    void denoise();
    void curvefitting();
    void datacombine();
    void preprocess();
    void generateparticles(int _particle_num);
    void saveparticles(char* filename);
    void gettwiss();
    QImage getphaseX(double x_min, double x_step, double x_max, double xp_min, double xp_step, double xp_max);
    QImage getphaseY(double y_min, double y_step, double y_max, double yp_min, double yp_step, double yp_max);
private:
    int width, height;
    int *data,*denoisedata,*fitdata,*combinedata;
    bool *signal;
    randwithweight weight;
    spot *allspots;
    particle *allparticles;
};

#endif // IMAGEANALYSE_H
