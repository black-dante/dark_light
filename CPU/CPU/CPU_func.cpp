

cpu_elem cpu_push(CPU_t* my_cpu);
cpu_elem cpu_pop(CPU_t* my_cpu);
cpu_elem cpu_add(CPU_t* my_cpu);
cpu_elem cpu_sub(CPU_t* my_cpu);
cpu_elem cpu_mul(CPU_t* my_cpu);
cpu_elem cpu_div(CPU_t* my_cpu);
cpu_elem cpu_out(CPU_t* my_cpu);
cpu_elem cpu_jmp(CPU_t* my_cpu);

cpu_elem cpu_push(CPU_t* my_cpu)
	{
		printf("push\n");
		my_cpu->counter++;
		stack_push(my_cpu->ram[my_cpu->counter], my_cpu->stack);
		my_cpu->counter++;
		return 0;
	}
	
cpu_elem cpu_pop(CPU_t* my_cpu)
	{
		printf("pop\n");
		my_cpu->counter++;
		stack_pop(my_cpu->stack);
		return 0;
	}
	
cpu_elem cpu_pushreg(CPU_t* my_cpu)
	{
		printf("pushreg\n");
		my_cpu->counter++;
		
		switch(my_cpu->ram[my_cpu->counter])
			{
				case 0:
				stack_push(my_cpu->rax, my_cpu->stack);
				break;
				
				case 1:
				stack_push(my_cpu->rbx, my_cpu->stack);
				break;
				
				case 2:
				stack_push(my_cpu->rcx, my_cpu->stack);
				break;
				
				case 3:
				stack_push(my_cpu->rdx, my_cpu->stack);
				break;
			}
		
		my_cpu->counter++;
		return 0;
	}
	
cpu_elem cpu_popreg(CPU_t* my_cpu)
	{
		printf("pushreg\n");
		my_cpu->counter++;
		
		switch(my_cpu->ram[my_cpu->counter])
			{
				case 0:
				my_cpu->rax = stack_pop(my_cpu->stack);
				break;
				
				case 1:
				my_cpu->rbx = stack_pop(my_cpu->stack);
				break;
				
				case 2:
				my_cpu->rcx = stack_pop(my_cpu->stack);
				break;
				
				case 3:
				my_cpu->rdx = stack_pop(my_cpu->stack);
				break;
			}
		
		my_cpu->counter++;
		return 0;
	}
	
cpu_elem cpu_add(CPU_t* my_cpu)
	{
		printf("add\n");
		my_cpu->counter++;
		cpu_elem add = stack_pop(my_cpu->stack) + stack_pop(my_cpu->stack);
		stack_push(add, my_cpu->stack);
		return 0;
	}
	
cpu_elem cpu_sub(CPU_t* my_cpu)
	{
		printf("sub\n");
		my_cpu->counter++;
		cpu_elem sub = stack_pop(my_cpu->stack) - stack_pop(my_cpu->stack);
		stack_push(sub, my_cpu->stack);
		return 0;
	}
	
cpu_elem cpu_mul(CPU_t* my_cpu)
	{
		printf("mul\n");
		my_cpu->counter++;
		cpu_elem mul = stack_pop(my_cpu->stack) * stack_pop(my_cpu->stack);
		stack_push(mul, my_cpu->stack);
		return 0;
	}
	
cpu_elem cpu_div(CPU_t* my_cpu)
	{
		printf("div\n");
		my_cpu->counter++;
		cpu_elem div = stack_pop(my_cpu->stack) / stack_pop(my_cpu->stack);
		stack_push(div, my_cpu->stack);
		return 0;
	}
	
cpu_elem cpu_out(CPU_t* my_cpu)
	{
		printf("out\n");
		my_cpu->counter++;
		cpu_elem out = stack_pop(my_cpu->stack);
		stack_push(out, my_cpu->stack);
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
		stack_push(in, my_cpu->stack);
		return 0;
	}
	
cpu_elem cpu_jmp(CPU_t* my_cpu)
	{
		printf("jmp\n");
		my_cpu->counter++;
		my_cpu->counter = my_cpu->ram[my_cpu->counter];
	}