
#define prototype(word)	void func_##word(FILE* output, struct buffer* my_buffer)

#define func1(word) 															\
void func_##word(FILE* output, struct buffer* my_buffer)						\
	{																			\
		fprintf(output, "pop\n");												\
		my_buffer->count++;														\
	}																			\


prototype(push);
prototype(pop);
prototype(add);
prototype(sub);
prototype(mul);
prototype(div);
prototype(out);
prototype(jmp);

func1(pop)
func1(add)
func1(sub)
func1(mul)
func1(div)
func1(out)
func1(in)

void func_push(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "push ");
		my_buffer->count++;
		fprintf(output, "%d\n", my_buffer->data[my_buffer->count++]);
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
	
void func_jmp(FILE* output, struct buffer* my_buffer)
	{
		fprintf(output, "jmp ");
		my_buffer->count++;
		fprintf(output, "%d\n", my_buffer->data[my_buffer->count++]);
	}