#include "../headers/useful_func.h"
#include <math.h>

//{--------------------------------------------------------------------------------------------------------------------------------------
#define CMD(word) cpu_elem cpu_##word(CPU_t* my_cpu);

#define COMMANDS_CPU
#include "../headers/CPU_struct.h"
#undef COMMANDS_CPU

#undef CMD(word)
//}--------------------------------------------------------------------------------------------------------------------------------------


#define PUSH(word) stack_push(word, my_cpu->stack)
#define POP() stack_pop(my_cpu->stack)


//{--------------------------------------------------------------------------------------------------------------------------------------
#define reg(reg_name) 							\
case reg_name:									\
stack_push(my_cpu->reg_name, my_cpu->stack);	\
break;											\


cpu_elem cpu_push(CPU_t* my_cpu)
	{
		printf("push\n");
		my_cpu->counter++;
		
		switch((int)(my_cpu->command_buf[my_cpu->counter]))
			{
				case 0:
				my_cpu->counter++;
				PUSH(my_cpu->command_buf[(int)(my_cpu->counter)]);
				break;
				
				case 1:
				PUSH(my_cpu->RAM[(int)(my_cpu->sys_reg)]);
				break;
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
				reg(sys_reg)
				
				default:
				printf("HELLO");
			}
		
		my_cpu->counter++;
		return 0;
	}
	
#undef reg(reg_name)
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------
#define reg(reg_name) 							\
case reg_name:									\
my_cpu->reg_name = stack_pop(my_cpu->stack);    \
break;											\


cpu_elem cpu_pop(CPU_t* my_cpu)
	{
		printf("pop\n");
		my_cpu->counter++;
		
		switch((int)(my_cpu->command_buf[my_cpu->counter]))
			{
				case 0:
				POP();
				break;
				
				case 1:
				my_cpu->RAM[(int)(my_cpu->sys_reg)] = POP();
				break;
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
				reg(sys_reg)
				
			}

		my_cpu->counter++;		
		return 0;
	}
	
#undef reg(reg_name)
//}--------------------------------------------------------------------------------------------------------------------------------------



//{--------------------------------------------------------------------------------------------------------------------------------------	
cpu_elem cpu_add(CPU_t* my_cpu)
	{
		printf("add\n");
		my_cpu->counter++;
		cpu_elem add = POP() + POP();
		PUSH(add);
		return 0;
	}
	
cpu_elem cpu_sub(CPU_t* my_cpu)
	{
		printf("sub\n");
		my_cpu->counter++;
		cpu_elem s1 = POP();
		cpu_elem s2 = POP();
		cpu_elem sub = s2 - s1;
		PUSH(sub);
		return 0;
	}
	
cpu_elem cpu_mul(CPU_t* my_cpu)
	{
		printf("mul\n");
		my_cpu->counter++;
		cpu_elem mul = POP() * POP();
		PUSH(mul);
		return 0;
	}
	
cpu_elem cpu_div(CPU_t* my_cpu)
	{
		printf("div\n");
		my_cpu->counter++;
		cpu_elem s1 = POP();
		cpu_elem s2 = POP();
		cpu_elem div = s2 / s1;
		PUSH(div);
		return 0;
	}
	
cpu_elem cpu_out(CPU_t* my_cpu)
	{
		printf("out\n");
		my_cpu->counter++;
		cpu_elem out = POP();
		PUSH(out);
		printf("%lf\n", out);
		return out;
	}
	
cpu_elem cpu_in(CPU_t* my_cpu)
	{
		printf("in\n");
		my_cpu->counter++;
		cpu_elem in;
		if(scanf("%lf",&in) != 1)
			{
				printf("error scanf");
				assert(0);
			}
		PUSH(in);
		return 0;
	}
	
cpu_elem cpu_jmp(CPU_t* my_cpu)
	{
		printf("jmp\n");
		my_cpu->counter++;
		my_cpu->counter = my_cpu->command_buf[my_cpu->counter];
	}
	
