using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor leftDownCraneMotor;
extern motor leftUpCraneMotor;
extern motor rightDownCraneMotor;
extern motor rightUpCraneMotor;
extern smartdrive Drivetrain;
extern motor leftClawMotor;
extern motor turningClawMotor;
extern motor rightClawMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );