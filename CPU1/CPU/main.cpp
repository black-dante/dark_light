#include "CPU.cpp"
#include <stdio.h>


int main(int argc, char* argv[])
	{
		FILE* _asm_ = fopen(argv[1], "r");
		
		CPU_t* my_cpu;
		
		CPU_create(&my_cpu, _asm_);
		
		cpu_start_command(my_cpu);
		
		CPU_destroy(&my_cpu);
		
	}