#include "stack.h"

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function stack_create()
 *
 *	@param[in] memory** the address at which the stack will be written
 *
 */	
void stack_create(STACK** memory)
	{
		assert(memory != NULL);
		
		*memory = (STACK*)calloc(1, sizeof(STACK));
		assert(*memory != NULL);
		
		(*memory)->data = (data_t*)calloc(capasity_first, sizeof(data_t));
		assert((*memory)->data != NULL);
		
		(*memory)->capasity = capasity_first;//кол во свободных и занятых ячеек
		(*memory)->size = 0; //кол-во ячеек памяти вообще
		
		(*memory)->sum = 0;
		
		stack_ok(*memory);
		st_assert(*memory);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function stack_destroy()
 *
 *	@param[in] memory** the address where the stack will be destroyed
 *
 */		
void stack_destroy(STACK** memory)
	{
		assert(memory != NULL);
		
		if(!(*memory)) return;
		st_assert(*memory);
		stack_ok(*memory);
		
		free((*memory)->data);
		
		(*memory)->data = NULL;
		(*memory)->size = 0;
		(*memory)->capasity = 0;
		(*memory)->sum = 0;
		
		*memory = NULL;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function push()
 *
 *	@param[in] memory* stack pointer
 *  @param[in] number data for the stack
 *
 *  return 1 if push is right
 *		   0 if push is error
 */		
int stack_push(data_t number, STACK* memory)
	{
		st_assert(memory);
		stack_ok(memory);
		
		if(memory->size + 1== memory->capasity) 
			if(stack_capasity_increase(memory));
			else 
				{
					fprintf(error_stack, "OPS st_assert %d:\n", ++error_count);
					fprintf(error_stack, "STACK IS FULL\nPUSH FAILED\n");
					fprintf(error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			
					fprintf(error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);									
					fprintf(error_stack, "\n\n\n\n\n");	
					
					return 0;
				}
			
		memory->data[memory->size] = number;
		
		memory->sum+= ((memory->size % 2) == 1) ? (memory->data[memory->size]) : ( - memory->data[memory->size]);
		
		memory->size++;
		
		st_assert(memory);
		stack_ok(memory);
		
		return 1;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function  pop()
 *
 *	@param[in] memory* stack pointer
 *
 *  return number from stack
 */			
data_t stack_pop(STACK* memory)
	{
		st_assert(memory);
		stack_ok(memory);
		
		if(memory->size == 0) 
			{
				fprintf(error_stack, "OPS st_assert %d:\n", ++error_count);
				fprintf(error_stack, "STACK IS EMPTY\nPOP FAILED\n"); //вывод из пустого стека
				fprintf(error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			
				fprintf(error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);									
				fprintf(error_stack, "\n\n\n\n\n");	
				
				return 666;
			}
		
		data_t number = memory->data[--memory->size];
		
		memory->sum-= ((memory->size % 2) == 1) ? (memory->data[memory->size]) : ( - memory->data[memory->size]);
		
		memory->data[memory->size] = 0;
		
		if(memory->size < (memory->capasity/4))
			stack_capasity_decrease(memory);
		
		st_assert(memory);
		stack_ok(memory);
		
		return number;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function stack_capasity_increase()
 *
 *	@param[in] memory* stack to increase size
 *
 *  return 1 if uncrease is right
 *		   0 if uncrease is error
 */			
int stack_capasity_increase(STACK* memory)
	{
		st_assert(memory);
		stack_ok(memory);
		
		data_t* pointer;
		
		if((pointer = (data_t* )realloc(memory->data, memory->capasity*2*sizeof(data_t))) != NULL)
			{
				memory->data = pointer;
				memory->capasity *= 2;
				return 1;
			}
		else
			for(size_t delta_capasity = memory->capasity/2; delta_capasity > 0; delta_capasity /= 2)
			{	
				if((pointer = (data_t* )realloc(memory->data, (memory->capasity + delta_capasity)*sizeof(data_t))) != NULL)
							{
								memory->data = pointer;
								memory->capasity += delta_capasity;
								return 1;
							}
			}
		
		st_assert(memory);
		stack_ok(memory);
		
		return 0;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function stack_capasity_decrease()
 *
 *	@param[in] memory* stack to reduce size
 *
 */	
void stack_capasity_decrease(STACK* memory)
	{
		st_assert(memory);
		stack_ok(memory);
		
		memory->capasity /= 2;
		memory->data = (data_t* )realloc(memory->data, memory->capasity*sizeof(data_t));
		
		st_assert(memory);
		stack_ok(memory);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function stack_Ok()
 *
 *	@param[in] memory* stack
 *
 *  @return 0: allways ok
 *			1: very fatal error
 *          2: fatal error
 *          3: fatal sum
 */		
int stack_ok(STACK* memory)
	{
		if(memory == NULL)
			return 1;
		
		if(!(memory->size >= 0 && memory->capasity >= memory->size  && memory->capasity > 0 && memory->data != NULL)) 
			return 2;
		
		if (!(hash_sum_ok(memory)))
			return 3;
		
		return 0;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function stack_print_info()
 *
 *	@param[in] memory* stack for information
 *  @param[in] info* output file
 *
 */		
void stack_print_info(STACK* memory, FILE* info)
	{
		fprintf(info, "stack_pointer = %d \nstack_data_pointer = %d \n", memory, memory->data);
		
		fprintf(info, "stack_capasity = %d \nstack_size = %d \n", memory->capasity, memory->size);
		fprintf(info, "data:\n");
		
		for(int i = 0; i < memory->size; i++)
			fprintf(info, "stack_data[%d] = %d \n", i, memory->data[i]);
		
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
	
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function hash_sum_create()
 *
 *   @param[in] memory* stack to get hash sum
 *
 */	
void hash_sum_create(STACK* memory)
	{
		memory->sum = 0;
		
		for(int i = 0; i < memory->size; i++)
			memory->sum+= ((i % 2) == 1) ? (memory->data[i]) : ( - memory->data[i]);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function hash_sum_create()
 *
 *   @param[in] memory* stack to check hash sums
 *
 *   @return 1: sum is correct
 *  		 0: sum isn't correct
 */	
int hash_sum_ok(STACK* memory)
	{
		double sum = 0;
		
		for(int i = 0; i < memory->size; i++)
			sum+= ((i % 2) == 1) ? (memory->data[i]) : ( - memory->data[i]);
		
		return comp_double_with_zero(sum - memory->sum) ? 1 : 0;
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
int comp_double_with_zero(double x)
	{
		x = x >= 0? x : -x;
		return x < EPSILON? 1: 0;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------