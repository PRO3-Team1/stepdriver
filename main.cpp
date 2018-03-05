/* 
 * File:   main.cpp
 * Author: JCT
 *
 * Created on 05 December 2017, 10:24
 */

#include "io.h"

double lRatio = 0;
double rRatio = 0;

int main(int argc, char** argv) {

    init();
    cout << "Listen for commands on stdin..." << endl;
    string input;
    while (1) {
        cin >> input;
        if (input.at(0) != '#') // This is the debug character
        {
            istringstream inputs(input);
            string token;
            int index = 0;
            string command;
            string args[2];
            while (getline(inputs, token, ',')) {
                if (index == 0) {
                    command = token;
                } else if (index < 3) { // There are only two parameters to the MOVE command
                    args[index - 1] = token;
                }
                index++;
            }

            if (command == "MOVE") {
                cout << "Moving: " << args[0] << " and " << args[1] << endl;
                converter(args[0], args[1]);
            }
            if (command == "END") {
                stop();
                cout << "Stopping" << endl;
            }
        }
    }
return EXIT_SUCCESS;
}

/*
 * converter takes a force and an angle and outputs Dir and step frequency to
 * the stepper motor drivers
 */
void converter(string iAngle, string iForce) {
    float force = stof(iForce);
    float angle = stof(iAngle);

    if (angleCalc(angle)) {
        printf("error in AngleCalc function");
    }

    float speed = force * rRatio * MAXSPEED; //TODO: fix this
    if (speed < 0) {
        speed = -speed;
        driver1_dir.setValue(GPIO::LOW);
    } else {
        driver1_dir.setValue(GPIO::HIGH);
    }
    driver1_step.setFrequency(speed);
    driver1_step.setDutyCycle((unsigned int) 100000); //From A4988 datasheet - minimum high time
    driver1_step.run();

    speed = force * lRatio * MAXSPEED; //TODO: fix this
    if (speed < 0) {
        speed = -speed;
        driver2_dir.setValue(GPIO::LOW);
    } else {
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
void init(void) {
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

/**
 * calls the stop method on both motor objects, stopping the motors
 */
void stop(void) {
    driver1_step.stop();
    driver2_step.stop();
    cout << "Stopping PWM" << endl;
}
