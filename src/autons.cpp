#include "main.h"

pros::adi::AnalogIn pot(8);
int auton = 0;
std::string autoNames[5] = {"no auto","left","right","solo awp","skills"};
void autoPrint(){
    pros::lcd::set_text(3, "auton: " + autoNames[auton]);
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

}
void autoRight(){

}
void autoSkills(){

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
