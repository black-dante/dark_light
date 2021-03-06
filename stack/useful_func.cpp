#ifndef USEFUL_FUNC
#define USEFUL_FUNC

int comp_double_with_zero(double x);

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function comp_double_with_zero()
 *
 *
 *   @param [out] x number to compare with zero
 *
 *
 *   @return 1: if the number is zero within the margin of error\n
 *           0: if the number is not zero
 */	
int comp_double_with_zero(double x)
	{
		x = x >= 0? x : -x;
		return x < EPSILON? 1: 0;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

#endif