#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef struct point{
    int  row, col;		// �б�������Ԫ��
    int dir;		//����
}mark;

typedef mark DataType;

typedef struct {
    DataType data[MAXSIZE]; 	// �洢ջ��Ԫ��
    int top;                  // ջ��ָ��
}SeqStack, * PSeqStack;

PSeqStack Init_SeqStack (void)		// ��ʼ��ջ
{
    PSeqStack S;              // ����ָ��˳��ջ��ָ�����
    S = (PSeqStack)malloc(sizeof(SeqStack));    // Ϊ˳��ջ��̬�����ڴ�
    if (S)
        S->top = -1;         // ��ʼ��ջ��ָ��Ϊ-1����ʾջΪ��
    else
        exit(-1);       // ������ʧ�����˳�����
    return S;
}

int Empty_SeqStack(PSeqStack S)		// �ж�ջ�Ƿ�Ϊ��,��Ϊ�շ���1�����򷵻�0
{
    if (S->top == -1)
        return 1;
    else
        return 0;
}

int Push_SeqStack(PSeqStack S,DataType x)		// ��ջ
{
    if (S->top == MAXSIZE - 1)        // ջ��
    {
        printf("ջ��������ջ\n");
        return 0;
    }
    else
    {
        S->top++;                // ջ��ָ���1
        S->data[S->top] = x;		// �¼���Ԫ�ز���topλ��
        return 1;
    }
}

int Pop_SeqStack(PSeqStack S,DataType *x)		// ��ջ
{
    if(Empty_SeqStack(S))
        return 0;        // ջ�գ����ܳ�ջ
    else
    {
        *x = S->data[S->top];                   // ��ȡջ��Ԫ��
        S->top--;                               // ջ��ָ���1
        return 1;
    }
}

int GetTop_SeqStack(PSeqStack S ,DataType *x)		// ��ȡջ��Ԫ��
{
    if(Empty_SeqStack(S))
        return 0;                  // ջ�գ��޷���ȡջ��Ԫ��
    else
    {
        *x = S->data[S->top];          // ��ȡջ��Ԫ��
        return 1;
    }
}
int GetLength_SeqStack(PSeqStack S)			//��ȡջ�ĳ���
{
    return S->top + 1;
}

void Distory_SeqStack(PSeqStack *S)		//����ջ���ͷſռ� 
{
    if(*S)
        free(*S);
    *S = NULL;
}
