#include "hash_tab.cpp"
#include "read_functions/fgetword.cpp"

const int MAXWORD = 100;
	
int main(int argc, char* argv[])
	{
		FILE* read = fopen(argv[1], "r");
		
		char word[MAXWORD + 1];
		int symbol = 0;
		
		int size = 30;
		
		hash_tab_t* hash_tab = hash_tab_create(size);
		
		while((symbol = fgetword_without_prob(word, MAXWORD, read)) != EOF)
			{
				if(symbol == LETTER)
					{
						put_data_to_tab(hash_tab, strdup(word), hash_Rot13);
					}
			}
			
			
		FILE* dump = fopen("dump.txt", "w");
		print_hash_tab_size(hash_tab, dump);
		FILE* dump1 = fopen("dump1.txt", "w");
		print_hash_tab(hash_tab, dump1);
		
		printf("pogr = %lf\n", hash_tab_pogr(hash_tab));
		
		hash_tab_destroy(hash_tab);
		fclose(dump);
	}