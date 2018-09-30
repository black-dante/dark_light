/*!
\file
\brief library for working with equations
*/

#include "equations_hed.h"
#include "complex_lib.cpp"

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
		
		if (abs_double(A) < EPSILON) return linear_equation(B, C, &(x1->Re));	//А = 0 => solve the linear equation
			
		if(abs_double(B) < EPSILON)
			{
				if(abs_double(C) < EPSILON) return INFINITY_OF_VALUES;			//B = 0 и C = 0 => infinitely many solutions
					
				else return 0; 													//B = 0 и С != 0 => no solutions
			}
		else
			{
				double square_discrim = B*B -4*A*C;
					
				if(square_discrim < 0) 
					{
						double discrim = sqrt(-square_discrim);
						x1->Re = -B/(2*A);
						x1->Im = discrim/(2*A);
						
						x2->Re = -B/(2*A);
						x2->Im = -discrim/(2*A);
						
						return TWO_COMPLEX_VALUES;								//the square of the discriminant is less than 0 => two complex roots
					}
				else
					{
						double discrim = sqrt(square_discrim);
							
						if(abs_double(discrim) < EPSILON)						//the discriminant is 0 => one root x1
							{
								x1->Re = -B/2*A;
								return 1;
							}
						else													//discriminant greater than 0 => two roots x1 and x2
							{
								x1->Re = (-B + discrim)/(2*A);
								x2->Re = (-B - discrim)/(2*A);
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
		
		if(abs_double(A) < EPSILON)
			{
				if(abs_double(B) < EPSILON) return INFINITY_OF_VALUES;			//A = 0 and B = 0 => infinitely many solutions
					
				else return 0;													//A = 0 and B! = 0 => no solutions
			}
		else																	//A! = 0 => one root x
			{
				*x = -B/A;
				return 1;
			}
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
double abs_double(double x)
	{
		return (x > 0? x : -x );
	}
//}--------------------------------------------------------------------------------------------------------------------------------------