#ifndef CURVEFIT_H
#define CURVEFIT_H

#include <qmath.h>

class curvefit
{
public:
    curvefit();
    ~curvefit();
    void init(double *_data,int _width, int _height);
    double getfitrate();
    double getdata(int x, int y);
    void prefit();
    void curvefitting();
private:
    bool ifspot;
    double *data;
    int width,height;
    int num;
    double amptitude, x0, y0, sigma_x, sigma_y;
    double amptitude_step, x0_step, y0_step, sigma_x_step, sigma_y_step;
    double fitrate;
};

#endif // CURVEFIT_H
