#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void target_matrix(char arr[], int ch[], int target, int None);
void sol(char arr[], int ch[], int idx, int len, int target)
{
	if (idx == len - 1)
	{
		int None = 0;
		if ((ch[0] == 0) && (ch[len - 2] == 0))
			None = 1;
		target_matrix(arr, ch, target, None);
		return;
	}
	ch[idx] = 1;//* 
	sol(arr, ch, idx + 1, len, target);
	ch[idx] = 2;//-  
	sol(arr, ch, idx + 1, len, target);
	ch[idx] = 3;//+ 
	sol(arr, ch, idx + 1, len, target);
	ch[idx] = 0;//æ»≥÷¿Ω
	if (arr[idx] != '0')
		sol(arr, ch, idx + 1, len, target);
}
void target_matrix(char arr[], int ch[], int target, int None)
{

	int i = 0, b = 0;
	unsigned long long int arr2[10];
	while (arr[i] != '\n')
	{
		arr2[i] = arr[i] - 48;
		i++;
	}
	int len = strlen(arr) - 1;
	i = 0;
	while (b < len - 1)
	{
		if (ch[b] == 0)
		{
			if (b == 0)
			{
				arr2[i + 1] = 10 * (arr2[i]) + (arr2[i + 1]);
				for (int j = 0; j < len - 1; j++)
				{
					arr2[j] = arr2[j + 1];
				}
				arr2[len - 1] = 0;
			}
			else

			{
				arr2[b + 1] = 10 * (arr2[b]) + (arr2[b + 1]);
				for (b; b < len - 1; b++)
				{
					arr2[b] = arr2[b + 1];
				}
				arr2[len - 1] = 0;
			}
		}
		b++;
	}
	i = 0; b = 0;
	int flag = 0;
	while (b < len - 1)
	{
		if ((ch[b] == 1) && (flag == 0))
		{
			i = b;
			arr2[i + 1] = (arr2[i]) * (arr2[i + 1]);
			for (i; i < len - 1; i++)
			{
				arr2[i] = arr2[i + 1];
			}
			arr2[len - 1] = 0;
			flag = 1;
		}
		else if ((ch[b] == 1) && (flag != 0))
		{
			arr2[b] = (arr2[b - 1]) * (arr2[b]);
			for (b - 1; b < len - 1; b++)
			{
				arr2[b - 1] = arr2[b];
			}
			arr2[len - 2] = 0;
		}
		b++;
	}
	i = 0; b = 0;
	while (b < len - 1)
	{
		if (ch[b] == 3)
		{
			arr2[i + 1] = (arr2[i]) + (arr2[i + 1]);
			for (int j = 0; j < len - 1; j++)
			{
				arr2[j] = arr2[j + 1];
			}
			arr2[len - 1] = 0;
		}
		else if (ch[b] == 2)
		{
			arr2[i + 1] = (arr2[i]) - (arr2[i + 1]);
			for (int j = 0; j < len - 1; j++)
			{
				arr2[j] = arr2[j + 1];
			}
			arr2[len - 1] = 0;
		}
		b++;
	}
	static int count = 0;
	if (arr2[0] == target)
	{
		count++;
		fprintf(stdout, "%c", arr[0]);
		for (int j = 1; j < len; j++)
		{
			if (ch[j - 1] == 1) fprintf(stdout, "*");
			if (ch[j - 1] == 2) fprintf(stdout, "-");
			if (ch[j - 1] == 3) fprintf(stdout, "+");
			fprintf(stdout, "%c", arr[j]);
		}
		fprintf(stdout, "=");
		char s[10];
		fprintf(stdout, "%d", target);
		fprintf(stdout, "\n");
	}

	if ((None == 1) && (count == 0))
		fprintf(stdout, "None");
}
int main() {
	char arr[10];
	fgets(arr, 10, stdin);
	char target1[10];
	fgets(target1, 10, stdin);
	int target = atoi(target1);
	int ch[10];
	sol(arr, ch, 0, strlen(arr) - 1, target);
	return 0;
}