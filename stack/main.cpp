#include "test.cpp"


int main()
	{
		FILE* error_stack = fopen("ERRORS/error_stack.txt", "w");
		FILE* error_data = fopen("ERRORS/error_data.txt", "w");
		
		struct stack* memory1 = {};
		
		stack_create(&memory1, "stack1", error_stack, error_data);
		
		test(memory1);
		
		fclose(error_stack);
		fclose(error_data);
		fclose(unit_test);
	}
