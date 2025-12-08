void intakeLoop();
void intakeIn();
void intakeOutLow(bool slowin);
void intakeOutMid(bool slowin);
void intakeOutHigh(int ms = -1);

void intakeStop();
extern pros::adi::Pneumatics tongue;
extern pros::adi::Pneumatics wing;
extern pros::Motor I3;
extern pros::Motor I2;
extern pros::Motor I1;
void setHood(bool in);
void setTrapDoor(bool in);
