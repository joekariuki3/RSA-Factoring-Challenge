#include"factors.h"

void factor(long long int num)
{
	char pair[256];
	int i = 2, j = 2;

	for (i = 2; i <= num; i++)
	{
		for (j = 2; j <= num; j++)
		{
			if (i * j == num)
			{
				printf("%lld=%d*%d\n", num, i, j);
			}
			break;
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
	size_t bufsize = 0;
	char *line = NULL, *strNum = NULL;

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

	while (getline(&line, &bufsize, data) != -1)
	{
		strNum = strtok(line, " \t\n");
		num = strtoll(strNum, NULL, 10);
		factor(num);
	}
	free(line);
	fclose(data);
	return (0);
}
