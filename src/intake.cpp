#include "main.h"
bool hoodState =false;
bool trapDoorState = false;
bool slow = false;
//pros::adi::Pneumatics trapDoor('c', false);
pros::adi::Pneumatics hood('f', false);
pros::adi::Pneumatics tongue('a', false);
void setHood(bool in){
    if (hoodState != in){
        hoodState = !hoodState;
        hood.toggle();
    }
}


pros::Motor I1 ((int)10, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor I2 ((int)9, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor I3 ((int)-21, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
//pros::MotorGroup intake({12,20});
void intakeIn(){
    setHood(false);
    

        I1.move_velocity(600);



        I2.move_velocity(60);
        I3.move_velocity(600);
}
void intakeOutLow(bool slowin){
    
    if(!slowin){
        I1.move_velocity(-600);
        I2.move_velocity(-500);
        I3.move_velocity(-600);
    }
    else{
        I1.move_velocity(-200);
        I2.move_velocity(-200);
        I3.move_velocity(-100);
    }
}
void intakeOutMid(bool slowin){
    
    if(!slowin){
    I1.move_velocity(600);
        I2.move_velocity(600);
        I3.move_velocity(-600);
    }
    else{
        I1.move_velocity(150);
        I2.move_velocity(150);
        I3.move_velocity(-300);
    }
    
}
int intakeRev = 0;
void intakeOutHigh(bool inauton){
    setHood(true);
    
        I3.move_velocity(600);
        if(intakeRev<=20&&!inauton){
            I1.move_velocity(-200);
            I2.move_velocity(-200);
            intakeRev++;
        }
        else{
            I1.move_velocity(600);
            I2.move_velocity(600);
            
        }
}
void intakeStop(){
        I1.move_velocity(0);
        I2.move_velocity(0);
        I3.move_velocity(0);
        intakeRev=0;
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
        intakeOutHigh(false);
    }
    else if(master.get_digital(DIGITAL_L2)){
        intakeOutMid(slow);
    }
    else{
        intakeStop();
    }

}