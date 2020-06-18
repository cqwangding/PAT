#include "imageanalyse.h"

int imageanalyse::spot_x_min=0;
int imageanalyse::spot_x_max=0;
int imageanalyse::spot_y_min=0;
int imageanalyse::spot_y_max=0;
int imageanalyse::spot_num=0;
int imageanalyse::particle_num=10000;
double imageanalyse::emittance_x=0;
double imageanalyse::alpha_x=0;
double imageanalyse::beta_x=0;
double imageanalyse::gama_x=0;
double imageanalyse::emittance_y=0;
double imageanalyse::alpha_y=0;
double imageanalyse::beta_y=0;
double imageanalyse::gama_y=0;

imageanalyse::imageanalyse()
{
    data=NULL;
    denoisedata=NULL;
    fitdata=NULL;
    combinedata=NULL;
    signal=NULL;
    allspots=NULL;
}

imageanalyse::~imageanalyse()
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
    if(allspots)
        delete[] allspots;
}

void imageanalyse::loadimage(QImage image)
{
    QRgb rgb;
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
    if(allspots)
        delete[] allspots;
    width=image.width();
    height=image.height();
    data=new int[width*height];
    denoisedata=new int[width*height];
    fitdata=new int[width*height];
    combinedata=new int[width*height];
    signal=new bool[width*height];
    int i,j,k;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            rgb=image.pixel(i,j);
            k=i*height+j;
            data[k]=qRed(rgb);
            signal[k]=false;
            data[k]=0;
            denoisedata[k]=0;
            fitdata[k]=0;
            combinedata[k]=0;
        }
    getallspots();
}

QImage imageanalyse::getimage()
{
    QImage image(width,height,QImage::Format_RGB32);
    int i,j,k,pix;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            pix=data[k];
            if(pix>255)
                pix=255;
            if(pix<0)
                pix=0;
            image.setPixel(i,j,qRgb(pix,pix,pix));
        }
    return image;
}

QImage imageanalyse::getdenoiseimage()
{
    QImage image(width,height,QImage::Format_RGB32);
    int i,j,k,pix;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            pix=denoisedata[k];
            if(pix>255)
                pix=255;
            if(pix<0)
                pix=0;
            image.setPixel(i,j,qRgb(pix,pix,pix));
        }
    return image;
}

QImage imageanalyse::getsignalimage()
{
    QImage image(width,height,QImage::Format_RGB32);
    int i,j,k,pix;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            pix=data[k];
            if(pix>255)
                pix=255;
            if(pix<0)
                pix=0;
            if(signal[k])
                image.setPixel(i,j,qRgb(pix,0,0));
            else
                image.setPixel(i,j,qRgb(pix,pix,pix));
        }
    return image;
}

QImage imageanalyse::getfitimage()
{
    QImage image(width,height,QImage::Format_RGB32);
    int i,j,k,pix;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            pix=fitdata[k];
            if(pix>255)
                pix=255;
            if(pix<0)
                pix=0;
            image.setPixel(i,j,qRgb(pix,pix,pix));
        }
    return image;
}

QImage imageanalyse::getcombineimage()
{
    QImage image(width,height,QImage::Format_RGB32);
    int i,j,k,pix;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            pix=combinedata[k];
            if(pix>255)
                pix=255;
            if(pix<0)
                pix=0;
            image.setPixel(i,j,qRgb(pix,pix,pix));
        }
    return image;
}

int* imageanalyse::getdata(int x, int y, int w, int h)
{
    if(!data)
        return NULL;
    int i,j,*newdata;
    newdata=new int[w*h];
    for(i=0;i<w;i++)
        for(j=0;j<h;j++)
        {
            newdata[i*h+j]=data[(i+x)*height+(j+y)];
        }
    return newdata;
}

int imageanalyse::getwidth()
{
    return width;
}
int imageanalyse::getheight()
{
    return height;
}

