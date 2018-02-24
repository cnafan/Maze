// �Թ����д.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<stack>
#include<random>
#include<Windows.h>
#include<exception>
#include <iomanip>//�Ҷ������
#include<regex>//�����ж������ַ����Ƿ�ȫΪ����

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
	migong(void)//�Թ���ʼ��
	{
		chang=10;
		kuan=10;
		//�����Թ�����
		arr=new int*[chang+2];
		for(int t=0;t<chang+2;t++)
			arr[t]=new int[chang+2];
		//��������Թ�
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
	migong(int a,int b):chang(a),kuan(b)//�Թ���ʼ��
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
		//1��ʾǽ 0��ʾͨ·

	}
	node getnext(node cur,int);
	int get(node,node);
	void display(int);
};
node migong::getnext(node c,int d)//��һ����
{
	node dir[4]={{0,1}, {1,0}, {0,-1}, {-1,0}};
	c.x+=dir[d].x;
	c.y+=dir[d].y;
	return c;
}
void migong::display(int s)
{
	if(s==0)//��ͨ·
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
	else//��ͨ·
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

int migong::get(node start,node end)//���Թ�·��
{
	//��� ���ڲ�ͨ
	if(arr[1][1]==1||arr[end.x][end.y]==1)
	{
		cout<<"��·��"<<endl;
		return 0;
	}
	stack <node> s;
	node curpos;
	curpos=start;
	int curstep=1;
	do{
		if(arr[curpos.x][curpos.y]==0)//��ͨ·
		{
			arr[curpos.x][curpos.y]=curstep;//�㼣
			curpos.direction=0;//����
			s.push(curpos);
			curstep++;
			if(curpos.x==end.x&&curpos.y==end.y)
			{
				cout<<"�ҵ��Թ�·����"<<endl;
				return 1;
			}
			curpos=getnext(curpos,curpos.direction);
		}
		else//����ͨ·
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
	cout<<"�޷������յ�"<<endl;
	return 2;
}
void menu()
{
	cout<<"---------------------------------------------------------\n";
	cout<<"1.����Ĭ�ϴ�С�Թ�,������·��\n2.�Զ����С�Թ�,������·��\n3.����\n4.�˳�\n";
}
class NumberParseException
{};
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "---------------------------------------------------------\n";
	cout << "'*'��ʾǽ,'.'��ʾͨ·,'_'��ʾ���߹���·\n";
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
			std::cout << "�����Թ��ĳ�(1-20)��";
			cin >> str_chang;
			std::regex rx("[0-9]+");
			bool bl_chang = std::regex_match(str_chang.begin(), str_chang.end(), rx);//����Ƿ�Ϊƥ������
			std::cout << "�����Թ��Ŀ�(1-20)��";
			cin >> str_kuan;
			std::regex rxx("[0-9]+");
			bool bl_kuan = std::regex_match(str_kuan.begin(), str_kuan.end(), rxx);//����Ƿ�Ϊƥ������
			if (bl_chang && bl_kuan)
			{
				chang = int(atof(str_chang.c_str()));//�ַ���ת��Ϊ����
				kuan = int(atof(str_kuan.c_str()));//�ַ���ת��Ϊ����
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
					cout << "----��������,����������\n";

			}
			else
				cout << "----��������\n";
			menu();
			break;
		}
		case 3:
			cout << "����:Johnny\n";
			break;
		case 4:
			exit(1);
			break;
		default:
			cout << "��������,��������\n";
			break;
		}

	}

	return 0;
}

