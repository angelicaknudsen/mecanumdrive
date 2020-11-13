#include "main.h"

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
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
#define MOTOR_FRONT_LEFT 9
#define MOTOR_BACK_LEFT 10
#define MOTOR_FRONT_RIGHT 2
#define MOTOR_BACK_RIGHT 3

void opcontrol() {

using namespace pros;
/*	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2); */

	int forward;
	int leftY, rightX, leftX;

	Motor driveFrontLeft(MOTOR_FRONT_LEFT);
	Motor driveFrontRight(MOTOR_FRONT_RIGHT, true);
	Motor driveBackLeft(MOTOR_BACK_LEFT);
	Motor driveBackRight(MOTOR_BACK_RIGHT, true);

	Controller joystick(CONTROLLER_MASTER);

	while (true) {

		//mecanum drive attempt w/ arcade drive mode

		leftY = joystick.get_analog(ANALOG_LEFT_Y); //left joystick controls forward and backward motion
		rightX = joystick.get_analog(ANALOG_RIGHT_X);//right joystick controls turning motion
		leftX = joystick.get_analog(ANALOG_LEFT_X);

		driveFrontLeft = (leftY + rightX + leftX)/3; //these values likely won't work, and I should really probably look at mecanum code.
		driveFrontRight = (leftY - rightX - leftX)/3;
		driveBackLeft = (leftY - rightX + leftX)/3;
		driveBackRight = (leftY + rightX - leftX)/3;

		//dividing each by two to make sure the values don't ever exceed 127
		//This isn't a huge issue normally since any values larger than 127 or smaller than -127 will be viewed as just the max/min,
		//but we want the turns to stay proportional to each other side (I think? Idk what I'm talking about)
		//This is largely based off of arcade drive code
	}
}
