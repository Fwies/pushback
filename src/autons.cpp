#include "main.h"

pros::adi::AnalogIn pot('a');
int auton = 0;
std::string autoNames[9] = {"no auto","left split","right split","skills","solo awp", "no wing left 7 ball", "no wing right 7 ball", "wing left 7 ball", "wing right 7 ball"};
void autoPrint(){
    pros::lcd::set_text(7, "auto: " + autoNames[auton]);
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
    

    chassis.setPose(0,0,270,false);
    wing.extend();
    intakeIn();
     //master.set_text(0, 0, std::to_string(chassis.getPose().theta));
    chassis.moveToPoint(-53,0,4000,{.maxSpeed=65,.minSpeed=65},false);
    master.set_text(0, 0, std::to_string(chassis.getPose().theta));
    
    chassis.turnToHeading(270,1000,{},false);
    chassis.waitUntilDone();
    
    distanceSensorReset(DS::FRONT,DS::LEFT, 270, 1, 1);
    

    

    chassis.turnToPoint(36,36,1000,{},false);
    chassis.moveToPoint(36,36,2000,{},false);
    chassis.turnToPoint(41,41,500,{},false);
    chassis.moveToPoint(41,41,1000,{},false);
    intakeIn();
    chassis.turnToHeading(315,1000,{.minSpeed=30,.earlyExitRange=10},false);
    intakeIn();
    chassis.turnToPoint(61,61,2000,{.forwards=false},false);
    chassis.waitUntilDone();
    chassis.moveToPoint(61,61,500,{.forwards=false},false);
    chassis.moveToPoint(61,61,500,{.forwards=false,.maxSpeed=40},false);
    leftDrive.move_voltage(-1000);
    rightDrive.move_voltage(-1000);
    intakeOutMid(true);
     int x = 0;
    while(x<8){
       
            I1.move_velocity(600);
            I2.move_velocity(100);
            pros::delay(200);
            I1.move_velocity(200);
            I2.move_velocity(200);
            pros::delay(200);

            x++;
           
    }
    
    //pros::delay(3300);
    tongue.extend();
    chassis.moveToPoint(22,32,2000,{},false);
    intakeIn();
    chassis.turnToPoint(22,4,1000,{},false);
    chassis.moveToPoint(22,4,2300,{.maxSpeed=50},false);
    
    chassis.moveToPoint(11,46,1500,{.forwards=false,.minSpeed=20,.earlyExitRange=6},false);
    
    tongue.retract();
    chassis.turnToPoint(11,112,200,{.forwards=false},false);//115
    chassis.moveToPoint(11,112,3000,{.forwards=false},false);
    chassis.turnToHeading(270,1000,{},false);
    double saveY = chassis.getPose().y;
    distanceSensorReset(DS::FRONT, DS::LEFT, 270, 1, 1);
    chassis.setPose(chassis.getPose().x, saveY, chassis.getPose().theta,false);
    
    chassis.moveToPoint(23,saveY,1000,{.forwards=false},false);
    
    chassis.turnToPoint(23,96,1000,{.forwards=false},false);

    
    chassis.moveToPoint(23,96,1500,{.forwards=false},true);
    //chassis.moveToPose(23,96,0,1500,{.forwards=false,.horizontalDrift=5},true);
    
    pros::delay(500);
    intakeOutHigh(1500);
    chassis.setPose(23,chassis.getPose().y,chassis.getPose().theta,false);
    intakeIn();
    tongue.extend();
    chassis.moveToPoint(23,140,500,{},false);
    chassis.moveToPoint(23,140,2000,{.maxSpeed=50},false);
   
    chassis.moveToPoint(23,96,500,{.forwards=false},false);

    chassis.moveToPoint(23,96,1000,{.forwards=false,.maxSpeed=60},true);
    pros::delay(300);
    intakeOutHigh(1500);
    intakeStop();
    tongue.retract();
    //chassis.moveToPoint(24,115,3000,{.minSpeed=30,.earlyExitRange=4},false);
    chassis.moveToPoint(46,134,3000,{},false);
    chassis.swingToHeading(90,DriveSide::RIGHT,1000,{},false);
    intakeIn();
    chassis.moveToPoint(103,138,5000,{.maxSpeed=65,.minSpeed=65},false);
    chassis.turnToHeading(90,1000,{},false);
    chassis.waitUntilDone();
    distanceSensorReset(DS::FRONT, DS::LEFT, 90, -1, -1);
    chassis.turnToPoint(-66,-30,1000,{.forwards=false},false);
    chassis.moveToPoint(-66,-30,2000,{.forwards=false,.minSpeed=20,.earlyExitRange=4},false);

    chassis.turnToPoint(-108,-36,250,{.forwards=false},false);
    chassis.moveToPoint(-108,-36,3000,{.forwards=false},false);
    chassis.turnToPoint(-101,-44,1000,{},false);
    chassis.moveToPoint(-101,-44,1000,{},false);
    intakeStop();
    chassis.turnToHeading(230,1000,{.minSpeed=20,.earlyExitRange=5},false);
    chassis.turnToPoint(-82,-64,1000,{},false);
    tongue.extend();
    chassis.moveToPoint(-82,-64,400,{},false);
    tongue.retract();
    chassis.moveToPoint(-82,-64,800,{.maxSpeed=50},false);
    x=0;
    while(x<400){
        
        intakeOutLow(true);
        x++;
        pros::delay(10);
    }
    chassis.swingToPoint(-24,-27,DriveSide::LEFT,1000,{.forwards=false, .direction = AngularDirection::CW_CLOCKWISE,.minSpeed=20,.earlyExitRange=10},false);
    intakeStop();
    chassis.moveToPoint(-24,-27,3000,{.forwards=false},false);
    chassis.turnToHeading(315,1000,{.minSpeed=30,.earlyExitRange=10},false);
    tongue.extend();
    chassis.turnToPoint(-24,0,1000,{},false);
    chassis.moveToPoint(-24,0,300,{},false);
    intakeIn();
    chassis.moveToPoint(-24,0,2000,{.maxSpeed=50},false);
   
     chassis.moveToPoint(-9,-46,1500,{.forwards=false,.minSpeed=20,.earlyExitRange=6},false);
    
    tongue.retract();
    chassis.turnToPoint(-9,-109,200,{.forwards=false},false);
    chassis.moveToPoint(-9,-109,3000,{.forwards=false},false);
    chassis.turnToHeading(90,1000,{},false);
    saveY = chassis.getPose().y;
    distanceSensorReset(DS::FRONT, DS::LEFT, 90, -1, 1);
    chassis.setPose(chassis.getPose().x, saveY, chassis.getPose().theta,false);
    
    chassis.moveToPoint(-25,saveY,1000,{.forwards=false},false);
    //chassis.moveToPoint(-25,-112,1000,{.forwards=false},false);
    //chassis.turnToHeading(180,300,{},false);
    //chassis.swingToHeading(0,DriveSide::LEFT,2000,{.direction = AngularDirection::CW_CLOCKWISE , .maxSpeed=60},false);
    chassis.turnToPoint(-25,-96,1000,{.forwards=false},false);
    chassis.moveToPoint(-25,-96,1500,{.forwards=false},true);
    
    pros::delay(500);
    intakeOutHigh(1500);
    chassis.setPose(-25,chassis.getPose().y,chassis.getPose().theta,false);
    intakeIn();
    tongue.extend();
    chassis.moveToPoint(-25,-137,500,{},false);
    chassis.moveToPoint(-25,-137,2000,{.maxSpeed=50},false);
   
    chassis.moveToPoint(-25,-96,500,{.forwards=false},false);

    chassis.moveToPoint(-25,-96,1000,{.forwards=false,.maxSpeed=60},true);
    pros::delay(300);
    intakeOutHigh(1500);
    intakeStop();
    tongue.retract();
    chassis.swingToPoint(-72,-115, DriveSide::RIGHT,2500,{.minSpeed=20,.earlyExitRange=5},false);
    chassis.moveToPoint(-72,-115,2500,{},false);
    chassis.turnToPoint(-72,-145,1000,{},false);
    chassis.moveToPoint(-72,-145,4000,{.minSpeed=127},false);

    
    
   
    
    


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
    /*chassis.moveToPoint(39,0,2000,{.forwards=false},true);
    chassis.waitUntil(35);
    chassis.cancelMotion();*/
    chassis.moveToPoint(39,0,2000,{.forwards=false},false);
    tongue.extend();
    chassis.turnToPoint(38,-13,850,{},false);
    
    //pros::delay(200);
    chassis.moveToPoint(38,-13,1000,{.maxSpeed=50},false);
    chassis.moveToPoint(40,21,700,{.forwards=false},false);
    chassis.moveToPoint(40,21,200,{.forwards=false,.maxSpeed=50},false);
     tongue.retract();
    intakeOutHigh(900);
   
    
    
    //chassis.swingToPoint(21,25,DriveSide::RIGHT,1000,{},false);
    chassis.turnToPoint(15,26,800,{.minSpeed=5,.earlyExitRange=3},false);
    intakeIn();
    chassis.moveToPoint(15,26,2000,{},true);
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
    chassis.moveToPoint(-18.4,36,600,{.forwards=false},false);

    intakeOutMid(true);
    chassis.turnToHeading(225,500,{},false);
    
    pros::delay(600);
    intakeIn();
    chassis.moveToPoint(-58,5,3000,{},false);//-53
    /*chassis.waitUntil(36);
    chassis.cancelMotion();
    chassis.moveToPoint(-58,5,3000,{.maxSpeed=40},false);*/
    
    
    
    //tongue.extend();
    chassis.turnToPoint(-58,-14,700,{},false);
    
    chassis.moveToPoint(-58,-14,600,{.maxSpeed=60},false);
    leftDrive.move_voltage(500);
    rightDrive.move_voltage(500);
    pros::delay(500);
    
    chassis.moveToPoint(-58,23,1500,{.forwards=false},true);
    pros::delay(650);
    intakeOutHigh(1000);
    tongue.retract();
    chassis.moveToPoint(-70,20,1000,{},false);
    chassis.turnToPoint(-70,45,1000,{.forwards=false},false);
    chassis.moveToPoint(-70,45,2000,{.forwards=false},false);
    
    //pros::delay(1500);
    //chassis.moveToPoint(-58,0,1000,{},false);
    
    

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
chassis.turnToPoint(-43,-17,300,{},false);
//chassis.moveToPoint(40,0,2000,{.minSpeed=40,.earlyExitRange=19},false);
// chassis.moveToPoint(41,0,1700,{},true);
// chassis.waitUntil(33);
// chassis.cancelMotion();
// chassis.moveToPoint(41,0,1700,{.maxSpeed=50,.minSpeed=30,.earlyExitRange=9},false);
//chassis.turnToPoint(42,-17,1000,{},false);
chassis.moveToPoint(-42.8,-17,1300,{.maxSpeed=60,.minSpeed=40},false);// 4 ball take this out
chassis.moveToPoint(-42.8,22,1750,{.forwards=false},false);//1200 for 7 500 for 4
intakeOutHigh();
pros::delay(1300);//1300 for 7 600 for 4
if(wingDescore){
    tongue.retract();
    wing.extend();
    chassis.moveToPoint(-52.5,13,1000,{},false);
    wing.retract();
    chassis.turnToPoint(-52.5,35,1000,{.forwards=false},false);
    chassis.moveToPoint(-52.8,34,5000,{.forwards=false,.maxSpeed=80},false);//5035
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
pros::delay(60);
chassis.turnToPoint(40,0,300,{},false);
chassis.moveToPoint(40,0,1900,{.minSpeed=30,.earlyExitRange=14},false);
chassis.turnToPoint(40,-24,300,{},false);
//chassis.moveToPoint(40,0,2000,{.minSpeed=40,.earlyExitRange=19},false);
// chassis.moveToPoint(41,0,1700,{},true);
// chassis.waitUntil(33);
// chassis.cancelMotion();
// chassis.moveToPoint(41,0,1700,{.maxSpeed=50,.minSpeed=30,.earlyExitRange=9},false);
//chassis.turnToPoint(42,-17,1000,{},false);
chassis.moveToPoint(40,-24,1500,{},true);
chassis.waitUntil(6);
chassis.cancelMotion();
chassis.moveToPoint(40,-24,1000,{.maxSpeed=60,.minSpeed=60},false);
chassis.moveToPoint(40,20,1200,{.forwards=false},false);
intakeOutHigh();
pros::delay(1200);
if(wingDescore){
tongue.retract();
//wing.extend();
chassis.moveToPoint(29,13,1500,{},false);
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
