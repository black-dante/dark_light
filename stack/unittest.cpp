#include <stdio.h>

FILE* unit_test = fopen("UNITTESTS/unit_test.txt","w");

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	UNITTEST
 *
 *	unit test to check anything.
 *  enter two variables, specify how to compare and types of variables.
 *  If the unit test fails, the error information will be in the unit test file.
 *
 */	
#define UNITTEST(var1,oper,var2,type1,type2)											\
	{																					\
		type1 var1_ = (var1);															\
		type2 var2_ = (var2);															\
																						\
		if((var1_ oper var2_) == 0)														\
			{																			\
				fprintf(unit_test, "\n  ERROR:\n\n");									\
																						\
				fprintf(unit_test, "  %s %s %s - false\n", #var1, #oper, #var2);		\
				fprintf(unit_test, "  ");												\
				fprint_##type1(var1_);													\
				fprintf(unit_test, "  %s ", #oper);										\
				fprint_##type2(var2_);													\
				fprintf(unit_test, " - false\n\n");										\
																						\
				fprintf(unit_test, "  file: %s\n", __FILE__);							\
				fprintf(unit_test, "  function: %s\n", __FUNCTION__);					\
				fprintf(unit_test, "  line: %d\n\n", __LINE__);							\
				fprintf(unit_test, "  data: %s\n", __DATE__);							\
				fprintf(unit_test, "  time: %s\n\n\n", __TIME__);						\
			}																			\
	}																					\

void fprint_char(char num)
	{
		fprintf(unit_test, "%c",num);
	}
	
void fprint_int(int num)
	{
		fprintf(unit_test, "%d",num);
	}
	
void fprint_float(float num)
	{
		fprintf(unit_test, "%f",num);
	}
	
void fprint_double(double num)
	{
		fprintf(unit_test, "%lf",num);
	}
	
//}--------------------------------------------------------------------------------------------------------------------------------------