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

void print_line()		//定义一个打印迷宫地图的函数
{
    int i, j;
    //循环输出二维数组maze中保存的地图信息
    for (i = 0; i < MAX_ROW; i++){
        for (j = 0; j < MAX_COL; j++)
            if (maze[i][j] == 1)       //如果该位置为1，即为墙，则输出"■"
				printf("■");
			//如果该位置是数字3或以上，则表示从起点开始到这个位置存在一条路径
            else if (maze[i][j] >= 3){
            	//因此如果是右下角的出口则输出"★"表示通路走到了终点，否则输出"☆"表示通路
                if (i == MAX_ROW-2 && j == MAX_COL-2)  
					printf("★");
                else                   
					printf("☆");
            }
            else  
				printf("  ");
            printf("\n");
        }
}

void visit(mark p,int sign, PSeqStack S)
{
    Push_SeqStack(S,p);		//将该位置p压入栈s中
	    switch (sign)
	    {
		    case 1: 	//向右走 
				p.col++;
				Push_SeqStack(S, p); 
				maze[p.row][p.col] = 2; 
				break;
		    case 2: 	//向下走
				p.row++; 
				Push_SeqStack(S, p); 
				maze[p.row][p.col] = 2; 
				break;
		    case 3: 	//向左走
				p.col--; 
				Push_SeqStack(S, p); 
				maze[p.row][p.col] = 2; 
				break;
		    case 4: 	//向上走
				p.row--; 
				Push_SeqStack(S, p); 
				maze[p.row][p.col] = 2; 
				break;
	    }
}

int main()
{
    struct point p = { 1, 1 };	//初始化当前点为起点(1,1)
    maze[p.row][p.col] = 2;	//遍历过的点设置为2
    PSeqStack S = Init_SeqStack();	//创建栈
    Push_SeqStack(S,p);	//将起点压入栈中
    while (!Empty_SeqStack(S))
    {			//栈不为空时循环
        Pop_SeqStack(S, &p);	//出栈
        if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)	//判断是否到达终点(max_row-2,max_col-2)
            break;
        else if (p.col + 1 < MAX_COL - 1 && maze[p.row][p.col + 1] == 0)		//向右搜索
        {
        	p.dir = 1;
            visit(p, 1, S);		//访问右边的点，并将其加入到栈中
        	continue;       //执行下一次循环
        }
        else if (p.row + 1 < MAX_ROW - 1 && maze[p.row + 1][p.col] == 0)		//向下搜索
        {
        	p.dir = 2;
            visit(p, 2, S);		//访问下边的点，并将其加入到栈中
        	continue;       //执行下一次循环
        }
        else if (p.col - 1 >= 1 && maze[p.row][p.col - 1] == 0)		//向左搜索
        {
        	p.dir = 3;
            visit(p, 3, S);		//访问左边的点，并将其加入到栈中
        	continue;       //执行下一次循环
        }
        else if (p.row - 1 >= 1 && maze[p.row - 1][p.col] == 0)		//向上搜索
        {
        	p.dir = 4;
            visit(p, 4, S);		//访问上边的点，并将其加入到栈中
        	continue;       //执行下一次循环
        }
    }
    if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)//判断是否找到终点
    {
        int count = GetLength_SeqStack(S)+3;//计算路径长度，为了与迷宫0,1,2的区别所以基数要以3开始
        printf("成功找到出口，该通路的坐标路线为：\n");
        printf("(%d,%d,0)", p.row, p.col);
        maze[p.row][p.col] = count;		//输出当前位置并将maze数组更新为count
        while (!Empty_SeqStack(S))//按照前驱进行查找
        {
            count--;
			Pop_SeqStack(S, &p);
            maze[p.row][p.col] = count;
			printf("->");
            printf("(%d,%d,%d)", p.row, p.col, p.dir);	//输出坐标
        }
        printf("\n\n");
        printf("该迷宫路径如下所示（'■'表示墙,'☆'表示路径,'★'表示终点）：\n");
        print_line();
    }
    else {
        printf("没有通路！\n");
    }
    return 0;
}
