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
    chassis.moveToPoint(-22,25.5,2000,{},true);//140
    chassis.waitUntil(7);
    chassis.cancelMotion();
    intakeIn();
    chassis.moveToPoint(-22,25.5,2000,{.maxSpeed=30,.minSpeed=30,.earlyExitRange=3},false);//140
    
    chassis.moveToPoint(-27,29,2000,{.maxSpeed=35,.minSpeed=35,.earlyExitRange=3},false);//140
    /*chassis.moveToPoint(17.5,26.2,2000,{.forwards=false,.earlyExitRange=3},true);
    chassis.turnToPoint(0,40,1500,{.maxSpeed=120},false);//
    chassis.moveToPoint(0,40,1500,{.maxSpeed=120},false);//
    intakeOutLow(true);
    pros::delay(1300);
    chassis.moveToPoint(17.5,24.2,2000,{.forwards=false,.earlyExitRange=3},false);
    intakeStop();
    */
    chassis.turnToPoint(-42,36,2500,{},false);
    intakeIn();
    chassis.moveToPoint(-42,36,3000,{},true);
    chassis.waitUntil(1);
    chassis.cancelMotion();
    chassis.moveToPoint(-42,36,3000,{.maxSpeed=20,.minSpeed=20,.earlyExitRange=4},false);
    //tongue.toggle();
    //pros::delay(350);
    //chassis.swingToHeading(76,DriveSide::RIGHT,500,{},false);
    
    chassis.moveToPoint(-18,25,1500,{.forwards=false},true);//16,16
    pros::delay(300);
    intakeStop();
    chassis.waitUntilDone();
    //chassis.turnToHeading(45,1000,{},false);
    
    //pros::delay(300);
    //chassis.turnToHeading(45,1000,{},false);
    chassis.turnToPoint(-10,28,1500,{.forwards=false,},true);//turns to the goal
    
    //tongue.toggle();
    //pros::delay(300);
    //chassis.moveToPose(19,19,315,1500,{},true);
    //chassis.waitUntil(200);
    
    
    chassis.waitUntilDone();
    
    //chassis.turnToHeading(chassis.getPose().theta-18,600,{.earlyExitRange=5},false); //wigglywobllywigglywobblywhoeo
    //chassis.waitUntilDone();
    
    //pros::delay(30000);
    //chassis.turnToPoint(5.1,27.1,1800,{},false);
    chassis.moveToPoint(-10,28,1800,{.forwards=false,.maxSpeed=60},false);//going into goal
    intakeOutMid(true);
    //I3.move_velocity(600);

    
    pros::delay(700);
     intakeStop();
     pros::delay(150);
     
     chassis.moveToPoint(-46,-5,2500,{},true);
     chassis.waitUntil(32);
     chassis.cancelMotion();
    chassis.moveToPoint(-46,-5,2500,{.maxSpeed=30},false);
    tongue.toggle();
    chassis.turnToPoint(-46,-24,2500,{.maxSpeed=70},false);
    //tongue.toggle();
    //pros::delay(400);
    chassis.moveToPoint(-46,-24,1300,{.maxSpeed=45},true);
    pros::delay(500);
    intakeIn();
    
    pros::delay(800);
    chassis.cancelMotion();
    
    chassis.moveToPoint(-45,11,1200,{.forwards=false,.maxSpeed=90},false);
    
    setHood(true);
    I3.move_velocity(600);
    I2.move_velocity(-300);
    I1.move_velocity(-300);
    pros::delay(200);
    intakeOutHigh(true);


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
     /*chassis.setPose(0,0,180,{false});
     I3.move_velocity(10);
    chassis.moveToPoint(-8,34,3000,{.forwards=false},false);//140
    chassis.turnToHeading(142,3000,{},false);*/
    //chassis.moveToPose(142,2000,{},false);//140
     //intakeOutHigh(true);
    //setHood(true);
     
     //pros::delay(600);
     //intakeStop();
     //intakeIn();
     //chassis.moveToPoint(2,14,2000,{.earlyExitRange=3},false);//140
    
    chassis.moveToPoint(22,27,2000,{},true);//140
    chassis.waitUntil(7);
    chassis.cancelMotion();
    intakeIn();
    chassis.moveToPoint(22,27,2000,{.maxSpeed=25,.minSpeed=25,.earlyExitRange=3},false);//140
    
    chassis.moveToPoint(27,31,2000,{.maxSpeed=30,.minSpeed=30},false);//140
    /*chassis.moveToPoint(17.5,26.2,2000,{.forwards=false,.earlyExitRange=3},true);
    chassis.turnToPoint(0,40,1500,{.maxSpeed=120},false);//
    chassis.moveToPoint(0,40,1500,{.maxSpeed=120},false);//
    intakeOutLow(true);
    pros::delay(1300);
    chassis.moveToPoint(17.5,24.2,2000,{.forwards=false,.earlyExitRange=3},false);
    intakeStop();
    */
    intakeStop();
    //chassis.turnToPoint(29,27,2500,{},false);
    //chassis.moveToPoint(29,27,2500,{},false);
    //chassis.turnToHeading(62,2500,{.maxSpeed=60},false);
    chassis.turnToPoint(38,34,2500,{},false);
    intakeIn();
    chassis.moveToPoint(38,34,3000,{},true);
    chassis.waitUntil(1);
    chassis.cancelMotion();
    chassis.moveToPoint(38,34,3000,{.maxSpeed=20,.minSpeed=20,},false);
    //tongue.toggle();
    //pros::delay(350);
    //chassis.swingToHeading(76,DriveSide::RIGHT,500,{},false);
    
    chassis.moveToPoint(18,23.5,1500,{.forwards=false},true);//16,16
    pros::delay(300);
    intakeStop();
    chassis.waitUntilDone();
    //chassis.turnToHeading(45,1000,{},false);
    
    //pros::delay(300);
    //chassis.turnToHeading(45,1000,{},false);
    //chassis.swingToPoint(7,32,DriveSide::LEFT,1500,{.maxSpeed=60},true);//turns to the goal
    //tongue.toggle();
    //pros::delay(300);
    //chassis.moveToPose(19,19,315,1500,{},true);
    //chassis.waitUntil(200);*/
    
    
    
    
    //chassis.turnToHeading(chassis.getPose().theta-18,600,{.earlyExitRange=5},false); //wigglywobllywigglywobblywhoeo
    //chassis.waitUntilDone();
    
    //pros::delay(30000);
    //chassis.turnToPoint(5.1,27.1,1800,{},false);
    chassis.turnToPoint(4,31.5,1800,{.maxSpeed=100},false);//
    chassis.moveToPoint(4,31.5,1800,{.maxSpeed=60},false);//going into goal
    intakeOutLow(false);
    pros::delay(100);
    I1.move_velocity(-200);
        I2.move_velocity(-100);
    I3.move_velocity(0);

    
    pros::delay(1100);
     intakeIn();
     pros::delay(100);
     intakeStop();
     chassis.moveToPoint(40,-3,2500,{.forwards=false},true);
     chassis.waitUntil(32);
     chassis.cancelMotion();
    chassis.moveToPoint(40,-3,2500,{.forwards=false,.maxSpeed=30},false);
    chassis.turnToPoint(40,-24,2500,{.maxSpeed=70},false);
    tongue.toggle();
    pros::delay(400);
    chassis.moveToPoint(40,-24,1400,{.maxSpeed=50},true);
    pros::delay(500);
    intakeIn();
    pros::delay(900);
    chassis.waitUntilDone();
    
    chassis.moveToPoint(41,10,1200,{.forwards=false,.maxSpeed=90},false);
    //chassis.turnToHeading(180,{});
    
    intakeOutHighAuto();


    
    
    
    
    
    //tongue.toggle();
     
}
void autoSkills(){
    schassis.moveToPoint(25,26,2000,{.maxSpeed=80},true);//140
    schassis.waitUntil(7);
    schassis.cancelMotion();
    intakeIn();
    schassis.moveToPoint(25,26,2500,{.maxSpeed=25,.minSpeed=25,.earlyExitRange=7},false);//140
    schassis.moveToPoint(25,37,2500,{.maxSpeed=30,.minSpeed=30},false);
    //schassis.swingToHeading(315,DriveSide::LEFT,1500,{.maxSpeed=70},false);
    //schassis.moveToPoint(32,34,4000,{.maxSpeed=35,.minSpeed=35},false);//140
    intakeStop();
    schassis.turnToPoint(16,22,1500,{.forwards=false,.maxSpeed=70},false);
    schassis.moveToPoint(16,22,1500,{.forwards=false},false);
    //schassis.turnToPoint(3.5,34.5,1200,{.maxSpeed=80},false);
    //schassis.moveToPoint(3.5,34.5,2500,{.maxSpeed=60},false);
    //schassis.turnToHeading(315,1000,{},true);
    //intakeOutLow(true);
    //pros::delay(2300);
    //intakeStop();
    schassis.turnToPoint(38,8,1500,{.forwards=false,.maxSpeed=70},true);
    schassis.moveToPoint(38,8,1500,{.forwards=false},true);
    schassis.waitUntil(30);
    schassis.cancelMotion();
    schassis.moveToPoint(38,8,1500,{.forwards=false,.maxSpeed=50},false);
    schassis.turnToPoint(40,20,1900,{.forwards=false,.maxSpeed=80},false);
    schassis.moveToPoint(40,20,3000,{.forwards=false,.maxSpeed=50},true);
    pros::delay(1500);
    intakeOutHighAuto();
    pros::delay(2000);

    
    tongue.toggle();
    pros::delay(600);
    schassis.moveToPoint(40,-20,3000,{.maxSpeed=50},true);
    pros::delay(900);
    intakeIn();
    pros::delay(2300);
    intakeStop();
    schassis.moveToPoint(40,20,3000,{.forwards=false,.maxSpeed=50},true);
    pros::delay(1500);
    intakeOutHighAuto();
    pros::delay(2000);
    tongue.toggle();
    //intakeStop();
    intakeOutLow(false);
    
    schassis.moveToPoint(40,0,2000,{},false);
    setHood(false);
    intakeStop();
    schassis.turnToPoint(28,12,2000,{.maxSpeed=70},false);
    schassis.moveToPoint(28,12,1000,{.minSpeed=1,.earlyExitRange=1},false);
    // schassis.moveToPoint(30,55,3000,{},false);
    // schassis.turnToPoint(4,89,3000,{},false);
    // intakeIn();
    // //schassis.moveToPoint(4,84,3000,{},false);
    // schassis.moveToPoint(4,89,2500,{.maxSpeed=25,.minSpeed=25,.earlyExitRange=9},false);
    // schassis.moveToPoint(8,87,2500,{.maxSpeed=30,.minSpeed=30},false);
    // intakeStop();

    
    /*schassis.moveToPoint(12,65,2000,{.forwards=false},false);
    schassis.turnToPoint(5.5,59,1500,{.forwards=false},false);
    schassis.moveToPoint(5.5,59,1500,{.forwards=false},false);
    schassis.turnToHeading(45,1000,{},true);*/
    //intakeOutMid(true);
    //pros::delay(2500);
    //intakeStop();
    //intakeOutLow(true);
    schassis.moveToPoint(28,80,1800,{},true);
    schassis.waitUntil(36);
    schassis.cancelMotion();
    schassis.moveToPoint(28,80,1800,{.maxSpeed=50},false);

    schassis.moveToPoint(40,85,1800,{},false);
    intakeOutLow(false);
    tongue.toggle();
     schassis.turnToPoint(40,110,2000,{.maxSpeed=70},false);

    pros::delay(400);
    schassis.moveToPoint(40,110,2000,{.maxSpeed=50},true);
    pros::delay(500);
    intakeIn();
    pros::delay(2300);
    intakeStop();
    
     schassis.moveToPoint(40,75,1800,{.forwards=false,.maxSpeed=50},true);
     //schassis.turnToHeading(0,1000);
    pros::delay(1500);
    intakeOutHighAuto();
    pros::delay(2000);
    tongue.toggle();
    intakeOutLow(false);
    schassis.moveToPoint(40,83,3000,{},false);
    intakeStop();


    schassis.turnToPoint(-23,84,1400,{.maxSpeed=80},false);
    schassis.moveToPoint(-23,84,1500,{},true);
    schassis.waitUntil(36);
    schassis.cancelMotion();
    schassis.moveToPoint(-23,84,1500,{.maxSpeed=50},false);
    intakeIn();
    schassis.turnToPoint(-32,69,1000,{},false);
    schassis.moveToPoint(-32,69,2500,{.maxSpeed=25,.minSpeed=25,.earlyExitRange=4},false);
    schassis.moveToPoint(-36,55,2500,{.maxSpeed=30,.minSpeed=30},false);
    intakeStop();
    schassis.moveToPoint(-31,68,1500,{.forwards=false,.maxSpeed=60},false);
    schassis.turnToPoint(-51,90,1500,{.forwards=false},false);
    schassis.moveToPoint(-51,90,1500,{.forwards=false},true);
    schassis.waitUntil(24);
    schassis.cancelMotion();
    schassis.moveToPoint(-51,90,1500,{.forwards=false,.maxSpeed=50},false);
    schassis.turnToPoint(-54,70,1500,{.forwards=false,.maxSpeed=60},false);
    schassis.moveToPoint(-54,70,1700,{.forwards=false,.maxSpeed=50},true);
    pros::delay(1700);
    intakeOutHighAuto();
    pros::delay(2000);
    //intakeOutLow(true);

    //schassis.turnToPoint(-54,107,1900,{.maxSpeed=70},false);
    tongue.toggle();
    
    pros::delay(400);
    intakeStop();
    schassis.moveToPoint(-51,110,2000,{.maxSpeed=50},true);
    pros::delay(800);
    intakeIn();
    pros::delay(2300);
    intakeStop();
    schassis.moveToPoint(-54,71,1500,{.forwards=false,.maxSpeed=50},true);
    pros::delay(1500);
    intakeOutHighAuto();
    pros::delay(2000);
    tongue.toggle();
    intakeOutLow(false);
    pros::delay(200);
    
    intakeOutLow(false);
    schassis.moveToPoint(-51,95,1500,{},false);
    intakeStop();
    setHood(false);
    schassis.turnToPoint(-45,75,3000,{.maxSpeed=70},false);
    schassis.moveToPoint(-45,75,3000,{},false);
    intakeIn();
    schassis.moveToPoint(-47,28,3000,{.minSpeed=1,.earlyExitRange=1},false);
    
    schassis.moveToPoint(-41,-10,2300,{},true);
    schassis.waitUntil(20);
    setHood(true);
    schassis.waitUntilDone();
    //double y = schassis.getPose().y;
    //schassis.setPose(schassis.getPose().x,schassis.getPose().y,180,false);
    schassis.turnToPoint(-15,-20,1000,{},false);
    intakeOutLow(false);
    //schassis.moveToPoint(-6,-23,10000,{.maxSpeed=80,.minSpeed=70},false);
    //schassis.moveToPoint(-28,-23,4000,{},false);
    //tongue.toggle();
    //pros::delay(300);
    schassis.moveToPoint(-15,-20,4000,{.maxSpeed=120,.minSpeed=120},false);
    /*schassis.moveToPoint(-62,0,3000,{},false);

    schassis.turnToPoint(-62,-30,1900,{.maxSpeed=70},false);
    tongue.toggle();
    pros::delay(400);
    schassis.moveToPoint(-62,-30,2000,{.maxSpeed=50},true);
    pros::delay(800);
    intakeIn();
    pros::delay(1800);
    intakeStop();
    schassis.moveToPoint(-62,20,1500,{.forwards=false,.maxSpeed=50},true);
    pros::delay(1500);
    intakeOutHigh(true);
    pros::delay(2000);*/

    


    
    //schassis.moveToPoint(18,68,4000,{},false);
    while(true){
        pros::lcd::set_text(0, "sX: " + std::to_string(schassis.getPose().x));
		pros::lcd::set_text(1, "sY: " + std::to_string(schassis.getPose().y));
		pros::lcd::set_text(2, "sO: " + std::to_string(schassis.getPose().theta));
    }




    

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
