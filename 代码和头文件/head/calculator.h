/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef CAL_CORE_H_INCLUDED
#define CAL_CORE_H_INCLUDED

/**************************************************************
*	Macro Define Section
**************************************************************/

#define OVERFLOW -1
#define MAX 100 

/**************************************************************
*	Struct Define Section
**************************************************************/
enum usu
{
	STACK_FULL = -10,
	STACK_RIGHT,
	STACK_EMPTY,
	SUCCESS,
	PUSH_SUCCESS
};
 
/**************************************************************
*	Prototype Declare Section
**************************************************************/
//初始化存放数的栈
void stack_num(int *stack,int *top);

//初始化存放运算符的栈 
void stack_operator(char *stack,int *top);

//检查栈是不是满
int check_full(int *top);

//检查栈是不是空
int check_empty(int *top);

//判断运算符的优先级
int priority(char c);

//比较运算符优先级 
int compare_priority(char *str,char *stack2,int *top2,int *stack1,int *top1);

//两数执行四则运算 
int calculate(int num1,int num2,char c) ;

//数进栈
int push_num(int *stack,int *num,int *top);

//运算符进栈 
int push_operator(char *stack,char *c,int *top);

//数出栈 
int pop_num(int *stack,int *top);

//运算符出栈 
char pop_operator(char *stack,int *top);

//输入和核心计算 
int CalcCore();

 /**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
 
 
