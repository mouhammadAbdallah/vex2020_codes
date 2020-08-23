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
// leftDownCraneMotor   motor         18
// leftUpCraneMotor     motor         6
// rightDownCraneMotor  motor         13
// rightUpCraneMotor    motor         3
// Drivetrain           drivetrain    1, 20, 11, 7, A
// leftClawMotor        motor         9
// turningClawMotor     motor         19
// rightClawMotor       motor         4
// frontLineTracker     line          H
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// methods declaration:
void moveRobot(int L, int R);
void moveCraneTo(int craneAngleTar);
void clawTurn(int speed);
void claw(int speed);
void clawTurnFor(int angleTarget);
void stopCrane();

// global instances
// crane
int craneAngleTarg;
int IErrcR, IErrcL;

// turning claw
int IErrcT;

void pre_auton(void) { vexcodeInit(); }

void autonomous(void) {
  Brain.Screen.clearScreen();
  // go forward a little to be able to go up
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(forward, 30, mm);
  Drivetrain.stop();

  // go up to be able to turn the claw and turn it
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1) {
    moveCraneTo(100);
    clawTurnFor(300);
  }
  // go down to be able to eat the cube and eat
  IErrcR = 0;
  IErrcL = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1) {
    clawTurn(0);
    moveCraneTo(20);
    claw(50);
  }
  stopCrane();

  // go forward to eat the cube
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(forward, 350, mm);
  Drivetrain.stop();

  // turn left after eating the cube
  Drivetrain.turnToHeading(-0.755 * 90, degrees);
  Drivetrain.stop();

  // go up to not crash a cube in the road and turn claw down
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1.5) {
    moveCraneTo(280);
    clawTurnFor(360);
  }
  stopCrane();
  // go forward to attend the tower
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(forward, 230, mm);
  Drivetrain.stop();

  // stay up and eject the cube
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1) {
    claw(-50);
    moveCraneTo(280);
    clawTurnFor(360);
  }
  claw(0);
  clawTurn(0);

  // go back  until line tracker notices the white line
  IErrcR = 0;
  IErrcL = 0;
  Drivetrain.setDriveVelocity(30, percent);
  while (frontLineTracker.reflectivity() < 60) {
    Drivetrain.drive(reverse);
    moveCraneTo(100);
  }
  Drivetrain.stop();
  stopCrane();

  // go back a little to center tile
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(reverse, 160, mm);
  Drivetrain.stop();
  // go down and set up the turning claw
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1) {
    moveCraneTo(0);
    clawTurnFor(350);
  }
  stopCrane();
  // turn right after eating the cube
  Drivetrain.turnToHeading(0, degrees);
  Drivetrain.stop();

  // go backward to attend the wall and initialize the gyro
  IErrcR = 0;
  IErrcL = 0;
  Brain.Timer.reset();
  Drivetrain.setDriveVelocity(50, percent);

  while (Brain.Timer.value() < 1.5) {
    Drivetrain.drive(reverse);
    moveCraneTo(0);
    clawTurnFor(350);

  }
  Drivetrain.stop();
  stopCrane();
  Drivetrain.setHeading(0, degrees);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // go forward to eat the second cube and eat it and let crane down
  claw(50);
  IErrcR = 0;
  IErrcL = 0;
  moveCraneTo(0);
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(forward, 1250, mm);
  Drivetrain.stop();

  // go back a little to be able to go up and let crane down
  IErrcR = 0;
  IErrcL = 0;
  moveCraneTo(0);
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(reverse, 170, mm);
  Drivetrain.stop();

  // go Up to put the cube on the tower
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1.5) {
    moveCraneTo(240);
    clawTurnFor(360);
  }

  // go forward to attend the tower
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(forward, 100, mm);
  Drivetrain.stop();

  // stay up and eject the cube
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1) {
    claw(-50);
    moveCraneTo(190);
    clawTurnFor(330);
  }
  claw(0);
  clawTurn(0);

  // go back a little to be able to go down
  Drivetrain.setDriveVelocity(20, percent);
  Drivetrain.driveFor(reverse, 280, mm);
  Drivetrain.stop();

  // go down and set up the turning claw
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1) {
    moveCraneTo(60);
    clawTurnFor(330);
  }
  stopCrane();
  claw(0);
  clawTurn(0);
