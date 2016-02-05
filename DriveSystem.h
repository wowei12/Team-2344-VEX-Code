#ifndef INCLUDE_DRIVESYSTEM_H
#define INCLUDE_DRIVESYSTEM_H

/****************************************************************/

#define DS_JOYSTICK_MODE				SPLIT_JOYSTICK_L
#define DS_DEADBAND 						5

#define DS_SLOW_TURN_RATIO			0.5
#define DS_MAX_SPEED						1000

#define DS_EPSILON							30
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

// 0 = x
// 1 = y
byte ds_aJoystick[] = {0, 0};

// Index 0: Turn state.
// Index 1: Turn button state.
bool 	ds_aTurnStates[] = {false, false};

// 0 = left side
// 1 = right side
float ds_aRequestedSpeed[] = {0, 0};
float ds_aCurrentSpeed[] = {0, 0};
byte 	ds_aMotorPower[] = {0, 0};


// 0 = newRate
// 1 = integral
// 2 = preError
int ds_aPID[][] = {
	{0, 0, 0},
	{0, 0, 0}
};

/****************************************************************/

void incDriveSpeed(byte side);

void setDsMotorSpeed(short nPower);
void setDsMotorSpeed(short nPowerL, short nPowerR);

bool isSlowTurning();
void setSlowTurning(bool bValue);
bool isSlowTurnButtonPressed();
void setSlowTurnButtonPressed(bool bValue);

/****************************************************************/

task driveSystem()
{
	while (true)
	{
		SensorValue[leftDriveEncoder] = 0;
		SensorValue[rightDriveEncoder] = 0;
		incDriveSpeed(0);
		incDriveSpeed(1);
		wait1Msec(125);
		ds_aCurrentSpeed[0] = SensorValue[leftDriveEncoder] / 125.0;
		ds_aCurrentSpeed[1] = SensorValue[rightDriveEncoder] / 125.0;
	}
}

/****************************************************************/

// side = 0 means left
// side = 1 means right

void incDriveSpeed(byte side)
{
	int nNewRate = 0;

	ds_aPID[side][0] = 0;

	if (ds_aRequestedSpeed[side] == 0)
	{
		ds_aCurrentSpeed[side] = 0;
	}
	else
	{
		int error = ds_aRequestedSpeed[side] - ds_aCurrentSpeed[side];

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
			setDsMotorSpeed(ds_aMotorPower[side] + nNewRate, -1);
		}
		else if (side == 1)
		{
			setDsMotorSpeed(-1, ds_aMotorPower[side] + nNewRate);
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
	if (nPowerL > -1)
	{
		ds_aMotorPower[0] = roundToLimit(nPowerL, -127, 127);
		motor[leftFrontMotor] = roundToLimit(nPowerL, -127, 127);
		motor[rightFrontMotor] = roundToLimit(nPowerR, -127, 127);
	}

	if (nPowerR > -1)
	{
		ds_aMotorPower[1] = roundToLimit(nPowerR, -127, 127);
		motor[leftBackMotor] = roundToLimit(nPowerL, -127, 127);
		motor[rightBackMotor] = roundToLimit(nPowerR, -127, 127);
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
