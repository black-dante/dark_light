//{--------------------------------------------------------------------------------------------------------------------------------------
#define CMD(word) void func_##word(FILE* output, struct buffer* my_buffer);

#define COMMANDS_CPU
#include "../headers/CPU_struct.h"
#undef COMMANDS_CPU

#undef CMD(word)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
#define func1(word) 															\
void func_##word(FILE* output, struct buffer* my_buffer)						\
	{																			\
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
#define reg(reg_name)										\
case reg_name:												\
fprintf(output, "%s\n", #reg_name);							\
my_buffer->count++;											\
break;														\


void func_push(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "push ");
		my_buffer->count++;

		switch((int)(my_buffer->data[my_buffer->count]))
			{
				case 0:
				my_buffer->count++;
				fprintf(output, "%lf\n", my_buffer->data[my_buffer->count++]);
				break;
				
				case 1:
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
		fprintf(output, "pop ");
		my_buffer->count++;
		switch((int)(my_buffer->data[my_buffer->count]))
			{
				case 0:
				fprintf(output, "\n");
				my_buffer->count++;
				break;
				
				case 1:
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
#define reg(reg_name)							\
case reg_name:									\
fprintf(output, "%s", #reg_name);				\
break;											\


void func_cmp(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "cmp ");
		my_buffer->count++;
		
		switch((int)(my_buffer->data[my_buffer->count]))
			{
				case 0:
				my_buffer->count++;
				fprintf(output,"%lf", my_buffer->data[my_buffer->count]);
				break;
				
				reg(sys_reg)
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
			}
		
		fprintf(output," ");
		
		my_buffer->count++;
		
		switch((int)(my_buffer->data[my_buffer->count]))
			{
				case 0:
				my_buffer->count++;
				fprintf(output,"%lf", my_buffer->data[my_buffer->count]);
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
#define jump_command(jump_name)																	\
void func_##jump_name(FILE* output, struct buffer* my_buffer)									\
	{																							\
		fprintf(output, "%s ", #jump_name);														\
		my_buffer->count++;																		\
		fprintf(output, "%lf\n", my_buffer->data[my_buffer->count++]);							\
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