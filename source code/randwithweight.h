#ifndef RANDWITHWEIGHT_H
#define RANDWITHWEIGHT_H

#include <cstdlib>
#include <stdlib.h>
#include <QTime>

class randwithweight
{
public:
    randwithweight();
    ~randwithweight();
    void init(int *_weight, int _number);
    int getweightall();
    int getrand();
private:
    int number, weight_all, rand_num, weight_extra;
    int *weight, *accumulate;
};

#endif // RANDWITHWEIGHT_H
