#include "main.h"
bool hoodState =false;
bool slow = false;
pros::adi::Pneumatics hood('f', false);
pros::adi::Pneumatics tongue('a', false);
void setHood(bool in){
    if (hoodState != in){
        hoodState = !hoodState;
        hood.toggle();
    }
}

pros::Motor I1 ((int)-14, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor I2 ((int)21, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
void intakeIn(){
    setHood(false);
        I1.move_velocity(600);
        I2.move_velocity(600);
}
void intakeOutLow(bool slowin){
    if(!slowin){
    I1.move_velocity(-600);
    I2.move_velocity(-600);
    }
    else{
       I1.move_velocity(-250);
    I2.move_velocity(-250); 
    }
}
void intakeOutMid(bool slowin){
    if(!slowin){
    I1.move_velocity(600);
    I2.move_velocity(-300);
    }
    else{
        I1.move_velocity(400);
    I2.move_velocity(-200);
    }
    
}
void intakeOutHigh(){
    setHood(true);
        I1.move_velocity(600);
        I2.move_velocity(600);
}
void intakeStop(){
    I1.move_velocity(0);
    I2.move_velocity(0);
}
void intakeLoop(){
    if(master.get_digital(DIGITAL_RIGHT)){
        slow = true;
    }
    else{
        slow = false;
    }
    if(master.get_digital(DIGITAL_Y)){
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