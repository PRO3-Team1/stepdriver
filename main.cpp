/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: JCT
 *
 * Created on 05 December 2017, 10:24
 */

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "gpio/PWM.h"

using namespace std;
using namespace exploringBB;

#define GPIOPIN_DRIVER1_ENABLE      27  //P8 - Pin 17
#define GPIOPIN_DRIVER1_MS1         66  //P8 - Pin 7
#define GPIOPIN_DRIVER1_MS2         69  //P8 - Pin 9
#define GPIOPIN_DRIVER1_MS3         65  //P8 - Pin 18
#define GPIOPIN_DRIVER1_RESET       26  //P8 - Pin 14
#define GPIOPIN_DRIVER1_SLEEP       46  //P8 - Pin 16
#define GPIOPIN_DRIVER1_STEP        ""
//#define GPIOPIN_DRIVER1_STEP        23  //P8 - Pin 13
#define GPIOPIN_DRIVER1_DIRECTION   68  //P8 - Pin 10

#define GPIOPIN_DRIVER2_ENABLE      48  //P9 - Pin 15
#define GPIOPIN_DRIVER2_MS1         49  //P9 - Pin 23
#define GPIOPIN_DRIVER2_MS2         117 //P9 - Pin 25   Not exported?
#define GPIOPIN_DRIVER2_MS3         115 //P9 - Pin 27
#define GPIOPIN_DRIVER2_RESET       112 //P9 - Pin 30
#define GPIOPIN_DRIVER2_SLEEP       20  //P9 - Pin 41   Not exported?
#define GPIOPIN_DRIVER2_STEP        "bs_pwm_test_P9_14.15"  //P9 - Pin 14
#define GPIOPIN_DRIVER2_DIRECTION   60  //P9 - Pin 12
/*
 * 
 */
int main(int argc, char** argv) {
    PWM driver2_step(GPIOPIN_DRIVER2_STEP);
    if(strcmp(argv[1],"start") == 0 && argc == 3)
    {
        cout << "Starting PWM with frequency of " << argv[2] << endl;
        driver2_step.setFrequency(atof(argv[2]));
        driver2_step.setDutyCycle((unsigned int)100000); //From A4988 datasheet - minimum high time
        driver2_step.run();
    }
    
    if(argc == 2 && strcmp(argv[1],"stop") == 0)
    {
        driver2_step.stop();
        cout << "Stopping PWM" << endl;
    }
    
   return 0;
}

