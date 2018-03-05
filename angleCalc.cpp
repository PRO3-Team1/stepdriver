/*
 * AngleCalc.c
 *
 *  Created on: 26. feb. 2018
 *      Author: Mich
 *      returns 0 on OK
 *      returns 1 on wrong input
 */
#include <math.h>
#include <stdio.h>

float deg = 0.1; // 6 deg void

extern double lRatio;
extern double rRatio;

int angleCalc(double Ang)
{

	/* forward and right */

	if ((0 <= Ang) && (Ang < M_PI_2-deg))
	{
		rRatio = sin(Ang);
		lRatio = 1;
		return 0;
	}

	/* forward and left */

	else if ((M_PI_2+deg < Ang) && (Ang <= M_PI))
	{
		rRatio = 1;
		lRatio = sin(Ang);
		return 0;
	}

	/* Back and left */

	else if ((M_PI < Ang) && (Ang <= M_PI+M_PI_2))
	{
		rRatio = -1;
		lRatio = sin(Ang);
		return 0;
	}

	/* Back and right */

	else if ((M_PI+M_PI_2 < Ang) && (Ang < M_PI*2))
	{
		rRatio = sin(Ang);
		lRatio = -1;
		return 0;
	}

	else
	{
		rRatio = 1;
		lRatio = 1;
		return 0;
		//printf("Full forward\n");
	}

	/* End section from -Phi to 0 */

	printf("THIS SHOULD NEVER BE PRINTED\n");
	return 1;
}

