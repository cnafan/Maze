// 迷宫随便写.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<stack>
#include<random>
#include<Windows.h>
#include<exception>
#include <iomanip>//右对齐输出
#include<regex>//正则判断输入字符串是否全为数字

using namespace std;
using std::cout;

#define random(x)(rand()%x)
const int maxx=50;
const int maxy=50;
struct node
{
	int x;
	int y;
	int direction;
};
class migong
{
	int map[maxx][maxy];
	int **arr;
	int chang;
	int kuan;
public:
	migong(void)//迷宫初始化
	{
		chang=10;
		kuan=10;
		//构建迷宫数组
		arr=new int*[chang+2];
		for(int t=0;t<chang+2;t++)
			arr[t]=new int[chang+2];
		//构建随机迷宫
		for(int i=0;i<chang+2;i++)
		{
			for(int j=0;j<chang+2;j++)
			{
				if(i==0||j==0||i==chang+1||j==chang+1)
				{
					arr[i][j]=1;
					continue;
				}
				int x=random(1000)%6;
				if(x==1||x==2||x==3||x==4||x==5)
					arr[i][j]=0;
				else
					arr[i][j]=1;
			}
		}
	}
	migong(int a,int b):chang(a),kuan(b)//迷宫初始化
	{
		arr=new int*[chang+2];
		for(int t=0;t<chang+2;t++)
			arr[t]=new int[kuan+2];
		for(int i=0;i<chang+2;i++)
		{
			for(int j=0;j<kuan+2;j++)
			{
				if(i==0||j==0||i==chang+1||j==kuan+1)
				{
					arr[i][j]=1;
					continue;
				}
				int x=random(1234)%4;
				if(x==1||x==2||x==3)
					arr[i][j]=0;
				else
					arr[i][j]=1;
			}
		}
		//1表示墙 0表示通路

	}
	node getnext(node cur,int);
	int get(node,node);
	void display(int);
};
node migong::getnext(node c,int d)//下一方向
{
	node dir[4]={{0,1}, {1,0}, {0,-1}, {-1,0}};
	c.x+=dir[d].x;
	c.y+=dir[d].y;
	return c;
}
void migong::display(int s)
{
	if(s==0)//无通路
	{		
		for(int t=0;t<chang+2;t++)
		{
			for(int tt=0;tt<kuan+2;tt++)
			{
				if(arr[t][tt]==1)
					cout<<setw(3)<<"*";				
				else if(arr[t][tt]==0)
					std::cout<<setw(3)<<".";

				else
					std::cout<<setw(3)<<arr[t][tt];
			}
			std::cout<<endl;
		}
	}
	else//有通路
	{
		for(int t=0;t<chang+2;t++)
		{
			for(int tt=0;tt<kuan+2;tt++)
			{
				if(t==1&&tt==1)
					std::cout<<setw(3)<<"1";
				else
				{
					if(arr[t][tt]==1)
						std::cout<<setw(3)<<"*";
					else if(arr[t][tt]==0)
						std::cout<<setw(3)<<".";

					else if(arr[t][tt]==-1)
						std::cout<<setw(3)<<"-";
					else
						std::cout<<setw(3)<<arr[t][tt];
				}
			}
			std::cout<<endl;
		}
	}
}

int migong::get(node start,node end)//求迷宫路径
{
	//入口 出口不通
	if(arr[1][1]==1||arr[end.x][end.y]==1)
	{
		cout<<"无路径"<<endl;
		return 0;
	}
	stack <node> s;
	node curpos;
	curpos=start;
	int curstep=1;
	do{
		if(arr[curpos.x][curpos.y]==0)//是通路
		{
			arr[curpos.x][curpos.y]=curstep;//足迹
			curpos.direction=0;//方向
			s.push(curpos);
			curstep++;
			if(curpos.x==end.x&&curpos.y==end.y)
			{
				cout<<"找到迷宫路径："<<endl;
				return 1;
			}
			curpos=getnext(curpos,curpos.direction);
		}
		else//不是通路
		{
			if(!s.empty())
			{
				curpos=s.top();
				s.pop();
				curstep--;
				while(curpos.direction==3&&!s.empty())
				{
					arr[curpos.x][curpos.y]=-1;
					curpos=s.top();
					s.pop();
					curstep--;
				}
				if(curpos.direction<3)
				{
					curpos.direction++;
					s.push(curpos);
					curstep++;
					curpos=getnext(curpos,curpos.direction);
				}
			}
		}
	}while (!s.empty());
	cout<<"无法到达终点"<<endl;
	return 2;
}
void menu()
{
	cout<<"---------------------------------------------------------\n";
	cout<<"1.生成默认大小迷宫,并生成路线\n2.自定义大小迷宫,并生成路径\n3.帮助\n4.退出\n";
}
class NumberParseException
{};
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "---------------------------------------------------------\n";
	cout << "'*'表示墙,'.'表示通路,'_'表示已走过的路\n";
	//cout<<"---------------------------------------------------------\n";
	int chang, kuan;
	string str_chang;
	string str_kuan;
	int n;
	menu();
	while (cin >> n)
	{
		switch (n)
		{
		case 1:
		{
			migong mi = migong();
			mi.display(0);
			node start;
			start.x = 1;
			start.y = 1;
			start.direction = 0;
			node end;
			end.x = 10;
			end.y = 10;
			end.direction = 0;
			int s = mi.get(start, end);
			if (s != 0)
				mi.display(s);
			menu();
			break;
		}
		case 2:
		{
			std::cout << "输入迷宫的长(1-20)：";
			cin >> str_chang;
			std::regex rx("[0-9]+");
			bool bl_chang = std::regex_match(str_chang.begin(), str_chang.end(), rx);//检测是否为匹配数字
			std::cout << "输入迷宫的宽(1-20)：";
			cin >> str_kuan;
			std::regex rxx("[0-9]+");
			bool bl_kuan = std::regex_match(str_kuan.begin(), str_kuan.end(), rxx);//检测是否为匹配数字
			if (bl_chang && bl_kuan)
			{
				chang = int(atof(str_chang.c_str()));//字符串转换为数字
				kuan = int(atof(str_kuan.c_str()));//字符串转换为数字
				if ((chang >= 1 && chang <= 20) && (kuan >= 1 && kuan <= 20))
				{
					migong mi = migong(chang, kuan);
					mi.display(0);
					node start;
					start.x = 1;
					start.y = 1;
					start.direction = 0;
					node end;
					end.x = chang;
					end.y = kuan;
					end.direction = 0;
					int s = mi.get(start, end);
					if (s != 0)
						mi.display(s);
				}
				else
					cout << "----输入有误,不满足条件\n";

			}
			else
				cout << "----输入有误\n";
			menu();
			break;
		}
		case 3:
			cout << "作者:Johnny\n";
			break;
		case 4:
			exit(1);
			break;
		default:
			cout << "输入有误,重新输入\n";
			break;
		}

	}

	return 0;
}

