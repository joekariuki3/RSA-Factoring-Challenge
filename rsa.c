#include"factors.h"

void factor(long long int num)
{
	char pair[256];
	int i = 2;
	
	for (i = 2; i <= num/2; i++)
	{
		if (num % i == 0 && i % i == 0 && i % 1 == 0)
		{
			printf("%lld=%lld*%d\n", num, num/i, i);
			return;
		}
	}
	
}
/**
 * main - start of main function
 * @argc: number of arguments passed to the ptogram
 * @argv: array of arguments passed
 * Return: 0 for sucess
 */
int main(int argc, char **argv)
{
	FILE *data;
	long long int num;

	if (argc < 2 || argc > 2)
	{
		fprintf(stderr, "Usage: factors <file>\n");
		exit(EXIT_FAILURE);
	}

	data = fopen(argv[1], "r");
	if (data == NULL)
	{
		fprintf(stderr, "Error: can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fscanf(data, "%lld\n",&num) != EOF)
	{
		factor(num);
	}
	fclose(data);
	return (0);
}