void imageanalyse::getallspots()
{
    int i,j,k,w,h;
    int *pdata;
    QPoint spot_origin,spot_seq;
    allspots=new spot[spot_num];
    for(i=0;i<=spot_x_max-spot_x_min;i++)
        for(j=0;j<=spot_y_max-spot_y_min;j++)
        {
            spot_seq.setX(i+spot_x_min);
            spot_seq.setY(j+spot_y_min);
            k=i*(spot_y_max-spot_y_min+1)+j;
            allspots[k].setseq(spot_seq);
            spot_origin.setX(int(spot::center.x()+(double(i+spot_x_min)-0.5)*spot::spot_space));
            spot_origin.setY(int(spot::center.y()+(double(j+spot_y_min)-0.5)*spot::spot_space));
            allspots[k].setorigin(spot_origin);
            w=int(spot::spot_space);
            h=int(spot::spot_space);
            pdata=getdata(spot_origin.x(),spot_origin.y(),w,h);
            allspots[k].setdata(w,h,pdata);
            delete[] pdata;
        }
}

void imageanalyse::signalmark()
{
    int i;
    for(i=0;i<spot_num;i++)
        allspots[i].signalmark();
    for(i=0;i<width*height;i++)
    {
        data[i]=0;
        signal[i]=false;
    }
    for(i=0;i<spot_num;i++)
    {
        allspots[i].putdata(width,height,data);
        allspots[i].putsignal(width,height,signal);
    }
}

void imageanalyse::keepnoise()
{
    int i;
    for(i=0;i<width*height;i++)
        data[i]=0;
    for(i=0;i<spot_num;i++)
    {
        allspots[i].settype(0);
        allspots[i].putdata(width,height,data);
    }
}

void imageanalyse::denoise()
{
    int i;
    for(i=0;i<spot_num;i++)
        allspots[i].denoise();
    for(i=0;i<width*height;i++)
        denoisedata[i]=0;
    for(i=0;i<spot_num;i++)
    {
        allspots[i].settype(1);
        allspots[i].putdata(width,height,denoisedata);
    }
}

void imageanalyse::curvefitting()
{
    int i;
    for(i=0;i<spot_num;i++)
        allspots[i].curvefitting();
    for(i=0;i<width*height;i++)
        fitdata[i]=0;
    for(i=0;i<spot_num;i++)
    {
        allspots[i].settype(2);
        allspots[i].putdata(width,height,fitdata);
    }
}

void imageanalyse::datacombine()
{
    int i;
    for(i=0;i<spot_num;i++)
        allspots[i].datacombine();
    for(i=0;i<width*height;i++)
        combinedata[i]=0;
    for(i=0;i<spot_num;i++)
    {
        allspots[i].settype(3);
        allspots[i].putdata(width,height,combinedata);
    }
}

void imageanalyse::preprocess()
{
    int i,*wt;
    wt=new int[spot_num];
    for(i=0;i<spot_num;i++)
    {
        allspots[i].preprocess();
        wt[i]=allspots[i].getweight();
    }
    weight.init(wt,spot_num);
    delete[] wt;
}

void imageanalyse::generateparticles(int _particle_num)
{
    particle_num=_particle_num;
    allparticles=new particle[particle_num];
    int i,r;
    for(i=0;i<particle_num;i++)
    {
        r=weight.getrand();
        allparticles[i]=allspots[r].generateparticle();
    }
    double x=0,y=0,xp=0,yp=0;
    for(i=0;i<particle_num;i++)
    {
        x+=allparticles[i].x;
        y+=allparticles[i].y;
        xp+=allparticles[i].xp;
        yp+=allparticles[i].yp;
    }
    x/=particle_num;
    xp/=particle_num;
    y/=particle_num;
    yp/=particle_num;
    for(i=0;i<particle_num;i++)
    {
        allparticles[i].x-=x;
        allparticles[i].y-=y;
        allparticles[i].xp-=xp;
        allparticles[i].yp-=yp;
    }
}

void imageanalyse::saveparticles(char* filename)
{
    ofstream out;
    out.open(filename);
    int i;
    out<<particle_num<<endl;
    out<<" 0 0 0 0 0 2.4"<<endl;
    for(i=0;i<particle_num;i++)
    {
        out<<allparticles[i].x/10<<"\t"<<allparticles[i].xp/1000<<"\t"<<allparticles[i].y/10<<"\t"<<allparticles[i].yp/1000<<"  0  "<<"\t"<<"  2.4  "<<"\t";
        out<<endl;
    }
}

