#ifndef INCLUDE_DRIVESYSTEM_H
#define INCLUDE_DRIVESYSTEM_H

/****************************************************************/

#define DS_DEADBAND 						5

#define DS_SLOW_TURN_RATIO			0.5
#define DS_MAX_SPEED						120

#define DS_EPSILON							1
#define DS_INTEGRAL_DUMP				500
#define DS_PROPORTION_CONST			0.01
#define DS_INTEGRAL_CONST				0.0
#define DS_DERIVATIVE_CONST			0.0

/****************************************************************/

typedef enum DS_JOYSTICK_MODES
{
	LEFT_JOYSTICK,
	RIGHT_JOYSTICK,
	SPLIT_JOYSTICK_L,
	SPLIT_JOYSTICK_R
};

typedef struct
{
	int x;
	int y;
}
Joystick_t;

typedef struct
{
	bool active;
	int leftPower;
	int rightPower;

	bool slowTurning;
	bool slowTurningPressed;
}
DriveSystem_t

/****************************************************************/

Joystick_t driveJoystick;
DriveSystem_t driveSystem;

/****************************************************************/

void incDriveSpeed(byte side);

void driveMtr(int power);
void driveMtr(int leftPower, int rightPower);

bool isSlowTurning();
void setSlowTurning(bool bValue);
bool isSlowTurnButtonPressed();
void setSlowTurnButtonPressed(bool bValue);

/****************************************************************/

task driveSystemTask()
{
	while (true)
	{
		int rstval = 0;
		ioctl(0x1, IO_DIG_SET, &rstval);
		ioctl(0x3, IO_DIG_SET, &rstval);
		//incDriveSpeed(0);
		//incDriveSpeed(1);
		wait1Msec(125);

		int sensrvals[] = {0, 0};
		//ioctl(0x1, IO_DIG_SET, &ds_aCurrentSpeed[0]);
		//ioctl(0x3, IO_DIG_SET, &ds_aCurrentSpeed[1]);
	}
}

/****************************************************************/

// side = 0 means left
// side = 1 means right

void incDriveSpeed(byte side)
{
	nNewRate = 0;

	ds_aPID[side][0] = 0;

	if (ds_aRequestedSpeed[side] == 0)
	{
		setDsMotorSpeed(0);
	}
	else
	{
		int error = ds_aRequestedSpeed[side] - ds_aCurrentSpeed[side];

		if (abs(ds_aPID[side][1]) >= DS_INTEGRAL_DUMP)
		{
			ds_aPID[side][1] = 0;
		}
		if (abs(error) > DS_EPSILON)
		{
			ds_aPID[side][1] += error;
		}

		int proportionValue = DS_PROPORTION_CONST * error;
		int integralValue = DS_INTEGRAL_CONST * ds_aPID[side][1];
		int derivativeValue = DS_DERIVATIVE_CONST * (error - ds_aPID[side][2]);

		nNewRate = proportionValue + integralValue + derivativeValue;

		if (side == 0)
		{
			setDsMotorSpeed(ds_aMotorPower[side] + nNewRate, -500);
		}
		else if (side == 1)
		{
			setDsMotorSpeed(-500, ds_aMotorPower[side] + nNewRate);
		}

		ds_aPID[side][2] = error;
	}
}

void setDsMotorSpeed(short nPower)
{
	ds_aMotorPower[0] = roundToLimit(nPower, -127, 127);
	ds_aMotorPower[1] = roundToLimit(nPower, -127, 127);

	motor[leftFrontMotor] = nPower;
	motor[rightFrontMotor] = nPower;
	motor[leftBackMotor] = nPower;
	motor[rightBackMotor] = nPower;
}

void setDsMotorSpeed(short nPowerL, short nPowerR)
{
	if (nPowerL != -500)
	{
		ds_aMotorPower[0] = roundToLimit(nPowerL, -127, 127);
		motor[leftFrontMotor] = ds_aMotorPower[0];
		motor[leftBackMotor] = ds_aMotorPower[0];
	}

	if (nPowerR != -500)
	{
		ds_aMotorPower[1] = roundToLimit(nPowerR, -127, 127);
		motor[rightFrontMotor] = ds_aMotorPower[1];
		motor[rightBackMotor] = ds_aMotorPower[1];
	}
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
