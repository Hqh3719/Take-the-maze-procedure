#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"seqstack.h"

#define MAX_ROW  11
#define MAX_COL  10

int maze[11][10] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 1, 0, 1, 1,
    1, 0, 1, 1, 1, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 1, 1,
    1, 0, 1, 1, 1, 1, 0, 0, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

void print_line()		//����һ����ӡ�Թ���ͼ�ĺ���
{
    int i, j;
    //ѭ�������ά����maze�б���ĵ�ͼ��Ϣ
    for (i = 0; i < MAX_ROW; i++){
        for (j = 0; j < MAX_COL; j++)
            if (maze[i][j] == 1)       //�����λ��Ϊ1����Ϊǽ�������"��"
				printf("��");
			//�����λ��������3�����ϣ����ʾ����㿪ʼ�����λ�ô���һ��·��
            else if (maze[i][j] >= 3){
            	//�����������½ǵĳ��������"��"��ʾͨ·�ߵ����յ㣬�������"��"��ʾͨ·
                if (i == MAX_ROW-2 && j == MAX_COL-2)  
					printf("��");
                else                   
					printf("��");
            }
            else  
				printf("  ");
            printf("\n");
        }
}

void visit(mark p,int sign, PSeqStack S)
{
    Push_SeqStack(S,p);		//����λ��pѹ��ջs��
	    switch (sign)
	    {
		    case 1: 	//������ 
				p.col++;
				Push_SeqStack(S, p); 
				maze[p.row][p.col] = 2; 
				break;
		    case 2: 	//������
				p.row++; 
				Push_SeqStack(S, p); 
				maze[p.row][p.col] = 2; 
				break;
		    case 3: 	//������
				p.col--; 
				Push_SeqStack(S, p); 
				maze[p.row][p.col] = 2; 
				break;
		    case 4: 	//������
				p.row--; 
				Push_SeqStack(S, p); 
				maze[p.row][p.col] = 2; 
				break;
	    }
}

int main()
{
    struct point p = { 1, 1 };	//��ʼ����ǰ��Ϊ���(1,1)
    maze[p.row][p.col] = 2;	//�������ĵ�����Ϊ2
    PSeqStack S = Init_SeqStack();	//����ջ
    Push_SeqStack(S,p);	//�����ѹ��ջ��
    while (!Empty_SeqStack(S))
    {			//ջ��Ϊ��ʱѭ��
        Pop_SeqStack(S, &p);	//��ջ
        if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)	//�ж��Ƿ񵽴��յ�(max_row-2,max_col-2)
            break;
        else if (p.col + 1 < MAX_COL - 1 && maze[p.row][p.col + 1] == 0)		//��������
        {
        	p.dir = 1;
            visit(p, 1, S);		//�����ұߵĵ㣬��������뵽ջ��
        	continue;       //ִ����һ��ѭ��
        }
        else if (p.row + 1 < MAX_ROW - 1 && maze[p.row + 1][p.col] == 0)		//��������
        {
        	p.dir = 2;
            visit(p, 2, S);		//�����±ߵĵ㣬��������뵽ջ��
        	continue;       //ִ����һ��ѭ��
        }
        else if (p.col - 1 >= 1 && maze[p.row][p.col - 1] == 0)		//��������
        {
        	p.dir = 3;
            visit(p, 3, S);		//������ߵĵ㣬��������뵽ջ��
        	continue;       //ִ����һ��ѭ��
        }
        else if (p.row - 1 >= 1 && maze[p.row - 1][p.col] == 0)		//��������
        {
        	p.dir = 4;
            visit(p, 4, S);		//�����ϱߵĵ㣬��������뵽ջ��
        	continue;       //ִ����һ��ѭ��
        }
    }
    if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)//�ж��Ƿ��ҵ��յ�
    {
        int count = GetLength_SeqStack(S)+3;//����·�����ȣ�Ϊ�����Թ�0,1,2���������Ի���Ҫ��3��ʼ
        printf("�ɹ��ҵ����ڣ���ͨ·������·��Ϊ��\n");
        printf("(%d,%d,0)", p.row, p.col);
        maze[p.row][p.col] = count;		//�����ǰλ�ò���maze�������Ϊcount
        while (!Empty_SeqStack(S))//����ǰ�����в���
        {
            count--;
			Pop_SeqStack(S, &p);
            maze[p.row][p.col] = count;
			printf("->");
            printf("(%d,%d,%d)", p.row, p.col, p.dir);	//�������
        }
        printf("\n\n");
        printf("���Թ�·��������ʾ��'��'��ʾǽ,'��'��ʾ·��,'��'��ʾ�յ㣩��\n");
        print_line();
    }
    else {
        printf("û��ͨ·��\n");
    }
    return 0;
}
