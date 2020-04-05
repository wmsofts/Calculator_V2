#include "../head/calculator.h"
#include "stdlib.h"
#include "stdio.h" 
#define MAX 100 

//初始化存放数的栈
void stack_num(int *stack,int *top)
{
	int i;
	for(i = 0;i < MAX;i ++)
	{
		stack[i] = 0;
	}
	*top = -1;
}

//初始化存放运算符的栈 
void stack_operator(char *stack,int *top)
{
	int i;
	for(i = 0;i < MAX;i ++)
	{
		stack[i] = 0;
	}
	*top = -1;
}

 //检查栈是不是满
int check_full(int *top)
{
	if(*top == MAX - 1)
	{
		return STACK_FULL;
	}
	return STACK_RIGHT;
}

//检查栈是不是空
int check_empty(int *top)
{
	if(*top == -1)
	{
		return STACK_EMPTY;
	}
	return STACK_RIGHT;
}

//判断运算符的优先级
int priority(char c)
{
	switch(c)
	{
		//加减同优先级 
		case '+': 
		case '-':
		{
			return 1;
			break;
		}
		//乘除同优先级 
		case '*':
		case '/':
		{
			return 2;
			break;
		}
		default:
		{
			return 0;
		}
	}
	return 0;
}

//比较运算符优先级 
int compare_priority(char *str,char *stack2,int *top2,int *stack1,int *top1)
{
	int num,num1,total;
	char c;
	if(*str == '\0')
	{
		return SUCCESS;
	}
	if(check_full(top2) == STACK_FULL)
	{
		return STACK_FULL;
	}
	else if(check_empty(top2) == STACK_EMPTY||*str == '(')
	{
		
		push_operator(stack2,str,top2);
	}
	else if(*str == ')')
	{
		c = pop_operator(stack2,top2); //从栈顶取出一个运算符
		while(c != '(')
		{
			num = pop_num(stack1,top1); //取出一个操作数
			num1 = pop_num(stack1,top1);
			total = calculate(num1,num,c); //运算
			push_num(stack1,&total,top1); //将运算结果入栈
			c = pop_operator(stack2,top2);
		}
	}
	else
	{
		c = pop_operator(stack2,top2);
		if(c == '(') 
		{
			push_operator(stack2,&c,top2);//运算符入栈
			push_operator(stack2,str,top2);
			return SUCCESS;
		}
		num = priority(c);
		num1 = priority(*str);
		if(num1 > num)//运算符优先级大于栈顶优先级
		{
			push_operator(stack2,&c,top2); //运算符入栈 
			push_operator(stack2,str,top2);
		}
		else
		{
			num = pop_num(stack1,top1);//取出栈顶运算符和操作数栈栈顶的连续两个操作数
			num1 = pop_num(stack1,top1);
			total = calculate(num1,num,c);//运算 
			push_num(stack1,&total,top1);//结果存入栈 
			compare_priority(str,stack2,top2,stack1,top1);//继续比较该运算符与栈顶运算符的优先级 
		}
	}
	return SUCCESS;
}

//两数执行四则运算 
int calculate(int num1,int num2,char c) 
{
	switch(c)
	{
		case '+':
		{
			return num1 + num2;
		}
		case '-':
		{
			return num1 - num2;
		}
		case '*':
		{
			return num1 * num2;
		}
		case '/':
		{
			return num1 / num2;
		}
		
	}
}

//数进栈
int push_num(int *stack,int *num,int *top)
{
	if(check_full(top) == STACK_FULL)
	{
		return STACK_FULL;
	}
	(*top) ++;
	stack[*top] = *num;
	return PUSH_SUCCESS;
}

//运算符进栈 
int push_operator(char *stack,char *c,int *top)
{
	if(check_full(top) == STACK_FULL)
	{
		return STACK_FULL;
	}
	(*top) ++;
	stack[*top] = *c;
	return PUSH_SUCCESS;
}

//数出栈 
int pop_num(int *stack,int *top)
{
	int num;
	if(check_empty(top) == STACK_EMPTY)
	{
		return STACK_EMPTY;
	}
	num = stack[*top];
	(*top) --;
	return num;
}

//运算符出栈 
char pop_operator(char *stack,int *top)
{
	char c;
	if(check_empty(top) == STACK_EMPTY)
	{
		return STACK_EMPTY;
	}
	c = stack[*top];
	(*top) --;
	return c;
}

//输入输出和核心计算 
int CalcCore()
{
	int num,num1;
	int total;
	char c;
	//分配空间
	char *dest = (char *)malloc(sizeof(100)); 
	char *temp = dest;//首地址
	char *str = (char *)malloc(sizeof(100));	
	//数栈	
	int stack1[MAX];					
	int top1;
	stack_num(stack1,&top1);
	//运算符栈		
	char stack2[MAX];					
	int top2;
	stack_operator(stack2,&top2);
	//输入 
	scanf("%s",str);
	char *ptr = str;	
    if(*str == '-') //解决第一个数是负数的特殊情况 
	{num = 0;
	push_num(stack1,&num,&top1);
	}
	while(*str != '\0')
	{   
		if(*str >= '0'&&*str <= '9')//数字 
		{
			while(*str >= '0'&&*str <= '9')
			{
				*temp = *str;
				str ++;
				temp ++;
		        
			}
			*temp = '\0';
			temp = dest;		
			num = atoi(dest);//字符串转整型
			push_num(stack1,&num,&top1);
		}		
		compare_priority(str,stack2,&top2,stack1,&top1);		//比较运算符的优先级 

		if(*str == ' '||(*str >= 'a' && *str <= 'z')||(*str >= 'A' && *str <= 'Z')) //避开错误输入 
		{
			printf("错误：式中含有字母，输入错误。");
			break;
		}
		if(*str == '\0')
		{break;
		}
		str ++;
	}
    //取出计算 
	while(top2 != -1)
	{
		num = pop_num(stack1,&top1);
		num1 = pop_num(stack1,&top1);
		c = pop_operator(stack2,&top2);
		total = calculate(num1,num,c);
		push_num(stack1,&total,&top1);
	}
	printf(" = %d\n",total);	
	return 0;
}
