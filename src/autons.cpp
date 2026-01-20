#include "main.h"

pros::adi::AnalogIn pot('h');
int auton = 0;
std::string autoNames[7] = {"no auto","left middle goal","right middle goal","skills","solo awp", "left 7 ball rush", "right 7 ball rush"};
void autoPrint(){
    
    pros::lcd::set_text(6, ": " + autoNames[auton]);
    master.set_text(0, 0, autoNames[auton]);
    
}
bool wingDescore = false;
void autoSet(int in){//-1 means pot
    
    
    if(in < 0){
        in = pot.get_value();
        if (in < ((1.0/7.0)*4096)){
            auton = 0;
        }
        else if (in < ((2.0/7.0)*4096)){
            auton = 1;
            wingDescore = false;
        }
        else if (in < ((3.0/7.0)*4096)){
            auton = 2;
            wingDescore = false;
        }
        else if (in < ((4.0/7.0)*4096)){
            auton = 3;
        }
        else if (in < ((5.0/7.0)*4096)){
            auton = 4;
        }
        else if (in < ((6.0/7.0)*4096)){
            auton = 5;
            wingDescore = true;
        }
        else if (in < ((7.0/7.0)*4096)){
            auton = 6;
            wingDescore = false;
        }
    }
    else{
        auton = in;
    }
}
void autoLeftMiddle(){
    chassis.setPose(0,0,90,false);
    intakeIn();
    chassis.moveToPoint(-40.5,0,2000,{.forwards=false},true);
    chassis.waitUntil(35);
    chassis.cancelMotion();
    chassis.moveToPoint(-40.5,0,2000,{.forwards=false,.maxSpeed=40},false);
    tongue.extend();
    chassis.turnToPoint(-40.5,-13,850,{},false);
    
    //pros::delay(200);
    chassis.moveToPoint(-40.5,-13,1000,{},false);
    chassis.moveToPoint(-42,23,1000,{.forwards=false},false);
    intakeOutHigh();
    tongue.retract();
    pros::delay(1100);
    chassis.swingToPoint(-14,27,DriveSide::LEFT,1000,{},false);
    intakeIn();
    chassis.moveToPoint(-14,27,2000,{.maxSpeed=30},true);
    chassis.waitUntil(14);
    chassis.cancelMotion();
    chassis.moveToPoint(-12,24,2000,{},false);
    //chassis.waitUntil(5);
    //intakeIn();
    
    chassis.turnToPoint(-5.3,34.5,2000,{.forwards=false},false);

    intakeOutMid(true);
    intakeStop();
    chassis.moveToPoint(-5.3,34.5,2000,{.forwards=false},false);
    //chassis.waitUntilDone();
    intakeOutMid(true);
    pros::delay(1500);
    chassis.moveToPoint(-32,15,2000,{},true);
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-32,15,2000,{.maxSpeed=45},false);
    wing.extend();
    //chassis.waitUntil(5);
    intakeStop();
    chassis.turnToPoint(-32,38,2000,{},false);
    //chassis.waitUntilDone();
    wing.retract();
    chassis.moveToPoint(-32,38,6000,{.maxSpeed=50},false);
    chassis.turnToHeading(23,1000,{},false);
    chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
}
void autoRightMiddle(){
    chassis.setPose(0,0,270,false);
    intakeIn();
    chassis.moveToPoint(39,0,2000,{.forwards=false},true);
    chassis.waitUntil(35);
    chassis.cancelMotion();
    chassis.moveToPoint(39,0,2000,{.forwards=false,.maxSpeed=40},false);
    tongue.extend();
    chassis.turnToPoint(39,-13,850,{},false);
    
    //pros::delay(200);
    chassis.moveToPoint(39,-13,1000,{},false);
    chassis.moveToPoint(39.5,23,1000,{.forwards=false},false);
    intakeOutHigh();
    tongue.retract();
    pros::delay(1100);
    chassis.swingToPoint(14,27,DriveSide::RIGHT,1000,{},false);
    intakeIn();
    chassis.moveToPoint(14,27,2000,{.maxSpeed=30},true);
    chassis.waitUntil(14);
    chassis.cancelMotion();
    chassis.moveToPoint(12,24,2000,{.minSpeed=30,.earlyExitRange=4},false);
    //chassis.waitUntil(5);
    //intakeIn();
    
    //chassis.turnToPoint(4.3,35.5,2000,{},false);

    
    chassis.moveToPoint(4.3,35.5,2000,{},false);
    //chassis.waitUntilDone();
    intakeOutLow(false);
    pros::delay(1500);
    chassis.moveToPoint(29,12,2000,{.forwards=false},false);
    wing.extend();
    //chassis.waitUntil(5);
    intakeStop();
    chassis.turnToPoint(29,38,2000,{.forwards=false},false);
    //chassis.waitUntilDone();
    wing.retract();
    chassis.moveToPoint(29,38,10000,{.forwards=false,.maxSpeed=50},false);
    chassis.setBrakeMode(MOTOR_BRAKE_HOLD);






}
void autoSkills(){
    wing.extend();
    chassis.swingToPoint(-41,0,DriveSide::LEFT, 1000,{.maxSpeed=80},false);
    chassis.moveToPoint(-41,0,2000,{},true);
    chassis.waitUntil(26);
    chassis.cancelMotion();
    chassis.moveToPoint(-41,0,2300,{.maxSpeed=50},false);
    tongue.extend();
    
    chassis.turnToPoint(-41,-13,1000,{},false);
    intakeIn();
    chassis.moveToPoint(-41,-13,3500,{.maxSpeed=60},false);
    chassis.moveToPoint(-52,18,2000,{.forwards=false,.minSpeed=60,.earlyExitRange=4},false);
    tongue.retract();
    chassis.moveToPoint(-52,78,4000,{.forwards=false,.minSpeed=40},false);
    chassis.turnToPoint(-39,82,2000,{.forwards=false},false);
    chassis.moveToPoint(-39,82,2000,{.forwards=false},false);
    chassis.turnToPoint(-38,74,2000,{.forwards=false},false);
    chassis.moveToPoint(-38,74,1000,{.forwards=false},false);
    intakeOutHigh();
    tongue.extend();
    pros::delay(2000);
    intakeIn();
    chassis.moveToPoint(-39, 110, 3400,{.maxSpeed=60},false);
    chassis.moveToPoint(-38,74,1600,{.forwards=false},false);
    intakeOutHigh();
    pros::delay(2000);
    intakeStop();
    tongue.retract();
    chassis.moveToPoint(-39,84,1000,{},false);
     chassis.turnToPoint(57,88,4000,{},false);
    chassis.moveToPoint(57,88,4000,{},true);
    chassis.waitUntil(60);
    chassis.cancelMotion();
    chassis.moveToPoint(57,88,4000,{.maxSpeed=40},false);
    tongue.extend();
    chassis.turnToPoint(57,110,4000,{},false);
    intakeIn();
    chassis.moveToPoint(57,110,3400,{.maxSpeed=60},false);

    chassis.moveToPoint(68,80,2000,{.forwards=false,.minSpeed=60,.earlyExitRange=4},false);
    tongue.retract();
    chassis.moveToPoint(68,18,4000,{.forwards=false,.minSpeed=40},false);
    chassis.turnToPoint(57,10,2000,{.forwards=false},false);
    chassis.moveToPoint(57,10,2000,{.forwards=false},false);
    chassis.turnToPoint(57,23,2000,{.forwards=false},false);
    chassis.moveToPoint(57,23,1000,{.forwards=false},false);
    intakeOutHigh();
    tongue.extend();
    pros::delay(2000);
    intakeIn();
    chassis.moveToPoint(57,-13,4000,{.maxSpeed=60},false);
    chassis.moveToPoint(57,23,1200,{.forwards=false},false);
    intakeOutHigh();
    pros::delay(2000);
    tongue.retract();
    intakeIn();
    wing.extend();
    chassis.moveToPoint(30,-10,2000,{.minSpeed=30, .earlyExitRange=3},false);
    chassis.moveToPoint(3,-10,4000,{},false);

    

    
    
    
    
    
}
void autoAWP(){
    chassis.setPose(0,0,270,false);
    intakeIn();
    chassis.moveToPoint(-20,0,300,{},false);
    pros::delay(250);
    chassis.moveToPoint(39,0,2000,{.forwards=false},true);
    chassis.waitUntil(35);
    chassis.cancelMotion();
    chassis.moveToPoint(39,0,2000,{.forwards=false,.maxSpeed=40},false);
    tongue.extend();
    chassis.turnToPoint(39,-13,850,{},false);
    
    //pros::delay(200);
    chassis.moveToPoint(39,-13,1000,{},false);
    chassis.moveToPoint(39.5,21,800,{.forwards=false},false);
    intakeOutHigh();
    tongue.retract();
    pros::delay(1100);
    
    //chassis.swingToPoint(21,25,DriveSide::RIGHT,1000,{},false);
    chassis.turnToPoint(16,27,1000,{},false);
    intakeIn();
    chassis.moveToPoint(16,27,2000,{},true);
    chassis.waitUntil(9);
    tongue.extend();
    chassis.waitUntilDone();
    chassis.turnToPoint(-27,24.7,300,{},false);
    chassis.moveToPoint(-29,24.7,2000,{},true);
    chassis.waitUntil(5);
    tongue.retract();
    chassis.waitUntil(38);
    //chassis.cancelMotion();
    
    //chassis.moveToPoint(-27,24.7,2000,{.maxSpeed=40},true);
    
    tongue.extend();
    chassis.waitUntilDone();
    chassis.turnToPoint(-18.4,39,1000,{.forwards=false},false);
    
    intakeOutMid(true);
    intakeStop();
    chassis.moveToPoint(-18.4,39,800,{.forwards=false},false);
    //intakeOutHigh();
    intakeOutMid(true);
    chassis.turnToHeading(225,500,{},false);
    
    pros::delay(400);
    intakeIn();
    chassis.moveToPoint(-57.5,5,3000,{},true);//-53
    chassis.waitUntil(36);
    chassis.cancelMotion();
    chassis.moveToPoint(-57.5,5,3000,{.maxSpeed=40},false);//-
    //chassis.waitUntil(50);
    //chassis.cancelMotion();
    //chassis.moveToPoint(-58.5,4,2000,{.minSpeed=30,.earlyExitRange=20},false);//gay
    tongue.extend();
    chassis.turnToPoint(-57.5,-14,1000,{},false);
    
    chassis.moveToPoint(-57.5,-14,1400,{.maxSpeed=60},false);
    //chassis.turnToPoint(-58.5,23,1000,{.forwards=false},false);
    chassis.moveToPoint(-57.5,23,1000,{.forwards=false},false);
    intakeOutHigh();
    
    

    while(true){
    pros::lcd::set_text(0, "y: " + std::to_string(schassis.getPose().y));
	pros::lcd::set_text(1, "x: " + std::to_string(schassis.getPose().x));
    }
}
void autoLeftElims()
{
    intakeIn();
chassis.moveToPoint(-14,20,2000,{.minSpeed=40,.earlyExitRange=10},false);
tongue.extend();
//pros::delay(70);
chassis.turnToPoint(-41,0,300,{},false);
chassis.moveToPoint(-42,0,1500,{.minSpeed=30,.earlyExitRange=14},false);
chassis.turnToPoint(-42,-17,300,{},false);
//chassis.moveToPoint(40,0,2000,{.minSpeed=40,.earlyExitRange=19},false);
// chassis.moveToPoint(41,0,1700,{},true);
// chassis.waitUntil(33);
// chassis.cancelMotion();
// chassis.moveToPoint(41,0,1700,{.maxSpeed=50,.minSpeed=30,.earlyExitRange=9},false);
//chassis.turnToPoint(42,-17,1000,{},false);
chassis.moveToPoint(-42,-17,1300,{.maxSpeed=60,.minSpeed=40},false);
chassis.moveToPoint(-41.5,20,1200,{.forwards=false},false);
intakeOutHigh();
pros::delay(1100);
tongue.retract();
wing.extend();
chassis.moveToPoint(-52.5,13,1000,{},false);
wing.retract();
chassis.turnToPoint(-52.5,35,1000,{.forwards=false},false);
chassis.moveToPoint(-52.5,35,2000,{.forwards=false,.maxSpeed=50},false);
chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
//rush no wing methodVVVV
//chassis.moveToPoint(-41.5,10,300,{},false);
//intakeIn();
//chassis.moveToPoint(-41.5,20,10000,{.forwards=false},false);

}
void autoRightElims()
{

intakeIn();
chassis.moveToPoint(14,20,2000,{.minSpeed=40,.earlyExitRange=10},false);
tongue.extend();
//pros::delay(70);
chassis.turnToPoint(41,0,300,{},false);
chassis.moveToPoint(42,0,1500,{.minSpeed=30,.earlyExitRange=14},false);
chassis.turnToPoint(42,-17,300,{},false);
//chassis.moveToPoint(40,0,2000,{.minSpeed=40,.earlyExitRange=19},false);
// chassis.moveToPoint(41,0,1700,{},true);
// chassis.waitUntil(33);
// chassis.cancelMotion();
// chassis.moveToPoint(41,0,1700,{.maxSpeed=50,.minSpeed=30,.earlyExitRange=9},false);
//chassis.turnToPoint(42,-17,1000,{},false);
chassis.moveToPoint(42,-17,1300,{.maxSpeed=60,.minSpeed=40},false);
chassis.moveToPoint(41.5,20,1200,{.forwards=false},false);
intakeOutHigh();
pros::delay(1100);
tongue.retract();
wing.extend();
chassis.moveToPoint(29,13,1000,{},false);
wing.retract();
chassis.turnToPoint(29,35,1000,{.forwards=false},false);
chassis.moveToPoint(29,35,2000,{.forwards=false,.maxSpeed=50},false);
chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
//rush no wing methodVVVV
//chassis.moveToPoint(41.5,10,300,{},false);
//intakeIn();
//chassis.moveToPoint(41.5,20,10000,{.forwards=false},false);



}



void autoRun(){
   
    if (auton == 1){
        autoLeftMiddle();
    }
    if (auton == 2){
        autoRightMiddle();
    }
    if (auton == 3){
        autoSkills();
    }
    if (auton == 4){
        autoAWP();
    }
    if (auton == 5){
        autoLeftElims();
    }
    if (auton == 6){
        autoRightElims();
        wingDescore=false;
    }
}
