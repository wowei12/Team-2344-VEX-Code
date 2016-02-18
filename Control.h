#ifndef INCLUDE_CONTROL_H
#define INCLUDE_CONTROL_H

/****************************************************************/

#define SHOOTER_BUTTON_OFF						Btn8L
#define SHOOTER_BUTTON_LOW_SPEED			Btn8D
#define SHOOTER_BUTTON_MID_SPEED			Btn8R
#define SHOOTER_BUTTON_MAX_SPEED			Btn8U
#define SHOOTER_REVERSE_BUTTON				Btn7D
#define SHOOTER_BUTTON_INCREASE 			Btn5U
#define SHOOTER_BUTTON_DECREASE 			Btn5D

#define DS_JOYSTICK_MODE							SPLIT_JOYSTICK_L
#define DS_SLOW_TURN_BUTTON 					Btn7R

#define LIFT_BUTTON_FORWARD 					Btn6U
#define LIFT_BUTTON_BACKWARD					Btn6D

#define INTAKE_BUTTON_FORWARD					Btn5U
#define INTAKE_BUTTON_BACKWARD				Btn5D

/****************************************************************/

void shooterctl();
void drivectl();
void liftctl();
void intakectl();

/****************************************************************/

task controlTask()
{
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
	if (vexRT[SHOOTER_BUTTON_MAX_SPEED])
	{
		shooterPID.requestedSpeed = SHOOTER_MAX_SPEED;
	}
	else if (vexRT[SHOOTER_BUTTON_MID_SPEED])
	{
		shooterPID.requestedSpeed = SHOOTER_MID_SPEED;
	}
	else if (vexRT[SHOOTER_BUTTON_LOW_SPEED])
	{
		shooterPID.requestedSpeed = SHOOTER_LOW_SPEED;
	}
	else if (vexRT[SHOOTER_REVERSE_BUTTON])
	{
		shooterPID.requestedSpeed = SHOOTER_REVERSE_SPEED;
	}
	else if (vexRT[SHOOTER_BUTTON_OFF])
	{
		shooterPID.requestedSpeed = 0.0;
	}

	if (vexRT[SHOOTER_BUTTON_INCREASE] && !shooter.inc)
	{
		shooterPID.requestedSpeed += SHOOTER_INC_RATE;
		shooter.inc = true;
	}
	else if (!vexRT[SHOOTER_BUTTON_INCREASE])
	{
		shooter.inc = false;
	}

	if (vexRT[SHOOTER_BUTTON_DECREASE] && !shooter.dec)
	{
		shooterPID.requestedSpeed -= SHOOTER_DEC_RATE;
		shooter.dec = true;
	}
	else if (!vexRT[SHOOTER_BUTTON_DECREASE])
	{
		shooter.dec = false;
	}
}

void drivectl()
{
	if (vexRT[DS_SLOW_TURN_BUTTON] && !isSlowTurnButtonPressed())
	{
		setSlowTurning(!isSlowTurning());
		setSlowTurnButtonPressed(true);
	}
	else if (!vexRT[DS_SLOW_TURN_BUTTON])
	{
		setSlowTurnButtonPressed(false);
	}

	switch (DS_JOYSTICK_MODE)
	{
		case LEFT_JOYSTICK:
			ds_aJoystick[0] = vexRT[Ch4];
			ds_aJoystick[1] = vexRT[Ch3];
			break;
		case RIGHT_JOYSTICK:
			ds_aJoystick[0] = vexRT[Ch1];
			ds_aJoystick[1] = vexRT[Ch2];
			break;
		case SPLIT_JOYSTICK_R:
			ds_aJoystick[0] = vexRT[Ch4];
			ds_aJoystick[1] = vexRT[Ch2];
			break;
		case SPLIT_JOYSTICK_L:
		default:
			ds_aJoystick[0] = vexRT[Ch1];
			ds_aJoystick[1] = vexRT[Ch3];
			break;
	}

	if (abs(ds_aJoystick[0]) > DS_DEADBAND || abs(ds_aJoystick[1]) > DS_DEADBAND)
	{
		short nNewJoystickY = (DS_SLOW_TURN_RATIO * ds_aJoystick[0]);

		setDsMotorSpeed((ds_aJoystick[1] + nNewJoystickY), (ds_aJoystick[1] - nNewJoystickY));
	}
	else
	{
		setDsMotorSpeed(0, 0);
	}
}

void liftctl()
{
	if (vexRT[LIFT_BUTTON_FORWARD])
	{
		lift.power = LIFT_SPEED;
	}
	else if (vexRT[LIFT_BUTTON_BACKWARD])
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
	if (vexRT[INTAKE_BUTTON_FORWARD])
	{
		intake.power = INTAKE_SPEED;
	}
	else if (vexRT[INTAKE_BUTTON_BACKWARD])
	{
		intake.power = -INTAKE_SPEED;
	}
	else
	{
		intake.power = 0;
	}
}
#endif
