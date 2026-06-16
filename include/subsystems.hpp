#pragma once

#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/vision.hpp"

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
extern MotorGroup arm_mg;
extern Motor wrist_motor;
extern Motor claw_motor;
extern Vision vision_sensor;
extern Controller master;
