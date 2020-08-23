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
// rightDownCraneMotor  motor         12
// rightUpCraneMotor    motor         5
// Drivetrain           drivetrain    1, 20, 11, 7, A
// leftClawMotor        motor         9
// turningClawMotor     motor         19
// rightClawMotor       motor         4
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

// global instances
// crane
int craneAngleTarg;
int IErrcR, IErrcL;

void pre_auton(void) {
  vexcodeInit();
  // crane
  IErrcR = 0;
  IErrcL = 0;
  craneAngleTarg = 0;
}

void autonomous(void) {}

void usercontrol(void) {

  while (1) {
    Brain.Screen.setCursor(1, 0);
    Brain.Screen.clearLine();
    Brain.Screen.print("leftCraneAngle=  ");
    Brain.Screen.print(0.5 * (leftUpCraneMotor.position(degrees) +
                              leftDownCraneMotor.position(degrees)));
    Brain.Screen.print("  rightCraneAngle=  ");
    Brain.Screen.print(0.5 * (rightUpCraneMotor.position(degrees) +
                              rightDownCraneMotor.position(degrees)));

    if (Controller1.ButtonX.pressing()) {
      craneAngleTarg = 375;
    }
    if (Controller1.ButtonA.pressing()) {
      craneAngleTarg = 265;
    }
    if (Controller1.ButtonB.pressing()) {
      craneAngleTarg = 175;
    }
    if (Controller1.ButtonY.pressing()) {
      craneAngleTarg = 20;
    }
    moveCraneTo(craneAngleTarg);

    Brain.Screen.setCursor(2, 0);
    Brain.Screen.clearLine();
    Brain.Screen.print("turningAngle=  ");
    Brain.Screen.print(turningClawMotor.position(degrees));

    if (Controller1.ButtonR1.pressing()) {
      clawTurn(50);
    }
    if (Controller1.ButtonR2.pressing()) {
      clawTurn(-50);
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

void clawTurn(int speed) {
  if (speed != 0) {
    turningClawMotor.setVelocity(speed, percent);
    turningClawMotor.spin(forward);
  } else {
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
