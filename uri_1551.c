/* SOLUÇÃO PARA PROBLEMA FRASE COMPLETA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void count(char* line)
{
	unsigned int count[26];
	unsigned int i;
	for (i = 0; i < 26; ++i)
		count[i] = 0;

	unsigned int len = strlen(line);
	for (i = 0; i < len; ++i)
	{
		if (line[i] >= 97 && line[i] <= 122)
			++count[line[i] - 97];
	}

	unsigned int count_distinct = 0;
	for (i = 0; i < 26; ++i)
	{
		if (count[i] > 0)
			++count_distinct;
	}

	if (count_distinct == 26)
		printf("frase completa\n");
	else if (count_distinct >= 13)
		printf("frase quase completa\n");
	else
		printf("frase mal elaborada\n");
}

int main()
{
	int num_cases;
	char line[1002];

	scanf("%d\n", &num_cases);
	unsigned int i;
	for (i = 0; i < num_cases; ++i)
	{
		fgets(line, 1002, stdin);
		count(line);
	}

	return EXIT_SUCCESS;
}
