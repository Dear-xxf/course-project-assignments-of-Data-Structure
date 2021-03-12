#include <istream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class node//存储课程信息的点类
{
	friend class graph;//声明为图的友元类
private:
	string index;//课程的编号
	string name;//课程的名称
	int time = 0;//课程的课时数
	int term = 0;//课程应在的学期
	int in = 0;//该课程的入度
	int take = 0;//该课程是否已经被安排，用于后续拓扑排序
public:
	node() {}//构造函数
	~node() {}//析构函数
};

void String_Split(string s, string delim, vector<string>& ans)//用于将从文件中读出的string类分割存到vector中
{
	string::size_type pos_1, pos_2 = 0;
	while (pos_2 != s.npos) {
		pos_1 = s.find_first_not_of(delim, pos_2);
		if (pos_1 == s.npos) break;
		pos_2 = s.find_first_of(delim, pos_1);
		ans.push_back(s.substr(pos_1, pos_2 - pos_1));
	}
}

class graph
{
private:
	vector<node> nodetable;//课程信息的存储容器
	int** arrey;//边数组存储入边情况
	int num;//输入的文件中课程数
	string classtable[8][5][10];//存储具体课表
	int classjudge[8][5][4];//具体课表时间是否被占用，用于后续判断
	vector<vector<node>> t;//存储每学期的课程
public:
	graph()
	{
		num = 0;
		for (int i = 0; i < 8; i++)//将三维数组classjudge初始化
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					classjudge[i][j][k] = 0;
				}
			}
		}
		for (int i = 0; i < 8; i++)//对课表进行初始化
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					classtable[i][j][k] = "0";
				}
			}
		}
		t.resize(8);//将容器t的大小设置为8
	}
	~graph()
	{
		for (int i = 0; i < num; i++)
		{
			delete[]arrey[i];
		}
		delete arrey;
	}
	void getnum(ifstream& OpenFile);//得到文件中有多少课程的函数
	void get_data(ifstream& OpenFile);//将文件中课程信息提取出来
	void sort();//拓扑排序
	void schedule();//排课函数
	void three(int i,int j,int q);//在课表中安排三个学时的课（i代表学期，j代表课程编号，q代表从哪一天开始寻找空课时）
	void two(int i,int j,int q);
	void out();//文件输出
};
void graph::getnum(ifstream& OpenFile)//得到文件中数据的行数并且初始化边数组
{
	string line;
	while (getline(OpenFile, line))//读取文件中的每一行
	{
		if (line == "") num--;//如果读出的line字符串为空，则跳出循环
		num++;//每读一次，num++
	}
	arrey = new int* [num];
	for (int i = 0; i < num; i++)//创建边的动态二维数组
	{
		arrey[i] = new int[num];
	}
	if (!arrey) cout << "数组开辟失败";
	else {
		for (int i = 0; i < num; i++)//初始化数组，将每个边先赋值为0
		{
			for (int j = 0; j < num; j++)
			{
				arrey[i][j] = 0;
			}
		}
	}
	OpenFile.close();
}
void graph::get_data(ifstream& OpenFile)//得到文件中的数据
{
	string line;
	string index, name;
	int i = 0;
	while (getline(OpenFile, line))//对文件中数据逐行提取
	{
		if (line == "") break;//如果得到空字符串跳出循环
		node data;//新建一个node类
		vector<string> ans;//建立一个容器ans用于保存切割后的字符串
		String_Split(line, " \t", ans);//将得到的字符串切割，每个数据保存到ans中
		data.index = ans[0];//对新建node类中的每一个数据赋值
		data.name = ans[1];
		data.time = stod(ans[2]);
		data.term = stod(ans[3]);
		int j = 4;
		while (j < ans.size())//如果存在先修课程，在容器中找到该先修课程，将它们边的情况保存到边数组中
		{
			for (int k = 0; k < nodetable.size(); k++)
			{
				if (nodetable[k].index == ans[j])
				{
					arrey[i][k] = 1;
				}
			}
			j++;
			data.in++;//该点中的入度记录加1
		}
		nodetable.push_back(data);
		i++;
	}
}
void graph::sort()
{
	int learntime = 0;//定义learntime用于计算每学期的学时数
	for (int i = 0; i < 8; i++)
	{
		vector<int> cur;
		while (learntime < 25)//规定每学期的学时数不超过25
		{
			int j = 0;
			for (j = 0; j < num; j++)
			{
				if (nodetable[j].term == i + 1 && nodetable[j].take == 0)//如果图中有特定学期的课程将它提取出来
				{
					node temp;
					temp.index = nodetable[j].index;
					temp.name = nodetable[j].name;
					temp.time = nodetable[j].time;
					t[i].push_back(temp);
					learntime = learntime + nodetable[j].time;
					nodetable[j].take = 1;
				}
			}
			j = 0;
			for (j = 0; j < num; j++)//接着寻找图中入度为0的点将其取出且没有规定学期的课程
			{
				if (nodetable[j].in == 0)
				{
					if (nodetable[j].term == 0 && nodetable[j].take == 0)
					{
						node temp;
						temp.index = nodetable[j].index;
						temp.name = nodetable[j].name;
						temp.time = nodetable[j].time;
						t[i].push_back(temp);
						learntime = learntime + nodetable[j].time;
						nodetable[j].take = 1;
						cur.push_back(j);//用容器cur将这学期的课程存放
						break;
					}
					else continue;
				}
			}
			if (j == num) break;
		}
		for (int k = 0; k < cur.size(); k++)//遍历cur的数据，将以cur中元素为先修的课程入度减1
		{
			for (int p = 0; p < num; p++)
			{
				if (arrey[p][cur[k]] == 1)
				{
					nodetable[p].in--;
				}
			}
		}
		learntime = 0;
	}
}
void graph::schedule()
{
	for (int i = 0; i < 8; i++)//对每一个学期进行遍历进行排课
	{
		for (int j = 0; j < t[i].size(); j++)//对每个学期内的每个课程进行考虑
		{
			switch (t[i][j].time)
			{
			case 3:
			{
				three(i,j,1);
				break;
			}
			case 4:
			{
				two(i,j,0);
				two(i,j,2);
				break;
			}
			case 5:
			{
				three(i,j,2);
				two(i,j,4);
				break;
			}
			case 6:
			{
				two(i,j,0);
				two(i,j,1);
				two(i,j,3);
				break;
			}
			}
		}
	}
}
void graph::three(int i,int j,int q)
{
	int count = 0;
	for (int p=0;p<5;p++)
	{
		if (classjudge[i][p][1]==0||classjudge[i][p][3]==0)
		{
			count = 1;
		}
	}
	int k = q;
	if (count == 1)//如果三个课时仍然存在的情况
	{
		while(1)
		{
			if (classjudge[i][k][1] == 0 || classjudge[i][k][3] == 0)
			{
				if (classjudge[i][k][1] == 0)
				{
					classjudge[i][k][1] = 3;
					classtable[i][k][2] = t[i][j].name;
					classtable[i][k][3] = t[i][j].name;
					classtable[i][k][4] = t[i][j].name;
				}
				else
				{
					classjudge[i][k][3] = 3;
					classtable[i][k][7] = t[i][j].name;
					classtable[i][k][8] = t[i][j].name;
					classtable[i][k][9] = t[i][j].name;
				}
				break;
			}
			k++;
			if (k >= 5)k = k - 5;
		}
	}
	else//没有三节课时的安排，放到两节课时中
	{
		while(1)
		{
			if (classjudge[i][k][0] == 0 || classjudge[i][k][2] == 0)
			{
				if (classjudge[i][k][2] == 0)//优先考虑下午的课，使得课表相对分散
				{
					classjudge[i][k][2] = 2;
					classtable[i][k][5] = t[i][j].name;
					classtable[i][k][6] = t[i][j].name;
				}
				else
				{
					classjudge[i][k][0] = 2;
					classtable[i][k][0] = t[i][j].name;
					classtable[i][k][1] = t[i][j].name;
				}
				break;
			}
			k++;
			if (k >= 5)k = k - 5;
		}
		k = q;
		while(1)//还需要再安排一节课时
		{
			if (classjudge[i][k][0] == 0 || classjudge[i][k][2] == 0 || classjudge[i][k][0] == 1 || classjudge[i][k][2] == 1)
			{
				if (classjudge[i][k][0] == 0)
				{
					classjudge[i][k][0] = 1;
					classtable[i][k][0] = t[i][j].name;
				}
				else if (classjudge[i][k][0] == 1)
				{
					classjudge[i][k][0] = 2;
					classtable[i][k][1] = t[i][j].name;
				}
				else if (classjudge[i][k][2] == 0)
				{
					classjudge[i][k][2] = 1;
					classtable[i][k][5] = t[i][j].name;
				}
				else
				{
					classjudge[i][k][2] = 2;
					classtable[i][k][6] = t[i][j].name;
				}
				break;
			}
			k++;
			if (k >= 5)k = k - 5;
		}
	}
}
void graph::two(int i,int j,int q)
{
	int count = 0;
	for (int p = 0; p < 5; p++)
	{
		if (classjudge[i][p][0] == 0 || classjudge[i][p][2] == 0)
		{
			count = 1;
		}
	}
	int k = q;
	if (count==1)//两个课时依然存在的情况
	{
		while(1)
		{
			if (classjudge[i][k][0] == 0 || classjudge[i][k][2] == 0)
			{
				if (classjudge[i][k][2] == 0)
				{
					classjudge[i][k][2] = 2;
					classtable[i][k][5] = t[i][j].name;
					classtable[i][k][6] = t[i][j].name;
				}
				else
				{
					classjudge[i][k][0] = 2;
					classtable[i][k][0] = t[i][j].name;
					classtable[i][k][1] = t[i][j].name;
				}
				break;
			}
			k++;
			if (k >= 5)k = k - 5;
		}
	}
	else//没有两节课时的课了，需要将其安排到三个课时的时间里
	{
		while(1)
		{
			if (classjudge[i][k][1] == 0 || classjudge[i][k][3] == 0)
			{
				if (classjudge[i][k][1] == 0)
				{
					classjudge[i][k][1] = 2;
					classtable[i][k][2] = t[i][j].name;
					classtable[i][k][3] = t[i][j].name;
				}
				else
				{
					classjudge[i][k][3] = 2;
					classtable[i][k][7] = t[i][j].name;
					classtable[i][k][8] = t[i][j].name;
				}
				break;
			}
			k++;
			if (k >= 5)k = k - 5;
		}
	}
}
void graph::out()
{
	ofstream OutFile("课表.txt");
	for (int i=0;i<8;i++)//学期循环
	{
		OutFile <<setw(10)<< "第"<<i+1<<"学期"<<endl;
		for (int j=0;j<10;j++)//课的循环
		{
			for (int k=0;k<5;k++)//天的循环
			{
				OutFile<<setw(16)<<classtable[i][k][j]<<"\t";
			}
			OutFile << endl;
		}
		OutFile << endl << endl;
	}
}

int main()
{
	ifstream OpenFile("课程.txt");
	ofstream OutFile("课表.txt");
	int i = 0;
	string ch;
	graph g;
	g.getnum(OpenFile);
	OpenFile.close();
	OpenFile.open("课程.txt");
	g.get_data(OpenFile);
	g.sort();
	g.schedule();
	OpenFile.close();
	g.out();
	return 0;
}