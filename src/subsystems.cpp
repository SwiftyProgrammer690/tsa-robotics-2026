#include "subsystems.hpp"

MotorGroup left_mg ({LEFT_MOTOR_1,  LEFT_MOTOR_2},  v5::MotorGears::green);
MotorGroup right_mg({RIGHT_MOTOR_1, RIGHT_MOTOR_2}, v5::MotorGears::green);
MotorGroup arm_mg  ({ARM_MOTOR_1,   -ARM_MOTOR_2},   v5::MotorGears::red);
MotorGroup wrist_mg({WRIST_MOTOR_1, -WRIST_MOTOR_2}, v5::MotorGears::green);

Motor claw_motor (CLAW_MOTOR,  v5::MotorGears::green);

Vision vision_sensor(VISION_PORT);
Controller master(E_CONTROLLER_MASTER);
Imu imu(IMU_PORT);
