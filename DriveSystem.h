

#ifndef INCLUDE_DRIVESYSTEM_H
#define INCLUDE_DRIVESYSTEM_H

/****************************************************************/

#define ARCADE_MODE 						SPLIT_JOYSTICK_L
#define DEADBAND 5

//#define REVERSE_DRIVE_BUTTON		Btn5U
#define SLOW_TURN_BUTTON 		Btn7R

/****************************************************************/

typedef enum ARCADE_MODES
{
	LEFT_JOYSTICK,
	RIGHT_JOYSTICK,
	SPLIT_JOYSTICK_L,
	SPLIT_JOYSTICK_R
};

byte joystickX = 0;
byte joystickY = 0;

float nNewTurnRatio = 0.5;

bool bStateRDrive = false;
bool bStateRDriveButton = false;

bool bStateSTurn = false;
bool bStateSTurnButton = false;

/****************************************************************/

int runDriveSystem(ARCADE_MODES nJoystick);

int setDriveSpeed(short nPower);
int setDriveSpeed(short nPowerLF, short nPowerRF, short nPowerLB, short nPowerRB);

bool isReversingDrive();
int setReverseDrive(bool bValue);
bool isRDriveButtonPressed();
int setRDriveButtonPressed(bool bValue);

bool isSlowTurning();
int setSlowTurning(bool bValue);
bool isSlowTurnButtonPressed();
int setSlowTurnButtonPressed(bool bValue);

/****************************************************************/

task driveSystem()
{
	while (true)
	{
#ifdef REVERSE_DRIVE_BUTTON
			if (vexRT[REVERSE_DRIVE_BUTTON] && !isRDriveButtonPressed())
			{
				setReverseDrive(!isReversingDrive());
				setRDriveButtonPressed(true);
			}
			else if (!vexRT[REVERSE_DRIVE_BUTTON])
			{
				setRDriveButtonPressed(false);
			}
#endif

			if (vexRT[SLOW_TURN_BUTTON] && !isSlowTurnButtonPressed())
			{
				setSlowTurning(!isSlowTurning());
				setSlowTurnButtonPressed(true);
			}
			else if (!vexRT[SLOW_TURN_BUTTON])
			{
				setSlowTurnButtonPressed(false);
			}

		runDriveSystem(ARCADE_MODE);
	}
}

/****************************************************************/

/*
	Read controller inputs from the controller.

	@nJoystick: Tells which joystick to use. Refer to enum above.
*/
int runDriveSystem(ARCADE_MODES nJoystick)
{
	switch (nJoystick)
	{
		case LEFT_JOYSTICK:
			joystickX = vexRT[Ch4];
			joystickY = vexRT[Ch3];
			break;

		case RIGHT_JOYSTICK:
			joystickX = vexRT[Ch1];
			joystickY = vexRT[Ch2];
			break;

		case SPLIT_JOYSTICK_L:
			joystickX = vexRT[Ch1];
			joystickY = vexRT[Ch3];
			break;

		case SPLIT_JOYSTICK_R:
			joystickX = vexRT[Ch4];
			joystickY = vexRT[Ch2];
			break;

		default:
			joystickX = vexRT[Ch1];
			joystickY = vexRT[Ch3];
			break;
	}

	if (abs(joystickX) > DEADBAND || abs(joystickY) > DEADBAND)
	{
		if (!isSlowTurning()) // isReversingDrive();
		{
			setDriveSpeed(
				joystickY + joystickX,
				joystickY - joystickX,
				joystickY + joystickX,
				joystickY - joystickX
			);
			//setDriveSpeed(
			//	(joystickY + joystickX),
			//	(joystickY - joystickX),
			//	(joystickY + joystickX),
			//	(joystickY - joystickX)
			//);
		}
		else
		{
			setDriveSpeed(
				joystickY + (nNewTurnRatio * joystickX),
				joystickY - (nNewTurnRatio * joystickX),
				joystickY + (nNewTurnRatio * joystickX),
				joystickY - (nNewTurnRatio * joystickX)
			);
			//setDriveSpeed(
			//	-(joystickY - joystickX),
			//	-(joystickY + joystickX),
			//	-(joystickY - joystickX),
			//	-(joystickY + joystickX)
			//);
		}
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

bool isReversingDrive()
{
	return bStateRDrive;
}

int setReverseDrive(bool bValue)
{
	bStateRDrive = bValue;

	return 1;
}

bool isRDriveButtonPressed()
{
	return bStateRDriveButton;
}

int setRDriveButtonPressed(bool bValue)
{
	bStateRDriveButton = bValue;

	return 1;
}


bool isSlowTurning()
{
	return bStateSTurn;
}

int setSlowTurning(bool bValue)
{
	bStateSTurn = bValue;

	return 1;
}

bool isSlowTurnButtonPressed()
{
	return bStateSTurnButton;
}

int setSlowTurnButtonPressed(bool bValue)
{
	bStateSTurnButton = bValue;

	return 1;
}

#endif
