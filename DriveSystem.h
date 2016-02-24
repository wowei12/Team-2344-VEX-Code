#ifndef INCLUDE_DRIVESYSTEM_H
#define INCLUDE_DRIVESYSTEM_H


/****************************************************************/

enum DS_JOYSTICK_MODES
{
	LEFT_JOYSTICK,
	RIGHT_JOYSTICK,
	SPLIT_JOYSTICK_L,
	SPLIT_JOYSTICK_R
};

/****************************************************************/

typedef struct
{
	word x;
	word y;
}
joystick_t;

typedef struct
{
	bool active;

	power_t leftPower;
	power_t rightPower;

	state_t slowTurning;

	btnState_t slowTurningPressed;
}
DriveSystem_t;

/****************************************************************/

joystick_t driveJoystick;
DriveSystem_t driveSystem;

/****************************************************************/

void driveMtr(power_t power);
void driveMtr(power_t leftPower, power_t rightPower);

/****************************************************************/

task driveSystemTask()
{
	driveJoystick.x = vexRT[Ch1];
	driveJoystick.y = vexRT[Ch3];

	driveSystem.active = false;
	driveSystem.leftPower = 0;
	driveSystem.rightPower = 0;
	driveSystem.slowTurning = false;
	driveSystem.slowTurningPressed = false;

	while (true)
	{
		driveMtr(driveSystem.leftPower, driveSystem.rightPower);

		if (driveSystem.leftPower != 0 && driveSystem.rightPower != 0)
		{
			driveSystem.active = true;
		}
		else
		{
			driveSystem.active = false;
		}
	}
}

/****************************************************************/

void driveMtr(power_t power)
{
	ioctl(leftFrontMotor, IO_MTR_SET, &power);
	ioctl(leftBackMotor, IO_MTR_SET, &power);
	ioctl(rightFrontMotor, IO_MTR_SET, &power);
	ioctl(rightBackMotor, IO_MTR_SET, &power);
}

void driveMtr(power_t leftPower, power_t rightPower)
{
	ioctl(leftFrontMotor, IO_MTR_SET, &leftPower);
	ioctl(leftBackMotor, IO_MTR_SET, &leftPower);

	ioctl(rightFrontMotor, IO_MTR_SET, &rightPower);
	ioctl(rightBackMotor, IO_MTR_SET, &rightPower);
}

#endif
