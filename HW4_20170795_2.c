#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 24
#define IS_FULL(ptr)(!(ptr))
#define FALSE 0
#define TRUE 1

typedef struct node *node_pointer;
typedef struct node {
	char* data;//이름 변수를 저장
	node_pointer link;
}node;

node_pointer seq[MAX_SIZE];

void record(char* name)//P를 받았을 때 배열에 저장해줌
{
	int i;
	node_pointer x;
	x = (node_pointer)malloc(sizeof(struct node));
	for (i = 0; i < MAX_SIZE; i++)
	{
		if (seq[i] == NULL)
			break;
		else
			continue;

	}
	x->data = (char*)calloc(sizeof(char),15);
	strcpy(x->data, name);
	x->link = seq[i];
	seq[i] = x;
}
void push(char* name,char* r_name)
{
	int i;
	int cnt = 0;
	for (i = 0; i < MAX_SIZE; i++)
	{
		node_pointer x;
		node_pointer tmp;
 		if (strcmp(seq[i]->data,name)==0)
		{
			x = (node_pointer)malloc(sizeof(struct node));
			tmp = (node_pointer)malloc(sizeof(struct node));
			x->data = (char*)calloc(sizeof(char), 15);
			strcpy(x->data, r_name);
			tmp = seq[i];
			while (tmp->link != NULL)
				tmp = tmp->link;
			tmp->link = x;
			x->link = NULL;
			cnt++;
		}
 		if (strcmp(seq[i]->data,r_name) == 0)
		{
			x = (node_pointer)malloc(sizeof(struct node));
			tmp = (node_pointer)malloc(sizeof(struct node));
			x->data = (char*)calloc(sizeof(char), 15);
			strcpy(x->data, name);
			tmp = seq[i];
			while (tmp->link != NULL)
				tmp = tmp->link;
			tmp->link = x;
			x->link = NULL;

			cnt++;
		}
		if (cnt == 2)
			break;
	}
}
//U
void pop(char* p1,char* p2)
{
	int i;
	int count = 0;
	node_pointer tmp,ptr;
	for (i = 0; i < MAX_SIZE; i++)
	{
		if (strcmp(seq[i]->data, p1) == 0)
		{
			tmp = seq[i];
			while (tmp->link!=NULL)
			{
				ptr = tmp;
				tmp = tmp->link;
				if (strcmp(tmp->data, p2) == 0)
				{
					ptr->link = tmp->link;
					free(tmp);
					count++;
					break;
				}
			}
		}
		if (strcmp(seq[i]->data, p2) == 0)
		{
			tmp = seq[i];
			while (tmp->link != NULL)
			{
				ptr = tmp;
				tmp = tmp->link;
				if (strcmp(tmp->data, p1) == 0)
				{
					ptr->link = tmp->link;
					free(tmp);
					count++;
				}
				break;
			}
		}
		if (count == 2)
			break;
	}
}
int main(void)
{
	FILE* fp;
	FILE* sp;
	node_pointer x;
	/*명령받을배열*/
	char str[15];
	char p1[15] = { '0' };
	char p2[15]={ '0' };//2개의 인자를 주어야할 경우 두번째 인자를 받을 배열
	char fcall;//호출해야할 함수를 알려줌
	fp = fopen("input.txt","r");
	sp = fopen("output.txt", "w");
	while (1)
	{
		//파일에서 한줄씩 명령 받음
		//fgets(str, sizeof(str), fp);
		fcall=fgetc(fp);
		if (fcall == 'X')
		{
			exit(1);
		}
		if (fcall == 'P')
		{
			fscanf(fp, "%s",str);
			record(str);
		}
		if (fcall == 'F')
		{
			fscanf(fp, "%s", p1);
			fscanf(fp, "%s", p2);
			push(p1,p2);
		}
		if (fcall == 'L')
		{
			int i;
			fscanf(fp, "%s", str);
			for (i= 0; i < MAX_SIZE; i++)
			{
				if (strcmp(seq[i]->data,str)==0)
					break;
			}
			x = seq[i];
			while (x->link!=NULL)
			{
				x = x->link;
				fprintf(sp,"%s ", x->data);
			}
			fprintf(sp,"\n");
		}
		if (fcall == 'U')
		{
			int i;
			node_pointer x;
			fscanf(fp, "%s", p1);
			fscanf(fp, "%s", p2);
			pop(p1, p2);
		}
		if (fcall == 'Q')
		{
			int i;
			int flag = 1;
			node_pointer x;
			fscanf(fp, "%s", p1);
			fscanf(fp, "%s", p2);
			for (i = 0; i < MAX_SIZE; i++)
			{
				if (strcmp(seq[i]->data, p1) == 0)
				{
					x = seq[i];
					for (;;)
					{
						if (strcmp(x->data, p2) == 0)
						{
							fprintf(sp, "Yes\n");
							flag = 0;
							break;
						}
						if (x->link == NULL)
						{
							fprintf(sp, "No\n");
							flag = 0;
							break;
						}
						x = x->link;
					}
				}
				if (flag == 0)
					break;
			}
		}
	}
	fclose(fp);
	fclose(sp);
	return 0;
}