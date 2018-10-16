#include "stack.h"

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *	@function stack_create()
 *
 *	@param[in] memory** the address at which the stack will be written
 *  @param[in] name name of stack
 *
 */	
void stack_create(STACK** memory, char* name)
	{
		assert(memory != NULL);
		
		*memory = (STACK*)calloc(1, sizeof(STACK));
		assert(*memory != NULL);
		
		(*memory)->data = (data_t*)calloc(CAPASITY_FIRST, sizeof(data_t));
		assert((*memory)->data != NULL);
		
		(*memory)->capasity = CAPASITY_FIRST;//кол во свободных и занятых ячеек
		(*memory)->size = 1; //кол-во ячеек памяти вообще + ячейка под первую канарейку
		
		(*memory)->data[0] = CANARY;
		(*memory)->data[1] = CANARY;
		
		hash_sum_create(*memory);
		
		{
		(*memory)->name = name;
		
		char str_name1[MAX_FILE_NAME] = {};
		strcpy(str_name1, "ERRORS/");
		strcat(str_name1, name);
		
		char str_name2[MAX_FILE_NAME] = {};
		strcpy(str_name2, "ERRORS/");
		strcat(str_name2, name);
			
		(*memory)->error_stack = fopen(strcat(str_name1, "_error_stack.txt"), "w");
		assert((*memory)->error_stack != NULL);
		
		(*memory)->error_data = fopen(strcat(str_name2, "_error_data.txt"), "w");
		assert((*memory)->error_data != NULL);
		}
		
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
		
		free((*memory)->data);
		
		(*memory)->data = NULL;
		(*memory)->size = 0;
		(*memory)->capasity = 0;
		(*memory)->sum = 0;
		(*memory)->name = NULL;
		(*memory)->error_count = 0;
		
		fclose((*memory)->error_stack);
		fclose((*memory)->error_data);
		
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
		
		if(memory->size + 1 == memory->capasity) 
			if(stack_capasity_increase(memory));
			else 
				{
					fprintf(memory->error_stack, "OPS st_assert %d:\n", ++(memory->error_count));
					fprintf(memory->error_stack, "STACK IS FULL\nPUSH FAILED\n");
					fprintf(memory->error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			
					fprintf(memory->error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);									
					fprintf(memory->error_stack, "\n\n\n\n\n");	
					
					return 0;
				}
			
		memory->data[memory->size] = number;
		
		memory->sum += ((memory->size % 2) == 1) ? (memory->data[memory->size]) : ( - memory->data[memory->size]);
		
		memory->size++;
		
		memory->data[memory->size] = CANARY;
		
		st_assert(memory);
		
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
		
		if(memory->size == 1) 
			{
				fprintf(memory->error_stack, "OPS st_assert %d:\n", ++(memory->error_count));
				fprintf(memory->error_stack, "STACK IS EMPTY\nPOP FAILED\n"); //вывод из пустого стека
				fprintf(memory->error_stack, "file = %s\nfunc = %s\nline = %d\n", __FILE__, __FUNCSIG__, __LINE__);			
				fprintf(memory->error_stack, "data = %s\ntime = %s\n", __DATE__, __TIME__);									
				fprintf(memory->error_stack, "\n\n\n\n\n");	
				
				return 666;
			}
		
		memory->data[memory->size] = 0;
		
		data_t number = memory->data[--memory->size];
		
		memory->sum -= ((memory->size % 2) == 1) ? (memory->data[memory->size]) : ( - memory->data[memory->size]);
		
		memory->data[memory->size] = CANARY;
		
		if(memory->size < memory->capasity/4)
			stack_capasity_decrease(memory);
		
		st_assert(memory);
		
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
		
		memory->capasity /= 2;
		memory->data = (data_t* )realloc(memory->data, memory->capasity*sizeof(data_t));
		
		st_assert(memory);
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
		
		if (!(hash_sum_ok(memory)) || memory->data[0] != CANARY || memory->data[memory->size] != CANARY)
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
		fprintf(info, "stack_pointer = %ld \nstack_data_pointer = %ld \n", (long int)memory, (long int)memory->data);
		
		fprintf(info, "stack_capasity = %d \nstack_size = %d \n", memory->capasity, memory->size);
		fprintf(info, "data:\n");
		
		for(int i = 0; i <= memory->size; i++)
			{
			fprintf(info, "stack_data[%d] =", i);
			fprintf_info(memory->data[i], info);
			fprintf(info, "\n");
			}
		
	}
	
void fprintf_info(char num, FILE* out)
	{
		fprintf(out, "%c",num);
	}
	
void fprintf_info(int num, FILE* out)
	{
		fprintf(out, "%d",num);
	}
	
void fprintf_info(float num, FILE* out)
	{
		fprintf(out, "%f",num);
	}
	
void fprintf_info(double num, FILE* out)
	{
		fprintf(out, "%lf",num);
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
			memory->sum += ((i % 2) == 1) ? (memory->data[i]) : ( - memory->data[i]);
	}
//}--------------------------------------------------------------------------------------------------------------------------------------

//{--------------------------------------------------------------------------------------------------------------------------------------
/**
 *   @function hash_sum_ok()
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
			sum += ((i % 2) == 1) ? (memory->data[i]) : ( - memory->data[i]);
		
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