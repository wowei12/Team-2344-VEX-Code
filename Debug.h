#ifndef INCLUDE_DEBUG_H
#define INCLUDE_DEBUG_H

/****************************************************************/

/****************************************************************/

int lights[8] = {light0, light1, light2, light3, light4, light5, light6, light7};

byte motorOutput = 0;

/****************************************************************/

void 	displayMotorData();

bool 	getBitState(int value, byte digit);

/****************************************************************/

task debug()
{
	while (true)
	{
		displayMotorData();
	}
}

/****************************************************************/

void displayMotorData()
{
	motorOutput = getShooterSpeed();

	int numberOfBits = sizeof(motorOutput) * 8;

	bool bitState;

	for (int i = 1; i <= numberOfBits; i++)
	{
		bitState = getBitState(motorOutput, i);

		if (bitState)
		{
			SensorValue[lights[i-1]] = 1;
		}
		else
		{
			SensorValue[lights[i-1]] = 0;
		}
	}
}

bool getBitState(int value, byte digit)
{
	int comparative = abs(value) & (1 << (digit - 1));

	if (comparative == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/****************************************************************/

#endif
