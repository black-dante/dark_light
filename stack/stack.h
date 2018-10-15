#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const double EPSILON = 0.00001;
const size_t CAPASITY_FIRST = 100;
const int CANARY = 66;
size_t ERROR_COUNT = 0;

FILE* error_stack = fopen("ERRORS/stack_error.txt","w");
FILE* error_data  = fopen("ERRORS/stack_data.txt","w");

typedef char data_t;

typedef struct stack
	{
		size_t size;
		size_t capasity;
		
		double sum;
		
		data_t* data;
		
	} STACK;
	
#include "st_assert.cpp"

void stack_create(STACK** memory);
void stack_destroy(STACK** memory);

int stack_push(data_t number, STACK* memory);
data_t stack_pop(STACK* memory);

int stack_capasity_increase(STACK* memory);
void stack_capasity_decrease(STACK* memory);

int stack_ok(STACK* memory);
void stack_print_info(STACK* memory, FILE* info);

void hash_sum_create(STACK* memory);
int hash_sum_ok(STACK* memory);

int comp_double_with_zero(double x);

void fprintf_info(char num, FILE* out);
void fprintf_info(int num, FILE* out);
void fprintf_info(float num, FILE* out);
void fprintf_info(double num, FILE* out);
