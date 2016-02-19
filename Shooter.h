#ifndef INCLUDE_SHOOTER_H
#define INCLUDE_SHOOTER_H

/****************************************************************/

#define SHOOTER_EPSILON								30
#define SHOOTER_PROPORTION_CONST					0.01
#define SHOOTER_INTEGRAL_CONST						0.0
#define SHOOTER_DERIVATIVE_CONST					0.0

#define SHOOTER_LOW_SPEED 							36.0
#define SHOOTER_MID_SPEED 							44.0
#define SHOOTER_MAX_SPEED 							56.0
#define SHOOTER_REVERSE_SPEED						-24.0

#define SHOOTER_INC_RATE 							1.0
#define SHOOTER_DEC_RATE 							1.0

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
		shooterPID.displacement = 0;
		shooterPID.speed = 0;

		wait1Msec(SHOOTER_TICK_HZ);

		ioctl(shooterEncoder, IO_DIG_GET, &shooterPID.displacement);
		shooterPID.speed = shooterPID.displacement / SHOOTER_TICK_HZ;

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
		shooterPID.error = shooterPID.requestedSpeed - shooterPID.speed;

		if (abs(shooterPID.error) > SHOOTER_EPSILON)
		{
			shooterPID.integral += shooterPID.error;
		}

		power_t rate_prop = SHOOTER_PROPORTION_CONST * shooterPID.error;
		power_t rate_integral = SHOOTER_INTEGRAL_CONST * shooterPID.integral;
		power_t rate_der = SHOOTER_DERIVATIVE_CONST * (shooterPID.error - shooterPID.preError);

		shooterPID.rate = rate_prop + rate_integral + rate_der;

		shooter.power += shooterPID.rate;

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
