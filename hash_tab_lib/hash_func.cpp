#define HASH(hash_func) hash_func, #hash_func,


struct hash_elem
	{
		long int (*func)(data_t data);
		char* word;
	};
	

int hash_elem_size(struct hash_elem* hash_ar)
	{
		int i = 0;
		
		for(i = 0; hash_ar[i].func != NULL; i++);
		
		return i;
	}
	
	
long int hash1(data_t data)
	{
		return 1;
	}
	
long int hash_first_symb(data_t data)
	{
		return data[0];
	}
	
long int hash_len(data_t data)
	{
		return strlen(data);
	}
	
long int hash_ascii_sum(data_t data)
	{
		long int count = 0;
		
		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			count += data[i];
		
		return count;
	}
	
long int hash_ascii_sum_on_length(data_t data)
	{
		long int count = 0;
		
		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			count += data[i];
		
		return count/strlen(data);
	}
	
long int hash_ascii_pn_sum(data_t data)
	{
		long int count = 0;
		
		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			count += i % 2 == 0? data[i] : -data[i];
		
		return count;
	}
	
	
long int stringToHash(data_t data)
	{
		long int count = 0;
		
		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			count = count*data[i] + data[i] + i;
		
		return count;
	}
	
long int hash_sdbm(data_t data)
	{
		long int count = 0;
		
		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			count = data[i] + (count << 6) + (count << 16) - count;
		
		return count;
	}
	
long int hash_djb2(data_t data)
	{
		long int count = 5381;
		
		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			count = data[i] + (count << 5) + count;
		
		return count;
	}
	
long int hash_adler32(data_t data)
	{
		wint_t s1 = 1;
		wint_t s2 = 0;
		
		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			{
				s1 = (s1 + data[i]) % 65521;
				s2 = (s2 + s1) % 65521;
			}
			
		return (s2 << 16) | s1;
	}
	
long int hash_FAQ6(data_t data)
	{

		unsigned int hash = 0;

		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			{
				hash += (unsigned char)data[i];
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
	
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;

	}

long int hash_Rot13(data_t data)
	{

		unsigned int hash = 0;

		int size = strlen(data);
		
		for(int i = 0; i < size; i++)
			{
				hash += (unsigned char)data[i];
				hash -= (hash << 13) | (hash >> 19);
			}

		return hash;

	}
	
	
struct hash_elem hash_ar[]
	{
		HASH(hash1)
		HASH(hash_first_symb)
		HASH(hash_len)
		HASH(hash_ascii_sum)
		HASH(hash_ascii_sum_on_length)
		HASH(hash_ascii_pn_sum)
		HASH(stringToHash)
		HASH(hash_sdbm)
		HASH(hash_djb2)
		HASH(hash_adler32)
		HASH(hash_FAQ6)
		HASH(hash_Rot13)
		NULL, "NULL"
	};

