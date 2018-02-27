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

extern double left;
extern double right;

int angleCalc(double Ang)
{

	/* forward and right */

	if ((0 <= Ang) && (Ang < M_PI_2-deg))
	{
		right = sin(Ang);
		left = 1;
		return 0;
	}

	/* forward and left */

	else if ((M_PI_2+deg < Ang) && (Ang <= M_PI))
	{
		right = 1;
		left = sin(Ang);
		return 0;
	}

	/* Back and left */

	else if ((M_PI < Ang) && (Ang <= M_PI+M_PI_2))
	{
		right = -1;
		left = cos(Ang);
		return 0;
	}

	/* Back and right */

	else if ((M_PI+M_PI_2 < Ang) && (Ang < M_PI*2))
	{
		right = sin(Ang);
		left = -1;
		return 0;
	}

	else
	{
		right = 1;
		left = 1;
		return 0;
		//printf("Full forward\n");
	}

	/* End section from -Phi to 0 */

	printf("THIS SHOULD NEVER BE PRINTED\n");
	return 1;
}

