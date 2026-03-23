void intakeLoop();
void intakeIn();
void intakeOutLow(bool slowin);
void intakeOutMid(bool slowin, int ms = -1);
void intakeOutHigh(int ms = -1);
enum COLORVALUE{
  REDUPPER = 30,
  REDLOWER = 0,
  BLUEUPPER = 300,
  BLUELOWER = 180,
  NOSORTUPPER = -1,
  NOSORTLOWER = 361,
};
extern pros::Optical optical;
void intakeStop();
extern pros::adi::Pneumatics tongue;
extern pros::adi::Pneumatics lift;
extern pros::adi::Pneumatics wing;
extern pros::Motor I3;
extern pros::Motor I2;
extern pros::Motor I1;
void intakeInThread(void* param);
void setHood(bool in);
void setTrapDoor(bool in);
