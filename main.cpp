/* 
 * File:   main.cpp
 * Author: TEAM1
 *
 * Created on 05 December 2017, 10:24
 */

#include "io.h"

double lRatio = 0;
double rRatio = 0;
/*
 * Main function. Here the stdin data is processed and handed off to handler functions
 */
int main(int argc, char** argv) {

    init();
    cout << "Listen for commands on stdin..." << endl;
    string input;
    while (1) {
        cin >> input;
        if (input.at(0) != '#') // This is the debug character
        {
            //Here there CSV input is imported line by line. Each line is split on commas
            // and copied into "command" and and array of "args"
            istringstream inputs(input); //convert the input string to a stringstream object
            string token;                //token (which will be taking from input)
            int index = 0;
            string command;              //parsed command from input stream
            string args[2];              //arguments for command
            while (getline(inputs, token, ',')) { //Tokenize the input string on ,
                if (index == 0) {
                    command = token;              //Assign the first token to the command
                } else if (index < 3) { // There are only two parameters to the MOVE command so we move the args over
                    args[index - 1] = token;
                }
                index++;
            }
            //Execute commands 
            if (command == "MOVE") { 
                cout << "Moving: " << args[0] << " and " << args[1] << endl;
                converter(args[0], args[1]);
            }
            else if (command == "END") {
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

    //The conversion from radian and force to relative float speeds for each engine is done in angleCalc
    //Please notice that this call uses the global variables lRatio and rRatio
    if (angleCalc(angle)) {
        printf("error in AngleCalc function");
    }

    float speed = force * lRatio * MAXSPEED; 
    if (speed < 0) {
        speed = -speed;
        /* Note that the dir is reversed between driver1 and driver 2, this is
         because they are mounted differently mechanically*/
        driver1_dir.setValue(GPIO::HIGH);
    } else {
        driver1_dir.setValue(GPIO::LOW);
    }
    driver1_step.setFrequency(speed);
    driver1_step.setDutyCycle((unsigned int) 100000); //From MP6500 datasheet - minimum high time
    driver1_step.run();

    speed = force * rRatio * MAXSPEED; 
    if (speed < 0) {
        speed = -speed;
        driver2_dir.setValue(GPIO::LOW);
    } else {
        driver2_dir.setValue(GPIO::HIGH);
    }
    driver2_step.setFrequency(speed);
    driver2_step.setDutyCycle((unsigned int) 100000); //From MP6500 datasheet - minimum high time
    driver2_step.run();
}

/*
 * Sets up pwm pins:
 * P9.14 & P8.13
 * 
 * Initializes the steppermotor driver with the default settings:
 * Microstepping option:    Full step
 * Enable:                  Low == enable
 * I1/I2:                   Low/Low = 2A current limit
 * Sleep:                   High
 * Dir:                     High
 * 
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
    driver1_i1.setDirection(GPIO::OUTPUT);
    driver1_i1.setValue(GPIO::LOW);

    usleep(250000);
    driver1_i2.setDirection(GPIO::OUTPUT);
    driver1_i2.setValue(GPIO::LOW);
    driver1_sleep.setDirection(GPIO::OUTPUT);
    driver1_sleep.setValue(GPIO::HIGH);
    driver1_dir.setDirection(GPIO::OUTPUT);
    driver1_dir.setValue(GPIO::HIGH);

    cout << "Driver 2..." << endl;
    driver2_enable.setDirection(GPIO::OUTPUT);
    driver2_enable.setValue(GPIO::LOW);
    driver2_ms1.setDirection(GPIO::OUTPUT);
    driver2_ms1.setValue(GPIO::LOW);
    driver2_ms2.setDirection(GPIO::OUTPUT);
    driver2_ms2.setValue(GPIO::LOW);
    driver2_i1.setDirection(GPIO::OUTPUT);
    driver2_i1.setValue(GPIO::LOW);

    driver2_i2.setDirection(GPIO::OUTPUT);
    driver2_i2.setValue(GPIO::LOW);
    driver2_sleep.setDirection(GPIO::OUTPUT);
    driver2_sleep.setValue(GPIO::HIGH);
    driver2_dir.setDirection(GPIO::OUTPUT);
    driver2_dir.setValue(GPIO::HIGH);

    cout << "Pinsetup done..." << endl;
}

/**
 * calls the stop method on both motor objects, stopping the motors, disabling PWM
 */
void stop(void) {
    driver1_step.stop();
    driver2_step.stop();
    cout << "Stopping PWM" << endl;
}
