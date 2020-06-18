#include "randwithweight.h"

randwithweight::randwithweight()
{
    weight=NULL;
    accumulate=NULL;
}

randwithweight::~randwithweight()
{
    if(weight)
        delete[] weight;
    if(accumulate)
        delete[] accumulate;
}

void randwithweight::init(int *_weight, int _number)
{
    if(weight)
        delete[] weight;
    if(accumulate)
        delete[] accumulate;
    number=_number;
    weight=new int[number];
    accumulate=new int[number];
    int i;
    weight_all=0;
    for(i=0;i<number;i++)
    {
        weight[i]=_weight[i];
        weight_all+=weight[i];
        accumulate[i]=weight_all;
    }
    if(weight_all==0)
        return;
    rand_num=1;
    int max=RAND_MAX+1;
    while(weight_all>max)
    {
        max*=(RAND_MAX+1);
        rand_num++;
    }
    weight_extra=max%weight_all;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

int randwithweight::getweightall()
{
    return weight_all;
}

int randwithweight::getrand()
{
    int i,r;
    do
    {
        r=0;
        for(i=0;i<rand_num;i++)
            r=r*(RAND_MAX+1)+qrand();
    }
    while(r<weight_extra);
    r-=weight_extra;
    if(weight_all<=0)
        weight_all=1;
    r=r%weight_all;
    int left,right,middle;
    if(r<accumulate[0])
        return 0;
    left=0;
    right=number-1;
    while(left+1<right)
    {
        middle=(left+right)/2;
        if(accumulate[middle]<=r)
            left=middle;
        else
            right=middle;
    }
    return right;
}
