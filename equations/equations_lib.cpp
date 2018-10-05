/*!
\file
\brief library for working with equations
*/

#include "equations_hed.h"
#include "complex_lib.cpp"

double comp_double_with_zero(double x);

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function quadratic_equation()
 *
 *
 *   @param [in] A A-coefficient
 *   @param [in] B B-coefficient
 *   @param [in] C C-coefficient
 *   @param [out] x1 the 1-st solution
 *   @param [out] x2 the 2-nd solution
 *
 *
 *   @return all solutions
 */
 
int quadratic_equation(double A, double B, double C, struct complex_ *x1, struct complex_ *x2)
	{
		assert(! isnan (A) );
		assert(! isnan (B) );
		assert(! isnan (C) );

		assert(! isinf (A) );
		assert(! isinf (B) );
		assert(! isinf (C) );

		assert(x1 != NULL);
		assert(x2 != NULL);
		assert(x1 != x2);
		
		if (comp_double_with_zero(A)) return linear_equation(B, C, &(x1->Re));	//А = 0 => solve the linear equation
			
		if(comp_double_with_zero(B))
			{
				if(comp_double_with_zero(C)) return INFINITY_OF_VALUES;			//B = 0 и C = 0 => infinitely many solutions
					
				else return 0; 													//B = 0 и С != 0 => no solutions
			}
		else
			{
				double square_discrim = B*B - 4*A*C;
					
				if(square_discrim < 0) 
					{
						double discrim = sqrt(-square_discrim);
						x1->Re = -B/(2*A);
						x1->Im = discrim/(2*A);
						
						x2->Re = -B/(2*A);
						x2->Im = -discrim/(2*A);
						
						return TWO_COMPLEX_VALUES;						//the square of the discriminant is less than 0 => two complex roots
					}
				else
					{
						double discrim = sqrt(square_discrim);
							
						if(comp_double_with_zero(discrim))				//the discriminant is 0 => one root x1
							{
								x1->Re = -B/2*A;
								return 1;
							}
						else											//discriminant greater than 0 => two roots x1 and x2
							{
								x1->Re = (-B + discrim)/(2*A);
								x1->Im = 0;
								
								x2->Re = (-B - discrim)/(2*A);
								x2->Im = 0;
								
								return 2;
							}
					}
			}
	}
//}--------------------------------------------------------------------------------------------------------------------------------------	

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function linear_equation()
 *
 *
 *   @param [in] A A-coefficient
 *   @param [in] B B-coefficient
 *   @param [out] x the solution
 *
 *
 *   @return all solutions
 */

int linear_equation(double A, double B, double *x)
	{
		assert(! isnan (A) );
		assert(! isnan (B) );

		assert(! isinf (A) );
		assert(! isinf (B) );

		assert(x != NULL);
		
		if(comp_double_with_zero(A))
			{
				if(comp_double_with_zero(B)) return INFINITY_OF_VALUES;			//A = 0 and B = 0 => infinitely many solutions
					
				else return 0;													//A = 0 and B != 0 => no solutions
			}
		else																	//A != 0 => one root x
			{
				*x = -B/A;
				return 1;
			}
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

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
double comp_double_with_zero(double x)
	{
		x = x >= 0? x : -x;
		return x < EPSILON? 1: 0;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------