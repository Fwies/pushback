#include "main.h"
pros::Motor L1 ((int)-11, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor L2 ((int)-12, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor L3 ((int)-13, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R1 ((int)20, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R2 ((int)19, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R3 ((int)18, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::MotorGroup leftDrive({-11,-12,-13});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup rightDrive({20,19,18});
double input = 0;
double mult = 0;
void driveLoop(){
   //tank drive code
    input = master.get_analog(ANALOG_LEFT_Y)*mult;
		if(input>0){
			input=(input*0.46456692913)+68;
			
		}
    if(input<0){
			input=(input*0.46456692913)-68;
			
		}
		
		//pros::lcd::set_text(0, std::to_string(input));
		leftDrive.move_voltage(((input*input*input)*0.00585281132));
		input = master.get_analog(ANALOG_RIGHT_Y)*mult;
		if(input>0){
			input=(input*0.46456692913)+68;
		}
		if(input<0){
			input=(input*0.46456692913)-68;
			
		}

		rightDrive.move_voltage(((input*input*input)*0.00585281132));
    //end tank drive code
}



lemlib::Drivetrain drivetrain(&leftDrive, // left motor group
                              &rightDrive, // right motor group
                              10.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // dri.vetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(16);
// horizontal tracking wheel encoder
//pros::Rotation horizontal_encoder(20);
pros::Rotation vertical_encoder(19);
pros::Rotation horizontal_encoder(18);
// horizontal tracking wheel

// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, 1.9921875, -0.875);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, 0.96, -5.125);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel,//&horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);
lemlib::OdomSensors ssensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr,//&horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(9, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              31, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              80, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              5000, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(7, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              74, // derivative gain (kD)
                                              0, // anti windup
                                              2, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              100, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
lemlib::Chassis schassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        ssensors // odometry sensors
);

pros::Distance distance_sensor_front(1);
pros::Distance distance_sensor_right(21);
pros::Distance distance_sensor_back(22);
pros::Distance distance_sensor_left(22);






pros::Distance distanceSensors[] = {distance_sensor_front, distance_sensor_right, distance_sensor_back, distance_sensor_left};
double distanceSensorsVerticalOffset[] = {0.2+1.44,5+1.44,0,0};
double distanceSensorsHorizontalOffset[] = {-5.25,0,0,0};



double theta = 0;


/*void distanceSensorReset(){
    front = distance_sensor_front.get()/25.4;// Distance sensors poll distance from walls 
    side = distance_sensor_side.get()/25.4; //  and convert to inches
    theta = schassis.getPose().theta; // get the heading for calculating to position

    
    while(abs(imu.get_pitch()) > 5){ // wait for imu pitch to be less than 5 degrees in either direction
      pros::delay(10);
    }
    while(abs(front-(distance_sensor_front.get()/25.4))>1){ // wait for front sensor reading to be consistant
      pros::delay(10);
      front = distance_sensor_front.get()/25.4;
    }
    while(abs(side-(distance_sensor_side.get()/25.4))>1){ // wait for side sensor reading ot be consistent
      pros::delay(10);
      side = distance_sensor_side.get()/25.4;
    }

    front = 72 - (front)*cos((theta-270)*(3.14159/180));// calculate x position
    side = 72 + (-side)*cos((theta-270)*(3.14159/180));//  calculate y position
    schassis.setPose(front,side,schassis.getPose().theta,false);// update global position
}*/
double xReading= 0;
double yReading =0;
double feildSize = 141; //inches
void distanceSensorReset(DS xSensor, DS ySensor, double targetTheta){
    //Check for good reading
    xReading = distanceSensors[xSensor].get();
    yReading = distanceSensors[ySensor].get();
    while(abs(xReading - distanceSensors[xSensor].get())>12 && abs(xReading - distanceSensors[xSensor].get())>12){
        xReading = distanceSensors[xSensor].get();
        yReading = distanceSensors[ySensor].get();
        pros::delay(10);
    }
    //take into account vertical offsets and convert to inches

    xReading = distanceSensorsVerticalOffset[xSensor] + distanceSensors[xSensor].get()/25.4;
    yReading = distanceSensorsVerticalOffset[ySensor] + distanceSensors[ySensor].get()/25.4;

    pros::lcd::set_text(3, "rawX: " + std::to_string(xReading));
		pros::lcd::set_text(4, "rawY: " + std::to_string(yReading));
    // Now take into account that the robot is not perfectly aligned with the walls.
    theta = imu.get_heading();//schassis.getPose().theta;
    xReading = (xReading)*cos((theta-targetTheta)*(M_PI/180)); // Have to convert degrees to radians for c++ cosign function
    yReading = (yReading)*cos((theta-targetTheta)*(M_PI/180));
    pros::lcd::set_text(5, "tiltcX: " + std::to_string(xReading));
		
    //take into account the sensors are of set side to side
    xReading -= distanceSensorsHorizontalOffset[xSensor]*sin((theta-targetTheta)*(M_PI/180));
    yReading -= distanceSensorsHorizontalOffset[ySensor]*sin((theta-targetTheta)*(M_PI/180));
    pros::lcd::set_text(6, "offsetcx: " + std::to_string(xReading));
    
    if (false){//schassis.getPose().x<0){
        //schassis.setPose(xReading-feildSize/2,0,schassis.getPose().theta,false);
        pros::lcd::set_text(0, "sX: " + std::to_string(xReading-feildSize/2));
    }
    else {
        //schassis.setPose(feildSize/2-xReading,0,schassis.getPose().theta,false);
        pros::lcd::set_text(0, "sX: " + std::to_string(feildSize/2-xReading));
    }
    if (false){//schassis.getPose().y>0){
        //schassis.setPose(schassis.getPose().x,feildSize/2-yReading,schassis.getPose().theta,false);
        pros::lcd::set_text(1, "sy " + std::to_string(feildSize/2-yReading));
    }
    else {
        //schassis.setPose(schassis.getPose().x,yReading-feildSize/2,schassis.getPose().theta,false);
        pros::lcd::set_text(1, "sy: " + std::to_string(yReading-feildSize/2));
    }
    /*pros::lcd::set_text(0, "sX: " + std::to_string(schassis.getPose().x));
		pros::lcd::set_text(1, "sY: " + std::to_string(schassis.getPose().y));*/
		pros::lcd::set_text(2, "sO: " + std::to_string(theta));//schassis.getPose().theta));



}
