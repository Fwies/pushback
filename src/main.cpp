#include "main.h"
#include <string>
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

void initialize() {
	pros::lcd::initialize();
	//schassis.calibrate();
	imu.reset();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	//chassis.calibrate(true);
	while(true){
	autoSet(-1);
	autoPrint();
	pros::delay(10);
	}
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	//lemlib::Pose og = lemlib::Pose(chassis.getPose());
	autoSet(-1);
	autoPrint();
	if(auton == 3){
		schassis.calibrate(true);
	}
	else{
		chassis.calibrate(true);
	}
	//chassis.setPose(og);
	while(true){
	autoSet(-1);
	autoPrint();
	pros::delay(10);
	}
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	
	autoSet(-1);
	autoPrint();
	autoRun();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


void opcontrol() {
	
	
	
	  // Creates a motor group with forwards port 5 and reversed ports 4 & 6

	/*schassis.calibrate();
	schassis.setPose(0,0,270,false);
	pros::delay(500);

	distanceSensorReset();*/
	while (true) {
		if (master.get_digital_new_press(DIGITAL_LEFT)){
			
			distanceSensorReset(DS::FRONT,DS::RIGHT, 90);
		}
		if(partner.get_digital(DIGITAL_R1)){
			master.rumble(".");
		}
		if(auton==3){
			if(partner.get_digital(DIGITAL_R2)){
				mult=1;
			}
			else{
				mult=0.8;
			}
		}
		else{
			if(partner.get_digital(DIGITAL_R2)){
				mult=0.7;
			}
			else{
				mult=1;
			}
		}
		
		/*pros::lcd::set_text(0, "X: " + std::to_string(chassis.getPose().x));
		pros::lcd::set_text(1, "Y: " + std::to_string(chassis.getPose().y));
		pros::lcd::set_text(2, "O: " + std::to_string(chassis.getPose().theta));*/
		/*pros::lcd::set_text(0, "sX: " + std::to_string(schassis.getPose().x));
		pros::lcd::set_text(1, "sY: " + std::to_string(schassis.getPose().y));
		pros::lcd::set_text(2, "sO: " + std::to_string(schassis.getPose().theta));*/
		
		autoSet(-1);
		autoPrint();
		driveLoop();
		intakeLoop();
		
		pros::delay(10);                               // Run for 10 ms then update
	}
}