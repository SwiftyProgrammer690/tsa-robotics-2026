#pragma once

#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/vision.hpp"

using namespace pros;

#define LEFT_MOTOR_1 17
#define LEFT_MOTOR_2 16
#define RIGHT_MOTOR_1 18
#define RIGHT_MOTOR_2 13
#define ARM_MOTOR_1 1
#define ARM_MOTOR_2 10
#define WRIST_MOTOR 9
#define CLAW_MOTOR 3
#define VISION_PORT 20
#define IMU_PORT    12

extern MotorGroup  left_mg;
extern MotorGroup  right_mg;
extern MotorGroup  arm_mg;
extern Motor       wrist_motor;
extern Motor       claw_motor;
extern Vision      vision_sensor;
extern Controller  master;
extern Imu         imu;
