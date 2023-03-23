//signal handling code for arduino intermediary microcontroller in 2023 NASA        //
//Lunabotics competition for the UND Robotics Club team. Reads input from Jetson to //
//activate & drive pin release servo. Reads shunt resistor measurement from mining  //
//stystem indicative of stuck fault condition and sends signal to Jetson to initiate//
//stuck-fault recovery. Also provides overvoltage/overcurrent protection to Jetson. //
//by Kevin Jordan, kevin.jordan@und.edu - March 2023                                //

#include <Servo.h>

//~~~~~~~~~~~~~~~~~~rover deployement servo var defs~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Servo deploy_servo;
int jetson_run_servo_in;
bool already_ran_flag = false;
bool run_servo;

//WARNING!!! NEED TO SET & CALIBRATE WHERE INITIAL POSITION OF IMPLEMENTED SERVO IS //
//AND SET INITIAL POSITION ACCORDINGLY. USE OF 0 HERE IS BASED ON ASSUMING SERVO IS //
//MANUALLY SET FULLY TO ONE SIDE & IS SAME POSITION PRE SYSTEM DEPLOYEMENT.         //
//ALWAYS CHECK THAT SERVO POSITION IS MANUALLY RESET BEFORE RESETTING ROVER SYSTEM  //
//OTHERWISE SERVO WILL FORCEFULLY RESET TO "0" UPON SYSTEM POWER UP / RESET.        //
int servo_position = 0;

const int jetson_run_servo_in_pin = A0;
const int servo_out_pin = 9;

//~~~~~~~~~~~~~~~~~~shunt resistor stuck fault var defs~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int shunt_current_reading;
long timer = 0;
long high_avg_3s_timer = 0;
double shunt_reading_avg = 1.0;
bool high_resistance_flag = false;
bool stuck_fault = false;

const int shunt_current_reading_pin = A1;
const int stuck_fault_out_pin_to_jetson = 24;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~limit switch var defs~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int full_extend_reading;
int full_retract_reading;
int timer2 = 0;
int timer3 = 0;
long high_ext_timer = 0;
long high_rtct_timer = 0;
bool high_ext_flag = false;
bool high_rtct_flag = false;
bool full_extend = false;
bool full_retract = false;

const int full_extend_reading_pin = 46;
const int full_retract_reading_pin = 32;
const int full_extend_out_pin_to_jetson = 42;
const int full_retract_out_pin_to_jetson = 38;


//testing only
//const int simulated_jetson_GPIO_read = 48; 

void setup() {
  
    //Serial.begin(9600); //uncomment for testing if needed
    //~~~~~~~~~~~~~~~~~~rover deployement servo setup~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //maually set servo position to INITIAL POSITION (see warning above) & attach
    deploy_servo.write(servo_position);
    deploy_servo.attach(servo_out_pin);
    
}


void loop() {
    
    //~~~~~~~~~~~~~~~~~~rover deployement servo control code~~~~~~~~~~~~~~~~~~~~~~~~//
    //read input from jetson
    jetson_run_servo_in = analogRead(jetson_run_servo_in_pin);
    
    //determine if logic HIGH or LOW
    if (620 <= jetson_run_servo_in) run_servo = true;
    else run_servo = false;

    //are we supposed to run servo?
    if (run_servo == true) {
        //have we already deployed so no need to run again?
        if (already_ran_flag == false) {
            //gradually actuate to oposite of servo position range
            for (servo_position = 0; servo_position <= 180; servo_position += 1) {
                deploy_servo.write(servo_position);
                delay(5); //DELAY CAN BE MODIFIED TO SET DESIRED ROTATION SPEED (lower is faster)
            }
            //once deployement ran set flag so does not run again
            already_ran_flag = true;
        }
    }

    
    //~~~~~~~~~~~~~~~~~~shunt resistor stuck fault signal code~~~~~~~~~~~~~~~~~~~~~~//
    //set system timer to be able to time stuck-fault warning state
    timer = (int)(millis()/1000);

    //read in voltage value from shunt resistor
    shunt_current_reading = analogRead(shunt_current_reading_pin);

    //smooth shunt signal data
    shunt_reading_avg = EXPONENTIAL_MOVING_AVG(shunt_reading_avg, shunt_current_reading);

    //check if smoothed readings are over threshold
    if (shunt_reading_avg >= 700) { //THRESHOLD VALUE NEEDS TO BE DETERMINED AND SET BASED ON FINAL SHUNT SIGNAL RANGE
        //set stuck-fault warning flag
        high_resistance_flag = true;
        //freeze timer to track how long system has been in stuck-fault warning state
        if (high_avg_3s_timer == 0) high_avg_3s_timer = timer;
        else high_avg_3s_timer = high_avg_3s_timer;
    }

    //if readings fall back in working tollerance
    else if (shunt_reading_avg < 700) { //THRESHOLD VALUE NEEDS TO BE DETERMINED AND SET BASED ON FINAL SHUNT SIGNAL RANGE
        //clear stuck-fault warning & reset frozen timer for future stuck-fault tracking
        high_resistance_flag = false;
        high_avg_3s_timer = 0;
    }

    //if system is in stuck-fault warning state
    if (high_resistance_flag == true) {
        //and its been in warning state for more than 3s
        if (timer - high_avg_3s_timer >= 2) {
            //STUCK-FAULT condition, set flag to true
            stuck_fault = true;
        }
    }

    //if system has already sent a STUCK-FAULT to Jetson
    if ((stuck_fault == true) && (timer - high_avg_3s_timer >= 3)) {
        //clear flag & reset signal output for future STUCK-FAULT detection
        stuck_fault = false;
    }

    //send stuck-fault signal to Jetson, default is logic LOW or NO STUCK-FAULT
    digitalWrite(stuck_fault_out_pin_to_jetson, stuck_fault);


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~limit switches signal code~~~~~~~~~~~~~~~~~~~~~~//
    timer2 = (int)(millis()/1000);

    full_extend_reading = digitalRead(full_extend_reading_pin);
    if (full_extend_reading == false) {
        high_ext_flag == true;
        if (high_ext_timer == 0) high_ext_timer = timer2;
        else high_ext_timer = high_ext_timer;
    }
    if (high_ext_flag == true) {
        if (timer2 - high_ext_timer >= 1) {
            full_extend = true;
        }
    }


    timer3 = (int)(millis()/1000);

    full_retract_reading = digitalRead(full_retract_reading_pin);
        if (full_retract_reading == false) {
        high_rtct_flag == true;
        if (high_rtct_timer == 0) high_rtct_timer = timer3;
        else high_rtct_timer = high_rtct_timer;
    }
    if (high_rtct_flag == true) {
        if (timer3 - high_rtct_timer >= 1) {
            full_retract = true;
        }
    }

}


double EXPONENTIAL_MOVING_AVG(double avg, double new_sample) {
    //~~~~~~~~~~~~~~Exonential moving average to filter raw shunt data~~~~~~~~~~~~~~~~~//
    //number of samples to average over
    int N = 20; //20 found to maximize responisveness & smooting ~1s for avg to settle
     
    avg -= avg / N;
    avg += new_sample / N;

    return avg;
}
