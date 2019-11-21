#include <stdio.h>
#include <stdlib.h>
#define MAX 10000
typedef struct node *nodepointer;
typedef struct node {
	int data;
	nodepointer next;
}node;
int n;
FILE* sp;
nodepointer nodearr[MAX];
int visited[MAX];
nodepointer make_node(int x)
{
	/*make node*/
	nodepointer a=(nodepointer)calloc(sizeof(node),1);
	a->data = x;
	a->next = NULL;
	return a;
}
void dfs(int v)
{
	/*depth first search of a graph beginning at v*/
	nodepointer w;
	visited[v] = 1;
	fprintf(sp, "%d ", v);
	for (w = nodearr[v]; w; w=w->next)
	{
		if (!visited[w->data])
			dfs(w->data);
	}
}
void connected(void)
{
	/*determine the connected components of a graph*/
	int i;
	for (i = 0; i < n; i++)
	{
		if (nodearr[i] != NULL)
		{
			if (!visited[i])
			{
				dfs(i);
				fprintf(sp, "\n");
			}
		}
	}
}
int main(void)
{
	/*to make output.txt empty file*/
	FILE* rp = fopen("output.txt", "w");
	fclose(rp);
	nodepointer add_temp;
	FILE* fp; 
	sp = fopen("output.txt", "a");
	fp = fopen("input.txt", "r");
	int i, j,k;
	for (i = 0; i < 100; i++)
		nodearr[i] = NULL;
	if (fp == NULL)
		fprintf(stdout, "No file input");
	fscanf(fp, "%d", &n);
	/*transpose to adjacency list*/
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)\
		{
			fscanf(fp, "%1d", &k);
			if (k == 1)
			{
				if (nodearr[i] == NULL)
				{
					nodearr[i] = make_node(i);
					add_temp = make_node(j);
					nodearr[i]->next = add_temp;
				}
				else if (nodearr[i] != NULL)
				{
					add_temp = make_node(j);
					nodepointer tmp;
					tmp = nodearr[i];
					while (tmp->next!= NULL)
						tmp = tmp->next;
					tmp->next= add_temp;
				}
			}
		}
	}
	/*by using dfs print out connected elements*/
	connected();
	fclose(fp);
	fclose(sp);
	return 0;
}