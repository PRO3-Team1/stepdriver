/*
 * AngleCalc.c
 *
 *  Created on: 26. feb. 2018
 *      Author: Mich
 *      returns 0 on OK
 *      returns 1 on wrong input
 */
#include <math.h>
#include <stdio.h>

double min(double a, double b) {
    if(a < b)
        return a;
    else
        return b;
}


double max(double a, double b) {
    if(a > b)
        return a;
    else
        return b;
}

#define SPEED_FACTOR 1.0
#define TURN_FACTOR  0.15

extern double lRatio;
extern double rRatio;

int angleCalc(double Ang)
{
    double forward = sin(Ang) * SPEED_FACTOR;
    double leftright = cos(Ang) * TURN_FACTOR;
    
    lRatio = max(-1.0,min(1.0, forward + leftright));
    rRatio = max(-1.0,min(1.0, forward - leftright));
    
    return 0;
}

