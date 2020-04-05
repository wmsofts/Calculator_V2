#include "..\head\calculator.h"
#include "..\calculator\calculator.c"
#include "stdlib.h"
#include "stdio.h" 
int main() 
{
    void ScreenShow();
    int CalcCore();
    ScreenShow(); 
    while(1){
	CalcCore();
	}
    return 0;
}
 
void ScreenShow(){
	printf("欢迎使用四则运算计算器V2！\n");
	printf("***********************\n");
	printf("说明：\n(1)支持带括号的运算式，括号必须是英文状态下输入的括号。\n");
	printf("(2)只支持第一个数为负数的情况。\n(3)不支持浮点运算。\n") ;
	printf("***********************\n");
	printf("请输入算术式，注意英文括号，按下Enter计算：\n");
} 
