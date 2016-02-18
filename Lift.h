#ifndef INCLUDE_LIFT_H
#define INCLUDE_LIFT_H

/****************************************************************/

#define LIFT_SPEED	127
#define INTAKE_SPEED 127

/****************************************************************/

typedef struct
{
	bool active;
	int power;
}
Lift_t;

typedef struct
{
	bool active;
	int power;
}
Intake_t;

/****************************************************************/

Lift_t lift;
Intake_t intake;

/****************************************************************/

void liftMtr(int power);
void intakeMtr(int power);

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

void liftMtr(int power)
{
	ioctl(liftMotor2, IO_MTR_SET, &power);
}

void intakeMtr(int power)
{
	ioctl(liftMotor1, IO_MTR_SET, &power);
}

/****************************************************************/

#endif
