#include "main.h"

pros::adi::AnalogIn pot(8);
int auton = 0;
std::string autoNames[5] = {"no auto","left","right","skills","solo awp"};
void autoPrint(){
    pros::lcd::set_text(3, "auton: " + autoNames[auton]);
}
void autoSet(int in){//-1 means pot
    if(master.get_digital_new_press(DIGITAL_LEFT)){
        chassis.setPose(0,0,270,false);
    }
    if(master.get_digital_new_press(DIGITAL_RIGHT)){
        chassis.setPose(0,0,90,false);
    }
    if(master.get_digital_new_press(DIGITAL_RIGHT)){
        chassis.setPose(0,0,chassis.getPose().theta,false);
    }
    
    if(in < 0){
        in = pot.get_value();
        if (in < (0.2*4096)){
            auton = 0;
        }
        else if (in < (0.4*4096)){
            auton = 1;
        }
        else if (in < (0.6*4096)){
            auton = 2;
        }
        else if (in < (0.8*4096)){
            auton = 3;
        }
        else if (in < (4096)){
            auton = 4;
        }
    }
    else{
        auton = in;
    }
}
void autoLeft(){
    


}
void autoRight(){
    /*chassis.moveToPoint(0,12,2000,{},false);
    chassis.moveToPoint(0,48,2000,{},false);
    chassis.moveToPoint(0,12,2000,{.forwards=false},false);
    chassis.moveToPoint(0,0,2000,{.forwards=false},false);*/
    /*chassis.turnToHeading(45,2000,{},false);
    master.rumble(".");
    
    chassis.turnToHeading(225,2000,{},false);
     master.rumble(".");
    
    chassis.turnToHeading(0,2000,{},false);
     master.rumble(".");*/
     chassis.setPose(0,0,180,{false});
     
     chassis.moveToPose(-12.5,34,142,2000,{.forwards=false},false);//140
     //intakeOutHigh(true);
    setHood(true);
     I3.move_velocity(100);
     pros::delay(400);
     intakeStop();
     intakeIn();
     chassis.moveToPoint(17.5,26.2,2000,{},true);//140
    chassis.waitUntil(8);
    chassis.cancelMotion();
    chassis.moveToPoint(17.5,26.2,2000,{.maxSpeed=50},true);//140
    chassis.waitUntil(8);
    tongue.toggle();
    chassis.waitUntilDone();
    chassis.moveToPoint(-2.3,42.8,2000,{.maxSpeed=60},true);//
    chassis.waitUntil(9);
    tongue.toggle();
     
}
void autoSkills(){
    
    

}
void autoAWP(){
    
  

}
void autoRun(){
    if (auton == 1){
        autoLeft();
    }
    if (auton == 2){
        autoRight();
    }
    if (auton == 3){
        autoSkills();
    }
    if (auton == 4){
        autoAWP();
    }
}
