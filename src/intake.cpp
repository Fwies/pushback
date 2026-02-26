#include "main.h"
bool hoodState =false;
bool trapDoorState = false;
bool slow = false;

pros::Distance topBall(6);
COLORVALUE OppUpper = COLORVALUE::BLUEUPPER;
COLORVALUE OppLower = COLORVALUE::BLUELOWER;
pros::adi::Pneumatics hood('z', false);
pros::adi::Pneumatics tongue('b', false);
pros::adi::Pneumatics lift('h', false);
pros::adi::Pneumatics wing('g', false);
pros::adi::Pneumatics middleGoal('f', false);

pros::Optical optical(7);
pros::Motor I1 ((int)9, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor I2 ((int)-2, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor I3 ((int)-3, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
int colorSortCountdown = 0;
int intakeRev = 0;
int topBallBuffer = 70;
void intakeIn(){
    middleGoal.extend();
    wing.extend();
    lift.retract();


    
    I1.move_velocity(600);
    I2.move_velocity(600);
    
    
    intakeRev = 0;
}

void intakeOutLow(bool slowin){
    lift.extend();
    if(!slowin){
        I1.move_velocity(-600);
        I2.move_velocity(-600);
        
        //if(intakeRev>=40){
            I3.move_velocity(-600);
        //}
        //else{
        //    I3.move_velocity(600);
        //}

    }
    else{
        
        I1.move_velocity(-100);
        if(intakeRev<20){
            
            I2.move_velocity(-600);
        }
        else if(intakeRev<40){
            
            I2.move_velocity(100);
        }
        else{
            intakeRev=0;
        }
        
        intakeRev++;
        //else{
        //    I3.move_velocity(600);
        //}
    }
    
}


void intakeOutMid(bool slowin, int ms){
    lift.retract();
    middleGoal.retract();
    
    if(ms<0){
        if(!slowin){
            
                I1.move_velocity(600);
                I2.move_velocity(600);
           
            
            
        }
        else{
            I1.move_velocity(200);
            I2.move_velocity(200);

            
        }
        intakeRev++;
    }
    else{
        for(int i = 0; i<ms/10; i++){
            intakeOutMid(slowin);
            pros::delay(10);
        }
    }
    
}
void intakeOutHigh(int ms){
    lift.retract();
    middleGoal.extend();
    if(ms<0){ // check that this is a iteration call and not to start a timed loop
        wing.retract();// open the hood
        if (intakeRev<10){
            
            I1.move_velocity(-200);// move first stages of intake
            I2.move_velocity(00);
            intakeRev++;
        }
        else{
            I1.move_velocity(600);// move first stages of intake
            if(I2.get_actual_velocity()<10&&I2.get_actual_velocity()>-5){
                intakeRev++;
            }
            else{
                intakeRev=10;
            }
            if(intakeRev >= 20){
                I2.move_velocity(-600);
            }
            else{
                I2.move_velocity(600);
            }
            
            
            
            
        }
           
        
        
            
        
    }
    else{
        for(int i = 0; i<ms/10; i++){
            intakeOutHigh();
            pros::delay(10);
        }
    }
}
void intakeStop(){
    lift.retract();
        I1.move_velocity(0);
        I2.move_velocity(0);
        I3.move_velocity(0);
        colorSortCountdown = 0;
        intakeRev = 0;
}
void intakeLoop(){
    if(master.get_digital(DIGITAL_RIGHT)){
        slow = true;
    }
    else{
        slow = false;
    }
    if(master.get_digital_new_press(DIGITAL_Y)){
        tongue.toggle();
    }
   
    
    if(master.get_digital(DIGITAL_R1)&&master.get_digital(DIGITAL_L1)){
        intakeOutLow(slow);
    }
    else if(master.get_digital(DIGITAL_R1)) {
        intakeIn();
    }
    else if(master.get_digital(DIGITAL_R2)){
        wing.set_value(false);
    }
    else if(master.get_digital(DIGITAL_L1)){
        intakeOutHigh();
    }
    else if(master.get_digital(DIGITAL_L2)){
        intakeOutMid(slow);
    }
    else{
        intakeStop();
        wing.set_value(true);
    }

}