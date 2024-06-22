#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef struct point{
    int  row, col;		// 列表中行列元素
    int dir;		//方向
}mark;

typedef mark DataType;

typedef struct {
    DataType data[MAXSIZE]; 	// 存储栈内元素
    int top;                  // 栈顶指针
}SeqStack, * PSeqStack;

PSeqStack Init_SeqStack (void)		// 初始化栈
{
    PSeqStack S;              // 定义指向顺序栈的指针变量
    S = (PSeqStack)malloc(sizeof(SeqStack));    // 为顺序栈动态分配内存
    if (S)
        S->top = -1;         // 初始化栈顶指针为-1，表示栈为空
    else
        exit(-1);       // 若分配失败则退出程序
    return S;
}

int Empty_SeqStack(PSeqStack S)		// 判断栈是否为空,若为空返回1，否则返回0
{
    if (S->top == -1)
        return 1;
    else
        return 0;
}

int Push_SeqStack(PSeqStack S,DataType x)		// 入栈
{
    if (S->top == MAXSIZE - 1)        // 栈满
    {
        printf("栈满不能入栈\n");
        return 0;
    }
    else
    {
        S->top++;                // 栈顶指针加1
        S->data[S->top] = x;		// 新加入元素插在top位置
        return 1;
    }
}

int Pop_SeqStack(PSeqStack S,DataType *x)		// 出栈
{
    if(Empty_SeqStack(S))
        return 0;        // 栈空，不能出栈
    else
    {
        *x = S->data[S->top];                   // 读取栈顶元素
        S->top--;                               // 栈顶指针减1
        return 1;
    }
}

int GetTop_SeqStack(PSeqStack S ,DataType *x)		// 获取栈顶元素
{
    if(Empty_SeqStack(S))
        return 0;                  // 栈空，无法获取栈顶元素
    else
    {
        *x = S->data[S->top];          // 读取栈顶元素
        return 1;
    }
}
int GetLength_SeqStack(PSeqStack S)			//获取栈的长度
{
    return S->top + 1;
}

void Distory_SeqStack(PSeqStack *S)		//销毁栈，释放空间 
{
    if(*S)
        free(*S);
    *S = NULL;
}
