#include<iostream>
#include<stack>//ջ 
#include<vector>//���� 
#include<time.h>//��ȡ��ǰʱ�� 
#include <Windows.h>//��ɫ�ı䣬ʱͣ 
#include<stdlib.h>//���� 
#include <cstdlib>
 
using namespace std;
 
#define X 13//�Թ���С 
#define Y 12
#define start_row 2//���
#define start_col 2
#define speed 30//�ٶ� 
 
struct box
{
	int row,col;		//��������
	int dir;		//������1 ��2 ��3 ��4
};
 
int mg[X][Y];	//��ʼ�Թ�
int mglx[X][Y];	//չʾ�Թ�·�ߣ���ԭ�Թ��ᱻ����
 
stack<box> path;	//·�ߣ����������뷽����Ϣ
 
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);	//��ɫ
 
void create_mg();	//��������Թ�
void copy_mg();		//�����Թ�
void play_mg();		//����Թ�·�����
void show_path();	//����·��չʾ 
void show_mg();		//�Թ�·��չʾ
void cout_green();	//��ӡ��ɫ
void cout_red();	//��ӡ��ɫ
void recover();		//�ָ���ɫ
 
void gotoxy(int row,int col);//������ƶ�����row,y��λ��
void HideCursor();//���ع��
 
 
 
