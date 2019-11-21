#include <stdio.h>
#include <string.h>
void insert(char arr[], int index, char ch);
void str_partition(char str[], int size, int i, int start);
void insert(char arr[], int index, char ch)
{
	memmove(arr + index + 1, arr + index, strlen(arr) - index + 1);
	arr[index] = ch;
}
void str_partition(char str[], int size, int i, int start)
{
	char str2[50];
	int j = 0;
	strcpy(str2, str);
	while (i < size)
	{
		for (i; i < size; i++)
		{
			if ((i==1)&&(j==0))
			{
				fputs(str, stdout);
				j++;
			}
			for (int j = i; j < size-1; j++)
			{
				if (i == j)
				{
					insert(str, start + i, '/');
					fputs(str, stdout);
					i += 1;
					start += 1;
					str_partition(str, size, i, start);
					start -= 1;
					strcpy(str, str2);
				}
			}
		}
	}
}
int main(void)
{
	char str[50];
	fgets(str, 10, stdin);
	int init_size = strlen(str);
	str_partition(str, init_size, 1, 0);
	return 0;
}