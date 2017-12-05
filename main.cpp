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
#include "unistd.h"
#include "motor/StepperMotor.h"
#include "gpio/PWM.h"

using namespace std;
using namespace exploringBB;

#define GPIOPIN_DRIVER1_ENABLE      27  //P8 - Pin 17
#define GPIOPIN_DRIVER1_MS1         66  //P8 - Pin 7
#define GPIOPIN_DRIVER1_MS2         69  //P8 - Pin 9
#define GPIOPIN_DRIVER1_MS3         65  //P8 - Pin 18
#define GPIOPIN_DRIVER1_RESET       26  //P8 - Pin 14
#define GPIOPIN_DRIVER1_SLEEP       46  //P8 - Pin 16
#define GPIOPIN_DRIVER1_STEP        23  //P8 - Pin 13
#define GPIOPIN_DRIVER1_DIRECTION   68  //P8 - Pin 10

#define GPIOPIN_DRIVER2_ENABLE      48  //P9 - Pin 15
#define GPIOPIN_DRIVER2_MS1         49  //P9 - Pin 23
#define GPIOPIN_DRIVER2_MS2         117 //P9 - Pin 25   Not exported?
#define GPIOPIN_DRIVER2_MS3         115 //P9 - Pin 27
#define GPIOPIN_DRIVER2_RESET       112 //P9 - Pin 30
#define GPIOPIN_DRIVER2_SLEEP       20  //P9 - Pin 41   Not exported?
#define GPIOPIN_DRIVER2_STEP        50  //P9 - Pin 14
#define GPIOPIN_DRIVER2_DIRECTION   60  //P9 - Pin 12
/*
 * 
 */
int main(int argc, char** argv) {
   system("echo 117 > /sys/class/gpio/export");
   system("echo 20 > /sys/class/gpio/export");
   
   cout << "Starting Team1 Stepper Motor Example:" << endl;
   //Using The EBBlibrary step motor driver package
   StepperMotor m1(GPIOPIN_DRIVER1_MS1, GPIOPIN_DRIVER1_MS2, GPIOPIN_DRIVER1_STEP, GPIOPIN_DRIVER1_SLEEP, GPIOPIN_DRIVER1_DIRECTION, 3*60, 200);
   StepperMotor m2(GPIOPIN_DRIVER2_MS1, GPIOPIN_DRIVER2_MS2, GPIOPIN_DRIVER2_STEP, GPIOPIN_DRIVER2_SLEEP, GPIOPIN_DRIVER2_DIRECTION, 3*60, 200);
   
   m1.setDirection(StepperMotor::ANTICLOCKWISE);
   m1.setStepMode(StepperMotor::STEP_FULL);

   cout << "Rotating 10 times at 180 rpm anti-clockwise, full step..." << endl;
   m1.rotate(3600.0f);   //in degrees
   
   cout << "Rotating 2 times at 10 rpm clockwise, full step..." << endl;
   m1.setDirection(StepperMotor::CLOCKWISE);
   m1.setSpeed(10);
   m1.rotate(720.0f);   //in degrees
   
   return 0;
}

