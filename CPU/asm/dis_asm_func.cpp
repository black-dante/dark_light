void func_push(FILE* output, struct buffer* my_buffer);
void func_pop(FILE* output, struct buffer* my_buffer);
void func_add(FILE* output, struct buffer* my_buffer);
void func_sub(FILE* output, struct buffer* my_buffer);
void func_mul(FILE* output, struct buffer* my_buffer);
void func_div(FILE* output, struct buffer* my_buffer);
void func_out(FILE* output, struct buffer* my_buffer);
void func_jmp(FILE* output, struct buffer* my_buffer);


void func_push(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "push ");
		my_buffer->count++;
		fprintf(output, "%d\n", my_buffer->data[my_buffer->count++]);
	}
	
void func_pop(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "pop\n");
		my_buffer->count++;
	}
	
void func_pushreg(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "pushreg ");
		my_buffer->count++;
		
		switch(my_buffer->data[my_buffer->count])
			{
				case 0:
				fprintf(output, "rax\n");
				break;
				
				case 1:
				fprintf(output, "rbx\n");
				break;
				
				case 2:
				fprintf(output, "rcx\n");
				break;
				
				case 3:
				fprintf(output, "rdx\n");
				break;
			}
			
		my_buffer->count++;
	}
	
void func_popreg(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "popreg ");
		my_buffer->count++;
		
		switch(my_buffer->data[my_buffer->count])
			{
				case 0:
				fprintf(output, "rax\n");
				break;
				
				case 1:
				fprintf(output, "rbx\n");
				break;
				
				case 2:
				fprintf(output, "rcx\n");
				break;
				
				case 3:
				fprintf(output, "rdx\n");
				break;
			}
			
		my_buffer->count++;
	}
	
void func_add(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "add\n");
		my_buffer->count++;
	}
	
void func_sub(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "sub\n");
		my_buffer->count++;
	}
	
void func_mul(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "mul\n");
		my_buffer->count++;
	}
	
void func_div(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "div\n");
		my_buffer->count++;
	}
	
void func_out(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "out\n");
		my_buffer->count++;
	}
	
void func_in(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "in\n");
		my_buffer->count++;
	}
	
void func_jmp(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "jmp ");
		my_buffer->count++;
		fprintf(output, "%d\n", my_buffer->data[my_buffer->count++]);
	}