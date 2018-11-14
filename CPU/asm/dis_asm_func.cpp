#include "../headers/useful_func.h"
#include <assert.h>
//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * prototypes
  *
  */
#define CMD(word) void func_##word(FILE* output, struct buffer* my_buffer);

#define COMMANDS_CPU
#include "../headers/CPU_struct.h"
#undef COMMANDS_CPU

#undef CMD(word)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * functions without parameters
  *
  */
#define func1(word) 															\
void func_##word(FILE* output, struct buffer* my_buffer)						\
	{																			\
		assert(output != NULL);													\
		assert(my_buffer != NULL);												\
																				\
		fprintf(output, "%s\n", #word);											\
		my_buffer->count++;														\
	}																			\


func1(add)
func1(sub)
func1(mul)
func1(div)
func1(out)
func1(in)
func1(ret)
func1(sin)
func1(cos)
func1(sqrt)
func1(end)

#undef func1(word)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * push and pop functions
  *
  * push options
  *		0: the number written in the second parameter is passed
  *     1: write to RAM
  *		others: writing to registers
  *
  * pop options
  *		0: extract number from stack
  *     1: extract number from ram
  *		others: extract number from registers
  */
#define reg(reg_name)										\
case reg_name:												\
fprintf(output, "%s\n", #reg_name);							\
my_buffer->count++;											\
break;														\


void func_push(FILE* output, struct buffer* my_buffer)
	{
		assert(output != NULL);
		assert(my_buffer != NULL);
		
		fprintf(output, "push ");
		my_buffer->count++;

		switch((int)(my_buffer->data[my_buffer->count]))
			{
				case default_write:
				my_buffer->count++;
				fprintf_num(output, *(buf_type* )(my_buffer->data + my_buffer->count));
				fprintf(output, "\n");
				my_buffer->count += sizeof(buf_type);
				break;
				
				case write_to_ram:
				fprintf(output, "[sys_reg]\n");
				my_buffer->count++;
				break;
				
				reg(sys_reg)
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
			}
	}
	
void func_pop(FILE* output, struct buffer* my_buffer)
	{
		assert(output != NULL);
		assert(my_buffer != NULL);
		
		fprintf(output, "pop ");
		my_buffer->count++;
		switch((int)(my_buffer->data[my_buffer->count]))
			{
				case default_write:
				fprintf(output, "\n");
				my_buffer->count++;
				break;
				
				case write_to_ram:
				fprintf(output, "[sys_reg]\n");
				my_buffer->count++;
				break;
				
				reg(sys_reg)
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
			}
	}
	
#undef reg(reg_name, reg_number)				
//}--------------------------------------------------------------------------------------------------------------------------------------



//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * @function func_cmp()
  * function comparing registers or numbers 
  * and setting flags depending on the comparison results
  *
  */
#define reg(reg_name)							\
case reg_name:									\
fprintf(output, "%s", #reg_name);				\
my_buffer->count++;                             \
break;											\


void func_cmp(FILE* output, struct buffer* my_buffer)
	{
		assert(output != NULL);
		assert(my_buffer != NULL);
		
		fprintf(output, "cmp ");
		my_buffer->count++;
		
		switch((int)(my_buffer->data[my_buffer->count]))
			{
				case default_write:
				my_buffer->count++;
				fprintf_num(output, *(buf_type* )(my_buffer->data + my_buffer->count));
				my_buffer->count += sizeof(buf_type);
				break;
				
				reg(sys_reg)
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
			}
		
		fprintf(output," ");
		

		
		switch((int)(my_buffer->data[my_buffer->count]))
			{
				case default_write:
				my_buffer->count++;
				fprintf_num(output, *(buf_type* )(my_buffer->data + my_buffer->count));
				my_buffer->count += sizeof(buf_type);
				break;
				
				reg(sys_reg)
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
			}
			
		fprintf(output,"\n");
	}
	
#undef reg(reg_name, reg_number)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
/**
  * conditional and unconditional transition functions
  * first parameter is the transition address
  *
  */
#define jump_command(jump_name)																	\
void func_##jump_name(FILE* output, struct buffer* my_buffer)									\
	{																							\
		assert(output != NULL);																	\
		assert(my_buffer != NULL);																\
																								\
		fprintf(output, "%s ", #jump_name);														\
		my_buffer->count++;																		\
		fprintf(output, "%d\n", *(int* )(my_buffer->data + my_buffer->count));					\
		my_buffer->count += sizeof(int);                                                  		\
	}																							\
	
jump_command(jmp)
jump_command(call)
jump_command(je)
jump_command(jne)
jump_command(ja)
jump_command(jae)
jump_command(jb)
jump_command(jbe)

#undef jump_command(jump_name)
//}--------------------------------------------------------------------------------------------------------------------------------------