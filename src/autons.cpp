#include "main.h"

pros::adi::AnalogIn pot(8);
int auton = 0;
std::string autoNames[5] = {"no auto ","left   ","right  ","skills ","solo awp "};
void autoPrint(){
    
    pros::lcd::set_text(6, ": " + autoNames[auton]);
    master.set_text(0, 0, autoNames[auton]);
}
void autoSet(int in){//-1 means pot
    
    
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
    
}
void autoSkills(){
    wing.toggle();
    schassis.swingToPoint(42,0,DriveSide::RIGHT,1200,{.maxSpeed=90},false);
    intakeIn();
    schassis.moveToPoint(42,0,800,{},false);
    intakeStop();
    schassis.moveToPoint(42,0,1000,{.maxSpeed=45},false);
    
    schassis.turnToPoint(41,-20,1500,{.maxSpeed=75},false);
    /*tongue.toggle();
    pros::delay(200);
    schassis.moveToPoint(41,-20,2500,{.maxSpeed=45},true);
    pros::delay(500);
    intakeIn();
    pros::delay(2000);
    schassis.moveToPoint(41,8,1000,{.forwards=false},false);
    tongue.toggle();
    */
    schassis.swingToPoint(57,80,DriveSide::LEFT,1500,{.direction=AngularDirection::CCW_COUNTERCLOCKWISE,.maxSpeed=80},false);
    intakeStop();
    schassis.moveToPoint(57,80,1000,{},false);
    schassis.moveToPoint(56,80,1500,{.maxSpeed=30,.minSpeed=1,.earlyExitRange=1},false);
    schassis.moveToPoint(38,87,1500,{.maxSpeed=70},false);
    schassis.turnToPoint(40,75,2000,{.forwards=false,.maxSpeed=90},false);
    /*schassis.moveToPoint(40,75,3700,{.forwards=false,.maxSpeed=50},true);
    
    pros::delay(1700);
    for (int i = 0; i<200; i++){
        intakeOutHigh(false);
        pros::delay(10);
    }
    intakeStop();
    tongue.toggle();
    schassis.moveToPoint(40,110,300,{},false);
    
    schassis.moveToPoint(40,110,2500,{.maxSpeed=50},true);
    pros::delay(500);
    intakeIn();
    pros::delay(2000);
    //intakeStop();
    schassis.moveToPoint(40,87,300,{.forwards=false},false);
    schassis.moveToPoint(40,75,3700,{.forwards=false,.maxSpeed=45},true);
    pros::delay(1700);
    for (int i = 0; i<200; i++){
        intakeOutHigh(false);
        pros::delay(10);
    }
    intakeStop();
    tongue.toggle();
    schassis.moveToPoint(40,87,1000,{.minSpeed=1,.earlyExitRange=1},false);*/
    schassis.moveToPoint(20,108,3000,{.minSpeed=1,.earlyExitRange=1},false);
    intakeIn();
    schassis.moveToPoint(-30,112,10000,{.minSpeed=110,.earlyExitRange=1},false);
    schassis.moveToPoint(-40,90,2000,{},false);
    tongue.toggle();
    schassis.turnToHeading(270,2000,{},false);
    intakeStop();
    schassis.turnToHeading(270,2000,{},false);
    //pros::delay(500);
    for(int i = 0; i<=100; i++){
        pros::lcd::set_text(3, std::to_string(distance_sensor_front.get()/25.4));
        pros::lcd::set_text(4, std::to_string(distance_sensor_front.get_confidence()));
        pros::delay(10);
    }
    //distanceSensorReset();
    
    pros::lcd::set_text(0, "sX: " + std::to_string(schassis.getPose().x));
		pros::lcd::set_text(1, "sY: " + std::to_string(schassis.getPose().y));
		pros::lcd::set_text(2, "sO: " + std::to_string(schassis.getPose().theta));
        pros::lcd::set_text(5, std::to_string(distance_sensor_front.get_confidence()));
         tongue.toggle();
        schassis.moveToPoint(21,-17.3,3000,{},false);
        schassis.turnToPoint(22,-32,3000,{.forwards=false},false);
        schassis.moveToPoint(22,-32,3000,{.forwards=false,.maxSpeed=50},false);
        
        pros::delay(99999);
   

    schassis.turnToPoint(-56,87,1500,{.maxSpeed=80},false);
    schassis.moveToPoint(-56,87,4000,{},true);
    schassis.waitUntil(72);
    schassis.cancelMotion();
    schassis.moveToPoint(-56,87,1000,{.maxSpeed=40},false);
    schassis.turnToPoint(-55,110,1500,{.maxSpeed=90},false);
    tongue.toggle();
    pros::delay(200);
    schassis.moveToPoint(-55,110,300,{},false);
    schassis.moveToPoint(-55,110,2500,{.maxSpeed=50},true);
    pros::delay(500);
    intakeIn();
    pros::delay(2000);
    schassis.moveToPoint(-68,87,1500,{.forwards=false},false);
    intakeStop();
    tongue.toggle();
    pros::delay(300);
    schassis.turnToPoint(-68,15,1500,{.maxSpeed=80},false);
    schassis.moveToPoint(-68,15,1100,{},false);
    schassis.moveToPoint(-68,15,1500,{.maxSpeed=30,.minSpeed=1,.earlyExitRange=1},false);
    schassis.moveToPoint(-53,8,2000,{.maxSpeed=70},false);
    schassis.turnToPoint(-55.2,20,1200,{.forwards=false},false);
    schassis.moveToPoint(-55.2,20,3700,{.forwards=false,.maxSpeed=45},true);
    pros::delay(1700);
    for (int i = 0; i<200; i++){
        intakeOutHigh(false);
        pros::delay(10);
    }
    intakeStop();
    

    schassis.moveToPoint(-54,-20,300,{},false);
    tongue.toggle();
    schassis.moveToPoint(-54,-20,2500,{.maxSpeed=45},true);
    pros::delay(500);
    intakeIn();
    pros::delay(2000);
    //intakeStop();


    schassis.moveToPoint(-54,20,300,{.forwards=false},false);
    schassis.moveToPoint(-54,20,3700,{.forwards=false,.maxSpeed=45},true);
    pros::delay(1700);
    for (int i = 0; i<200; i++){
        intakeOutHigh(false);
        pros::delay(10);
    }
    intakeStop();
    tongue.toggle();
    schassis.moveToPoint(-40,-7,2000,{.minSpeed=1,.earlyExitRange=1},false);
    intakeOutLow(false);
    schassis.moveToPoint(-5,-12,10000,{.minSpeed=110},false);
    intakeIn();
    schassis.moveToPoint(-5,40,10000,{.minSpeed=110},false);
    
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
