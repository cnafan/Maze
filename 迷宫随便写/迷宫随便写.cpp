// 迷宫随便写.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<stack>
#include <vector>
#include<random>
#include <iomanip>//右对齐输出
#include<regex>//正则判断输入字符串是否全为数字
#define MAXRANDOM 100000
#define MAXMAZESIZE 65
#define DEFAULTSIZE 10
#define MAXX 100
#define MAXY 100
#define random(x)(rand()%x)
using namespace std;

static int  difficulty = 6;

//x,y从1开始计数
struct node
{
	int x;
	int y;
	int direction;
};
class migong
{
	vector<node>v;
	int map[MAXX][MAXY];
	int **arr;
	int width;
	int height;
public:
	migong(void)//迷宫初始化
	{
		width = DEFAULTSIZE;
		height = DEFAULTSIZE;
		//构建迷宫数组
		arr = new int*[width + 2];
		for (int t = 0; t < width + 2; t++)
			arr[t] = new int[width + 2];
		//构建随机迷宫
		for (int i = 0; i < width + 2; i++)
		{
			for (int j = 0; j < width + 2; j++)
			{
				if (i == 0 || j == 0 || i == width + 1 || j == width + 1)
				{
					arr[i][j] = 1;
					continue;
				}
				int x = random(MAXRANDOM) % difficulty;
				if (x == 0)
					arr[i][j] = 1;
				else
					arr[i][j] = 0;
			}
		}
	}
	migong(int a, int b) :width(a), height(b)//迷宫初始化
	{
		arr = new int*[width + 2];
		for (int t = 0; t < width + 2; t++)
			arr[t] = new int[height + 2];
		for (int i = 0; i < width + 2; i++)
		{
			for (int j = 0; j < height + 2; j++)
			{
				if (i == 0 || j == 0 || i == width + 1 || j == height + 1)
				{
					arr[i][j] = 1;
					continue;
				}
				int x = random(MAXRANDOM) % difficulty;
				if (x == 0)
					arr[i][j] = 1;
				else
					arr[i][j] = 0;
			}
		}
		//1表示墙 0表示通路

	}
	node getnext(node cur, int);
	int get(node, node);
	void display(int);
	vector<node> getvector();
};

