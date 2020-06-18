#include "spot.h"

double spot::pixel=0.048807;
double spot::hole_diameter=0.1;
double spot::hole_space=1;
double spot::distance=40;
double spot::spot_space=0;
double spot::spot_intensitymin=10;
int spot::spot_areamin=5;
QPointF spot::center;

spot::spot()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    data=NULL;
    denoisedata=NULL;
    fitdata=NULL;
    combinedata=NULL;
    signal=NULL;
    intensity=0;
    intensitymax=0;
    average=0;
    type=0;
}

spot::~spot()
{
    if(data)
        delete[] data;
    if(denoisedata)
        delete[] denoisedata;
    if(fitdata)
        delete[] fitdata;
    if(combinedata)
        delete[] combinedata;
    if(signal)
        delete[] signal;
}

void spot::setdata(int _width, int _height, int *_data)
{
    width=_width;
    height=_height;
    num=width*height;
    data=new int[num];
    denoisedata=new int[num];
    fitdata=new int[num];
    combinedata=new int[num];
    signal=new bool[num];
    int i;
    for(i=0;i<num;i++)
    {
        data[i]=_data[i];
        denoisedata[i]=0;
        fitdata[i]=0;
        combinedata[i]=0;
        signal[i]=false;
    }
}

void spot::setorigin(QPoint _origin)
{
    origin=_origin;
}

void spot::setseq(QPoint _seq)
{
    seq=_seq;
}

void spot::getstat()
{
    int i,j,k;
    intensitymax=0;
    background=0;
    average=0;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            intensity+=data[k];
            if(data[k]>intensitymax)
                intensitymax=data[k];
        }
    for(i=0;i<width;i++)
    {
        background+=data[i*height];
        background+=data[i*height+height-1];
    }
    for(i=0;i<height;i++)
    {
        background+=data[i];
        background+=data[(width-1)*height+i];
    }
    background/=double(width*2+height*2);
    average=double(intensity)/width/height;
}

int spot::getvalue(QPoint p)
{
    return getvalue(p.x(),p.y());
}

int spot::getvalue(int x, int y)
{
    if(x<0||x>=width||y<0||y>=height)
        return 0;
    else
        return data[x*height+y];
}

void spot::swap(int p1, int p2, QPoint *pdata)
{
    QPoint temp=pdata[p1];
    pdata[p1]=pdata[p2];
    pdata[p2]=temp;
}

void spot::sort(int _begin, int _end, QPoint *pdata)
{
    if(_begin>=_end)
        return;
    int i,begin,end,middle;
    begin=_begin;
    end=_end;
    middle=(begin+end)/2;
    while(begin!=end)
    {
        for(i=begin;i<middle;i++)
            if(getvalue(pdata[i])<getvalue(pdata[middle]))
            {
                swap(i,middle,pdata);
                middle=i;
                break;
            }
        begin=i;
        for(i=end;i>middle;i--)
            if(getvalue(pdata[i])>getvalue(pdata[middle]))
            {
                swap(i,middle,pdata);
                middle=i;
                break;
            }
        end=i;
    }
    sort(_begin,middle-1,pdata);
    sort(middle+1,_end,pdata);
}

void spot::swap(int p1, int p2, int *pdata)
{
    int temp=pdata[p1];
    pdata[p1]=pdata[p2];
    pdata[p2]=temp;
}

void spot::sort(int _begin, int _end, int *pdata)
{
    if(_begin>=_end)
        return;
    int i,begin,end,middle;
    begin=_begin;
    end=_end;
    middle=(begin+end)/2;
    while(begin!=end)
    {
        for(i=begin;i<middle;i++)
            if(pdata[i]<pdata[middle])
            {
                swap(i,middle,pdata);
                middle=i;
                break;
            }
        begin=i;
        for(i=end;i>middle;i--)
            if(pdata[i]>pdata[middle])
            {
                swap(i,middle,pdata);
                middle=i;
                break;
            }
        end=i;
    }
    sort(_begin,middle-1,pdata);
    sort(middle+1,_end,pdata);
}

void spot::curvefitting()
{
    int i,j,k;
    double *newdata;
    newdata=new double[num];
    for(i=0;i<num;i++)
    {
        if(signal[i])
            newdata[i]=double(data[i])/256;
        else
            newdata[i]=0;
    }
    curvefit fit;
    fit.init(newdata,width,height);
    fit.curvefitting();
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            fitdata[k]=fit.getdata(i,j)*256;
        }
    delete[] newdata;
}

void spot::datacombine()
{
    int i,j,k;
    for(i=0;i<num;i++)
    {
        if(signal[i])
        {
            if(data[i]>=255)
                combinedata[i]=fitdata[i];
            else
                combinedata[i]=data[i];
        }
        else
            combinedata[i]=fitdata[i];
    }
}