void imageanalyse::gettwiss()
{
    int i;
    double xx=0,xxp=0,xpxp=0,yy=0,yyp=0,ypyp=0;
    for(i=0;i<particle_num;i++)
    {
        xx+=allparticles[i].x*allparticles[i].x;
        xxp+=allparticles[i].x*allparticles[i].xp;
        xpxp+=allparticles[i].xp*allparticles[i].xp;
        yy+=allparticles[i].y*allparticles[i].y;
        yyp+=allparticles[i].y*allparticles[i].yp;
        ypyp+=allparticles[i].yp*allparticles[i].yp;
    }
    xx/=particle_num;
    xxp/=particle_num;
    xpxp/=particle_num;
    yy/=particle_num;
    yyp/=particle_num;
    ypyp/=particle_num;
    emittance_x=sqrt(xx*xpxp-xxp*xxp);
    beta_x=xx/emittance_x;
    alpha_x=-xxp/emittance_x;
    gama_x=xpxp/emittance_x;
    emittance_y=sqrt(yy*ypyp-yyp*yyp);
    beta_y=yy/emittance_y;
    alpha_y=-yyp/emittance_y;
    gama_y=ypyp/emittance_y;
}

QImage imageanalyse::getphaseX(double x_min, double x_step, double x_max, double xp_min, double xp_step, double xp_max)
{
    int i,j,k,w,h,pix;
    double *phasedata;
    w=(x_max-x_min)/x_step;
    h=(xp_max-xp_min)/xp_step;
    phasedata=new double[w*h];
    for(i=0;i<w*h;i++)
        phasedata[i]=0;
    for(i=0;i<particle_num;i++)
    {
        j=(allparticles[i].x-x_min)/x_step;
        k=(allparticles[i].xp-xp_min)/xp_step;
        if(j>=0&&j<w&&k>=0&&k<h)
            phasedata[j*h+k]+=1;
    }
    double max=0;
    for(i=0;i<w*h;i++)
    {
        if(phasedata[i]>max)
            max=phasedata[i];
    }
    for(i=0;i<w*h;i++)
    {
        phasedata[i]/=max;
    }
    QImage image(w,h,QImage::Format_RGB32);
    QRgb value, color[1024];
    for(i=0;i<256;i++)
    {
        color[i]=qRgb(0,i,255);
        color[i+256]=qRgb(0,255,255-i);
        color[i+512]=qRgb(i,255,0);
        color[i+768]=qRgb(255,255-i,0);
    }
    for(i=0;i<w;i++)
        for(j=0;j<h;j++)
        {
            k=i*h+h-1-j;
            pix=phasedata[k]*1023;
            if(pix<0)
                value=color[0];
            else if(pix>1023)
                value=color[1023];
            else
                value=color[pix];
            image.setPixel(i,j,value);
        }
    return image;
}

QImage imageanalyse::getphaseY(double y_min, double y_step, double y_max, double yp_min, double yp_step, double yp_max)
{
    int i,j,k,w,h,pix;
    double *phasedata;
    w=(y_max-y_min)/y_step;
    h=(yp_max-yp_min)/yp_step;
    phasedata=new double[w*h];
    for(i=0;i<w*h;i++)
        phasedata[i]=0;
    for(i=0;i<particle_num;i++)
    {
        j=(allparticles[i].y-y_min)/y_step;
        k=(allparticles[i].yp-yp_min)/yp_step;
        if(j>=0&&j<w&&k>=0&&k<h)
            phasedata[j*h+k]+=1;
    }
    double max=0;
    for(i=0;i<w*h;i++)
    {
        if(phasedata[i]>max)
            max=phasedata[i];
    }
    for(i=0;i<w*h;i++)
    {
        phasedata[i]/=max;
    }
    QImage image(w,h,QImage::Format_RGB32);
    QRgb value, color[1024];
    for(i=0;i<256;i++)
    {
        color[i]=qRgb(0,i,255);
        color[i+256]=qRgb(0,255,255-i);
        color[i+512]=qRgb(i,255,0);
        color[i+768]=qRgb(255,255-i,0);
    }
    for(i=0;i<w;i++)
        for(j=0;j<h;j++)
        {
            k=i*h+h-1-j;
            pix=phasedata[k]*1023;
            if(pix<0)
                value=color[0];
            else if(pix>1023)
                value=color[1023];
            else
                value=color[pix];
            image.setPixel(i,j,value);
        }
    return image;
    /*for(i=0;i<w;i++)
        for(j=0;j<h;j++)
        {
            k=i*h+h-1-j;
            image.setPixel(i,j,qRgb(phasedata[k]*255,0,0));
        }
    return image;
    */
}

