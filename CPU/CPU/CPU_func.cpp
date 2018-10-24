#define prototype(word)	cpu_elem cpu_##word(CPU_t* my_cpu)

prototype(push);
prototype(pop);
prototype(add);
prototype(sub);
prototype(mul);
prototype(div);
prototype(out);
prototype(jmp);

#define PUSH(word) stack_push(word, my_cpu->stack)
#define POP() stack_pop(my_cpu->stack)


cpu_elem cpu_push(CPU_t* my_cpu)
	{
		printf("push\n");
		my_cpu->counter++;
		PUSH(my_cpu->command_buf[my_cpu->counter]);
		my_cpu->counter++;
		return 0;
	}
	
cpu_elem cpu_pop(CPU_t* my_cpu)
	{
		printf("pop\n");
		my_cpu->counter++;
		POP();
		return 0;
	}
	
cpu_elem cpu_pushreg(CPU_t* my_cpu)
	{
		printf("pushreg\n");
		my_cpu->counter++;
		
		switch(my_cpu->command_buf[my_cpu->counter])
			{
				case 0:
				PUSH(my_cpu->rax);
				break;
				
				case 1:
				PUSH(my_cpu->rbx);
				break;
				
				case 2:
				PUSH(my_cpu->rcx);
				break;
				
				case 3:
				PUSH(my_cpu->rdx);
				break;
			}
		
		my_cpu->counter++;
		return 0;
	}
	
cpu_elem cpu_popreg(CPU_t* my_cpu)
	{
		printf("pushreg\n");
		my_cpu->counter++;
		
		switch(my_cpu->command_buf[my_cpu->counter])
			{
				case 0:
				my_cpu->rax = POP();
				break;
				
				case 1:
				my_cpu->rbx = POP();
				break;
				
				case 2:
				my_cpu->rcx = POP();
				break;
				
				case 3:
				my_cpu->rdx = POP();
				break;
			}
		
		my_cpu->counter++;
		return 0;
	}
	
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
		cpu_elem sub = POP() - POP();
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
		cpu_elem div = POP() / POP();
		PUSH(div);
		return 0;
	}
	
cpu_elem cpu_out(CPU_t* my_cpu)
	{
		printf("out\n");
		my_cpu->counter++;
		cpu_elem out = POP();
		PUSH(out);
		printf("%d\n", out);
		return out;
	}
	
cpu_elem cpu_in(CPU_t* my_cpu)
	{
		printf("in\n");
		my_cpu->counter++;
		cpu_elem in;
		if(scanf("&d",&in) != 1)
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