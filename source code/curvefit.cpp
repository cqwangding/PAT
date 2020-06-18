#include "curvefit.h"

curvefit::curvefit()
{
    data=NULL;
}

curvefit::~curvefit()
{
    if(data)
        delete[] data;
}

void curvefit::init(double *_data,int _width, int _height)
{
    width=_width;
    height=_height;
    num=width*height;
    data=new double[num];
    int i;
    for(i=0;i<num;i++)
        data[i]=_data[i];
}


double curvefit::getfitrate()
{
    double x,y,overlap=0,combination=0;
    double *fitdata=new double[num];
    int i,j,k;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            x=i;
            y=j;
            k=i*height+j;
            fitdata[k]=amptitude*exp(-(x-x0)*(x-x0)/sigma_x/sigma_x/2-(y-y0)*(y-y0)/sigma_y/sigma_y/2);
            if(fitdata[k]>1)
                fitdata[k]=1;
        }
    for(i=0;i<num;i++)
    {
        if(data[i]>0)
        {
            if(fitdata[i]<data[i])
            {
                overlap+=fitdata[i];
                combination+=data[i];
            }
            else{
                overlap+=data[i];
                combination+=fitdata[i];
            }
        }
        else
            combination+=fitdata[i];
    }
    delete[] fitdata;
    if(combination==0)
        return 0;
    else
        return overlap/combination;
}

double curvefit::getdata(int x, int y)
{
    if(!ifspot)
        return 0;
    else
        return amptitude*exp(-(x-x0)*(x-x0)/sigma_x/sigma_x/2-(y-y0)*(y-y0)/sigma_y/sigma_y/2);
}

void curvefit::prefit()
{
    int i,j,k;
    double max,min;
    /*double average=0;
    for(i=0;i<width;i++)
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            average+=data[k];
        }
    average/=double(width*height);

    if(average>=background+0.005)
        ifspot=true;
    else
        ifspot=false;*/
    x0=0;
    y0=0;
    double intensity=0;
    max=0;
    min=1;
    for(i=0;i<width;i++)
    {
        for(j=0;j<height;j++)
        {
            k=i*height+j;
            x0+=double(i)*data[k];
            y0+=double(j)*data[k];
            intensity+=data[k];
            if(data[k]>max)
                max=data[k];
            if(data[k]<min)
                min=data[k];
        }
    }
    if(intensity==0||max-min<0.1)
    {
        ifspot=false;
        return;
    }
    else
        ifspot=true;
    x0=x0/intensity;
    y0=y0/intensity;
    amptitude=max;
    sigma_x=double(width)/10;
    sigma_y=double(height)/10;
}

void curvefit::curvefitting()
{
    prefit();
    if(!ifspot)
        return;
    bool change=true;
    double rate1,rate2,rate;
    double temp;
    while(change)
    {
        change=false;
        //background_step=0.1;
        amptitude_step=0.1;
        x0_step=1;
        y0_step=1;
        sigma_x_step=1;
        sigma_y_step=1;
        /*while(background_step>0.001){
            rate=getfitrate();
            temp=background;
            background=temp-background_step;
            rate1=getfitrate();
            background=temp+background_step;
            rate2=getfitrate();
            if(rate>=rate1&&rate>=rate2){
                background=temp;
                background_step/=2;
            }
            else if(rate1>rate2){
                background=temp-background_step;
                //background_step*=2;
                change=true;
            }
            else{
                background=temp+background_step;
                //background_step*=2;
                change=true;
            }
        }
        while(x0_step>0.01){
            rate=getfitrate();
            temp=x0;
            x0=temp-x0_step;
            rate1=getfitrate();
            x0=temp+x0_step;
            rate2=getfitrate();
            if(rate>=rate1&&rate>=rate2){
                x0=temp;
                x0_step/=2;
            }
            else if(rate1>rate2){
                x0=temp-x0_step;
                //x0_step*=2;
                change=true;
            }
            else{
                x0=temp+x0_step;
                //x0_step*=2;
                change=true;
            }
        }
        while(y0_step>0.01){
            rate=getfitrate();
            temp=y0;
            y0=temp-y0_step;
            rate1=getfitrate();
            y0=temp+y0_step;
            rate2=getfitrate();
            if(rate>=rate1&&rate>=rate2){
                y0=temp;
                y0_step/=2;
            }
            else if(rate1>rate2){
                y0=temp-y0_step;
                //y0_step*=2;
                change=true;
            }
            else{
                y0=temp+y0_step;
                //y0_step*=2;
                change=true;
            }
        }*/
        while(sigma_x_step>0.01)
        {
            rate=getfitrate();
            temp=sigma_x;
            if(sigma_x>sigma_x_step)
                sigma_x=temp-sigma_x_step;
            rate1=getfitrate();
            sigma_x=temp+sigma_x_step;
            rate2=getfitrate();
            if(rate>=rate1&&rate>=rate2)
            {
                sigma_x=temp;
                sigma_x_step/=2;
            }
            else if(rate1>rate2)
            {
                sigma_x=temp-sigma_x_step;
                //sigma_x_step*=2;
                change=true;
            }
            else{
                sigma_x=temp+sigma_x_step;
                //sigma_x_step*=2;
                change=true;
            }
        }
        while(sigma_y_step>0.01)
        {
            rate=getfitrate();
            temp=sigma_y;
            if(sigma_y>sigma_y_step)
                sigma_y=temp-sigma_y_step;
            rate1=getfitrate();
            sigma_y=temp+sigma_y_step;
            rate2=getfitrate();
            if(rate>=rate1&&rate>=rate2)
            {
                sigma_y=temp;
                sigma_y_step/=2;
            }
            else if(rate1>rate2)
            {
                sigma_y=temp-sigma_y_step;
                //sigma_y_step*=2;
                change=true;
            }
            else{
                sigma_y=temp+sigma_y_step;
                //sigma_y_step*=2;
                change=true;
            }
        }
        while(amptitude_step>0.01)
        {
            rate=getfitrate();
            temp=amptitude;
            amptitude=temp-amptitude_step;
            rate1=getfitrate();
            amptitude=temp+amptitude_step;
            rate2=getfitrate();
            if(rate>=rate1&&rate>=rate2)
            {
                amptitude=temp;
                amptitude_step/=2;
                            }
            else if(rate1>rate2)
            {
                amptitude=temp-amptitude_step;
                //amptitude_step*=2;
                change=true;
            }
            else{
                amptitude=temp+amptitude_step;
                //amptitude_step*=2;
                change=true;
            }
        }
    }
    fitrate=getfitrate();
}
