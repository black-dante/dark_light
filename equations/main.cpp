/*!
\file
\brief Main Function

Here the whole program begins to work
*/

#include <stdio.h>
#include "equations_lib.cpp"

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function main()
 *
 *   @return 0 - the program completed successfully
 *			 1 - The program is completed with an error. Not the correct input format
 */
int main(void)
	{
		double A = 0, B = 0, C = 0;
		struct complex_ x1 = {0, 0};
		struct complex_ x2 = {0, 0};
		
		printf("#Enter the coefficients of the quadratic equation\n");
		
		if(scanf("%lf %lf %lf", &A, &B, &C) != 3)
			{
				printf("SYSTEM ERROR: incorrect input format\n");
				return 1;
			}
		
		int nRoots = quadratic_equation(A, B, C, &x1, &x2);
		
		switch (nRoots)
			{
				case INFINITY_OF_VALUES:
				printf("#The equation has infinitely many solutions\n");
				break;
				
				case TWO_COMPLEX_VALUES:
				printf("#The equation has two complex roots x1 = %.2f + i*(%.2f) and x2 = %.2f + i*(%.2f)\n", x1.Re, x1.Im, x2.Re, x2.Im);
				break;
				
				case 0:
				printf("#The equation has no solutions\n");
				break;
				
				case 1:
				printf("#The equation has one root x1 = %.2f\n", x1.Re);
				break;
				
				case 2:
				printf("#The equation has two roots x1 = %.2f and x2 = %.2f\n", x1.Re, x2.Re);
				break;
				
				default:
				printf("#SYSTEM ERROR: nRoots = %d\n#A = %.2f\n#B = %.2f\n#B = %.2f\n", nRoots, A, B, C);
				break;
			}
			
		return 0;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