int main()
{
	while(true)
	{
		system("cls");	//����
		char choice;
		cout<<endl<<endl<<"*****\t��ӭ�����Թ��������\t*******"<<endl<<endl<<endl;
		cout<<"\t[1] ��������Թ�."<<endl;
		cout<<"\t[2] �����Թ�."<<endl;
		cout<<"\t[3] �˳���Ϸ."<<endl<<endl;
		cout<<"\t\t������� "<<X-4<<" �� "<<Y-4<<" ���Թ�"<<endl<<endl;
		cout<<"****************************************"<<endl<<endl;
		cout<<"���������ѡ��";
		cin>>choice;
		if(choice=='1')
		{
			system("cls");
			while(true)
			{
				create_mg();
				if(mg[X-3][Y-3]==0)		//���յ���һ��ǽ�������������Թ�
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
			cout<<endl<<"**********\t�����Թ�\t************"<<endl;
		    const char* command = "maze_stack.exe";		//�����ⲿ�ļ�"maze_stack.cpp"	
		    int result = std::system(command);    // ִ������
			cout<<endl<<"****************************************"<<endl<<endl;
		}
		
		else if(choice=='3')
			return 0;
		else
			cout<<"��������ȷ��ѡ��!"<<endl;
		system("pause");
	}
}
 
void create_mg()	//��������Թ�
{
	for(int i=0; i<Y; i++)	//��ʼ���Թ����ڲ�Ϊǽ�壻��ΧΪͨ·����������
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
	//�ֱ��Ӧ���������ҷ���
	int dRow[] = {1, 0, -1, 0};
	int dCol[] = {0, -1, 0, 1};
	vector<int> QX,QY;	//���ڴ洢ǽ������
	QX.push_back(start_row);	//����㿪ʼ
	QY.push_back(start_col);
	while(QX.size())	//��ǽ
	{
		srand((unsigned int)(time(NULL)));	//���ݵ�ǰʱ�䣬����һ�����������
		int index=rand()%(QX.size());	//�������һ�����꣬ѡȡһ��ǽ
		int row=QX[index];
		int col=QY[index];
		int flag=0;		//��¼��ǽ����ͨ·����
		int r,c;
		for(int i=0; i<4; i++)
		{
			r=row+dRow[i];
			c=col+dCol[i];
			if(mg[r][c]==0)
				flag++;
		}
		if(flag<=1)		//����ǽ������ͨ·��һ����û��ʱ�����ǽ��Ϊ��·
		{
			mg[row][col]=0;
			for(int i=0; i<4; i++)
			{
				r=row+dRow[i];
				c=col+dCol[i];
				if(mg[r][c]==1)		//����ǽ���ܵ�ǽ�������
				{
					QX.push_back(r);
					QY.push_back(c);
				}
			}
		}
		//����ǰǽ�Ƴ�����
		QX.erase(QX.begin()+index);
		QY.erase(QY.begin()+index);
	}
}
 
void play_mg()
{
	//�ֱ��Ӧ���������ҷ���
	int dRow[] = {0, 1, 0, -1};
	int dCol[] = {1, 0, -1, 0};
	box start;		//��ʼλ��
	start.row=start_row;
	start.col=start_col;
	path.push(start);
	while(!path.empty())
	{
		box temp;
		bool flag=false;	//�жϸ������Ƿ���ͨ·
		int row = path.top().row;
		int col = path.top().col;
		mg[row][col]=1;		//�������Ѿ���,����Ϊǽ
		for(int i=0; i<4; i++) 		//���ĸ�λ�ý�����̽,������1 ��2 ��3 ��4
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
		if(row==X-3&&col==Y-3)		//�����յ�
			break;
		mglx[row][col]=temp.dir+1;		//�������Ѿ���,��2 ��3 ��4 ��5
		if(!flag)		//�����������ͨ·�������
		{
			box t=path.top();
			mglx[t.row][t.col]=6;		//���ݺ�Ҫ�Ѹ�������Ϊ������·��
			path.pop();
		}
		HideCursor();
		gotoxy(0,0);
		Sleep(speed);		//�����ٶ�
		show_mg();
	}
}
 
void show_path()	//չʾ����·��
{
	if(path.empty())
	{
		cout<<"���Թ��޽�!"<<endl;
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
	cout<<endl<<endl<<"��ͨ·������·��Ϊ��"<<endl;
	cout<<"���=>";
	for(int i=length-1; i>=0; i--)
		cout<<"("<<temp[i].row-1<<","<<temp[i].col-1<<","<<temp[i-1].dir<<")=>";
	cout<<"�յ�"<<endl<<endl;
}
 
void show_mg()		//չʾ�Թ�·��
{
	for(int i=0; i<X; i++)
	{
		for(int j=0; j<Y; j++)
		{
			//ǽ��·  ��2�� ��3�� ��4�� ��5�� ���
			if(i==start_row&&j==start_col)
				cout<<"��";
			else if(i==X-3&&j==Y-3)
				cout<<"��";
			else if(mglx[i][j]==1)
				cout<<"��";
			else if(mglx[i][j]==2)
			{
				cout_green();
				cout<<"��";
				recover();
			}
			else if(mglx[i][j]==3)
			{
				cout_green();
				cout<<"��";
				recover();
			}
			else if(mglx[i][j]==4)
			{
				cout_green();
				cout<<"��";
				recover();
			}
			else if(mglx[i][j]==5)
			{
				cout_green();
				cout<<"��";
				recover();
			}
			else if(mglx[i][j]==6)
			{
				cout_red();
				cout<<"��";
				recover();
			}
			else
				cout<<"  ";
		}
		cout<<endl;
	}
}
 
void copy_mg()		//�����Թ�
{
	for(int i=0; i<X; i++)
	{
		for(int j=0; j<Y; j++)
			mglx[i][j]=mg[i][j];
	}
}
 
void cout_green()	//��ɫ
{
	SetConsoleTextAttribute(hout, 2);
}
void cout_red()		//��ɫ
{
	SetConsoleTextAttribute(hout, 4);
}
void recover()		//��ɫ
{
	SetConsoleTextAttribute(hout, 1|2|4);
}
void gotoxy(int x,int y)	//������ƶ�����x,y��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    //��ȡ��׼����豸���
	COORD pos= {x,y};     //����λ��
	SetConsoleCursorPosition(handle,pos);   //���ÿ���̨���λ��
}
void HideCursor()	//���ع��
{
	CONSOLE_CURSOR_INFO cursor_info= {1,0}; 	//0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
