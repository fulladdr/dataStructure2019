#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 21

typedef enum {
	lparen, rparen, plus, minus, times, divide,
	mod, eos, unary,operand	
} precedence;

static int isp[] = { 0,19,12,12,13,13,13,0,20,21};
static int icp[] = { 20,19,12,12,13,13,13,0,20,21};

char expr[MAX_EXPR_SIZE];
char expr2[MAX_EXPR_SIZE];
char postFix[MAX_EXPR_SIZE];
int i = 0;
int top = -1;
precedence getToken3(char *symbol, int *n);
precedence stack[MAX_STACK_SIZE];
char stack2[MAX_STACK_SIZE];
void push(precedence item);
void push2(char item);
precedence pop();
precedence pop2();
void stackFull();
void stackEmpty();
precedence Tokenmatch(char *x);
precedence getToken(char *symbol, int *n);
precedence printToken(precedence t);
int eval(void);
precedence getToken2(char *symbol, int *n);
void expr_check();
void push(precedence item)
{
	if (top >= MAX_STACK_SIZE - 1)
	{
		stackFull();
	}
	stack[++top] = item;
}
void push2(char item)
{
	if (top >= MAX_STACK_SIZE - 1)
	{
		stackFull();
	}
	stack2[++top] = item;
}
precedence pop()
{
	if (top == -1)
	{
		stackEmpty();
	}
	return stack[(top)--];
}
precedence pop2()
{
	if (top == -1)
	{
		stackEmpty();
	}
	return stack2[top--];
}
void stackFull()
{
	exit(EXIT_FAILURE);
}
void stackEmpty()
{
	exit(EXIT_FAILURE);
}
precedence Tokenmatch(char *x)
{
	switch (*x)
	{
	case '(': return lparen; break;
	case ')': return rparen; break;
	case '+': return plus; break;
	case '-': return minus; break;
	case '#':return unary; break;
	case '/': return divide; break;
	case '*': return times; break;
	case '%': return mod; break;
	case '\0': return eos; break;
	default: return operand;
	}
}
void expr_check()
{
	//올바른 식인지 판단해줌
	int i, len = strlen(expr);
	int oprt_num = 0, oprn_num = 0, lparen_num = 0, rparen_num = 0;;
	for (i = 0; i < len; i++)
	{
		precedence x = Tokenmatch(&expr[i]);
		{
			switch (x)
			{
			case(operand):
			{
				oprn_num++; break; }
			case(lparen):
			{
				lparen_num++; break; }
			case(rparen):
			{	rparen_num++; break; }
			case(plus):
			{
				oprt_num++; break; }
			case(minus):
			{
				if (expr[i - 1] == '\0' || expr[i - 1] == '(')
					break;
				else
				{
					oprt_num++;
					break;
				}
			}
			case(divide):
			{
				oprt_num++; break;
			}
			case(times):
			{
				oprt_num++; break;
			}
			case(mod):
			{
				oprt_num++; break;
			}
			}
		}
	}
	//각각의 operator과 operand 숫자를 세어준다
	if (lparen_num != rparen_num)
	{//왼쪽괄호의 수와 오른쪽 괄호의 수는 같아야 한다
		fprintf(stderr, "Invalid expression");
		exit(EXIT_FAILURE);
	}
	else if (oprn_num != oprt_num + 1)
	{//연산자의 수는 피연산자의 수보다 한개 적어야 한다
		fprintf(stderr, "Invalid expression");
		exit(EXIT_FAILURE);
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
	case '-':
	{
		if (expr[(*n)-2]=='\0'||expr[(*n)-2]=='(')
			return unary;
		else
			return minus;
	}
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}
precedence getToken2(char *symbol, int *n)
{
	*symbol = expr2[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen; break;
	case ')': return rparen; break;
	case '+': return plus; break;
	case '-':
	{
		if (expr2[(*n) - 2] == '\0' || expr2[(*n) - 2] == '(')
		{
			return unary; break;
		}
		else
		{
			return minus; break;
		}
	}
	case '/': {return divide; break; }
	case '*': {return times; break; }
	case '%': {return mod; break; }
	case '\0': {return eos; break; }
	default: {return operand; }
	}
}
precedence getToken3(char *symbol, int *n)
{
	*symbol = expr2[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen; break;
	case ')': return rparen; break;
	case '+': return plus; break;
	case '-':return minus; break;
	case '#':return unary; break;
	case '/': return divide; break;
	case '*': return times; break;
	case '%': return mod; break;
	case '\0': return eos; break; 
	default: return operand;
	}
}
precedence printToken(precedence  t)
{
	switch (t)
	{
	case lparen: fprintf(stdout,"(");
		break;
	case rparen: fprintf(stdout,")");
		break;
	case plus: fprintf(stdout, "+");
		break;
	case minus: fprintf(stdout, "-");
		break;
	case divide: fprintf(stdout, "/");
		break;
	case times: fprintf(stdout, "*");
		break;
	case mod: fprintf(stdout, "%%");
		break;
	case unary: fprintf(stdout, "#");
		break;
	case eos: fprintf(stdout, " ");
		break;//""
	default: fprintf(stdout, "\n");
	}
}
void postfix(void)
{
	fprintf(stdout, "Postfix: ");
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	expr_check();
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
		{
			fprintf(stdout, "%c", symbol);
		}
		//postfix의 경우 operand의 순서는 바뀌지 않는다는 사실에 입각해서 바로 프린트해줌
		else if (token == rparen)
		{
			while (stack[top] != lparen)
			{  
				printToken(pop());
			}
			pop();//왼쪽괄호는 프린트 하지 않고 pop해줌
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
			//스택안에 있는 토큰의 연산자 순위가 더 높아 먼저 처리해줘야 할 경우 프린트해준다
			{
				printToken(pop());
			}
			push(token);
		}
	}
	while ((token = pop()) != eos)
	{
		//eos를 만날때까지 토큰을 차례대로 print해줌
		printToken(token);
	}
	fprintf(stdout, "\n");
}
int	eval(void)
{
	//postfix 식의 계산 결과를 출력
	int op1, op2;
	char symbol;
	precedence token;
	int n = 0, k = 0;
 	top = 0;
	stack2[0] = '\0';
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
		{
			expr2[k++] = symbol;
		}
		else if (token == rparen)
		{
			while (stack2[top] != '(')
			{
				expr2[k++] = pop2();
			}
			pop2();
		}
		else
		{
			while (isp[Tokenmatch(&stack2[top])] >= icp[token])
			{
				if (stack2[top] == '#')
					expr2[k++] = '#';
				//unary character일 경우는 별도로 하여 처리
				else
					expr2[k++] = pop2();
			}
			if (token == unary)
				push2('#');
			else
				push2(symbol);
		}
	}
	while (top!=-1)
	{
		expr2[k++] = pop2();
	}
	n = 0;
	token = getToken3(&symbol, &n);
	while (token != eos)
	{
		if (token == operand) 
			push2(symbol);
		else if (token == unary)
		{
			op1 = pop2()-48;
			push2(op1*(-1) + 48);
		}
		//unary character일 경우는 -처리 해준다음에 다시 넣어줌
		else
		{
			op2 = pop2()-48;
			op1 = pop2()-48;
			switch (token)
			{
			case plus: push2(op1 + op2 + 48);break;
			case minus: push2(op1 - op2 + 48); break;
			case times: push2(op1*op2 + 48); break;
			case divide:push2(op1 / op2 + 48); break;
			case mod: push2(op1%op2 + 48);
			}
		} 
		token = getToken3(&symbol, &n);
	}
	return pop2()-48;
}
int main()
 {
	fprintf(stdout, "Input: ");
	fscanf(stdin, "%s", expr);
	postfix();//postfix함수에 넣는다
	fprintf(stdout, "Result: %d", eval());
	fprintf(stdout, "\n");
	return 0;
}