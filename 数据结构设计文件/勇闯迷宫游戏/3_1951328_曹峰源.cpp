#include <iostream>
using namespace std;
#define exit_row 5
#define exit_col 5
#define maze_row 7
#define maze_col 7
bool isfind = 0;
struct point//������¼�����Ϣ
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
	void insert(int x, int y);//���ݴ�������
	void del(int x, int y);//��<x,y>�Ժ��������е�����ȫ��ɾ��
	void print();//�������е�Ԫ�ش�ӡ����
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

struct Maze//����Maze�ṹ���������Թ�����
{
	char map[maze_row][maze_col];
	void print()
	{
		cout << "�Թ���ͼ"<<endl;
		for (int i=0;i<maze_row;i++)
		{
			cout << "\t" << i << "��";
		}
		cout << endl;
		for (int i=0;i<maze_row;i++)
		{
			cout << i << "��"<<"\t";
			for (int j=0;j<maze_col;j++)
			{
				cout << map[i][j]<<"\t";
			}
			cout << endl;
		}
		cout << endl;
	}
};
void Mazeget(Maze* maze)//���Թ���ͼ�����ȥ
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
bool isexit(point cur)//�ж��Ƿ�Ϊ����
{
	if (cur.row == exit_row && cur.col == exit_col)
	{
		return true;
	}
	else return false;
}
bool stay(Maze* maze, point cur)//�жϸõ�cur�Ƿ�������
{
	if (cur.row < 0 || cur.row >= maze_row || cur.col < 0 || cur.col >= maze_col)
	{
		return 0;
	}
	if (maze->map[cur.row][cur.col] == '*')
	{
		//˵����·������δ�߹���·��˵���������
		return 1;
	}
	else
	{
		return 0;
	}
}
void findpath(Maze* maze, point cur, point entry, linklist& s)//Ѱ��·��
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
	if (isexit(cur) == 1)//�Ƿ�Ϊ���ڣ��ǵĻ�Ѱ���Թ��������
	{
		cout << "�ҵ�һ������" << endl << endl;
		cout << "�Թ�·��" << endl << endl;
		s.print();
		isfind = 1;
		return;
	}
	//���ĸ�������еݹ�
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
		int count = 0;//�����ͼ��û��û���߹��ĵ�ʱ��˵��û������������յ��·��
		for (int i = 0; i < maze_row; i++)
		{
			for (int j = 0; j < maze_col; j++)
			{
				if (maze->map[i][j] == '*') count++;
			}
		}
		if (count == 0)
		{
			cout << "û������������յ��·��" << endl;
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