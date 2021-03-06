#ifndef INCLUDE_SHOOTER_H
#define INCLUDE_SHOOTER_H

/****************************************************************/

#define SHOOTER_BUTTON_OFF						Btn8L
#define SHOOTER_BUTTON_LOW_SPEED			Btn8D
#define SHOOTER_BUTTON_MID_SPEED			Btn8R
#define SHOOTER_BUTTON_MAX_SPEED			Btn8U
#define SHOOTER_REVERSE_BUTTON				Btn7D
#define SHOOTER_BUTTON_INCREASE 			Btn5U
#define SHOOTER_BUTTON_DECREASE 			Btn5D

#define SHOOTER_INC_RATE 25
#define SHOOTER_DEC_RATE 25

#define SHOOTER_EPSILON								30
#define SHOOTER_PROPORTION_CONST			0.01
#define SHOOTER_INTEGRAL_CONST				0.0
#define SHOOTER_DERIVATIVE_CONST			0.027

#define SHOOTER_LOW_SPEED 						900 //CHECK // 2000
#define SHOOTER_MID_SPEED 						1100 //CHECK // 2300
#define SHOOTER_MAX_SPEED 						1400 //CHECK // 2600
#define SHOOTER_REVERSE_SPEED					-600


/****************************************************************/

bool bShooterActive = false;
bool bShooterIncreaseState = false;
bool bShooterDecreaseState = false;

int nRequestedSpeed	= 0;
int nCurrentSpeed		= 0;
byte nMotorPower = 0;

int newRate = 0;
int	integral = 0;
int preError = 0;

/****************************************************************/

task 	constantRamp();

int		incShooterSpeed();

int		getShooterRequestedSpeed();
int		setShooterRequestedSpeed(int nSpeed);

int		getShooterSpeed();
int		setShooterSpeed(int nSpeed);

byte 	getShooterMotorPower();
int 	setShooterMotorPower(short nPower);

int		getShooterEncoderValue();
int		setShooterEncoderValue(int nValue);

bool	isShooterActive();
int		setShooterActive(bool bValue);

bool	isShooterIncreaseActive();
int		setShooterIncrease(bool bValue);

bool	isShooterDecreaseActive();
int		setShooterDecrease(bool bValue);

//short getRampRate();

/****************************************************************/

task shooter()
{
	startTask(constantRamp);

	while (true)
	{
		if (vexRT[SHOOTER_BUTTON_MAX_SPEED])
		{
			setShooterRequestedSpeed(SHOOTER_MAX_SPEED);
			setShooterActive(true);
		}
		else if (vexRT[SHOOTER_BUTTON_MID_SPEED])
		{
			setShooterRequestedSpeed(SHOOTER_MID_SPEED);
			setShooterActive(true);
		}
		else if (vexRT[SHOOTER_BUTTON_LOW_SPEED])
		{
			setShooterRequestedSpeed(SHOOTER_LOW_SPEED);
			setShooterActive(true);
		}
		else if (vexRT[SHOOTER_REVERSE_BUTTON]){
			setShooterRequestedSpeed(SHOOTER_REVERSE_SPEED);
			setShooterActive(true);
		}
		else if (vexRT[SHOOTER_BUTTON_OFF])
		{
			setShooterRequestedSpeed(0);
			setShooterActive(false);
		}

		if (vexRT[SHOOTER_BUTTON_INCREASE] && !isShooterIncreaseActive())
		{
			setShooterRequestedSpeed(getShooterRequestedSpeed() + SHOOTER_INC_RATE);
			setShooterIncrease(true);
		}
		else if (!vexRT[SHOOTER_BUTTON_INCREASE])
		{
			setShooterIncrease(false);
		}

		if (vexRT[SHOOTER_BUTTON_DECREASE] && !isShooterDecreaseActive())
		{
			setShooterRequestedSpeed(getShooterRequestedSpeed() - SHOOTER_DEC_RATE);
			setShooterDecrease(true);
		}
		else if (!vexRT[SHOOTER_BUTTON_DECREASE])
		{
			setShooterDecrease(false);
		}

		//setShooterRequestedSpeed(SHOOTER_LOW_SPEED);
	}
}

task constantRamp()
{
	while (true)
	{
		setShooterEncoderValue(0);
		incShooterSpeed();
		wait1Msec(125);
		setShooterSpeed(getShooterEncoderValue());
	}
}

/****************************************************************/

int incShooterSpeed()
{
	newRate = 0;

	if (getShooterRequestedSpeed() == 0)
	{
		setShooterMotorPower(0);
	}
	else
	{
		int nError = getShooterRequestedSpeed() - getShooterSpeed();

		if (abs(nError) > SHOOTER_EPSILON)
		{
			integral += nError;
		}

		int nProportion = SHOOTER_PROPORTION_CONST * nError;
		int nIntegral = SHOOTER_INTEGRAL_CONST * integral;
		int nDerivative = SHOOTER_DERIVATIVE_CONST * (nError - preError);

		newRate = nProportion + nIntegral + nDerivative;

		setShooterMotorPower(getShooterMotorPower() + newRate);

		preError = nError;
	}

	return 1;
}

/****************************************************************/

int getShooterRequestedSpeed()
{
	return nRequestedSpeed;
}

int	setShooterRequestedSpeed(int nSpeed)
{
	nRequestedSpeed = nSpeed;

	return 1;
}


int getShooterSpeed()
{
	return nCurrentSpeed;
}

int setShooterSpeed(int nSpeed)
{
	nCurrentSpeed = nSpeed;

	return 1;
}


byte getShooterMotorPower()
{
	return nMotorPower;
}

int setShooterMotorPower(short nPower)
{
	byte newPower = roundToLimit(nPower, -127, 127);

	nMotorPower = newPower;

	motor[shooterMotor1] = newPower;
	motor[shooterMotor2] = newPower;
	motor[shooterMotor3] = newPower;
	motor[shooterMotor4] = newPower;

	return 1;
}


int	getShooterEncoderValue()
{
	return SensorValue[shooterEncoder];
}

int	setShooterEncoderValue(int nValue)
{
	SensorValue[shooterEncoder] = nValue;

	return 1;
}


bool isShooterActive()
{
	return bShooterActive;
}

int setShooterActive(bool bValue)
{
	bShooterActive = bValue;

	return 1;
}


bool isShooterIncreaseActive()
{
	return bShooterIncreaseState;
}

int setShooterIncrease(bool bValue)
{
	bShooterIncreaseState = bValue;

	return 1;
}


bool isShooterDecreaseActive()
{
	return bShooterDecreaseState;
}

int	setShooterDecrease(bool bValue)
{
	bShooterDecreaseState = bValue;

	return 1;
}


/****************************************************************/

#endif
