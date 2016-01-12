#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if(argc != 3)	// check make sure proper number of arguments
	{
		fprintf(stderr, "Wrong number of arguments");
		exit(1);
	}
		
	int counter1 = 0;
	int counter2 = 0;
	
	//Obtain size of arguments
	int a;
	for(a = 0; argv[1][a] != '\0'; a++)		
	{
		counter1++;
	}
	
	int j;
	for(j = 0; argv[2][j] != '\0'; j++)
	{
		counter2++;
	}
	
	int q;
	int r;
	char check;
	for(q = 0; q < counter1; q++)
	{
		check = argv[1][q];
		for(r = q+1; r < counter1; r++)
		{
			if(check == argv[1][r])
			{
				fprintf(stderr, "No duplicate bytes in from");
				exit(1);
			}
		}
	}
	
	if(counter1 != counter2)
	{
		fprintf(stderr, "Argument sizes don't match");
		exit(1);
	}

	int z = getchar();
	int found = 0;
	int i;
	while(z != EOF)
	{
		
		for(i = 0; i < counter1; i++)
		{
			if(z == argv[1][i])
			{
				putchar(argv[2][i]);
				found = 1;
				
				break;
			}
		}

		if(found == 1)
		{
			found = 0;
		}
		else
		{
			putchar(z);
		}
		z= getchar();
		
	}
	return 0;
}