void spot::signalmark()
{
    int i,j;
    int *backupdata=data;

    int *newdata=new int[num];
    int block[9];
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            block[0]=getvalue(i-1,j-1);
            block[1]=getvalue(i-1,j);
            block[2]=getvalue(i-1,j+1);
            block[3]=getvalue(i,j-1);
            block[4]=getvalue(i,j);
            block[5]=getvalue(i,j+1);
            block[6]=getvalue(i+1,j-1);
            block[7]=getvalue(i+1,j);
            block[8]=getvalue(i+1,j+1);
            sort(0,8,block);
            newdata[i*height+j]=block[4];
        }
    data=newdata;
    newdata=new int[num];
    double dblock;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            dblock=0;
            dblock+=getvalue(i-1,j-1);
            dblock+=getvalue(i-1,j);
            dblock+=getvalue(i-1,j+1);
            dblock+=getvalue(i,j-1);
            dblock+=getvalue(i,j);
            dblock+=getvalue(i,j+1);
            dblock+=getvalue(i+1,j-1);
            dblock+=getvalue(i+1,j);
            dblock+=getvalue(i+1,j+1);
            newdata[i*height+j]=dblock/9;
        }
    delete[] data;
    data=newdata;

    getstat();

    //double intensitymin=average;
    double intensitymin=background+spot::spot_intensitymin;
    for(i=0;i<num;i++)
    {
        if(data[i]>=intensitymin)
            signal[i]=true;
        else
            signal[i]=false;
    }
    delete[] data;
    data=backupdata;
}

void spot::denoise()
{
    int i,j,k;
    for(i=0;i<num;i++)
    {
        if(signal[i])
            denoisedata[i]=data[i];
        else
            denoisedata[i]=0;
    }
}

void spot::putdata(int _width, int _height, int *_data)
{
    int i,j;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            _data[(origin.x()+i)*_height+(origin.y()+j)]=data[i*height+j];
        }
}

void spot::putdenoisedata(int _width, int _height, int *_denoisedata)
{
    int i,j;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            _denoisedata[(origin.x()+i)*_height+(origin.y()+j)]=denoisedata[i*height+j];
        }
}

void spot::putfitdata(int _width, int _height, int *_fitdata)
{
    int i,j;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            _fitdata[(origin.x()+i)*_height+(origin.y()+j)]=fitdata[i*height+j];
        }
}

void spot::putcombinedata(int _width, int _height, int *_combinedata)
{
    int i,j;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            _combinedata[(origin.x()+i)*_height+(origin.y()+j)]=combinedata[i*height+j];
        }
}

void spot::putsignal(int _width, int _height, bool *_signal)
{
    int i,j;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            _signal[(origin.x()+i)*_height+(origin.y()+j)]=signal[i*height+j];
        }
}

void spot::preprocess()
{
    if(type==0)
        weight.init(data,num);
    else if(type==1)
        weight.init(denoisedata,num);
    else if(type==2)
        weight.init(fitdata,num);
    else if(type==3)
        weight.init(combinedata,num);
}

particle spot::generateparticle()
{
    particle p;
    double x1,y1,x2,y2,xshift,yshift;
    do{
        x1=double(qrand())/double(RAND_MAX)-0.5;
        y1=double(qrand())/double(RAND_MAX)-0.5;
    }
    while(x1*x1+y1*y1>0.25);
    int r;
    r=weight.getrand();
    x2=int(r/height);
    x2+=double(qrand())/double(RAND_MAX)-0.5;
    y2=r%height;
    y2+=double(qrand())/double(RAND_MAX)-0.5;
    p.x=seq.x()*spot::hole_space;
    p.y=seq.y()*spot::hole_space;
    xshift=(x2+double(origin.x())-spot::center.x())*spot::pixel-p.x;
    yshift=(y2+double(origin.y())-spot::center.y())*spot::pixel-p.y;
    p.x+=x1*spot::hole_diameter;
    p.y+=y1*spot::hole_diameter;
    p.xp=xshift/spot::distance*1000;
    p.yp=yshift/spot::distance*1000;
    p.y=-p.y;
    p.yp=-p.yp;
    /*
    p.x=(x1*spot::hole_diameter+seq.x()*spot::hole_space);
    p.y=(y1*spot::hole_diameter+seq.y()*spot::hole_space);
    xshift=(x2+double(origin.x())-spot::center.x())*spot::pixel-p.x;
    yshift=(y2+double(origin.y())-spot::center.y())*spot::pixel-p.y;
    p.xp=xshift/spot::distance*1000;
    p.yp=yshift/spot::distance*1000;
    p.y=-p.y;
    p.yp=-p.yp;
    */
    return p;
}

int spot::getweight()
{
    return weight.getweightall();
}

void spot::settype(int t)
{
    type=t;
}
