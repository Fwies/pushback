#include "main.h"
bool hoodState =false;
bool trapDoorState = false;
bool slow = false;
pros::adi::Pneumatics trapDoor('c', false);
pros::adi::Pneumatics hood('f', false);
pros::adi::Pneumatics tongue('a', false);
void setHood(bool in){
    if (hoodState != in){
        hoodState = !hoodState;
        hood.toggle();
    }
}
void setTrapDoor(bool in){
    if (trapDoorState != in){
        trapDoorState = !trapDoorState;
        trapDoor.toggle();
    }
}

pros::Motor I1 ((int)-20, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor I2 ((int)12, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::MotorGroup intake({12,20});
void intakeIn(){
    setHood(false);
    setTrapDoor(false);
        intake.move_velocity(600);
}
void intakeOutLow(bool slowin){
    setTrapDoor(false);
    if(!slowin){
    intake.move_velocity(-600);
    }
    else{
       intake.move_velocity(-250);
    }
}
void intakeOutMid(bool slowin){
    setTrapDoor(true);
    if(!slowin){
    intake.move_velocity(600);
    }
    else{
        intake.move_velocity(200);
    }
    
}
void intakeOutHigh(){
    setHood(true);
    setTrapDoor(false);
        intake.move_velocity(600);
}
void intakeStop(){
    intake.move_velocity(0);
}
void intakeLoop(){
    I1.set_brake_mode(MOTOR_BRAKE_HOLD);
    I2.set_brake_mode(MOTOR_BRAKE_HOLD);
    if(master.get_digital(DIGITAL_RIGHT)){
        slow = true;
    }
    else{
        slow = false;
    }
    if(master.get_digital_new_press(DIGITAL_Y)){
        tongue.toggle();
    }
    if(master.get_digital(DIGITAL_R1)) {
        intakeIn();
    }
    else if(master.get_digital(DIGITAL_R2)){
        intakeOutLow(slow);
        
    }
    else if(master.get_digital(DIGITAL_L1)){
        intakeOutHigh();
    }
    else if(master.get_digital(DIGITAL_L2)){
        intakeOutMid(slow);
    }
    else{
        intakeStop();
    }

}