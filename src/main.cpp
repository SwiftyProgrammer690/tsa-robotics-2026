#include "main.h"
#include "subsystems.hpp"

#include <atomic>
#include <cmath>

using namespace pros;

static std::atomic<bool> oscillate_active{false};

// Turns the chassis to target_deg relative to the IMU zero point.
// Exits early if oscillate_active is cleared.
static void turn_to_angle(double target_deg) {
	constexpr double  kP         = 1.8;
	constexpr double  kTolerance = 1.5;  // degrees
	constexpr int32_t kMinPower  = 22;   // minimum to overcome static friction

	while (oscillate_active.load()) {
		const double error = target_deg - imu.get_rotation();
		if (std::abs(error) < kTolerance) break;

		int32_t power = static_cast<int32_t>(kP * error);
		if (power > 0 && power <  kMinPower) power =  kMinPower;
		if (power < 0 && power > -kMinPower) power = -kMinPower;
		if (power >  127) power =  127;
		if (power < -127) power = -127;

		left_mg.move( power);
		right_mg.move(-power);

		delay(10);
	}

	left_mg.move(0);
	right_mg.move(0);
}

static void oscillate_task_fn(void*) {
	imu.set_rotation(0.0);

	while (oscillate_active.load()) {
		turn_to_angle( 45.0);
		if (!oscillate_active.load()) break;
		delay(250);

		turn_to_angle(-45.0);
		if (!oscillate_active.load()) break;
		delay(250);
	}

	left_mg.move(0);
	right_mg.move(0);
}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		lcd::set_text(2, "I was pressed!");
	} else {
		lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Calibrating IMU...");
	lcd::register_btn1_cb(on_center_button);

	// Hold position when idle so gravity doesn't drop the arm/wrist.
	arm_mg.set_brake_mode_all(E_MOTOR_BRAKE_HOLD);
	wrist_mg.set_brake_mode_all(E_MOTOR_BRAKE_HOLD);
	claw_motor.set_brake_mode_all(E_MOTOR_BRAKE_HOLD);

	imu.reset(true);  // blocking — waits until calibration is complete
	lcd::set_text(1, "Ready!");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// Slow by default for precise obstacle-course navigation.
	// DIGITAL_Y toggles boost on/off.
	// DIGITAL_B toggles the ±45° oscillation routine on/off.
	constexpr double kSlowSpeed  = 0.35;
	constexpr double kBoostSpeed = 1.0;

	bool boost_enabled = false;

	while (true) {
		if (master.get_digital_new_press(DIGITAL_Y)) {
			boost_enabled = !boost_enabled;
		}

		// if (master.get_digital_new_press(DIGITAL_B)) {
		// 	if (oscillate_active.load()) {
		// 		oscillate_active = false;  // task sees this and exits on its own
		// 	} else {
		// 		oscillate_active = true;
		// 		Task(oscillate_task_fn, nullptr, "oscillate");
		// 	}
		// }

		// Drivetrain — handed off to oscillate task while it's running
		if (!oscillate_active.load()) {
			const double speed = boost_enabled ? kBoostSpeed : kSlowSpeed;
			const int    dir   = master.get_analog(ANALOG_RIGHT_X);
			const int    turn  = master.get_analog(ANALOG_LEFT_Y);

			right_mg.move(static_cast<int32_t>(speed * (dir - turn)));
			left_mg.move(static_cast<int32_t>(speed * (dir + turn)));
		}

		if (master.get_digital(DIGITAL_RIGHT)) {
			arm_mg.move(50);
		} else if (master.get_digital(DIGITAL_DOWN)) {
			arm_mg.move(-50);
		} else {
			arm_mg.brake();  // hold position instead of coasting down
		}

		if (master.get_digital(DIGITAL_R1)) {
			wrist_mg.move(-40);
		} else if (master.get_digital(DIGITAL_R2)) {
			wrist_mg.move(40);
		} else {
			wrist_mg.brake();  // hold position instead of coasting down
		}

		if (master.get_digital(DIGITAL_L1)) {
			claw_motor.move(-30);
		} else if (master.get_digital(DIGITAL_L2)) {
			claw_motor.move(30);
		} else {
			claw_motor.brake();
		}

		lcd::print(0, "Boost:%s Osc:%s",
		           boost_enabled          ? "ON " : "OFF",
		           oscillate_active.load() ? "ON " : "OFF");

		delay(20);
	}
}
