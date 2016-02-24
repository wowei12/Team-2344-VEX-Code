#ifndef INCLUDE_SHOOTER_H
#define INCLUDE_SHOOTER_H

/****************************************************************/

#define SHOOTER_INTEGRAL_CAP					2000
#define SHOOTER_PROPORTION_CONST			0.09
#define SHOOTER_INTEGRAL_CONST				0.0
#define SHOOTER_DERIVATIVE_CONST			1.0

#define SHOOTER_LOW_SPEED 						300
#define SHOOTER_MID_SPEED 						400
#define SHOOTER_MAX_SPEED 						600
#define SHOOTER_REVERSE_SPEED					-200

#define SHOOTER_INC_RATE 							25
#define SHOOTER_DEC_RATE 							25

#define SHOOTER_TICK_HZ 							125


/****************************************************************/

typedef struct
{
	state_t active;

	power_t power;

	btnState_t inc; // increment
	btnState_t dec; // decrement
}
Shooter_t;

/****************************************************************/

Shooter_t		shooter;
PID_t 			shooterPID;

/****************************************************************/

void	iterateShooterPID();
void 	shooterMtr(power_t power);

/****************************************************************/

task shooterTask()
{
	shooter.active = false;
	shooter.power = 0;
	shooter.inc = false;
	shooter.dec = false;

	shooterPID.displacement = 0;
	shooterPID.speed = 0.0;
	shooterPID.requestedSpeed = 0.0;
	shooterPID.error = 0.0;
	shooterPID.preError = 0.0;
	shooterPID.rate = 0;
	shooterPID.integral = 0;

	while (true)
	{
		int resetValue = 0;
		ioctl(shooterEncoder, IO_DIG_SET, &resetValue);

		wait1Msec(SHOOTER_TICK_HZ);

		ioctl(shooterEncoder, IO_DIG_GET, &shooterPID.displacement);
		shooterPID.speed = (float)shooterPID.displacement;

		iterateShooterPID();

		shooterMtr(shooter.power);
		shooter.active = (shooter.power != 0) ? true : false;
	}
}

/****************************************************************/

void iterateShooterPID()
{
	shooterPID.rate = 0;

	if (shooterPID.requestedSpeed == 0)
	{
		shooter.power = 0;
	}
	else
	{
		shooterPID.error = (shooterPID.requestedSpeed - shooterPID.speed);

		shooterPID.integral += shooterPID.error * SHOOTER_TICK_HZ;
		shooterPID.integral = roundToLimit(round(shooterPID.integral), -SHOOTER_INTEGRAL_CAP, SHOOTER_INTEGRAL_CAP);

		static float rate_prop = 0.0;
		static float rate_integral = 0.0;
		static float rate_der = 0.0;

		rate_prop = (SHOOTER_PROPORTION_CONST * shooterPID.error);
		rate_integral = (SHOOTER_INTEGRAL_CONST * shooterPID.integral);
		rate_der = (SHOOTER_DERIVATIVE_CONST * (shooterPID.error - shooterPID.preError));

		shooterPID.rate = rate_prop + rate_integral + rate_der;

		shooter.power += shooterPID.rate;

		if (shooterPID.requestedSpeed/abs(shooterPID.requestedSpeed) == 1)
		{
			shooter.power = roundToLimit(shooter.power, 0, 128);
		}
		else
		{
			shooter.power = roundToLimit(shooter.power, 0, -128);
		}


		shooterPID.preError = shooterPID.error;
	}
}

/****************************************************************/


void shooterMtr(power_t power)
{
	ioctl(shooterMotor1, IO_MTR_SET, &power);
	ioctl(shooterMotor2, IO_MTR_SET, &power);
	ioctl(shooterMotor3, IO_MTR_SET, &power);
	ioctl(shooterMotor4, IO_MTR_SET, &power);
}

/****************************************************************/

#endif
