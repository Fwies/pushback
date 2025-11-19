#include "main.h"

pros::adi::AnalogIn pot(8);
int auton = 0;
std::string autoNames[5] = {"no auto ","left   ","right  ","skills ","solo awp "};
void autoPrint(){
    //master.clear_line(0);
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
    wing.toggle();
    chassis.moveToPoint(-11,11,2000,{.minSpeed=1,.earlyExitRange=1},false);//140
    
    intakeIn();
    chassis.moveToPoint(-22,27,2000,{.maxSpeed=25,.minSpeed=25,.earlyExitRange=1},false);//140
    chassis.turnToPoint(-34,29,1000,{.maxSpeed=100},false);
    chassis.moveToPoint(-34,29,2000,{.maxSpeed=80,.minSpeed=30},false);//140
    
    intakeStop();
    //chassis.turnToPoint(29,27,2500,{},false);
    //chassis.moveToPoint(29,27,2500,{},false);
    //chassis.turnToHeading(62,2500,{.maxSpeed=60},false);
    chassis.turnToPoint(-39,36,2500,{},false);
    intakeIn();
    /*chassis.moveToPoint(39,36,3000,{},true);
    chassis.waitUntil(1);
    chassis.cancelMotion();*/
    chassis.moveToPoint(-38,37,3000,{.maxSpeed=20,.minSpeed=20},false);
    
    chassis.moveToPoint(-19,25,1500,{.forwards=false},true);//16,16
    pros::delay(300);
    intakeStop();
    chassis.waitUntilDone();
    
    chassis.turnToPoint(-9,30,1800,{.forwards=false,.maxSpeed=90},false);//
    chassis.moveToPoint(-9,30,1800,{.forwards=false,.maxSpeed=100},false);//going into goal
    intakeOutMid(true);
    
    

    
    pros::delay(1100);
     intakeIn();
     pros::delay(100);
     
     chassis.moveToPoint(-43,-3,2500,{},true);
     chassis.waitUntil(10);
     intakeStop();
     chassis.waitUntil(32);
     chassis.cancelMotion();
    chassis.moveToPoint(-43,-3,2500,{.maxSpeed=30},false);
    chassis.turnToPoint(-43,-24,2500,{.maxSpeed=70},false);
    tongue.toggle();
    pros::delay(400);
    chassis.moveToPoint(-43,-24,1000,{.maxSpeed=50},true);
    pros::delay(500);
    intakeIn();
    pros::delay(500);
    chassis.waitUntilDone();
    
    chassis.moveToPoint(-42,20,1200,{.forwards=false,.maxSpeed=65},false);
    //chassis.turnToHeading(180,{});
    
    while(true){
        intakeOutHigh(false);
        pros::delay(10);
    }



}
void autoRight(){
    
    chassis.moveToPoint(11,11,2000,{.minSpeed=1,.earlyExitRange=1},false);//140
    
    intakeIn();
    chassis.moveToPoint(22,27,2000,{.maxSpeed=25,.minSpeed=25,.earlyExitRange=1},false);//140
    chassis.turnToPoint(34,29,1000,{.maxSpeed=100},false);
    chassis.moveToPoint(34,29,2000,{.maxSpeed=80,.minSpeed=30},false);//140
    
    intakeStop();
    //chassis.turnToPoint(29,27,2500,{},false);
    //chassis.moveToPoint(29,27,2500,{},false);
    //chassis.turnToHeading(62,2500,{.maxSpeed=60},false);
    chassis.turnToPoint(39,36,2500,{},false);
    intakeIn();
    /*chassis.moveToPoint(39,36,3000,{},true);
    chassis.waitUntil(1);
    chassis.cancelMotion();*/
    chassis.moveToPoint(38,36,3000,{.maxSpeed=20,.minSpeed=20},false);
    
    chassis.moveToPoint(18,25,1500,{.forwards=false},true);//16,16
    pros::delay(300);
    intakeStop();
    chassis.waitUntilDone();
    
    chassis.turnToPoint(6.5,33.5,1800,{.maxSpeed=90},false);//
    chassis.moveToPoint(6.5,33.5,1800,{.maxSpeed=100},false);//going into goal
    intakeOutLow(false);
    pros::delay(100);
    I1.move_velocity(-200);
        I2.move_velocity(-100);
    I3.move_velocity(0);

    
    pros::delay(1100);
     intakeIn();
     pros::delay(100);
     
     chassis.moveToPoint(40,-3,2500,{.forwards=false},true);
     chassis.waitUntil(10);
     intakeStop();
     chassis.waitUntil(22);
     chassis.cancelMotion();
    chassis.moveToPoint(40,-3,2500,{.forwards=false,.maxSpeed=30},false);
    chassis.turnToPoint(40,-24,2500,{.maxSpeed=70},false);
    tongue.toggle();
    pros::delay(400);
    chassis.moveToPoint(40,-24,1000,{.maxSpeed=50},true);
    pros::delay(500);
    intakeIn();
    pros::delay(500);
    chassis.waitUntilDone();
    
    chassis.moveToPoint(40,20,1200,{.forwards=false,.maxSpeed=65},false);
    //chassis.turnToHeading(180,{});
    
    while(true){
        intakeOutHigh(false);
        pros::delay(10);
    }


    
    
    
    
    
    //tongue.toggle();
     
}
void autoSkills(){

    schassis.swingToPoint(42,0,DriveSide::RIGHT,1200,{.maxSpeed=90},false);
    intakeIn();
    schassis.moveToPoint(42,0,800,{},false);
    intakeStop();
    schassis.moveToPoint(42,0,1000,{.maxSpeed=45},false);
    
    schassis.turnToPoint(41,-20,1500,{.maxSpeed=75},false);
    tongue.toggle();
    pros::delay(200);
    schassis.moveToPoint(41,-20,2500,{.maxSpeed=45},true);
    pros::delay(500);
    intakeIn();
    pros::delay(2000);
    schassis.moveToPoint(41,8,1000,{.forwards=false},false);
    tongue.toggle();
    
    schassis.swingToPoint(57,80,DriveSide::LEFT,1500,{.direction=AngularDirection::CCW_COUNTERCLOCKWISE,.maxSpeed=80},false);
    intakeStop();
    schassis.moveToPoint(57,80,1000,{},false);
    schassis.moveToPoint(56,80,1500,{.maxSpeed=30,.minSpeed=1,.earlyExitRange=1},false);
    schassis.moveToPoint(38,87,1500,{.maxSpeed=70},false);
    schassis.turnToPoint(40,75,2000,{.forwards=false,.maxSpeed=90},false);
    schassis.moveToPoint(40,75,3700,{.forwards=false,.maxSpeed=50},true);
    
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
    schassis.moveToPoint(40,87,1000,{},false);
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
    intakeIn();
    pros::delay(100);
    intakeStop();
    chassis.setPose(0,0,90,false);
    chassis.moveToPoint(24.5,3,1000,{},false);
    tongue.toggle();
    intakeIn();
    chassis.turnToPoint(27,-15,2000,{},false);
    chassis.moveToPoint(27,-15,1000,{.maxSpeed=45,.earlyExitRange=30},false);
    chassis.moveToPoint(24.5,24,1000,{.forwards=false},false);
    for (int i = 0; i<100; i++){
        intakeOutHigh(false);
        pros::delay(10);
    }
    tongue.toggle();
    chassis.moveToPoint(26,12,2000,{.minSpeed=30,.earlyExitRange=10},false);
    intakeStop();
     chassis.turnToPoint(0,27,2000,{},false);
    intakeIn();
    chassis.moveToPoint(3,28,2000,{.minSpeed=10,.earlyExitRange=3},false);
    chassis.moveToPoint(-30,33,2000,{.minSpeed=10,.earlyExitRange=3},false);
    chassis.moveToPoint(-40,24,2000,{.maxSpeed=60,.earlyExitRange=3},false);
chassis.waitUntilDone();
     intakeStop();
     chassis.moveToPoint(-25.5,41,1000,{.forwards=false,.maxSpeed=50,.earlyExitRange=3},false);
for (int i = 0; i<500; i++){
        intakeOutMid(false);
        pros::delay(10);
    }

chassis.moveToPoint(-60,0,1000,{.forwards=false,.maxSpeed=50,.earlyExitRange=3},false);
chassis.turnToPoint(-80,-15,2000,{},false);
chassis.moveToPoint(-80,-15,2000,{},false);


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
