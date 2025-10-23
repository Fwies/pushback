void intakeLoop();
void intakeIn();
void intakeOutLow(bool slowin);
void intakeOutMid(bool slowin);
void intakeOutHigh();
void intakeStop();
extern pros::adi::Pneumatics tongue;

void setHood(bool in);
void setTrapDoor(bool in);