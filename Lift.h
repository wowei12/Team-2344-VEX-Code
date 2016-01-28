#ifndef INCLUDE_LIFT_H
#define INCLUDE_LIFT_H

/****************************************************************/

#define LIFT_BUTTON_FORWARD 		Btn6U
#define LIFT_BUTTON_BACKWARD		Btn6D
#define INTAKE_BUTTON_FORWARD		Btn5U
#define INTAKE_BUTTON_BACKWARD	Btn5D

#define LIFT_SPEED	127

/****************************************************************/

bool bLiftActive = false;
bool bIntakeActive = false;

/****************************************************************/

int setLiftSpeed(short nPower);
int setIntakeSpeed(short nPower);

bool isLiftActive();
int setLiftActive(bool bValue);

bool isIntakeActive();
int setIntakeActive(bool bValue);

/****************************************************************/

task lift()
{
	while (true)
	{
		if (vexRT[LIFT_BUTTON_FORWARD])
		{
			setLiftSpeed(LIFT_SPEED);
			setLiftActive(true);
		}
		else if (vexRT[LIFT_BUTTON_BACKWARD])
		{
			setLiftSpeed(-LIFT_SPEED);
			setLiftActive(true);
		}
		else
		{
			setLiftActive(false);
			setLiftSpeed(0);
			//setLiftSpeed(LIFT_SPEED);
		}

		if (vexRT[INTAKE_BUTTON_FORWARD])
		{
			setIntakeSpeed(LIFT_SPEED);
			setIntakeActive(true);
		}
		else if (vexRT[INTAKE_BUTTON_BACKWARD])
		{
			setIntakeSpeed(-LIFT_SPEED);
			setIntakeActive(true);
		}
		else
		{
			setIntakeSpeed(0);
			setIntakeActive(false);
		}
	}
}

/****************************************************************/

int setLiftSpeed(short nPower)
{
	byte newPower = roundToLimit(nPower, -127, 127);

	motor[liftMotor2] = newPower;

	return 1;
}

int setIntakeSpeed(short nPower)
{
	byte newPower = roundToLimit(nPower, -127, 127);

	motor[liftMotor1] = newPower;

	return 1;
}

bool isLiftActive()
{
	return bLiftActive;
}

int setLiftActive(bool bValue)
{
	bLiftActive = bValue;

	return 1;
}

bool isIntakeActive()
{
	return bIntakeActive;
}

int setIntakeActive(bool bValue)
{
	bIntakeActive = bValue;

	return 1;
}

/****************************************************************/

#endif
