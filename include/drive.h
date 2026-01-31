#include "main.h"

extern lemlib::Chassis chassis;
extern lemlib::Chassis schassis;
void driveLoop();
extern pros::Imu imu;
extern pros::Distance distance_sensor_front;
extern double mult;
extern pros::Distance distance_sensor_front;
extern pros::MotorGroup leftDrive;    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
extern pros::MotorGroup rightDrive;
enum DS{
  FRONT = 0,
  RIGHT = 1,
  BACK = 2,
  LEFT = 3
};
  
void distanceSensorReset(DS xSensor, DS ySensor, double targetTheta);