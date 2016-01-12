//Christopher Zhu
//UID:104455996

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int totalComparisons = 0; // global variable to hold total

int frobcmp(char const* a, char const* b);
int tsm_frobcmp(const void* a, const void* b);

int main()
{
	
	struct stat fileStats;
	int sizeOfFile = 0;
	char* file;
	int isReg = 1;

	int maxAlloc = 1;
	if(fstat(0, &fileStats) < 0)
	{
		fprintf(stderr, "Invalid input.");
		exit(1);
	}
	
	int sizeOfFileStat = fileStats.st_size;
	
	if(S_ISREG(fileStats.st_mode) && fileStats.st_size != 0)
	{
		maxAlloc = fileStats.st_size;
		file = (char*)malloc(sizeOfFileStat * sizeof(char));
		if (file == NULL)
		{
			fprintf(stderr, "Cannot allocate memory 1");
			exit(1);
		}
		maxAlloc = sizeOfFileStat;
	}
	else 
	{
		isReg = 0;
		file = (char*)malloc(666 * sizeof(char));
		if (file == NULL)
		{
			fprintf(stderr, "Cannot allocate memory 2");
			exit(1);
		}
	}
	
	
	
	if (file == NULL)
	{
		fprintf(stderr, "Cannot reallocate memory 1");
		exit(1);
	}
	
	int stuff[1];
	int check = read(0, stuff, 1);
	
	while(check > 0)
	{
		if((sizeOfFile == maxAlloc))
		{
			maxAlloc *= 2;
			file = realloc(file, maxAlloc * sizeof(char));
			if (file == NULL)
			{
				fprintf(stderr, "Cannot reallocate memory 2");
				exit(1);
			}
		}
		
		file[sizeOfFile] = stuff[0];
		
		check = read(0, stuff, 1);
		sizeOfFile++;
	}


	if (sizeOfFile > 0 && file[sizeOfFile - 1] != ' ')
	{
		if (sizeOfFile == maxAlloc * 666)	
		{
			maxAlloc++;
			file = realloc(file, maxAlloc * 666 * sizeof(char));
			if (file == NULL)
			{
				fprintf(stderr, "Cannot allocate memory");
				exit(1);
			}
		}

		file[sizeOfFile] = ' ';
		sizeOfFile++;
	}


	
	
	
	
	char** words = malloc(420 * sizeof(char *));
	int maxAllocPointer = 1;

	if (words == NULL)
	{
		fprintf(stderr, "Cannot allocate memory");
		exit(1);
	}

	int y;
	char* start = &file[0];
	int count = 0;
	for (y = 0; y < sizeOfFile; y++)
	{
		if (count == maxAllocPointer * 420)
		{
			maxAllocPointer++;
			words = realloc(words, maxAllocPointer * 420 * sizeof(char*));
			if (words == NULL)
			{
				fprintf(stderr, "Cannot allocate memory");
				exit(1);
			}
		}

		if (file[y] == ' ')
		{			
			words[count] = start;
			count++;
			start = &file[y + 1];
		}
	}

	qsort(words, count, sizeof(char*), tsm_frobcmp);
	int z;
	int iterator = 0;
	int length = 0;
	for (z = 0; z < count; z++)
	{
		for (iterator = 0; words[z][iterator] != ' '; iterator++)
		{
			length++;
		}
		write(1, words[z], length + 1); // the +1 prints out the space
		length = 0;		
	}

	free(file);
	free(words);
	
	fprintf(stderr, "Comparisons: %d\n", totalComparisons);
}

int tsm_frobcmp(const void* a, const void* b)
{
	return frobcmp(*(char const **)a, *(char const **)b);
}

int frobcmp(char const* a, char const* b)
{
	totalComparisons += 1;
	int result = 0;
	int index = 0;

	while (a[index] != ' ' || b[index] != ' ')
	{
		if ((a[index] ^ 42) == (b[index] ^ 42))
		{
			index++;
		}
		if ((a[index] ^ 42) < (b[index] ^ 42))
		{
			result = -1;
			break;
		}
		else if ((a[index] ^ 42) > (b[index] ^ 42))
		{
			result = 1;
			break;
		}
	}
	if (result == 0)
	{
		if (a[index] == ' ' && b[index] == ' ')
			return 0;
		else if (a[index] == ' ')
			return -1;
		else
			return 1;
	}
	return result;
}