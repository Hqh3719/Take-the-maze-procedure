#include<iostream>
#include<stack>//栈 
#include<vector>//容器 
#include<time.h>//获取当前时间 
#include <Windows.h>//颜色改变，时停 
#include<stdlib.h>//清屏 
#include <cstdlib>
 
using namespace std;
 
#define X 13//迷宫大小 
#define Y 12
#define start_row 2//起点
#define start_col 2
#define speed 30//速度 
 
struct box
{
	int row,col;		//行列坐标
	int dir;		//方向：右1 下2 左3 上4
};
 
int mg[X][Y];	//初始迷宫
int mglx[X][Y];	//展示迷宫路线，因原迷宫会被打乱
 
stack<box> path;	//路线，包含坐标与方向信息
 
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);	//颜色
 
void create_mg();	//随机生成迷宫
void copy_mg();		//复制迷宫
void play_mg();		//完成迷宫路线求解
void show_path();	//坐标路线展示 
void show_mg();		//迷宫路线展示
void cout_green();	//打印绿色
void cout_red();	//打印红色
void recover();		//恢复白色
 
void gotoxy(int row,int col);//将光标移动到（row,y）位置
void HideCursor();//隐藏光标
 
 
 
int main()
{
	while(true)
	{
		system("cls");	//清屏
		char choice;
		cout<<endl<<endl<<"*****\t欢迎来到迷宫求解问题\t*******"<<endl<<endl<<endl;
		cout<<"\t[1] 生成随机迷宫."<<endl;
		cout<<"\t[2] 测试迷宫."<<endl;
		cout<<"\t[3] 退出游戏."<<endl<<endl;
		cout<<"\t\t随机生成 "<<X-4<<" × "<<Y-4<<" 的迷宫"<<endl<<endl;
		cout<<"****************************************"<<endl<<endl;
		cout<<"请输入你的选择：";
		cin>>choice;
		if(choice=='1')
		{
			system("cls");
			while(true)
			{
				create_mg();
				if(mg[X-3][Y-3]==0)		//若终点是一堵墙，则重新生成迷宫
					break;
			}
			copy_mg();
			show_mg();
			system("pause");
			play_mg();
			show_path();
		}
		else if(choice=='2')
		{
			cout<<endl<<"**********\t测试迷宫\t************"<<endl;
		    const char* command = "maze_stack.exe";		//运行外部文件"maze_stack.cpp"	
		    int result = std::system(command);    // 执行命令
			cout<<endl<<"****************************************"<<endl<<endl;
		}
		
		else if(choice=='3')
			return 0;
		else
			cout<<"请输入正确的选择!"<<endl;
		system("pause");
	}
}
 
void create_mg()	//随机生成迷宫
{
	for(int i=0; i<Y; i++)	//初始化迷宫：内部为墙体；外围为通路，当做屏障
	{
		mg[0][i]=0;
		mg[X-1][i]=0;
	}
	for(int i=1; i<X-1; i++)
		for(int j=0; j<Y; j++)
		{
			if(j==0||j==Y-1)
				mg[i][j]=0;
			else
				mg[i][j]=1;
		}
	//分别对应着上下左右方向
	int dRow[] = {1, 0, -1, 0};
	int dCol[] = {0, -1, 0, 1};
	vector<int> QX,QY;	//用于存储墙体坐标
	QX.push_back(start_row);	//从起点开始
	QY.push_back(start_col);
	while(QX.size())	//拆墙
	{
		srand((unsigned int)(time(NULL)));	//根据当前时间，生成一个随机数种子
		int index=rand()%(QX.size());	//随机生成一个坐标，选取一堵墙
		int row=QX[index];
		int col=QY[index];
		int flag=0;		//记录该墙四周通路个数
		int r,c;
		for(int i=0; i<4; i++)
		{
			r=row+dRow[i];
			c=col+dCol[i];
			if(mg[r][c]==0)
				flag++;
		}
		if(flag<=1)		//当该墙体四周通路有一条或没有时，则该墙改为道路
		{
			mg[row][col]=0;
			for(int i=0; i<4; i++)
			{
				r=row+dRow[i];
				c=col+dCol[i];
				if(mg[r][c]==1)		//将该墙四周的墙加入队列
				{
					QX.push_back(r);
					QY.push_back(c);
				}
			}
		}
		//将当前墙移除队列
		QX.erase(QX.begin()+index);
		QY.erase(QY.begin()+index);
	}
}
 
