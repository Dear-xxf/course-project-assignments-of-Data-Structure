#include <iostream>
using namespace std;
#define exit_row 5
#define exit_col 5
#define maze_row 7
#define maze_col 7
bool isfind = 0;
struct point//用来记录点的信息
{
	int row;
	int col;
	point* next = NULL;
};
class linklist
{
private:
	point* first;
	point* current;
public:
	linklist()
	{
		first = new point;
		current = first;
	}
	~linklist()
	{
		current = first->next;
		delete first;
		while (current != NULL)
		{
			point* p = current;
			current = current->next;
			delete p;
		}
	}
	void insert(int x, int y);//数据存入链表
	void del(int x, int y);//将<x,y>以后在链表中的数据全部删除
	void print();//将链表中的元素打印出来
};
void linklist::insert(int x, int y)
{
	current = first;
	while (current->next != NULL)
	{
		current = current->next;
	}
	point* p = new point;
	p->row = x;
	p->col = y;
	current->next = p;
}
void linklist::del(int x, int y)
{
	current = first->next;
	while (!(current->row == x&&current->col == y))
	{
		current = current->next;
	}
	point* p = current->next;
	current->next = NULL;
	while (p != NULL)
	{
		point*q=p;
		p = p->next;
		delete q;
	}
}
void linklist::print()
{
	current = first->next;
	cout << "<" << current->row << "," << current->col << ">";
	current = current->next;
	while (current!=NULL)
	{
		cout <<" ---> <" << current->row << "," << current->col <<">";
		current = current->next;
	}
}

struct Maze//创建Maze结构体来保存迷宫数据
{
	char map[maze_row][maze_col];
	void print()
	{
		cout << "迷宫地图"<<endl;
		for (int i=0;i<maze_row;i++)
		{
			cout << "\t" << i << "列";
		}
		cout << endl;
		for (int i=0;i<maze_row;i++)
		{
			cout << i << "行"<<"\t";
			for (int j=0;j<maze_col;j++)
			{
				cout << map[i][j]<<"\t";
			}
			cout << endl;
		}
		cout << endl;
	}
};
void Mazeget(Maze* maze)//将迷宫地图输入进去
{
	if (maze==NULL)
	{
		return;
	}
	char temp[maze_row][maze_col] =
	{
		{'#','#','#','#','#','#','#'},
		{'#','*','#','*','*','*','#'},
		{'#','*','#','*','#','#','#'},
		{'#','*','*','*','#','*','#'},
		{'#','*','#','*','*','*','#'},
		{'#','*','#','*','#','*','#'},
		{'#','#','#','#','#','#','#'}
	};
	int row = 0;
	for (int row=0; row<maze_row;row++)
	{
		for (int col=0;col<maze_col;col++)
		{
			maze->map[row][col] = temp[row][col];
		}
	}
}
bool isexit(point cur)//判断是否为出口
{
	if (cur.row == exit_row && cur.col == exit_col)
	{
		return true;
	}
	else return false;
}
bool stay(Maze* maze, point cur)//判断该点cur是否可以落脚
{
	if (cur.row < 0 || cur.row >= maze_row || cur.col < 0 || cur.col >= maze_col)
	{
		return 0;
	}
	if (maze->map[cur.row][cur.col] == '*')
	{
		//说明是路，且是未走过的路，说明可以落脚
		return 1;
	}
	else
	{
		return 0;
	}
}
void findpath(Maze* maze, point cur, point entry, linklist& s)//寻找路径
{
	if (maze == NULL)
	{
		return;
	}
	if (stay(maze, cur) == 0)
	{
		return;
	}
	maze->map[cur.row][cur.col] = '0';
	s.insert(cur.row, cur.col);
	if (isexit(cur) == 1)//是否为出口，是的话寻找迷宫出口完成
	{
		cout << "找到一个出口" << endl << endl;
		cout << "迷宫路径" << endl << endl;
		s.print();
		isfind = 1;
		return;
	}
	//向四个方向进行递归
	point up = cur;
	up.row -= 1;
	findpath(maze, up, entry,s);
	s.del(cur.row,cur.col);
	point right = cur;
	right.col += 1;
	findpath(maze, right, entry,s);
	s.del(cur.row, cur.col);
	point down = cur;
	down.row += 1;
	findpath(maze, down, entry,s);
	s.del(cur.row, cur.col);
	point left = cur;
	left.col -= 1;
	findpath(maze, left, entry,s);
	s.del(cur.row, cur.col);
}
void path(Maze* maze, point entry,linklist& s)
{
	if (maze == NULL) return;
	findpath(maze, entry, entry,s);
	if (isfind == 0)
	{
		int count = 0;//如果地图中没有没有走过的点时，说明没有连接起点与终点的路径
		for (int i = 0; i < maze_row; i++)
		{
			for (int j = 0; j < maze_col; j++)
			{
				if (maze->map[i][j] == '*') count++;
			}
		}
		if (count == 0)
		{
			cout << "没有连接起点与终点的路径" << endl;
			return;
		}
	}
}
int main()
{
	Maze* maze;
	maze = new Maze;
	linklist s;
	Mazeget(maze);
	maze->print();
	point entry = { 1,1 };
	path(maze,entry,s);
	cout << endl;
	system("pause");
	return 0;
}