#include <iostream>
using namespace std;
class graph
{
private:
	int numofvertex;//图中点的个数
	int numofedge;//图中边的个数
	char* avertex;//存放点的数组
	int** aedge;//存放边的二维数组
	int* primedge;//存放最小生成树边的数据
	char* primu;//存放最小生成树起点
	char* primv;//存放最小生成树终点
public:
	graph() { numofvertex = 0; numofedge = 0; }
	~graph()
	{
		delete[]avertex; //释放点数组
		for (int i = 0; i < numofvertex; i++)//释放边数组
		{
			delete[]aedge[i];
		}
		delete[]aedge;
	}
	int getnumofvertex() { return numofvertex; }//得到点的个数
	int getnumofedge() { return numofedge; }//得到边的个数
	void create(int n);//用于开辟一个大小为n的数组来存储点的数据
	void insertedge(char u, char v, int cost);//向图中插入边
	void prim(char u);//prim算法实现最小生成树
	void printprim();//将最小生成树打印出来
};
void graph::create(int n)
{
	numofvertex = n;
	aedge = new int* [numofvertex];
	for (int i = 0; i < numofvertex; i++)
	{
		aedge[i] = new int[numofvertex];
	}
	char u;
	avertex = new char[numofvertex];
	for (int i = 0; i < numofvertex; i++)
	{
		avertex[i] = '0';
	}
	for (int i = 0; i < numofvertex; i++)
	{
		for (int j = 0; j < numofvertex; j++)
		{
			aedge[i][j] = 0;
		}
	}
	for (int i = 0; i < numofvertex; i++)
	{
		cin >> u;
		int j = 0;
		for (j = 0; j < numofvertex; j++)
		{
			if (avertex[j] == '0') break;
			if (avertex[j] == u) break;
		}
		if (avertex[j] == '0')
		{
			avertex[i] = u;
		}
		else
		{
			cout << "输入的点已经存在" << endl;
			i--;
		}
	}
}
void graph::insertedge(char u, char v, int cost)
{
	int x = -1, y = -1;
	for (int i = 0; i < numofvertex; i++)
	{
		if (avertex[i] == u) { x = i; break; }
	}
	if (x == -1)
	{
		cout << "该图中没有点"<<u << endl;
		return;
	}
	for (int i = 0; i < numofvertex; i++)
	{
		if (avertex[i] == v) { y = i; break; }
	}
	if (y == -1)
	{
		cout << "该图中没有点"<<v << endl;
		return;
	}
	if (cost<=0)
	{
		cout << "该边的权值违法！";
		return;
	}
	aedge[x][y] = cost;
	aedge[y][x] = cost;
	numofedge++;
}
void graph::prim(char u)
{
	int num1 = getnumofedge();//num1等于图中边的个数
	int num2 = getnumofvertex();//num2等于图中点的个数
	primedge = new int[num2 - 1];//primedge用于存放最小生成树边的数据
	primu = new char[num2 - 1];//用于存放最小生成树起点的数据
	primv = new char[num2 - 1];//用于存放最小生成树终点的数据
	int* p = new int[num1];//开辟一个大小为边个数的数组
	int* q = new int[num2];//开辟一个大小为点个数的数组
	int i = 0, j = 0, k = 0;
	for (i = 0; i < numofvertex; i++)
	{
		if (avertex[i] == u)break;
	}
	if (i == numofvertex)
	{
		cout << "输入的起始顶点有误！" << endl;
		return;
	}
	i = 0;
	for (k = 0; k < num1; k++)//将p数组中每个值都先赋为0
	{
		p[k] = 0;
	}
	k = 0;
	for (i = 0; i < numofvertex; i++)//现将起点u的所有边进入p数组
	{
		if (avertex[i] == u) break;
	}
	for (j = i; j < numofvertex; j++)
	{
		if (aedge[i][j] != 0)
		{
			p[k] = aedge[i][j]; k++;
		}
	}
	k = 0;
	for (i = 0; i < numofvertex - 1; i++)
	{
		int min = 0, count = 0;
		j = 0;
		while (j < num1)//统计现在p数组中有多少条边
		{
			if (p[j] == 0) break;
			j++;
		}
		count = j;//count为当前p数组中有多少边
		for (j = 0; j < count; j++)
		{
			if (p[min] > p[j]) { min = j; }
		}
		int mincost = p[min];//得到最小开销，将其交换到数组p中的靠后位置
		p[min] = p[count - 1];
		p[count - 1] = mincost;
		int m = 0, n = 0;
		for (m = 0; m < numofvertex; m++)//得到原边矩阵中的起点和终点的信息，如果起点和终点不满足prim算法，则忽略
		{
			for (n = m; n < numofvertex; n++)
			{
				if (aedge[m][n] == mincost)//在aedge数组中找到该最小值的位置
				{
					if (q[m] == 1 && q[n] == 1) { p[count - 1] = 0; i--; }//如果该最小值的两个点已经连通了，就将该边删掉，i--
					else//如果没有连通
					{
						p[count - 1] = 0;//先将该边删掉
						q[m] = 1; q[n] = 1;//两个点置为连通
						primedge[k] = mincost;//相关的生成树的值进入特定数组存储
						primu[k] = avertex[m]; primv[k] = avertex[n];
						k++;
						for (int s = n; s < numofvertex; s++)//将下一个点连通的边进入p数组
						{
							if (aedge[n][s] != 0) { p[count - 1] = aedge[n][s]; count++; }
						}
					}
				}
			}
		}
	}
	cout << "生成prim最小生成树！" << endl << endl;
}
void graph::printprim()
{
	for (int i = 0; i < numofvertex - 1; i++)
	{
		cout << primu[i] << "-<" << primedge[i] << ">->" << primv[i] << "  ";
	}
}

int main()
{
	cout << "**          电网造价系统          **" << endl;
	cout << "====================================" << endl;
	cout << "**        A--创建电网顶点         **" << endl;
	cout << "**        B--添加电网的边         **" << endl;
	cout << "**        C--构造最小生成树       **" << endl;
	cout << "**        D--显示最小生成树       **" << endl;
	cout << "**        E--退出  程序           **" << endl;
	cout << "====================================" << endl;
	graph g;
	cout << "请选择操作：";
	char order;
	while (cin >> order)
	{
		switch (order)
		{
		case 'A':
		{
			cout << "请输入顶点的个数：";
			int N;
			while (cin >> N)
			{
				if (N > 0) break;
				else cout << "输入的点的个数不符合要求";
			}
			cout << "请依次输入各顶点的名称：";
			g.create(N);
			cout << endl;
			break;
		}
		case 'B':
		{
			while (1)
			{
				cout << "请输入两个顶点及边：";
				char u, v;
				int cost;
				cin >> u >> v >> cost;
				if (u == '?') break;
				g.insertedge(u, v, cost);
			}
			cout << endl;
			break;
		}
		case 'C':
		{
			cout << "请输入起始顶点：";
			char u;
			cin >> u;
			g.prim(u);
			break;
		}
		case 'D':
		{
			cout << "最小生成树的顶点及边为：" << endl;
			g.printprim();
			cout << endl << endl;
			break;
		}
		case 'E':
		{
			system("pause");
			exit(0);
			break;
		}
		default:cout << "输入的操作码有误" << endl; break;
		}
		cout << "请选择操作：";
	}
	return 0;
}