#include "main.h"
pros::Motor L1 ((int)3, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor L2 ((int)4, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor L3 ((int)-1, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R1 ((int)-1, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R2 ((int)-2, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R3 ((int)2, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::MotorGroup leftDrive({3,-4,-1});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup rightDrive({-1,2,2});
double input = 0;
void driveLoop(){
    input = master.get_analog(ANALOG_LEFT_Y);
		if(input>0){
			input=(input*0.46456692913)+68;
			
		}
		
		pros::lcd::set_text(0, std::to_string(input));
		leftDrive.move_voltage((input*input*input)*0.00585281132);
		input = master.get_analog(ANALOG_RIGHT_Y);
		if(input>0){
			input=(input*0.46456692913)+68;
		}
		rightDrive.move_voltage((input*input*input)*0.00585281132);
}



lemlib::Drivetrain drivetrain(&leftDrive, // left motor group
                              &rightDrive, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(10);
// horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(20);
pros::Rotation vertical_encoder(20);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(1, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              0, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              80, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(1, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              0, // derivative gain (kD)
                                              0, // anti windup
                                              2, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);