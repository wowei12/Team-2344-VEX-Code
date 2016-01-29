#ifndef INCLUDE_DRIVESYSTEM_H
#define INCLUDE_DRIVESYSTEM_H

/****************************************************************/

#define DS_JOYSTICK_MODE				SPLIT_JOYSTICK_L
#define DS_DEADBAND 						5

#define DS_SLOW_TURN_BUTTON 		Btn7R
#define DS_SLOW_TURN_RATIO			0.5

/****************************************************************/

typedef enum DS_JOYSTICK_MODES
{
	LEFT_JOYSTICK,
	RIGHT_JOYSTICK,
	SPLIT_JOYSTICK_L,
	SPLIT_JOYSTICK_R
};

byte ds_aJoystick[] = {0, 0};

// Index 0: Turn state.
// Index 1: Turn button state.
bool ds_aTurnStates[] = {false, false};

/****************************************************************/

int runDriveSystem();

int setDriveSpeed(short nPower);
int setDriveSpeed(short nPowerLF, short nPowerRF, short nPowerLB, short nPowerRB);

bool isSlowTurning();
void setSlowTurning(bool bValue);
bool isSlowTurnButtonPressed();
void setSlowTurnButtonPressed(bool bValue);

/****************************************************************/

task driveSystem()
{
	while (true)
	{
		if (vexRT[DS_SLOW_TURN_BUTTON] && !isSlowTurnButtonPressed())
		{
			setSlowTurning(!isSlowTurning());
			setSlowTurnButtonPressed(true);
		}
		else if (!vexRT[DS_SLOW_TURN_BUTTON])
		{
			setSlowTurnButtonPressed(false);
		}

		runDriveSystem();
	}
}

/****************************************************************/

/*
	Read controller inputs from the controller.

	@nJoystick: Tells which joystick to use. Refer to enum above.
*/
int runDriveSystem()
{
	switch (DS_JOYSTICK_MODE)
	{
		case LEFT_JOYSTICK:
			ds_aJoystick[0] = vexRT[Ch4];
			ds_aJoystick[1] = vexRT[Ch3];
			break;

		case RIGHT_JOYSTICK:
			ds_aJoystick[0] = vexRT[Ch1];
			ds_aJoystick[1] = vexRT[Ch2];
			break;
		case SPLIT_JOYSTICK_R:
			ds_aJoystick[0] = vexRT[Ch4];
			ds_aJoystick[1] = vexRT[Ch2];
			break;
		case SPLIT_JOYSTICK_L:
		default:
			ds_aJoystick[0] = vexRT[Ch1];
			ds_aJoystick[1] = vexRT[Ch3];
			break;
	}

	if (abs(ds_aJoystick[0]) > DS_DEADBAND || abs(ds_aJoystick[1]) > DS_DEADBAND)
	{
		short nNewJoystickY = (DS_SLOW_TURN_RATIO * ds_aJoystick[0]);
		setDriveSpeed(
			roundToLimit(ds_aJoystick[1] + nNewJoystickY, -127, 127),
			roundToLimit(ds_aJoystick[1] - nNewJoystickY, -127, 127),
			roundToLimit(ds_aJoystick[1] + nNewJoystickY, -127, 127),
			roundToLimit(ds_aJoystick[1] - nNewJoystickY, -127, 127)
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

bool isSlowTurning()
{
	return ds_aTurnStates[0];
}

void setSlowTurning(bool bValue)
{
	ds_aTurnStates[0] = bValue;
}

bool isSlowTurnButtonPressed()
{
	return ds_aTurnStates[1];
}

void setSlowTurnButtonPressed(bool bValue)
{
	ds_aTurnStates[1] = bValue;
}

#endif
