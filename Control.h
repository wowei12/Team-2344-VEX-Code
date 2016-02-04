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
#define SHOOTER_INC_RATE 25
#define SHOOTER_DEC_RATE 25

#define DS_SLOW_TURN_BUTTON 		Btn7R

/****************************************************************/

void iterateShooterControl();
void iterateShooterIncControl();
void iterateDriveSlowControl();

/****************************************************************/

task control()
{
	while (true)
	{
		iterateShooterControl();
		iterateShooterIncControl();
		iterateDriveSlowControl();
	}
}

/****************************************************************/

void iterateShooterControl()
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
}

void iterateShooterIncControl()
{
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
}

void iterateDriveSlowControl()
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
}

#endif
