#ifndef INCLUDE_LIFT_H
#define INCLUDE_LIFT_H

/****************************************************************/

#define LIFT_POWER	100
#define INTAKE_POWER 127

/****************************************************************/

typedef struct
{
	state_t active;
	power_t power;
}
Lift_t;

typedef struct
{
	state_t active;
	power_t power;
}
Intake_t;

/****************************************************************/

Lift_t lift;
Intake_t intake;

/****************************************************************/

void liftMtr(power_t power);
void intakeMtr(power_t power);

/****************************************************************/

task liftTask()
{
	lift.active = false;
	lift.power = 0;

	intake.active = false;
	intake.power = 0;

	while (true)
	{
		liftMtr(lift.power);
		intakeMtr(intake.power);

		lift.active = (lift.power != 0) ? true : false;
		intake.active = (intake.power != 0) ? true : false;
	}
}

/****************************************************************/

void liftMtr(power_t power)
{
	ioctl(liftMotor2, IO_MTR_SET, &power);
}

void intakeMtr(power_t power)
{
	ioctl(liftMotor1, IO_MTR_SET, &power);
}

/****************************************************************/

#endif
