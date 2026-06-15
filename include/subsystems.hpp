#include "main.h"
#include "pros/motors.h"

#define LEFT_MOTOR_1 1
#define LEFT_MOTOR_2 2
#define RIGHT_MOTOR_1 3
#define RIGHT_MOTOR_2 4
#define ARM_MOTOR_1 5
#define ARM_MOTOR_2 6
#define CLAW_MOTOR 7
    
using namespace pros;

extern MotorGroup left_mg;
extern MotorGroup right_mg;

// Motor left_motor_1 (LEFT_MOTOR_1, MOTOR_GEAR_GREEN, false);
// Motor left_motor_2 (LEFT_MOTOR_2, MOTOR_GEAR_GREEN, true);
// Motor right_motor_1 (RIGHT_MOTOR_1, MOTOR_GEAR_GREEN, false);
// Motor right_motor_2 (RIGHT_MOTOR_2, MOTOR_GEAR_GREEN, true);n
Motor arm_motor_1 (1, E_MOTOR_GEARSET_18);
Motor arm_motor_2 (2, E_MOTOR_GEARSET_18);
Motor claw_motor (CLAW_MOTOR, E_MOTOR_GEARSET_18);

Controller master (E_CONTROLLER_MASTER);