///////////////////////////////////////////////////////////////////////////////////////////////////////
  //turn left to the 3rd third cube
  Drivetrain.turnToHeading(-0.755 *90, degrees);
  Drivetrain.stop();

  // go backward to attend the wall and initialize the gyro
  IErrcR = 0;
  IErrcL = 0;
  Brain.Timer.reset();
  Drivetrain.setDriveVelocity(50, percent);

  while (Brain.Timer.value() < 2) {
    Drivetrain.drive(reverse);
    moveCraneTo(0);
    clawTurnFor(330);

  }
  Drivetrain.stop();
  stopCrane();
  Drivetrain.setHeading(0, degrees);

  // go forward to attend the tower line and eat it and let crane down
  //wait(2000,msec);
  claw(-50);
  IErrcR = 0;
  IErrcL = 0;
  moveCraneTo(0);
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(forward, 2000, mm);
  Drivetrain.stop();
  wait(500,msec);

  // go back a little and let crane down
  IErrcR = 0;
  IErrcL = 0;
  moveCraneTo(0);
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(reverse, 440, mm);
  Drivetrain.stop();

  //turn right to the 3rd third cube
  Drivetrain.turnToHeading(0.755*90, degrees);
  Drivetrain.stop();
  // go forward to eat the cube and let crane down
  claw(50);
  IErrcR = 0;
  IErrcL = 0;
  moveCraneTo(0);
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(forward, 400, mm);
  Drivetrain.stop();

  // go back a little to be able to go up and let crane down
  IErrcR = 0;
  IErrcL = 0;
  moveCraneTo(0);
  clawTurnFor(410);

  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(reverse, 220, mm);
  Drivetrain.stop();

  // go Up to put the cube on the tower
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 3) {
    moveCraneTo(410);
    clawTurnFor(410);
  }

  // go forward to attend the tower
  Drivetrain.setDriveVelocity(20, percent);
  Drivetrain.driveFor(forward, 170, mm);
  Drivetrain.stop();

  // stay up and eject the cube
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 2) {
    claw(-50);
    moveCraneTo(410);
    clawTurnFor(410);
  }
  claw(0);
  clawTurn(0);

  // go back a little to be able to go down
  Drivetrain.setDriveVelocity(20, percent);
  Drivetrain.driveFor(reverse, 300, mm);
  Drivetrain.stop();

  // go down and set up the turning claw
  IErrcR = 0;
  IErrcL = 0;
  IErrcT = 0;
  Brain.Timer.reset();
  while (Brain.Timer.value() < 1) {
    moveCraneTo(60);
    clawTurnFor(320);
  }
  stopCrane();
  claw(0);
  clawTurn(0);

  }

void usercontrol(void) {
  autonomous();
  // crane
  IErrcR = 0;
  IErrcL = 0;
  craneAngleTarg = 0;
  // turning claw
  IErrcT = 0;

     while (1) {
    Brain.Screen.setCursor(1, 0);
    Brain.Screen.clearLine();
    Brain.Screen.print("leftCraneUp= ");
    Brain.Screen.print(leftUpCraneMotor.position(degrees));
    Brain.Screen.print(" rightCraneUp=  ");
    Brain.Screen.print(rightUpCraneMotor.position(degrees));
    Brain.Screen.setCursor(2, 0);
    Brain.Screen.clearLine();
    Brain.Screen.print("leftCraneDown=  ");
    Brain.Screen.print(leftDownCraneMotor.position(degrees));
    Brain.Screen.print("  rightCraneDown=  ");
    Brain.Screen.print(rightDownCraneMotor.position(degrees));


    if (Controller1.ButtonX.pressing()) {
      craneAngleTarg = 360;
      IErrcR = 0;IErrcL = 0;
    }
    if (Controller1.ButtonA.pressing()) {
      craneAngleTarg = 265;
      IErrcR = 0;IErrcL = 0;
    }
    if (Controller1.ButtonB.pressing()) {
      craneAngleTarg = 175;
      IErrcR = 0;IErrcL = 0;
    }
    if (Controller1.ButtonY.pressing()) {
      craneAngleTarg = 15;
      IErrcR = 0;IErrcL = 0;
    }
    moveCraneTo(craneAngleTarg);

    Brain.Screen.setCursor(3, 0);
    Brain.Screen.clearLine();
    Brain.Screen.print("turningAngle=  ");
    Brain.Screen.print(turningClawMotor.position(degrees));

    if (Controller1.ButtonR1.pressing()) {
      clawTurn(-50);
    }
    if (Controller1.ButtonR2.pressing()) {
      clawTurn(50);
    }
    if (!Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing()) {
      clawTurn(0);
    }

    if (Controller1.ButtonL1.pressing()) {
      claw(50);
    }
    if (Controller1.ButtonL2.pressing()) {
      claw(-50);
    }
    if (!Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing()) {
      claw(0);
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

void moveCraneTo(int craneAngleTar) {

  int lcraneAngle, rcraneAngle, lcraneSpeed, rcraneSpeed, ErrL, ErrR;

  lcraneAngle = 0.5 * (leftUpCraneMotor.position(degrees) +
                       leftDownCraneMotor.position(degrees));

  rcraneAngle = 0.5 * (rightUpCraneMotor.position(degrees) +
                       rightDownCraneMotor.position(degrees));

  ErrL = craneAngleTar - lcraneAngle;
  ErrR = craneAngleTar - lcraneAngle;
  lcraneSpeed = 0.3 * ErrL + 0.00001 * IErrcL;
  rcraneSpeed = 0.3 * ErrR + 0.00001 * IErrcR;

  leftUpCraneMotor.setVelocity(lcraneSpeed, percent);
  leftUpCraneMotor.spin(forward);
  leftDownCraneMotor.setVelocity(lcraneSpeed, percent);
  leftDownCraneMotor.spin(forward);
  rightUpCraneMotor.setVelocity(rcraneSpeed, percent);
  rightUpCraneMotor.spin(forward);
  rightDownCraneMotor.setVelocity(rcraneSpeed, percent);
  rightDownCraneMotor.spin(forward);

  if (abs(lcraneSpeed) < 50) {
    IErrcL = IErrcL + ErrL;
  }
  if (abs(rcraneSpeed) < 50) {
    IErrcR = IErrcR + ErrR;
  }

  if (abs(ErrL) < 3) {
    leftUpCraneMotor.setStopping(hold);
    leftDownCraneMotor.setStopping(hold);
    leftUpCraneMotor.stop();
    leftDownCraneMotor.stop();
  }
  if (abs(ErrR) < 3) {
    rightUpCraneMotor.setStopping(hold);
    rightDownCraneMotor.setStopping(hold);
    rightUpCraneMotor.stop();
    rightDownCraneMotor.stop();
  }
}
void stopCrane() {
  rightUpCraneMotor.stop();
  rightDownCraneMotor.stop();
  leftUpCraneMotor.stop();
  leftDownCraneMotor.stop();
}

void clawTurn(int speed) {
  if (speed != 0) {
    turningClawMotor.setVelocity(speed, percent);
    turningClawMotor.spin(forward);
  } else {
    turningClawMotor.setStopping(hold);
    turningClawMotor.stop();
  }
}
void clawTurnFor(int angleTarget) {
  int anglet, speed, Err;

  anglet = turningClawMotor.position(degrees);

  Err = angleTarget - anglet;
  speed = 0.3 * Err + 0.00001 * IErrcT;

  turningClawMotor.setVelocity(speed, percent);
  turningClawMotor.spin(forward);

  if (abs(speed) < 50) {
    IErrcT = IErrcT + Err;
  }

  if (abs(Err) < 3) {
    turningClawMotor.setStopping(hold);
    turningClawMotor.stop();
  }
}

void claw(int speed) {
  if (speed != 0) {
    leftClawMotor.setVelocity(speed, percent);
    rightClawMotor.setVelocity(speed, percent);
    leftClawMotor.spin(forward);
    rightClawMotor.spin(forward);
  } else {
    leftClawMotor.setStopping(hold);
    leftClawMotor.stop();
    rightClawMotor.setStopping(hold);
    rightClawMotor.stop();
  }
}