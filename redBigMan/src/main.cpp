/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 15, 10, 20, A
// leftStandMotor       motor         3               
// rightStandMotor      motor         9               
// leftClawMotor        motor         6               
// rightClawMotor       motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

//methods declaration:
void moveRobot(int LSpeed, int RSpeed);
void standUp(int standAngleTar);
void eatCube(int eatSpeed);
void throwCube(int throwSpeed);


// define your global instances of motors and other devices here
int IErrS;
bool bStandUp;
bool eat;



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  IErrS=0;
  bStandUp=false;
  eat=false;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  int leftJoysticPosition,rightJoysticPosition;
  // User control code here, inside the loop
  Drivetrain.setTurnVelocity(30,percent);
  Drivetrain.turnFor(right,90,degrees);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    leftJoysticPosition=Controller1.Axis3.position(percent);
		rightJoysticPosition =Controller1.Axis2.position(percent);
		moveRobot(leftJoysticPosition,rightJoysticPosition);

    Brain.Screen.clearLine();
    Brain.Screen.print(0.5*leftStandMotor.position(degrees)+0.5*rightStandMotor.position(degrees));
    if(Controller1.ButtonDown.pressing()){
        bStandUp=false;
    }
    if(Controller1.ButtonUp.pressing()){
      bStandUp=true;
    }

    if(bStandUp==true)standUp(521);
    else standUp(10);

    if(Controller1.ButtonL1.pressing()){
      eat=true;
    }

    if(eat==true)eatCube(50);

    if(Controller1.ButtonL2.pressing()){
      if(eat==true){
        eat=false;
        eatCube(0);
      }
      else throwCube(40);
    }
    else if(eat==false)throwCube(0);

    if(Controller1.ButtonLeft.pressing()){
       moveRobot(-5,-5);
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

void moveRobot(int LSpeed, int RSpeed){
  	if(abs(LSpeed) < 10 && abs(RSpeed)<10){Drivetrain.stop();}
		if(LSpeed*RSpeed < 0){ //turn
      if(RSpeed<0){//turn right
          Drivetrain.setTurnVelocity(0.5*LSpeed,percent);
          Drivetrain.turn(right);
      }
      else{//turn left
          Drivetrain.setTurnVelocity(0.5*RSpeed,percent);
          Drivetrain.turn(left);
      }
    }
    else{//direct
      if(RSpeed+LSpeed>0){//go forward
            if(RSpeed<LSpeed)RSpeed=LSpeed;
            Drivetrain.setDriveVelocity(0.8*RSpeed,percent);
            Drivetrain.drive(forward);
      }
      else{//
            if(RSpeed<LSpeed)RSpeed=LSpeed;
            Drivetrain.setDriveVelocity(0.8*RSpeed,percent);
            Drivetrain.drive(forward);
      }
    }
}

void standUp(int standAngleTar){
  int standAngle,standSpeed,ErrS;

  standAngle=0.5*leftStandMotor.position(degrees)+0.5*rightStandMotor.position(degrees);

  ErrS=standAngleTar-standAngle;

  standSpeed=0.1*ErrS+0.00001*IErrS;
   
  leftStandMotor.setVelocity(standSpeed,percent);
  rightStandMotor.setVelocity(standSpeed,percent);
  leftStandMotor.spin(forward);
  rightStandMotor.spin(forward);

  if(abs(standSpeed) < 70)
	{
		IErrS = IErrS + ErrS;
	}
  

}
void eatCube(int eatSpeed){
  leftClawMotor.setVelocity(eatSpeed,percent);
  rightClawMotor.setVelocity(eatSpeed,percent);
  rightClawMotor.spin(forward);
  leftClawMotor.spin(forward);

}
void throwCube(int throwSpeed){
  leftClawMotor.setVelocity(throwSpeed,percent);
  rightClawMotor.setVelocity(throwSpeed,percent);
  rightClawMotor.spin(reverse);
  leftClawMotor.spin(reverse);
}