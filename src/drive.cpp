#include "main.h"
pros::Motor L1 ((int)-11, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor L2 ((int)-12, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor L3 ((int)-13, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R1 ((int)20, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R2 ((int)19, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::Motor R3 ((int)18, pros::v5::MotorGears::blue, pros::MotorUnits::rotations);
pros::MotorGroup leftDrive({-11,-12,-13});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup rightDrive({20,19,18});

void printTemps(){
    pros::lcd::set_text(0, "L1: " + std::to_string(L1.get_temperature()));
		pros::lcd::set_text(1, "L2: " + std::to_string(L2.get_temperature()));
		pros::lcd::set_text(2, "L3: " + std::to_string(L3.get_temperature()));
		pros::lcd::set_text(3, "R1: " + std::to_string(R1.get_temperature()));
		pros::lcd::set_text(4, "R2: " + std::to_string(R2.get_temperature()));
		pros::lcd::set_text(5, "R3: " + std::to_string(R3.get_temperature()));
}


// pros::MotorGroup leftDrive({-7,6,13});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
// pros::MotorGroup rightDrive({20,-10,-1});


double input = 0;
double mult = 0;
double speed = 1;


void speedChange()
{
    if(master.get_digital_new_press(DIGITAL_UP)&&speed!=1){
        speed=speed+0.1;
        master.rumble(".");
        if(speed>1){
            speed=1;
            master.rumble("-");
        }
    } else if(master.get_digital_new_press(DIGITAL_DOWN)){
        speed=speed-0.1;
        master.rumble(".");
        if(speed<0){
            speed=0;
            master.rumble("-");
        }
    }
}

void driveLoop(){

speedChange();

   //tank drive code
    input = master.get_analog(ANALOG_LEFT_Y)*speed;
		if(input>0){
			input=(input*0.46456692913)+68;
			
		}
    if(input<0){
			input=(input*0.46456692913)-68;
			
		}
		
		//pros::lcd::set_text(0, std::to_string(input));
		leftDrive.move_voltage(((input*input*input)*0.00585281132));
		input = master.get_analog(ANALOG_RIGHT_Y)*speed;
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
pros::Imu imu(17);
// horizontal tracking wheel encoder
//pros::Rotation horizontal_encoder(20);
pros::Rotation vertical_encoder(4);
pros::Rotation horizontal_encoder(15);
// horizontal tracking wheel

// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, 1.9921875, -0.5);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.0625);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel,//&horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);
lemlib::OdomSensors ssensors(nullptr,//&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr,//&horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(11, // proportional gain (kP)9
                                              0, // integral gain (kI)
                                              54, // derivative gain (kD)38
                                              0, // anti windup
                                               1 , //1 small error range, in inches
                                              100, //100 small error range timeout, in milliseconds
                                              3, //3 large error range, in inches
                                              500, //500 large error range timeout, in milliseconds
                                              0 //20 maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(6, // proportional gain (kP)6
                                              0, // integral gain (kI)
                                              47, // derivative gain (kD)48
                                              0, // anti windup
                                              2,//1, // small error range, in degrees
                                              50, //50 small error range timeout, in milliseconds
                                              3,//3, // large error range, in degrees
                                              500,//500, // large error range timeout, in milliseconds
                                              0//0 // maximum acceleration (slew)
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

pros::Distance distance_sensor_front(7);
pros::Distance distance_sensor_right(22);
pros::Distance distance_sensor_back(22);
pros::Distance distance_sensor_left(3);




// V array to store all the sensors V
pros::Distance distanceSensors[] = {distance_sensor_front, distance_sensor_right, distance_sensor_back, distance_sensor_left};
double distanceSensorsVerticalOffset[] = {5.875+1.436,     4.163+1.44,              0+1.44,               4.163+1.44}; // stores how far the sensor its on its y axis
double distanceSensorsHorizontalOffset[] = {3.5,0.25,0,-0.25}; // stores how far the sensor is on its x axis
double theta = 0; // will store the theta for consistant calculations
double xReading = 0; // variable to store the reading
double yReading = 0; // variable to store the reading
double fieldSize = 141; // stores the field size in inches
void distanceSensorReset(DS xSensor, DS ySensor, double targetTheta){
    // get Initial readings
    xReading = distanceSensors[xSensor].get();
    yReading = distanceSensors[ySensor].get();
    
    // repeatedly check the sensors until they seem to give a consistent reading
    while(abs(xReading - distanceSensors[xSensor].get())>12 && abs(xReading - distanceSensors[xSensor].get())>12){
        xReading = distanceSensors[xSensor].get();
        yReading = distanceSensors[ySensor].get();
        pros::delay(10);
    }
    
    //take into account vertical offsets and convert to inches
    xReading = distanceSensorsVerticalOffset[xSensor] + distanceSensors[xSensor].get()/25.4;
    yReading = distanceSensorsVerticalOffset[ySensor] + distanceSensors[ySensor].get()/25.4;

    // Now take into account that the robot is not perfectly aligned with the walls.
    theta = schassis.getPose().theta;
    xReading = (xReading)*cos((theta-targetTheta)*(M_PI/180)); // Have to convert degrees to radians for c++ cosign function
    yReading = (yReading)*cos((theta-targetTheta)*(M_PI/180));

    //take into account the sensors are offset on their x axis.
    xReading -= distanceSensorsHorizontalOffset[xSensor]*sin((theta-targetTheta)*(M_PI/180));
    yReading -= distanceSensorsHorizontalOffset[ySensor]*sin((theta-targetTheta)*(M_PI/180));
    
    // use the measurements to calculate the position. Use the previous beleived position to figure out quandrant.
    /*if (schassis.getPose().x<0){// Right side field
        //schassis.setPose(xReading-fieldSize/2,schassis.getPose().y,schassis.getPose().theta,false);
        schassis.setPose(xReading,schassis.getPose().y,schassis.getPose().theta,false);
    }
    else { // Left side of field
       // schassis.setPose(fieldSize/2-xReading,schassis.getPose().y,schassis.getPose().theta,false);
        schassis.setPose(-xReading,schassis.getPose().y,schassis.getPose().theta,false);
    }
    if (schassis.getPose().y>0){// Upper half of field
        //schassis.setPose(schassis.getPose().x,fieldSize/2-yReading,schassis.getPose().theta,false);
        schassis.setPose(schassis.getPose().x,-yReading,schassis.getPose().theta,false);
    }
    else { // lower half of field
        //schassis.setPose(schassis.getPose().x,yReading-fieldSize/2,schassis.getPose().theta,false);
        schassis.setPose(schassis.getPose().x,yReading,schassis.getPose().theta,false);
    }*/
    schassis.setPose(-xReading,schassis.getPose().y,schassis.getPose().theta,false);
    schassis.setPose(schassis.getPose().x,-yReading,schassis.getPose().theta,false);
    

	
}
