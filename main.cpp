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

#define MAXSPEED 450 //Motor max step frequency

void converter(string iAngle, string iForce);
void init(void);
void stop(void);

double lRatio = 0;
double rRatio = 0;

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

int main(int argc, char** argv)
{

	if (argc < 2)
	{
		puts("Stepdriver tool for BBB");
		puts("Commands:");
		puts(" - init");
		puts("\t Initialize all pins correctly. Must be run first");
		puts(" - set [left] [right]");
		puts(
				"\t Set the speed of left and right with two floats values. Negative values for reverse");
		puts(" - stop");
		puts("\t Stops both motors");
		puts(" - listen");
		puts("\t Puts into listen mode that accepts commands on STDIN");
		return (EXIT_SUCCESS);
	}

	if (argc == 2 && strcmp(argv[1], "init") == 0)
	{
		init();
		exit (EXIT_SUCCESS);
	}

	if (argc == 2 && strcmp(argv[1], "stop") == 0)
	{
		stop();
		exit (EXIT_SUCCESS);
	}

	if (argc == 4 && strcmp(argv[1], "set") == 0)
	{
		cout << "Setting PWM with frequency of " << argv[2] << " and "
				<< argv[3] << endl;
		float speed = atof(argv[2]);
		if (speed < 0)
		{
			speed = -speed;
			driver1_dir.setValue(GPIO::LOW);
		}
		else
		{
			driver1_dir.setValue(GPIO::HIGH);
		}
		driver1_step.setFrequency(speed);
		driver1_step.setDutyCycle((unsigned int) 100000); //From A4988 datasheet - minimum high time
		driver1_step.run();

		speed = atof(argv[3]);
		if (speed < 0)
		{
			speed = -speed;
			driver2_dir.setValue(GPIO::LOW);
		}
		else
		{
			driver2_dir.setValue(GPIO::HIGH);
		}
		driver2_step.setFrequency(speed);
		driver2_step.setDutyCycle((unsigned int) 100000); //From A4988 datasheet - minimum high time
		driver2_step.run();
	}

	if (argc == 2 && strcmp(argv[1], "listen") == 0)
	{
		init();
		cout << "Listen for commands on stdin..." << endl;
		string input;
		while (1)
		{
			cin >> input;
			if (input.at(0) != '#') // This is the debug character
			{
				istringstream inputs(input);
				string token;
				int index = 0;
				string command;
				string args[2];
				while (getline(inputs, token, ','))
				{
					if (index == 0)
					{
						command = token;
					}
					else if (index < 3)
					{ // There are only two parameters to the MOVE command
						args[index - 1] = token;
					}
					index++;
				}

				if (command == "MOVE")
				{
					cout << "Moving: " << args[0] << " and " << args[1] << endl;
					converter(args[0], args[1]);
				}
				if (command == "END")
				{
					stop();
					cout << "Stopping" << endl;
				}
			}
		}
	}
	return EXIT_SUCCESS;
}
/*
 * converter takes a force and an angle and outputs Dir and step frequency to
 * the stepper motor drivers
 */
void converter(string iAngle, string iForce)
{
	float force = stof(iForce);
	float angle = stof(iAngle);

	if (angleCalc(angle))
	{
		printf("error in AngleCalc function");
	}

	float speed = force * lRatio * MAXSPEED; //TODO: fix this
	if (speed < 0)
	{
		speed = -speed;
		driver1_dir.setValue(GPIO::LOW);
	}
	else
	{
		driver1_dir.setValue(GPIO::HIGH);
	}
	driver1_step.setFrequency(speed);
	driver1_step.setDutyCycle((unsigned int) 100000); //From A4988 datasheet - minimum high time
	driver1_step.run();

	speed = force * rRatio * MAXSPEED; //TODO: fix this
	if (speed < 0)
	{
		speed = -speed;
		driver2_dir.setValue(GPIO::LOW);
	}
	else
	{
		driver2_dir.setValue(GPIO::HIGH);
	}
	driver2_step.setFrequency(speed);
	driver2_step.setDutyCycle((unsigned int) 100000); //From A4988 datasheet - minimum high time
	driver2_step.run();
}

/*
 * Sets up pwm pins:
 * P9.14 & P8.13
 * 
 * Initializes the steppermotor driver with the default settings:
 * Microstepping option:    Full step
 * Enable:                  Low (Low == enable)
 * Reset:                   High
 * Sleep:                   High
 * Dir:                     High
 */
void init(void)
{
	cout << "Initializing pins for PWM" << endl;
	system("config-pin P9.14 pwm");
	system("config-pin P8.13 pwm");

	write("/sys/class/pwm/pwmchip3/", "export", 0); //P9.14
	write("/sys/class/pwm/pwmchip6/", "export", 1); //P8.13

	cout << "Setting up digital pins" << endl;

	cout << "Driver 1..." << endl;
	usleep(250000);
	driver1_enable.setDirection(GPIO::OUTPUT);
	driver1_enable.setValue(GPIO::LOW); //Should be low to enable the output
	driver1_ms1.setDirection(GPIO::OUTPUT);
	driver1_ms1.setValue(GPIO::LOW);
	driver1_ms2.setDirection(GPIO::OUTPUT);
	driver1_ms2.setValue(GPIO::LOW);
	driver1_ms3.setDirection(GPIO::OUTPUT);
	driver1_ms3.setValue(GPIO::LOW);

	cout << "Driver 2..." << endl;
	usleep(250000);
	driver1_reset.setDirection(GPIO::OUTPUT);
	driver1_reset.setValue(GPIO::HIGH);
	driver1_sleep.setDirection(GPIO::OUTPUT);
	driver1_sleep.setValue(GPIO::HIGH);
	driver1_dir.setDirection(GPIO::OUTPUT);
	driver1_dir.setValue(GPIO::HIGH);

	driver2_enable.setDirection(GPIO::OUTPUT);
	driver2_enable.setValue(GPIO::LOW);
	driver2_ms1.setDirection(GPIO::OUTPUT);
	driver2_ms1.setValue(GPIO::LOW);
	driver2_ms2.setDirection(GPIO::OUTPUT);
	driver2_ms2.setValue(GPIO::LOW);
	driver2_ms3.setDirection(GPIO::OUTPUT);
	driver2_ms3.setValue(GPIO::LOW);

	driver2_reset.setDirection(GPIO::OUTPUT);
	driver2_reset.setValue(GPIO::HIGH);
	driver2_sleep.setDirection(GPIO::OUTPUT);
	driver2_sleep.setValue(GPIO::HIGH);
	driver2_dir.setDirection(GPIO::OUTPUT);
	driver2_dir.setValue(GPIO::HIGH);

	cout << "Pinsetup done..." << endl;
}

/*
 * calls the stop method on both motor objects, stopping the motors
 */
void stop(void)
{
	driver1_step.stop();
	driver2_step.stop();
	cout << "Stopping PWM" << endl;
}
