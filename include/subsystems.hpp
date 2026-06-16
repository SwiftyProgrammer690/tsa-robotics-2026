#include "main.h"
#include "pros/motors.h"
#include "pros/motors.hpp"

using namespace pros;

#define LEFT_MOTOR_1 1
#define LEFT_MOTOR_2 2
#define RIGHT_MOTOR_1 3
#define RIGHT_MOTOR_2 4
#define ARM_MOTOR_1 5
#define ARM_MOTOR_2 6
#define WRIST_MOTOR 7
#define CLAW_MOTOR 8
#define VISION_PORT 9

extern MotorGroup left_mg;
extern MotorGroup right_mg;

// Motor left_motor_1 (LEFT_MOTOR_1, MOTOR_GEAR_GREEN, false);
// Motor left_motor_2 (LEFT_MOTOR_2, MOTOR_GEAR_GREEN, true);
// Motor right_motor_1 (RIGHT_MOTOR_1, MOTOR_GEAR_GREEN, false);
// Motor right_motor_2 (RIGHT_MOTOR_2, MOTOR_GEAR_GREEN, true);

Motor arm_motor_1 (ARM_MOTOR_1, v5::MotorGears::red);
Motor arm_motor_2 (ARM_MOTOR_2, v5::MotorGears::red);
Motor wrist_motor(WRIST_MOTOR, v5::MotorGears::green);
Motor claw_motor(CLAW_MOTOR, v5::MotorGears::green);

Vision vision_sensor(VISION_PORT);

Controller master (E_CONTROLLER_MASTER);