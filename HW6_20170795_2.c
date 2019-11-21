#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000
void KruskalMst();
int isEmpty1(void);
void dfs(int v);
void convert();
typedef struct node *nodepointer;
typedef struct node {
	int data;
	int weight;
	nodepointer next;
}node;
typedef struct edge{
	int u, v, w;
}edge;
typedef struct edge *edgepointer;
typedef struct edgelist {
	edge data[MAX];
	int n;
}edgelist;
edgelist elist;
edgelist spanlist;
int visited[MAX];
int visited_dfs[MAX];
FILE *fp;//read
FILE *rp;//write
nodepointer nodearr[MAX];
nodepointer finalarr[MAX];
void sort(void);
void initarr(void);
void union1(int belongs[], int c1, int c2);
nodepointer make_node(int x, int weight);
int find(int belongs[], int vertexno);
int n;//number of vertex
/*make node*/
nodepointer make_node(int x, int weight)
{
	nodepointer a = (nodepointer)calloc(sizeof(node), 1);
	a->data = x;
	a->weight = weight;
	a->next = NULL;
	return a;
}
/*make adj_matrix to adj_list*/
void adj_matrix(void)
{
	int i, j, k;
	nodepointer add_temp;
	/*file open*/
	fp = fopen("input.txt", "r");
	if (fp == NULL)
		fprintf(stderr, "No file input\n");
	fscanf(fp, "%d", &n);
	/*transpose to adjacency list*/
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			fscanf(fp, "%d", &k);
			if (k != -1)
			{
				if (nodearr[i] == NULL)
				{
					nodearr[i] = make_node(i,0);
					add_temp = make_node(j,k);
					nodearr[i]->next = add_temp;
				}
				else if (nodearr[i] != NULL)
				{
					add_temp = make_node(j,k);
					nodepointer tmp;
					tmp = nodearr[i];
					while (tmp->next != NULL)
						tmp = tmp->next;
					tmp->next = add_temp;
				}
			}
		}
	}
	fclose(fp);
	return;
}
void kruskal(void)
{
	int i, j,a,b;
	int belongs[MAX];
	nodepointer x;
	elist.n = 0;
	for (i = 0; i < n; i++)
	{
			x = nodearr[i];
			/*make list recording weight*/
			while (x->next != NULL)
			{
				elist.data[elist.n].v = i;
				elist.data[elist.n].u = x->next->data;
				elist.data[elist.n].w = x->next->weight;
				elist.n++;
				visited[x->next->data] = 1;
				x = x->next;
			}
	}
	/*sort according to weight*/
	sort();
	KruskalMst();
	return;
}
/*build MST*/
void KruskalMst()
{
	int e = 0, v = n - 1;
	int a, b;
	int belongs[MAX];
	for (int i = 0; i < n; i++)
		belongs[i] = i;
	spanlist.n = 0;
	while (e < v - 1)
	{
		for (int i = 0; i < elist.n; i++)
		{
			a = find(belongs, elist.data[i].u);
			b = find(belongs, elist.data[i].v);
			if (a != b)
			{
				spanlist.data[spanlist.n] = elist.data[i];
 				spanlist.n = spanlist.n + 1;
				union1(belongs, a, b);
				e++;
			}
		}
	}
	convert();
} 
nodepointer convert_arr[MAX];
void convert()
{
	int i, j,a,b;
	nodepointer add_temp;
	for (i = 0; i < n; i++)
	{
		a = spanlist.data[i].u;
		b = spanlist.data[i].v;
		if (convert_arr[a] == NULL)
		{
			convert_arr[a] = make_node(a, 0);
			add_temp = make_node(b, 0);
			convert_arr[a]->next = add_temp;
		}
		else if (convert_arr[a] != NULL)
		{
			add_temp = make_node(b, 0);				
			nodepointer tmp;
			tmp = convert_arr[i];
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = add_temp;
		}
		if (convert_arr[b] == NULL)
		{
			convert_arr[b] = make_node(b, 0);
			add_temp = make_node(a, 0);
			convert_arr[b]->next = add_temp;
		}
		else if (convert_arr[b] != NULL)
		{
			add_temp = make_node(a, 0);
			nodepointer tmp;
			tmp = convert_arr[i];
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = add_temp;
		}
	}
	dfs(convert_arr[0]->data);
}
void dfs(int x)
{
	nodepointer w;
	visited_dfs[x] = 1;
	fprintf(rp, "%d ", x);
	for (w = convert_arr[x]; w; w=w->next)
	{
		if (visited_dfs[w->data]==0)
			dfs(w->data);
	}
} 
/*figure out if its empty*/
int isEmpty1(void)
{
	if (elist.data == NULL)
		return 1;
	else
		return 0;
}
int find(int belongs[], int vertexno)
{
	return(belongs[vertexno]);
}
void union1(int belongs[], int c1, int c2)
{
	int i;

	for (i = 0; i < n; i++)
		if (belongs[i] == c2)
			belongs[i] = c1;
}
/*sort according to weight*/
void sort()
{
	int i, j;
	edge temp;
	for (i = 1; i < elist.n; i++)
	{
		for (j = 0; j < elist.n - 1; j++)
		{
			if (elist.data[j].w > elist.data[j + 1].w)
			{
				temp = elist.data[j];
				elist.data[j] = elist.data[j + 1];
				elist.data[j + 1] = temp;
			}
		}
	}

	return;
}
int main(void)
{
	rp = fopen("output.txt", "w");
	fclose(rp);
	rp = fopen("output.txt", "a");
	/*Make adjecency matrix*/
	adj_matrix();
	kruskal();
	int i, cost = 0;
	for (i = 0; i < spanlist.n; i++)
		cost = cost + spanlist.data[i].w;
	fprintf(rp,"\n%d\n", cost);
	fclose(rp);
	return 0;
}