void play_mg()
{
	//分别对应着上下左右方向
	int dRow[] = {0, 1, 0, -1};
	int dCol[] = {1, 0, -1, 0};
	box start;		//起始位置
	start.row=start_row;
	start.col=start_col;
	path.push(start);
	while(!path.empty())
	{
		box temp;
		bool flag=false;	//判断该坐标是否有通路
		int row = path.top().row;
		int col = path.top().col;
		mg[row][col]=1;		//该坐标已经过,设置为墙
		for(int i=0; i<4; i++) 		//向四个位置进行试探,方向：右1 下2 左3 上4
		{
			int r=row+dRow[i];
			int c=col+dCol[i];
			if(mg[r][c]==0)
			{
				temp.row=r;
				temp.col=c;
				temp.dir=i+1;
				path.push(temp);
				flag=true;
				break;
			}
		}
		if(row==X-3&&col==Y-3)		//到达终点
			break;
		mglx[row][col]=temp.dir+1;		//该坐标已经过,右2 下3 左4 上5
		if(!flag)		//若该坐标点无通路，则回溯
		{
			box t=path.top();
			mglx[t.row][t.col]=6;		//回溯后要把该坐标设为不可走路线
			path.pop();
		}
		HideCursor();
		gotoxy(0,0);
		Sleep(speed);		//设置速度
		show_mg();
	}
}
 
void show_path()	//展示坐标路线
{
	if(path.empty())
	{
		cout<<"此迷宫无解!"<<endl;
		return;
	}
	box temp[100];
	int length=0;
	while(!path.empty())
	{
		temp[length]=path.top();
		length++;
		path.pop();
	}
	cout<<endl<<endl<<"该通路的坐标路线为："<<endl;
	cout<<"起点=>";
	for(int i=length-1; i>=0; i--)
		cout<<"("<<temp[i].row-1<<","<<temp[i].col-1<<","<<temp[i-1].dir<<")=>";
	cout<<"终点"<<endl<<endl;
}
 
void show_mg()		//展示迷宫路线
{
	for(int i=0; i<X; i++)
	{
		for(int j=0; j<Y; j++)
		{
			//墙■路  右2→ 下3↓ 左4← 上5↑ 错×
			if(i==start_row&&j==start_col)
				cout<<"☆";
			else if(i==X-3&&j==Y-3)
				cout<<"★";
			else if(mglx[i][j]==1)
				cout<<"■";
			else if(mglx[i][j]==2)
			{
				cout_green();
				cout<<"→";
				recover();
			}
			else if(mglx[i][j]==3)
			{
				cout_green();
				cout<<"↓";
				recover();
			}
			else if(mglx[i][j]==4)
			{
				cout_green();
				cout<<"←";
				recover();
			}
			else if(mglx[i][j]==5)
			{
				cout_green();
				cout<<"↑";
				recover();
			}
			else if(mglx[i][j]==6)
			{
				cout_red();
				cout<<"×";
				recover();
			}
			else
				cout<<"  ";
		}
		cout<<endl;
	}
}
 
void copy_mg()		//复制迷宫
{
	for(int i=0; i<X; i++)
	{
		for(int j=0; j<Y; j++)
			mglx[i][j]=mg[i][j];
	}
}
 
void cout_green()	//绿色
{
	SetConsoleTextAttribute(hout, 2);
}
void cout_red()		//红色
{
	SetConsoleTextAttribute(hout, 4);
}
void recover()		//白色
{
	SetConsoleTextAttribute(hout, 1|2|4);
}
void gotoxy(int x,int y)	//将光标移动到（x,y）位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    //获取标准输出设备句柄
	COORD pos= {x,y};     //坐标位置
	SetConsoleCursorPosition(handle,pos);   //设置控制台光标位置
}
void HideCursor()	//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info= {1,0}; 	//0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
