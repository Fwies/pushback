#include "main.h"
pros::Motor L1 ((int)-10, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor L2 ((int)-9, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor L3 ((int)-8, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R1 ((int)5, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R2 ((int)6, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R3 ((int)4, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::MotorGroup leftDrive({-10,-9,-8});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup rightDrive({4,6,5});
double input = 0;
void driveLoop(){
   //tank drive code
    input = master.get_analog(ANALOG_LEFT_Y);
		if(input>0){
			input=(input*0.46456692913)+68;
			
		}
    if(input<0){
			input=(input*0.46456692913)-68;
			
		}
		
		//pros::lcd::set_text(0, std::to_string(input));
		leftDrive.move_voltage(((input*input*input)*0.00585281132)*0.85);
		input = master.get_analog(ANALOG_RIGHT_Y);
		if(input>0){
			input=(input*0.46456692913)+68;
		}
		if(input<0){
			input=(input*0.46456692913)-68;
			
		}

		rightDrive.move_voltage(((input*input*input)*0.00585281132)*0.85);
    //end tank drive code
}



lemlib::Drivetrain drivetrain(&leftDrive, // left motor group
                              &rightDrive, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(7);
// horizontal tracking wheel encoder
//pros::Rotation horizontal_encoder(20);
pros::Rotation vertical_encoder(21);
// horizontal tracking wheel

// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, 0.5);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr,//&horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(8, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              38, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              80, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              5000, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(7, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              60, // derivative gain (kD)
                                              0, // anti windup
                                              2, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              2, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);