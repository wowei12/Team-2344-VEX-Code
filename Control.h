#ifndef INCLUDE_CONTROL_H
#define INCLUDE_CONTROL_H

/****************************************************************/

#define SHOOTER_OFF_BUTTON					Btn8L
#define SHOOTER_LOW_BUTTON					Btn8D
#define SHOOTER_MID_BUTTON					Btn8R
#define SHOOTER_MAX_BUTTON					Btn8U
#define SHOOTER_REVERSE_BUTTON			Btn7D
#define SHOOTER_INC_BUTTON 					Btn5U
#define SHOOTER_DEC_BUTTON 					Btn5D


#define DS_SLOWTURN_BUTTON 					Btn7R
#define DS_SLOWTURN_RATIO						0.5
#define DS_JOYSTICK_MODE						SPLIT_JOYSTICK_L
#define DS_JOYSTICK_DEADBAND 				5

#define LIFT_FORWARD_BUTTON 				Btn6U
#define LIFT_BACKWARD_BUTTON				Btn6D

#define INTAKE_FORWARD_BUTTON				Btn5U
#define INTAKE_BACKWARD_BUTTON				Btn5D

/****************************************************************/

void shooterctl();
void drivectl();
void liftctl();
void intakectl();

/****************************************************************/

task controlTask()
{
	switch (DS_JOYSTICK_MODE)
	{
	case LEFT_JOYSTICK:
		driveJoystick.x = &vexRT[Ch4];
		driveJoystick.y = &vexRT[Ch3];
		break;
	case RIGHT_JOYSTICK:
		driveJoystick.x = &vexRT[Ch1];
		driveJoystick.y = &vexRT[Ch2];
		break;
	case SPLIT_JOYSTICK_R:
		driveJoystick.x = &vexRT[Ch4];
		driveJoystick.y = &vexRT[Ch2];
		break;
	case SPLIT_JOYSTICK_L:
	default:
		driveJoystick.x = &vexRT[Ch1];
		driveJoystick.y = &vexRT[Ch3];
		break;
	}

	while (true)
	{
		shooterctl();
		drivectl();
		liftctl();
		intakectl();
	}
}

/****************************************************************/

void shooterctl()
{
	if (vexRT[SHOOTER_MAX_BUTTON])
	{
		shooterPID.requestedSpeed = SHOOTER_MAX_SPEED;
	}
	else if (vexRT[SHOOTER_MID_BUTTON])
	{
		shooterPID.requestedSpeed = SHOOTER_MID_SPEED;
	}
	else if (vexRT[SHOOTER_LOW_BUTTON])
	{
		shooterPID.requestedSpeed = SHOOTER_LOW_SPEED;
	}
	else if (vexRT[SHOOTER_REVERSE_BUTTON])
	{
		shooterPID.requestedSpeed = SHOOTER_REVERSE_SPEED;
	}
	else if (vexRT[SHOOTER_OFF_BUTTON])
	{
		shooterPID.requestedSpeed = 0.0;
	}

	if (vexRT[SHOOTER_INC_BUTTON] && !shooter.inc)
	{
		shooterPID.requestedSpeed += SHOOTER_INC_RATE;
		shooter.inc = true;
	}
	else if (!vexRT[SHOOTER_INC_BUTTON])
	{
		shooter.inc = false;
	}

	if (vexRT[SHOOTER_DEC_BUTTON] && !shooter.dec)
	{
		shooterPID.requestedSpeed -= SHOOTER_DEC_RATE;
		shooter.dec = true;
	}
	else if (!vexRT[SHOOTER_DEC_BUTTON])
	{
		shooter.dec = false;
	}
}

void drivectl()
{
	if (vexRT[DS_SLOWTURN_BUTTON] && !driveSystem.slowTurningPressed)
	{
		driveSystem.slowTurning = !driveSystem.slowTurning;
		driveSystem.slowTurningPressed = true;
	}
	else if (!vexRT[DS_SLOWTURN_BUTTON])
	{
		driveSystem.slowTurningPressed = false;
	}

	power_t x = *driveJoystick.x;
	power_t y = *driveJoystick.y;

	if (abs(x) > DS_JOYSTICK_DEADBAND || abs(y) > DS_JOYSTICK_DEADBAND)
	{
		if (driveSystem.slowTurning)
		{
			x *= DS_SLOWTURN_RATIO;
		}

		driveSystem.leftPower = y + x;
		driveSystem.rightPower = y - x;
	}
	else
	{
		driveSystem.leftPower = 0;
		driveSystem.rightPower = 0;
	}
}

void liftctl()
{
	if (vexRT[LIFT_FORWARD_BUTTON])
	{
		lift.power = LIFT_SPEED;
	}
	else if (vexRT[LIFT_BACKWARD_BUTTON])
	{
		lift.power = -LIFT_SPEED;
	}
	else
	{
		lift.power = 0;
	}
}

void intakectl()
{
	if (vexRT[INTAKE_FORWARD_BUTTON])
	{
		intake.power = INTAKE_SPEED;
	}
	else if (vexRT[INTAKE_BACKWARD_BUTTON])
	{
		intake.power = -INTAKE_SPEED;
	}
	else
	{
		intake.power = 0;
	}
}
#endif
