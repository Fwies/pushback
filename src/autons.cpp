#include "main.h"

pros::adi::AnalogIn pot('a');
int auton = 0;
std::string autoNames[9] = {"no auto","left split","right split","skills","solo awp", "no wing left 7 ball", "no wing right 7 ball", "wing left 7 ball", "wing right 7 ball"};
void autoPrint(){
    pros::lcd::set_text(6, ": " + autoNames[auton]);
    master.set_text(0, 0, autoNames[auton]);
    
}
bool wingDescore = false;
void autoSet(int in){//-1 means pot
    
    
    if(in < 0){
        in = pot.get_value();
        if (in < ((1.0/9.0)*4096)){
            auton = 0;
        }
        else if (in < ((2.0/9.0)*4096)){
            auton = 1;
            
        }
        else if (in < ((3.0/9.0)*4096)){
            auton = 2;
           
        }
        else if (in < ((4.0/9.0)*4096)){
            auton = 3;
        }
        else if (in < ((5.0/9.0)*4096)){
            auton = 4;
        }
        else if (in < ((6.0/9.0)*4096)){
            auton = 5;
            
        }
        else if (in < ((7.0/9.0)*4096)){
            auton = 6;
            
        }
        else if (in < ((8.0/9.0)*4096)){
            auton = 7;
            
        }
        else if (in < ((9.0/9.0)*4096)){
            auton = 8;
            
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
    chassis.moveToPoint(-41.5,23,1000,{.forwards=false,.maxSpeed=60},false);
    intakeOutHigh();
    tongue.retract();
    pros::delay(1300);
    chassis.swingToPoint(-12,27,DriveSide::LEFT,1500,{.maxSpeed=60},false);
    intakeIn();

    chassis.moveToPoint(-12,27,2000,{.maxSpeed=50},true);
    chassis.waitUntil(14);
    chassis.cancelMotion();
    tongue.extend();
    chassis.moveToPoint(-12,24,2000,{},false);
    //chassis.waitUntil(5);
    //intakeIn();
    
    chassis.turnToPoint(-4,36,2000,{.forwards=false},false);

    intakeOutMid(true);
    intakeStop();
    chassis.moveToPoint(-4,36,2000,{.forwards=false},false);
    //chassis.waitUntilDone();
    intakeOutMid(true);
    pros::delay(2000);
    tongue.retract();
    chassis.moveToPoint(-30,15,2000,{},true);
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-30,15,2000,{.maxSpeed=45},false);
    wing.extend();
    //chassis.waitUntil(5);
    intakeStop();
    chassis.turnToPoint(-30,40,2000,{},false);
    //chassis.waitUntilDone();
    wing.retract();
    chassis.moveToPoint(-30,40,6000,{.maxSpeed=50},false);
    chassis.turnToHeading(15,1000,{},false);
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
    intakeIn();
    //first sneaky middle goal ball
    chassis.moveToPoint(-16,24,2000,{},true);
    chassis.waitUntil(12);
    chassis.cancelMotion();

    chassis.moveToPoint(-16,24,2000,{.maxSpeed=50},false);
    
    chassis.turnToPoint(-6,34,1000,{.forwards=false},false);//turn to mid goal
    intakeOutMid(true);
    intakeStop();
    chassis.moveToPoint(-6,34,1000,{.forwards=false},false);//move to goal
    intakeOutMid(true);
    pros::delay(1200);
    chassis.moveToPoint(-43,0,2000,{},true);//move to infront of loader
    chassis.waitUntil(28);
    intakeIn();
    intakeStop();
    chassis.cancelMotion();
    chassis.moveToPoint(-43,0,2500,{.maxSpeed=40},false);
    tongue.extend();
    
    chassis.turnToPoint(-43,-15,1000,{},false);
    intakeIn();
    chassis.moveToPoint(-43,-15,1500,{.maxSpeed=40},false);// move into loader
    leftDrive.move_voltage(1000);
    rightDrive.move_voltage(1000);
    pros::delay(1500);
    chassis.moveToPoint(-52,12,2000,{.forwards=false,.minSpeed=30,.earlyExitRange=4},false);// move away
    tongue.retract();
    chassis.moveToPoint(-52,78,4000,{.forwards=false},true); // move to other end
    chassis.waitUntil(48);
    chassis.cancelMotion();
    chassis.moveToPoint(-52,76,4000,{.forwards=false,.maxSpeed=50},false);
    //chassis.turnToPoint(-40.5,82,2000,{.forwards=false},false); // turn to infront of goal
    chassis.moveToPoint(-40.5,86,2000,{.forwards=false},false);// move to infront of goal
    chassis.turnToPoint(-40.5,68,2000,{.forwards=false},false);//turn to face goal
    chassis.moveToPoint(-40.5,68,800,{.forwards=false,.maxSpeed=40},false);// move to goal
    intakeOutHigh();
    tongue.extend();
    pros::delay(2000);
    
    chassis.turnToPoint(-40.5, 110, 1000,{},false);// turn to align with matchloader
    chassis.moveToPoint(-40.5, 110, 400,{},false);//move to matchloader
    intakeIn();
    chassis.moveToPoint(-40.5, 110, 1500,{.maxSpeed=40},false);
    leftDrive.move_voltage(1000);
    rightDrive.move_voltage(1000);
    pros::delay(1500);
    chassis.moveToPoint(-40.5,68,300,{.forwards=false},false);// move to goal
    chassis.moveToPoint(-40.5,68,1200,{.forwards=false,.maxSpeed=40},false);
    intakeOutHigh();
    pros::delay(2000);
    
    tongue.retract();
    chassis.moveToPoint(-40.5,84,1000,{},false); // move away from goal
    intakeStop();
    chassis.moveToPoint(-18,108,2000,{},false);// move to next to zone
    chassis.turnToPoint(32,109,2000,{},false);// turn to face accross from goal
    intakeIn();
     chassis.moveToPoint(32,109,2000,{.maxSpeed=70},false);// slow move accross first
     chassis.moveToPoint(32,109,4000,{.maxSpeed=100},false);//move accross goal
     chassis.turnToHeading(90,1000,{},false);// turn to prepare for reset
     distanceSensorReset(DS::FRONT,DS::LEFT,90);// reset

     chassis.turnToPoint(-62.5,-35.7,700,{.forwards=false},false);
    chassis.moveToPoint(-62.5,-35.7,2000,{.forwards=false},false);// move to be able to intake sneaky ball
    chassis.turnToPoint(-55,-43,1000,{},false);// turn to face ball
    chassis.moveToPoint(-55,-43,1500,{},false);// get ball
    pros::delay(200);
    intakeStop();
    chassis.moveToPoint(-47,-49,1000,{},false);// move to align with goal
    
    chassis.turnToPoint(-59,-60,1000,{.forwards=false},false);// turn to face goal
    intakeOutMid(true);
    intakeStop();
    chassis.moveToPoint(-59,-60,3000,{.forwards=false,.maxSpeed=50},false);// mvoe to goal
    intakeOutMid(true);
    pros::delay(2500);
    chassis.moveToPoint(-22,-24,2000,{},true);// move to infront of laoder
    chassis.waitUntil(35);
    chassis.cancelMotion();
    chassis.moveToPoint(-22,-24,2000,{.maxSpeed=40},false);
    tongue.extend();
    chassis.turnToPoint(-22,-3,1500,{},false);// turn to loader
    intakeIn();
    chassis.moveToPoint(-22,-3,1500,{.maxSpeed=40},false);// move to loader
    leftDrive.move_voltage(1000);
    rightDrive.move_voltage(1000);
    pros::delay(1500);
    chassis.moveToPoint(-10,-44,2000,{.forwards=false,.minSpeed=60,.earlyExitRange=4},false);// move away 
    tongue.retract();
    chassis.moveToPoint(-10,-105,2000,{.forwards=false},true);// move to other side
    chassis.waitUntil(70);
    chassis.cancelMotion();
    chassis.moveToPoint(-10,-105,2000,{.forwards=false,.maxSpeed=40},false);
    chassis.turnToPoint(-22,-114,2000,{.forwards=false},false);// turn to in front of goal
    chassis.moveToPoint(-22,-114,2000,{.forwards=false},false);// move to in front of goal

    chassis.turnToPoint(-22,-96,2000,{.forwards=false},false);// turn to goal
    chassis.moveToPoint(-22,-96,1400,{.forwards=false,.maxSpeed=40},false);// go to goal
    intakeOutHigh();
    tongue.extend();
    chassis.turnToPoint(-22,-130,1000,{},false);// turn to loader
    pros::delay(2000);

    chassis.moveToPoint(-22,-130,500,{},false);
    intakeIn();
    chassis.moveToPoint(-22,-130,1200,{.maxSpeed=40},false);// move to loader
    leftDrive.move_voltage(1000);
    rightDrive.move_voltage(1000);
    pros::delay(1500);
    chassis.moveToPoint(-22,-96,300,{.forwards=false},false);// move to goal
    chassis.moveToPoint(-22,-96,2000,{.forwards=false,.maxSpeed=40},false);
    intakeOutHigh();
    pros::delay(2000);
    tongue.retract();
    intakeIn();
    chassis.moveToPoint(-48,-135,3000,{},false);// move to infront of zone
   chassis.turnToPoint(-72,-136,3000,{},false);// turn to face zone
   chassis.moveToPoint(-72,-136,3000,{},true);// move to zone
   while(distance_sensor_front.get_distance()/25.4 > 63){
    
    pros::delay(10);
   }
   chassis.cancelMotion();
   chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
   
    
    


    while(true){
        pros::lcd::set_text(0, "x: " + std::to_string(schassis.getPose().x));
        pros::lcd::set_text(1, "y: " + std::to_string(schassis.getPose().y));
        pros::delay(10);
    }

     /*//pros::delay(99999);
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
    chassis.moveToPoint(3,-10,4000,{},false);*/

    

    
    
    
    
    
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
    chassis.turnToPoint(38,-13,850,{},false);
    
    //pros::delay(200);
    chassis.moveToPoint(38,-13,1300,{.maxSpeed=50},false);
    chassis.moveToPoint(40,21,400,{.forwards=false},false);
    chassis.moveToPoint(40,21,600,{.forwards=false,.maxSpeed=50},false);
    intakeOutHigh();
    tongue.retract();
    pros::delay(1100);
    
    //chassis.swingToPoint(21,25,DriveSide::RIGHT,1000,{},false);
    chassis.turnToPoint(16,27,800,{},false);
    intakeIn();
    chassis.moveToPoint(16,27,2000,{},true);
    chassis.waitUntil(9);
    tongue.extend();
    chassis.cancelMotion();
    chassis.turnToPoint(-27,24.7,100,{},false);
    chassis.moveToPoint(-29,24.7,2000,{},true);
    chassis.waitUntil(5);
    tongue.retract();
    chassis.waitUntil(42);
    //chassis.cancelMotion();
    
    //chassis.moveToPoint(-27,24.7,2000,{.maxSpeed=40},true);
    
    tongue.extend();
    chassis.waitUntilDone();
    chassis.turnToPoint(-18.4,36,1000,{.forwards=false},false);
    
    intakeOutMid(true);
    intakeStop();
    chassis.moveToPoint(-18.4,36,700,{.forwards=false},false);

    intakeOutMid(true);
    chassis.turnToHeading(225,500,{},false);
    
    pros::delay(700);
    intakeIn();
    chassis.moveToPoint(-56.5,5,3000,{},true);//-53
    chassis.waitUntil(36);
    chassis.cancelMotion();
    chassis.moveToPoint(-56.5,5,3000,{.maxSpeed=40},false);
    
    
    
    //tongue.extend();
    chassis.turnToPoint(-56.5,-14,700,{},false);
    
    //chassis.moveToPoint(-56.5,-14,1400,{.maxSpeed=60},false);
    
    chassis.moveToPoint(-56.5,23,500,{.forwards=false},false);
    intakeOutHigh();
    pros::delay(1500);
    chassis.moveToPoint(-56.5,0,1000,{},false);
    
    

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
pros::delay(70);
chassis.turnToPoint(-41,0,300,{},false);
chassis.moveToPoint(-42,0,1500,{.minSpeed=30,.earlyExitRange=17},false);
chassis.turnToPoint(-42,-17,300,{},false);
//chassis.moveToPoint(40,0,2000,{.minSpeed=40,.earlyExitRange=19},false);
// chassis.moveToPoint(41,0,1700,{},true);
// chassis.waitUntil(33);
// chassis.cancelMotion();
// chassis.moveToPoint(41,0,1700,{.maxSpeed=50,.minSpeed=30,.earlyExitRange=9},false);
//chassis.turnToPoint(42,-17,1000,{},false);
chassis.moveToPoint(-42,-17,1300,{.maxSpeed=60,.minSpeed=40},false);// 4 ball take this out
chassis.moveToPoint(-41.5,20,1200,{.forwards=false},false);//1200 for 7 500 for 4
intakeOutHigh();
pros::delay(1300);//1300 for 7 600 for 4
if(wingDescore){
    tongue.retract();
    wing.extend();
    chassis.moveToPoint(-52.5,13,1000,{},false);
    wing.retract();
    chassis.turnToPoint(-52.5,35,1000,{.forwards=false},false);
    chassis.moveToPoint(-52.5,35,5000,{.forwards=false,.maxSpeed=50},false);
    chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
}
else{
    chassis.moveToPoint(-41.5,10,300,{},false);
    intakeIn();
    chassis.moveToPoint(-41.5,20,10000,{.forwards=false},false);
}

}
void autoRightElims()
{

intakeIn();
chassis.moveToPoint(14,20,2000,{.minSpeed=40,.earlyExitRange=10},false);
tongue.extend();
pros::delay(50);
chassis.turnToPoint(40,0,300,{},false);
chassis.moveToPoint(40,0,1500,{.minSpeed=30,.earlyExitRange=16},false);
chassis.turnToPoint(40,-17,300,{},false);
//chassis.moveToPoint(40,0,2000,{.minSpeed=40,.earlyExitRange=19},false);
// chassis.moveToPoint(41,0,1700,{},true);
// chassis.waitUntil(33);
// chassis.cancelMotion();
// chassis.moveToPoint(41,0,1700,{.maxSpeed=50,.minSpeed=30,.earlyExitRange=9},false);
//chassis.turnToPoint(42,-17,1000,{},false);
chassis.moveToPoint(40,-17,1300,{.maxSpeed=40,.minSpeed=20},false);
chassis.moveToPoint(39,20,1200,{.forwards=false},false);
intakeOutHigh();
pros::delay(1200);
if(wingDescore){
tongue.retract();
//wing.extend();
chassis.moveToPoint(29,13,1000,{},false);
wing.retract();
chassis.turnToPoint(26.5,35,1000,{.forwards=false},false);
chassis.moveToPoint(29,35,2000,{.forwards=false,.maxSpeed=50},false);
chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
}
else{
chassis.moveToPoint(41.5,10,300,{},false);
intakeIn();
chassis.moveToPoint(41.5,20,10000,{.forwards=false},false);
}


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
        wingDescore=false;
        autoLeftElims();
    }
    if (auton == 6){
        wingDescore=false;
        autoRightElims();
        
    }
    if (auton == 7){
        wingDescore=true;
        autoLeftElims();
    }
    if (auton == 8){
        wingDescore=true;
        autoRightElims();
        
    }
}
