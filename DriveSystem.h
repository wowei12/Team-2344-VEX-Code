#ifndef INCLUDE_DRIVESYSTEM_H
#define INCLUDE_DRIVESYSTEM_H

/****************************************************************/

#define DS_JOYSTICK_MODE		SPLIT_JOYSTICK_L
#define DS_DEADBAND 			5

/****************************************************************/

typedef enum DS_JOYSTICK_MODES
{
	LEFT_JOYSTICK,
	RIGHT_JOYSTICK,
	SPLIT_JOYSTICK_L,
	SPLIT_JOYSTICK_R
};

byte ds_aJoystick[] = {0, 0};

/****************************************************************/

int runDriveSystem(DS_JOYSTICK_MODES nJoystick);

int setDriveSpeed(short nPower);
int setDriveSpeed(short nPowerLF, short nPowerRF, short nPowerLB, short nPowerRB);

/****************************************************************/

task driveSystem()
{
	while (true)
	{
		runDriveSystem();
	}
}

/****************************************************************/

/*
	Read controller inputs from the controller.

	@nJoystick: Tells which joystick to use. Refer to enum above.
*/
int runDriveSystem(DS_JOYSTICK_MODES nJoystick)
{
	switch (DS_JOYSTICK_MODE)
	{
		case LEFT_JOYSTICK:
			ds_aJoystick = {vexRT[Ch4], vexRT[Ch3]};
			break;

		case RIGHT_JOYSTICK:
			ds_aJoystick = {vexRT[Ch1], vexRT[Ch2]};
			break;
		case SPLIT_JOYSTICK_R:
			ds_aJoystick = {vexRT[Ch4], vexRT[Ch2]};
			break;
		case SPLIT_JOYSTICK_L:
		default:
			ds_aJoystick = {vexRT[Ch1], vexRT[Ch3]};
			break;
	}

	if (abs(ds_aJoystick[0]) > DS_DEADBAND || abs(ds_aJoystick[1]) > DS_DEADBAND)
	{
		setDriveSpeed(
			roundToLimit(ds_Joystick[1] + ds_Joystick[0], -127, 127),
			roundToLimit(ds_Joystick[1] - ds_Joystick[0], -127, 127),
			roundToLimit(ds_Joystick[1] + ds_Joystick[0], -127, 127),
			roundToLimit(ds_Joystick[1] - ds_Joystick[0], -127, 127)
		);
	}
	else
	{
		setDriveSpeed(0);
	}

	return 1;
}

int setDriveSpeed(short nPower)
{
	byte newPower = roundToLimit(nPower, -127, 127);

	motor[leftFrontMotor] = newPower;
	motor[rightFrontMotor] = newPower;
	motor[leftBackMotor] = newPower;
	motor[rightBackMotor] = newPower;

	return 1;
}

int setDriveSpeed(short nPowerLF, short nPowerRF, short nPowerLB, short nPowerRB)
{
	motor[leftFrontMotor] = roundToLimit(nPowerLF, -127, 127);
	motor[rightFrontMotor] = roundToLimit(nPowerRF, -127, 127);
	motor[leftBackMotor] = roundToLimit(nPowerLB, -127, 127);
	motor[rightBackMotor] = roundToLimit(nPowerRB, -127, 127);

	return 1;
}

#endif
