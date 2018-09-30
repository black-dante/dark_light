/*!
\file
\brief here constants and prototypes of functions
*/

#include <math.h>
#include <assert.h>
//{--------------------------------------------------------------------------------------------------------------------------------------

/*!
* a constant denoting that the equation has infinitely many roots
*/
const int INFINITY_OF_VALUES  = -1;	

/*!
* a constant denoting that the equation has two complex roots
*/												
const int TWO_COMPLEX_VALUES = -2;	

/*!
* constant for comparing double numbers with zero
*/												
const int EPSILON = 0.00001;

//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------

/*!
* function returns the number module double
*/
double abs_double(double x);														

/*!
* function for the quadratic equation
*/
int quadratic_equation(double A, double B, double C, double *x1, double *x2);	

/*!
* function for the linear equation
*/
int linear_equation(double A, double B, double *x);		

//}--------------------------------------------------------------------------------------------------------------------------------------
