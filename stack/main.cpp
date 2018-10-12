#include "stack.cpp"
#include "unittest.cpp"
#include "grap_lib.cpp"

void test(STACK* memory);

int main()
	{
		
		struct stack* memory = {};
		
		stack_create(&memory);
		
		test(memory);
		
	}
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function test()
 *
 *   @param[in] memory* test stack
 *
 */		
void test(STACK* memory)
	{
		printf("Test 1 without attack\n");
		
		printf("STACK is pushing\n");
		
		for(int i = 0; i <=1000; i++)
			{
				printf("\r");
				UNITTEST(stack_push(i, memory), ==, 1, int, int);
				print_prog_bar(i/10);
			}
		
		printf("\nSTACK push is ok\n");
		
		printf("STACK is poping\n");
		
		for(int i = 1000; i >= 0; i--)
			{
				printf("\r");
				UNITTEST(stack_pop(memory), ==, i, int, int);
				print_prog_bar((1000-i)/10);
			}
			
		printf("\nSTACK pop is ok\n");
			
		stack_destroy(&memory);
		stack_destroy(&memory);
		
		stack_create(&memory);
		stack_create(&memory);
		
		printf("Test 2 with attack\n");
		
		printf("STACK is pushing\n");
		
		for(int i = 0; i <=2000; i++)
			{
				printf("\r");
				UNITTEST(stack_push(i, memory), ==, 1, int, int);
				print_prog_bar(i/20);
			}
		
		printf("\nSTACK push is ok\n");
		
		printf("attack\n");
		
		for(int i = 0; i <=200; i++)
			{
				printf("\r");
				memory->data[rand()*200/RAND_MAX] = 0;
				print_prog_bar(i/2);
			}
		
		printf("\nSTACK is poping\n");
		
		for(int i = 2000; i >= 0; i--)
			{
				printf("\r");
				UNITTEST(stack_pop(memory), ==, i, int, int);
				print_prog_bar((2000-i)/20);
			}	
		printf("\nSTACK pop is ok\n");
		
		stack_destroy(&memory);
		stack_destroy(&memory);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------