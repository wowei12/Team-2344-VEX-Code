#ifndef INCLUDE_UTILS_H
#define INCLUDE_UTILS_H

/****************************************************************/

#define ANA_MTR_GET 		0x0
#define ANA_MTR_SET 		0x1
#define DIG_GET	 		0x2
#define DIG_SET 		0x3
#define ANA_GET 		0x4
#define ANA_SET 		0x5

/****************************************************************/

int ioctl(int pd, int opcode, int *args)
{
	if (opcode == ANA_MTR_GET)
	{
		motor[pd] = args[0];
	}
	else if (opcode == ANA_MTR_SET)
	{
		args[0] = motor[pd];
	}
	else if (opcode == DIG_GET)
	{
		SensorValue[pd] = args[0]
	}
	else if (opcode == DIG_SET)
	{
		args[0] = SensorValue[pd];
	}
	else if (opcode == ANA_SET)
	{
		args[0] = SensorValue[pd];
	}
}

/****************************************************************/

/*
	Rounds nValue to the following nStart and nEnd if it is less than or greater than.
	Useful for rounding down power in motors.
*/
int roundToLimit(int nValue, int nStart, int nEnd)
{
	int initialRange = 0;
	int finalRange = 0;

	if (nStart < nEnd)
	{
		initialRange = nStart;
		finalRange = nEnd;
	}
	else
	{
		initialRange = nEnd;
		initialRange = nStart;
	}

	if (nValue < nStart)
	{
		nValue = nStart;
	}
	else if (nValue > nEnd)
	{
		nValue = nEnd;
	}

	return nValue;
}

/****************************************************************/

#endif