vector<node> migong::getvector() {
	return	v;
}
void setdifficulty(int);
node migong::getnext(node c, int d)//下一方向
{
	node dir[4] = { { 0,1 },{ 1,0 },{ 0,-1 } , {-1,0} };//右、下、左、上
	c.x += dir[d].x;
	c.y += dir[d].y;
	return c;
}
void migong::display(int s)
{
	switch (s)
	{
	case 0:
		for (int t = 0; t < width + 2; t++)
		{
			for (int tt = 0; tt < height + 2; tt++)
			{
				switch (arr[t][tt])
				{
				case 1:
					cout << setw(3) << "■";
					break;
				case 0:
					std::cout << setw(3) << ".";
					break;
				default:
					break;

				}
			}
			std::cout << endl;
		}
		break;
	default:
		for (int t = 0; t < width + 2; t++)
		{
			for (int tt = 0; tt < height + 2; tt++)
			{

				if (t == 1 && tt == 1)
					std::cout << setw(3) << "1";
				else
				{

					if (arr[t][tt] == 1)
						std::cout << setw(3) << "■";
					else if (arr[t][tt] == 0)
						std::cout << setw(3) << ".";

					else if (arr[t][tt] == -1)
						std::cout << setw(3) << "-";
					else
						std::cout << setw(3) << arr[t][tt];
				}
			}
			std::cout << endl;
		}
		break;
	}
}
/***
* 求迷宫路径
* @param start,end
* @return result
*/
int migong::get(node start, node end)
{
	//入口 出口不通
	if (arr[1][1] == 1 || arr[end.x][end.y] == 1)
	{
		cout << "无路径" << endl;
		return 0;
	}
	stack <node> s;
	node curpos;
	curpos = start;
	int curstep = 1;
	do {
		if (arr[curpos.x][curpos.y] == 0)//是通路
		{
			arr[curpos.x][curpos.y] = curstep++;//足迹
			curpos.direction = 0;//方向
			s.push(curpos);
			v.push_back(curpos);
			if (curpos.x == end.x&&curpos.y == end.y)
			{
				cout << "找到迷宫路径：" << endl;
				return 1;
			}
			curpos = getnext(curpos, curpos.direction);
		}
		else//不是通路
		{
			if (!s.empty())
			{
				curpos = s.top();
				s.pop();
				curstep--;
				while (curpos.direction == 3 && !s.empty())
				{
					arr[curpos.x][curpos.y] = -1;
					curpos = s.top();
					s.pop();
					curstep--;
				}
				if (curpos.direction < 3)
				{
					curpos.direction++;
					s.push(curpos);
					v.push_back(curpos);
					curstep++;
					curpos = getnext(curpos, curpos.direction);
				}
			}
		}
	} while (!s.empty());
	cout << "无法到达终点" << endl;
	return 2;
}
void setdifficulty(int n)
{
	difficulty = n;
}
void menu()
{
	cout << "---------------------------------------------------------\n";
	cout << "'■'表示墙,'.'表示通路,'_'表示已走过的路\n";
	cout << "1.生成" << DEFAULTSIZE << "*" << DEFAULTSIZE << "迷宫\n2.自定义大小迷宫\n3.修改难度系数\n4.退出\n";
	cout << "---------------------------------------------------------\n";
}
int _tmain(int argc, _TCHAR* argv[])
{
	int width, height;
	string str_width;
	string str_height;
	int n;
	menu();
	while (cin >> n)
	{
		system("cls");//清屏
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
			end.x = DEFAULTSIZE;
			end.y = DEFAULTSIZE;
			end.direction = 0;
			int s = mi.get(start, end);
			if (s != 0)
				mi.display(s);
			menu();
			break;
		}
		case 2:
		{
			std::cout << "输入迷宫的长(1-" << MAXMAZESIZE << "):";
			cin >> str_width;
			std::regex rx("[0-9]+");
			bool bl_width = std::regex_match(str_width.begin(), str_width.end(), rx);//检测是否为匹配数字
			std::cout << "输入迷宫的宽(1-" << MAXMAZESIZE << "):";
			cin >> str_height;
			bool bl_height = std::regex_match(str_height.begin(), str_height.end(), rx);//检测是否为匹配数字
			if (bl_width && bl_height)
			{
				width = int(atof(str_width.c_str()));//字符串转换为数字
				height = int(atof(str_height.c_str()));//字符串转换为数字
				if ((width >= 1 && width <= MAXMAZESIZE) && (height >= 1 && height <= MAXMAZESIZE))
				{
					migong mi = migong(width, height);
					mi.display(0);
					node start;
					start.x = 1;
					start.y = 1;
					start.direction = 0;
					node end;
					end.x = width;
					end.y = height;
					end.direction = 0;
					int s = mi.get(start, end);
					if (s != 0)
						mi.display(s);
				}
				else
					cout << "输入有误,长和宽不满足条件\n";
			}
			else
				cout << "长和宽必须为数字\n";
			menu();
			break;
			/*vector<node>::iterator it;
			for (it = mi.getvector().begin()+1; it != mi.getvector().end(); it++) {
				cout << it->x<<"-"<<it->y << " ";
			}*/
		}
		case 3:
		{
			string diff = "0";
			cout << "请输入难度系数(1-10)(难度依次递减):";
			std::regex rx("[0-9]+");
			cin >> diff;
			bool diff_re = std::regex_match(diff.begin(), diff.end(), rx);//检测是否为匹配数字
			if (diff_re)
				setdifficulty((int(atof(diff.c_str()))) % 11);
			else
				cout << "输入有误,重新输入(1-10)\n";
			menu();
			break;

		}
		case 4:
			exit(1);
			break;
		default:
			cout << "输入有误,重新输入(1-3)\n";
			menu();
			break;
		}
	}
	return 0;
}