cpu_elem cpu_call(CPU_t* my_cpu)
	{
		printf("call\n");
		my_cpu->counter += 2;
		stack_push(my_cpu->counter, my_cpu->command_pointer);
		my_cpu->counter = my_cpu->command_buf[my_cpu->counter - 1];
	}

cpu_elem cpu_ret(CPU_t* my_cpu)
	{
		printf("ret\n");
		my_cpu->counter = stack_pop(my_cpu->command_pointer);
	}
	
cpu_elem cpu_sqrt(CPU_t* my_cpu)
	{
		printf("sqrt\n");
		my_cpu->counter++;
		cpu_elem sqrt_t = sqrt(POP());
		PUSH(sqrt_t);
		return 0;
	}
	
cpu_elem cpu_sin(CPU_t* my_cpu)
	{
		printf("sin\n");
		my_cpu->counter++;
		cpu_elem sin_t = sin(POP());
		PUSH(sin_t);
		return 0;
	}
	
cpu_elem cpu_cos(CPU_t* my_cpu)
	{
		printf("cos\n");
		my_cpu->counter++;
		cpu_elem cos_t = cos(POP());
		PUSH(cos_t);
		return 0;
	}
	
cpu_elem cpu_end(CPU_t* my_cpu)
	{
		printf("end\n");
		my_cpu->counter = my_cpu->max_count;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------
	
	
	
//{--------------------------------------------------------------------------------------------------------------------------------------	
cpu_elem cpu_cmp(CPU_t* my_cpu)
	{
		printf("cmp\n");
		my_cpu->counter++;
		int a = 0;
		int b = 0;
		
		switch((int)(my_cpu->command_buf[my_cpu->counter]))
			{
				case 0:
				my_cpu->counter++;
				a = my_cpu->command_buf[my_cpu->counter];
				break;
				
				#define reg(reg_name)							\
				case reg_name:									\
				a = my_cpu->reg_name;							\
				break;											\
				
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
				reg(sys_reg)
				
				#undef reg(reg_name)
			}
			
		my_cpu->counter++;
		
		switch((int)(my_cpu->command_buf[my_cpu->counter]))
			{
				case 0:
				my_cpu->counter++;
				b = my_cpu->command_buf[my_cpu->counter];
				break;
				
				#define reg(reg_name)							\
				case reg_name:									\
				b = my_cpu->reg_name;							\
				break;											\
				
				
				#define REGISTERS_CPU
				#include "../headers/CPU_struct.h"
				#undef REGISTERS_CPU
				reg(sys_reg)
				
				#undef reg(reg_name)
			}
			
		if(comp_double_with_zero(a - b) == 1)
			{
				my_cpu->ZF = 1;
				my_cpu->CF = 0;
			}
		else if(comp_two_double(a, b) > 0)
			{
				my_cpu->ZF = 0;
				my_cpu->CF = 0;
			}
		else
			{
				my_cpu->ZF = 0;
				my_cpu->CF = 1;
			}
			
		my_cpu->counter++;
	}
//}--------------------------------------------------------------------------------------------------------------------------------------


//{--------------------------------------------------------------------------------------------------------------------------------------	
#define jump_command(jump_name, condition)					\
cpu_elem cpu_##jump_name(CPU_t* my_cpu)						\
	{														\
		if(condition)										\
			cpu_jmp(my_cpu);								\
		else												\
			my_cpu->counter+=2;								\
	}														\
	
jump_command(je, my_cpu->ZF == 1)
jump_command(jne, my_cpu->ZF == 0)
jump_command(ja, my_cpu->CF == 0 && my_cpu->ZF == 0)
jump_command(jae, my_cpu->CF == 0)
jump_command(jb, my_cpu->CF == 1)
jump_command(jbe, my_cpu->CF == 1 && my_cpu->ZF == 1)

#undef jump_command(jump_name, condition)
//}--------------------------------------------------------------------------------------------------------------------------------------




