#include "area.h"

area::area()
{
    width=0;
    height=0;
    data=NULL;
    areadata=NULL;
    num=0;
    sum=0;
}

area::area(const area &a)
{
    width=a.width;
    height=a.height;
    num=a.num;
    sum=a.sum;
    data=a.data;
    areadata=new bool[width*height];
    for(int i=0;i<width*height;i++)
        areadata[i]=a.areadata[i];
}

area::area(int _width, int _height, int *_data)
{
    width=_width;
    height=_height;
    data=_data;
    areadata=new bool[width*height];
    for(int i=0;i<width*height;i++)
        areadata[i]=0;
    num=0;
    sum=0;
}

area::~area()
{
    if(areadata)
        delete[] areadata;
}

bool area::addpoint(int x, int y)
{
    if(x<0||x>=width||y<0||y>=height||areadata[x*height+y])
        return 0;
    else{
        areadata[x*height+y]=1;
        num++;
        sum+=data[x*height+y];
        return 1;
    }
}

bool area::getpoint(int x, int y)
{
    if(x<0||x>=width||y<0||y>=height)
        return 0;
    else
        return areadata[x*height+y];
}

void area::addarea(area a)
{
    int i,j;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            if(a.getpoint(i,j))
                addpoint(i,j);
        }
}

double area::getaverage()
{
    if(num==0)
        return 0;
    else
        return double(sum)/double(num);
}

bool area::ifconnect(int x, int y)
{
    if(getpoint(x+1,y)||getpoint(x-1,y)||getpoint(x,y+1)||getpoint(x,y-1))
        return 1;
    else
        return 0;
}

void area::clear()
{
    for(int i=0;i<width*height;i++)
        areadata[i]=0;
    num=0;
    sum=0;
}

int area::getwidth()
{
    return width;
}

int area::getheight()
{
    return height;
}

int* area::getdata()
{
    return data;
}

bool* area::getareadata()
{
    return areadata;
}

int area::getnum()
{
    return num;
}

int area::getsum()
{
    return sum;
}

area& area::operator =(const area & a)
{
    width=a.width;
    height=a.height;
    num=a.num;
    sum=a.sum;
    data=a.data;
    if(areadata)
        delete[] areadata;
    areadata=new bool[width*height];
    for(int i=0;i<width*height;i++)
        areadata[i]=a.areadata[i];
}
