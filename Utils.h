#ifndef INCLUDE_UTILS_H
#define INCLUDE_UTILS_H

/****************************************************************/

#define IO_MTR_GET 		0x0
#define IO_MTR_SET 		0x1
#define IO_DIG_GET	 	0x2
#define IO_DIG_SET 		0x3
#define IO_ANA_GET 		0x4
#define IO_ANA_SET 		0x5

#define IOERR_NO_ERROR					0x0
#define IOERR_INDEX_OUTSIDE_BOUNDS		0x1
#define IOERR_INVALID_ARGUMENT			0x2

/****************************************************************/

typedef int	power_t

typedef bool state_t;
typedef bool btnState_t;

typedef int distance_t;
typedef float speed_t;

typedef struct
{
	distance_t displacement;
	speed_t speed;
	speed_t requestedSpeed;

	speed_t error;
	speed_t preError;
	power_t rate;
	distance_t integral;
}
PID_t;

/****************************************************************/

int ioctl(int pd, int opcode, void *args = NULL)
{
	if (opcode == IO_MTR_GET)
	{
		if (pd >= (int)port1 && pd <= (int)port10)
		{
			if (args != NULL)
			{
				power_t *argsCast = (power_t*)args;

				argsCast[0] = motor[pd];
			}
			else
			{
				return IOERR_INVALID_ARGUMENT;
			}
		}
		else
		{
			return IOERR_INDEX_OUTSIDE_BOUNDS;
		}
	}
	else if (opcode == IO_MTR_SET)
	{
		if (pd >= (int)port1 && pd <= (int)port10)
		{
			if (args != NULL)
			{
				power_t *argsCast = (power_t*)args;
				motor[pd] = argsCast[0];
			}
			else
			{
				return IOERR_INVALID_ARGUMENT;
			}
		}
		else
		{
			return IOERR_INDEX_OUTSIDE_BOUNDS;
		}
	}
	else if (opcode == IO_DIG_GET)
	{
		if (pd >= (int)dgtl1 && pd <= (int)dgtl12)
		{
			if (args != NULL)
			{
				power_t *argsCast = (power_t*)args;
				argsCast[0] = SensorValue[pd];
			}
			else
			{
				return IOERR_INVALID_ARGUMENT;
			}
		}
		else
		{
			return IOERR_INDEX_OUTSIDE_BOUNDS;
		}
	}
	else if (opcode == IO_DIG_SET)
	{
		if (pd >= (int)dgtl1 && pd <= (int)dgtl12)
		{
			if (args != NULL)
			{
				power_t *argsCast = (power_t*)args;
				SensorValue[pd] = argsCast[0];
			}
			else
			{
				return IOERR_INVALID_ARGUMENT;
			}
		}
		else
		{
			return IOERR_INDEX_OUTSIDE_BOUNDS;
		}
	}

	else if (opcode == IO_ANA_GET)
	{
		if (pd >= (int)in1 && pd <= (int)in8)
		{
			if (args != NULL)
			{
				power_t *argsCast = (power_t*)args;
				argsCast[0] = SensorValue[pd];
			}
			else
			{
				return IOERR_INVALID_ARGUMENT;
			}
		}
		else
		{
			return IOERR_INDEX_OUTSIDE_BOUNDS;
		}
	}

	else if (opcode == IO_ANA_SET)
	{
		if (pd >= (int)in1 && pd <= (int)in8)
		{
			if (args != NULL)
			{
				power_t *argsCast = (power_t*)args;
				argsCast[0] = SensorValue[pd];
			}
			else
			{
				return IOERR_INVALID_ARGUMENT;
			}
		}
		else
		{
			return IOERR_INDEX_OUTSIDE_BOUNDS;
		}
	}

	return IOERR_NO_ERROR;
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
