#ifndef INCLUDE_UTILS_H
#define INCLUDE_UTILS_H

/****************************************************************/

/****************************************************************/



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
