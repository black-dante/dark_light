#include "test.cpp"

int main()
	{
		
		struct stack* memory = {};
		
		stack_create(&memory);
		
		test(memory);
		
		fclose(error_stack);
		fclose(error_data);
		fclose(unit_test);
	}
