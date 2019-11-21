#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
void check_array(int num, int *arr)
{
	int flag = 0;
	int i, j, min, max;
	int temp;
	min = 0;
	for (j = 1; j < num; j++)
	{
		if (arr[j] < arr[min])
			min = j;
	}
	min = arr[min];
	max = 0;
	for (j = 1; j < num; j++)
	{
		if (arr[j] > arr[max])
			max = j;
	}
	max = arr[max];
	if (max - min + 1 == num)
	{
		int *visit = (int*)calloc(num, sizeof(int));
		for (i = 0; i < num; i++)
		{
			if (visit[arr[i] - min] == 1)
			{
				flag = 0;
				break;
			}
			visit[arr[i] - min] = 1;
		}
		if (i == num)
			flag = 1;
	}
	if (flag == 1)
		fprintf(stdout, "%d", 1);
	else
		fprintf(stdout, "%d", 0);
}
int main(void)
{
	int num, i;
	fscanf(stdin, "%d", &num);
	int *arr = (int*)calloc(num, sizeof(int));
	for (i = 0; i < num; i++)
		fscanf(stdin, "%d", &arr[i]);
	check_array(num, arr);
	return 0;
}