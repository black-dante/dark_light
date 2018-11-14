#include "list_ar.cpp"

int main(int argc, char* argv[])
	{
		FILE* error_file = fopen("errorr.txt", "w");
		
		list_ar_t* list_ar = list_ar_create(error_file);
		
		add_first_elem(list_ar, "word1");
		add_first_elem(list_ar, "word2");
		add_first_elem(list_ar, "word3");
		add_first_elem(list_ar, "word4");
		add_first_elem(list_ar, "word5");
		add_first_elem(list_ar, "word6");
		
		//list_ar->first->next->next->next = NULL;
		
		ls_assert(list_ar);
		
		FILE* dump = fopen("dump.txt", "w");
		
		list_ar_destroy(&list_ar);
		list_ar_destroy(&list_ar);
		
		fclose(dump);
	}