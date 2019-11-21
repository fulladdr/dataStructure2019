#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
char expr[MAX_EXPR_SIZE];
char stack[MAX_STACK_SIZE];
char* stack2[MAX_STACK_SIZE];

int top = -1;
int top2 = -1;

typedef enum {
	lparen, rparen, plus, minus, times, divide,
	mod, eos, operand
} precedence;
precedence Tokenmatch(char *x);
precedence getToken(char *symbol, int *n);
void push(char c);
void push2(char* item);
char pop(void);
char* pop2(void);
void stackFull(void);
void stackEmpty(void);
void prefix(void);
void append(char *dst, char c);
int i = 0;

static int isp[] = { 0,19,12,12,13,13,13,0,21 };
static int icp[] = { 20,19,12,12,13,13,13,0,21 };

void append(char *dst, char c) {
	char *p = dst;
	while (*p != '\0') p++; // 문자열 끝 탐색
	*p = c;
	*(p + 1) = '\0';
}
precedence Tokenmatch(char *x)
{
	switch (*x)
	{
	case '(': return lparen; break;
	case ')': return rparen; break;
	case '+': return plus; break;
	case '-': return minus; break;
	case '/': return divide; break;
	case '*': return times; break;
	case '%': return mod; break;
	case '\0': return eos; break;
	default: return operand;
	}
}
precedence getToken(char *symbol, int *n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}
void push(char c)
{
	if (top >= MAX_STACK_SIZE - 1)
	{
		stackFull();
	}
	stack[++top] = c;
}
void push2(char* item)
{
	//스트링을 넣는 배열 선언
	if (top2 >= MAX_STACK_SIZE - 1)
	{
		stackFull();
	}
	top2++;
	stack2[top2] = (char*)malloc(sizeof(char)*strlen(item) + 1);
	int len = strlen(item);
	for (int i = 0; i < len + 1; i++)
		stack2[top2][i] = item[i];
}

char pop()
{
	if (top == -1)
	{
		stackEmpty();
	}
	return stack[(top)--];
}

char* pop2()
{
	if (top2 == -1)
	{
		stackEmpty();
	}
	return stack2[(top2)--];
}

void stackFull()
{
	exit(EXIT_FAILURE);
}

void stackEmpty()
{
	exit(EXIT_FAILURE);
}

void prefix(void)
{
	char string[21];
	char symbol;
	char *op1, *op2;
	precedence token;
	int n = 0;
	stack[0] = '\0';
	stack2[0] = '\0';
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (symbol == '(')
		{
			push(symbol);
		}
		else if (symbol == ')')
		{
			while (top != -1 && stack[top] != '(')
			{
				//오른쪽 괄호를 만났을 때 왼쪽 괄호를 만날 때까지 pop해준 다음에 연산자부터 붙여줌
				op1 = pop2();
				op2 = pop2();
				int idx = 0;
				string[idx++] = stack[top];
				int len = strlen(op2);
				for (int i = 0; i < len; i++) string[idx++] = op2[i];
				len = strlen(op1);
				for (int i = 0; i < len; i++) string[idx++] = op1[i];
				string[idx] = '\0';

				pop();
				push2(string);
			}
			pop();//pop left parenthesis
		}
		else if (token == operand)
		{
			char a[2];
			a[0] = symbol;
			a[1] = 0;
			push2(a);
		}
		else
		{
			while (top != -1 && isp[Tokenmatch(&stack[top])] >= icp[token])
			{
				op1 = pop2();
				op2 = pop2();
				int idx = 0;
				string[idx++] = stack[top];
				int len = strlen(op2);
				for (int i = 0; i < len; i++) string[idx++] = op2[i];
				len = strlen(op1);
				for (int i = 0; i < len; i++) string[idx++] = op1[i];
				string[idx] = '\0';
				pop();
				push2(string);
			}
			push(symbol);
		}
	}

	while (top != -1)
	{
		op1 = pop2();
		op2 = pop2();
		int idx = 0;
		string[idx++] = stack[top];
		int len = strlen(op2);
		for (int i = 0; i < len; i++) string[idx++] = op2[i];
		len = strlen(op1);
		for (int i = 0; i < len; i++) string[idx++] = op1[i];
		string[idx] = '\0';

		pop();
		push2(string);
	}
	fprintf(stdout,"%s", stack2[top2]);
	fprintf(stdout, "\n");
}

int main()
{
	fprintf(stdout, "Infix:");
	fscanf(stdin, "%s", expr);
	prefix();
	return 0;
}