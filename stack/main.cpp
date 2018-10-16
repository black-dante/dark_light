#include "test.cpp"


int main()
	{
		
		struct stack* memory1 = {};
		
		stack_create(&memory1, "stack1");
		
		test(memory1);
		
		fclose(unit_test);
	}
