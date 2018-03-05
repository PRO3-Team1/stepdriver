/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   io.h
 * Author: anders
 *
 * Created on March 5, 2018, 1:19 PM
 */

#ifndef IO_H
#define IO_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sstream>
#include <math.h>
#include "angleCalc.h"
#include "./vendor/EBBLibrary/gpio/PWM.h"
#include "./vendor/EBBLibrary/gpio/GPIO.h"
#include "vendor/EBBLibrary/gpio/util.h"

using namespace std;
using namespace exploringBB;

#define GPIOPIN_DRIVER1_ENABLE      27  //P8 - Pin 17
#define GPIOPIN_DRIVER1_MS1         66  //P8 - Pin 7
#define GPIOPIN_DRIVER1_MS2         69  //P8 - Pin 9
#define GPIOPIN_DRIVER1_MS3         65  //P8 - Pin 18
#define GPIOPIN_DRIVER1_RESET       26  //P8 - Pin 14
#define GPIOPIN_DRIVER1_SLEEP       46  //P8 - Pin 16
#define GPIOPIN_DRIVER1_STEP        "pwmchip6/pwm1" //P8 - Pin 13
#define GPIOPIN_DRIVER1_DIRECTION   68  //P8 - Pin 10

#define GPIOPIN_DRIVER2_ENABLE      48  //P9 - Pin 15
#define GPIOPIN_DRIVER2_MS1         49  //P9 - Pin 23
#define GPIOPIN_DRIVER2_MS2         117 //P9 - Pin 25
#define GPIOPIN_DRIVER2_MS3         115 //P9 - Pin 27
#define GPIOPIN_DRIVER2_RESET       112 //P9 - Pin 30
#define GPIOPIN_DRIVER2_SLEEP       20  //P9 - Pin 41
#define GPIOPIN_DRIVER2_STEP        "pwmchip3/pwm0"  //P9 - Pin 14
#define GPIOPIN_DRIVER2_DIRECTION   60  //P9 - Pin 12

#define MAXSPEED 600 //Motor max step frequency

void converter(string iAngle, string iForce);
void init(void);
void stop(void);

GPIO driver1_enable(GPIOPIN_DRIVER1_ENABLE);
GPIO driver1_ms1(GPIOPIN_DRIVER1_MS1);
GPIO driver1_ms2(GPIOPIN_DRIVER1_MS2);
GPIO driver1_ms3(GPIOPIN_DRIVER1_MS3);
GPIO driver1_reset(GPIOPIN_DRIVER1_RESET);
GPIO driver1_sleep(GPIOPIN_DRIVER1_SLEEP);
GPIO driver1_dir(GPIOPIN_DRIVER1_DIRECTION);

GPIO driver2_enable(GPIOPIN_DRIVER2_ENABLE);
GPIO driver2_ms1(GPIOPIN_DRIVER2_MS1);
GPIO driver2_ms2(GPIOPIN_DRIVER2_MS2);
GPIO driver2_ms3(GPIOPIN_DRIVER2_MS3);
GPIO driver2_reset(GPIOPIN_DRIVER2_RESET);
GPIO driver2_sleep(GPIOPIN_DRIVER2_SLEEP);
GPIO driver2_dir(GPIOPIN_DRIVER2_DIRECTION);

PWM driver1_step(GPIOPIN_DRIVER1_STEP);
PWM driver2_step(GPIOPIN_DRIVER2_STEP);

#endif /* IO_H */

