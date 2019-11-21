#include <stdio.h>
#include <string.h>
void fail(char *pat, int *failure);
void pmatch(char *string, char *pat)
{
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	int lps[30];
	fail(pat, lps);
	while (i < lens)
	{
		while (i < lens&&j < lenp)
		{
			if (string[i] == pat[j])
			{
				i++; j++;
			}
			else if (j == 0)
				i++;
			else
				j = lps[j - 1] + 1;
		}
		if (j == lenp)
			fprintf(stdout, "%d\n", i - lenp);
		if (i == lens)
			break;
		else if (i != lens)
			i = i - lenp + 1;
		j = 0;
	}
}
void fail(char *pat, int *failure)
{
	int j;
	int i, n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++)
	{
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else failure[j] = -1;
	}
}
int main(void)
{
	char str[30];
	fscanf(stdin, "%s", str);
	char pat[30];
	fscanf(stdin, "%s", pat);
	pmatch(str, pat);
	return 0;
}