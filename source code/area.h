#ifndef AREA_H
#define AREA_H

#include <QPoint>

class area
{
public:
    area();
    area(const area &a);
    area(int _width, int _height, int *_data);
    ~area();
    bool addpoint(int x, int y);
    bool getpoint(int x, int y);
    double getaverage();
    void addarea(area a);
    bool ifconnect(int x, int y);
    void clear();
    int getwidth();
    int getheight();
    int* getdata();
    bool* getareadata();
    int getnum();
    int getsum();
    area& operator =(const area & a);
private:
    int num;
    int sum;
    int width, height;
    bool *areadata;
    int *data;
};

#endif // AREA_H
