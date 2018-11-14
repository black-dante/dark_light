#ifndef USEFUL_FUNC
#define USEFUL_FUNC



int comp_double_with_zero(double x);
int comp_two_double(double x1, double x2);

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
	
int comp_two_double(double x1, double x2)
	{
		double delta_x = x1 - x2;
		
		return delta_x > 0? 1: -1;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

void fprintf_num(FILE* out, char num);
void fprintf_num(FILE* out, int num);
void fprintf_num(FILE* out, float num);
void fprintf_num(FILE* out, double num);

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  *	  functions for printing an unknown variable type
  *
  */
void fprintf_num(FILE* out, char num)
	{
		fprintf(out, "%c",num);
	}
	
void fprintf_num(FILE* out, int num)
	{
		fprintf(out, "%d",num);
	}
	
void fprintf_num(FILE* out, float num)
	{
		fprintf(out, "%.2f",num);
	}
	
void fprintf_num(FILE* out, double num)
	{
		fprintf(out, "%.2lf",num);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


#endif