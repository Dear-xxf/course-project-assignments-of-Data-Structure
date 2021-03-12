#include <istream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class node//�洢�γ���Ϣ�ĵ���
{
	friend class graph;//����Ϊͼ����Ԫ��
private:
	string index;//�γ̵ı��
	string name;//�γ̵�����
	int time = 0;//�γ̵Ŀ�ʱ��
	int term = 0;//�γ�Ӧ�ڵ�ѧ��
	int in = 0;//�ÿγ̵����
	int take = 0;//�ÿγ��Ƿ��Ѿ������ţ����ں�����������
public:
	node() {}//���캯��
	~node() {}//��������
};

void String_Split(string s, string delim, vector<string>& ans)//���ڽ����ļ��ж�����string��ָ�浽vector��
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
	vector<node> nodetable;//�γ���Ϣ�Ĵ洢����
	int** arrey;//������洢������
	int num;//������ļ��пγ���
	string classtable[8][5][10];//�洢����α�
	int classjudge[8][5][4];//����α�ʱ���Ƿ�ռ�ã����ں����ж�
	vector<vector<node>> t;//�洢ÿѧ�ڵĿγ�
public:
	graph()
	{
		num = 0;
		for (int i = 0; i < 8; i++)//����ά����classjudge��ʼ��
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					classjudge[i][j][k] = 0;
				}
			}
		}
		for (int i = 0; i < 8; i++)//�Կα���г�ʼ��
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					classtable[i][j][k] = "0";
				}
			}
		}
		t.resize(8);//������t�Ĵ�С����Ϊ8
	}
	~graph()
	{
		for (int i = 0; i < num; i++)
		{
			delete[]arrey[i];
		}
		delete arrey;
	}
	void getnum(ifstream& OpenFile);//�õ��ļ����ж��ٿγ̵ĺ���
	void get_data(ifstream& OpenFile);//���ļ��пγ���Ϣ��ȡ����
	void sort();//��������
	void schedule();//�ſκ���
	void three(int i,int j,int q);//�ڿα��а�������ѧʱ�ĿΣ�i����ѧ�ڣ�j����γ̱�ţ�q�������һ�쿪ʼѰ�ҿտ�ʱ��
	void two(int i,int j,int q);
	void out();//�ļ����
};
void graph::getnum(ifstream& OpenFile)//�õ��ļ������ݵ��������ҳ�ʼ��������
{
	string line;
	while (getline(OpenFile, line))//��ȡ�ļ��е�ÿһ��
	{
		if (line == "") num--;//���������line�ַ���Ϊ�գ�������ѭ��
		num++;//ÿ��һ�Σ�num++
	}
	arrey = new int* [num];
	for (int i = 0; i < num; i++)//�����ߵĶ�̬��ά����
	{
		arrey[i] = new int[num];
	}
	if (!arrey) cout << "���鿪��ʧ��";
	else {
		for (int i = 0; i < num; i++)//��ʼ�����飬��ÿ�����ȸ�ֵΪ0
		{
			for (int j = 0; j < num; j++)
			{
				arrey[i][j] = 0;
			}
		}
	}
	OpenFile.close();
}
void graph::get_data(ifstream& OpenFile)//�õ��ļ��е�����
{
	string line;
	string index, name;
	int i = 0;
	while (getline(OpenFile, line))//���ļ�������������ȡ
	{
		if (line == "") break;//����õ����ַ�������ѭ��
		node data;//�½�һ��node��
		vector<string> ans;//����һ������ans���ڱ����и����ַ���
		String_Split(line, " \t", ans);//���õ����ַ����иÿ�����ݱ��浽ans��
		data.index = ans[0];//���½�node���е�ÿһ�����ݸ�ֵ
		data.name = ans[1];
		data.time = stod(ans[2]);
		data.term = stod(ans[3]);
		int j = 4;
		while (j < ans.size())//����������޿γ̣����������ҵ������޿γ̣������Ǳߵ�������浽��������
		{
			for (int k = 0; k < nodetable.size(); k++)
			{
				if (nodetable[k].index == ans[j])
				{
					arrey[i][k] = 1;
				}
			}
			j++;
			data.in++;//�õ��е���ȼ�¼��1
		}
		nodetable.push_back(data);
		i++;
	}
}
void graph::sort()
{
	int learntime = 0;//����learntime���ڼ���ÿѧ�ڵ�ѧʱ��
	for (int i = 0; i < 8; i++)
	{
		vector<int> cur;
		while (learntime < 25)//�涨ÿѧ�ڵ�ѧʱ��������25
		{
			int j = 0;
			for (j = 0; j < num; j++)
			{
				if (nodetable[j].term == i + 1 && nodetable[j].take == 0)//���ͼ�����ض�ѧ�ڵĿγ̽�����ȡ����
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
			for (j = 0; j < num; j++)//����Ѱ��ͼ�����Ϊ0�ĵ㽫��ȡ����û�й涨ѧ�ڵĿγ�
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
						cur.push_back(j);//������cur����ѧ�ڵĿγ̴��
						break;
					}
					else continue;
				}
			}
			if (j == num) break;
		}
		for (int k = 0; k < cur.size(); k++)//����cur�����ݣ�����cur��Ԫ��Ϊ���޵Ŀγ���ȼ�1
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
	for (int i = 0; i < 8; i++)//��ÿһ��ѧ�ڽ��б��������ſ�
	{
		for (int j = 0; j < t[i].size(); j++)//��ÿ��ѧ���ڵ�ÿ���γ̽��п���
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
	if (count == 1)//���������ʱ��Ȼ���ڵ����
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
	else//û�����ڿ�ʱ�İ��ţ��ŵ����ڿ�ʱ��
	{
		while(1)
		{
			if (classjudge[i][k][0] == 0 || classjudge[i][k][2] == 0)
			{
				if (classjudge[i][k][2] == 0)//���ȿ�������ĿΣ�ʹ�ÿα���Է�ɢ
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
		while(1)//����Ҫ�ٰ���һ�ڿ�ʱ
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
	if (count==1)//������ʱ��Ȼ���ڵ����
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
	else//û�����ڿ�ʱ�Ŀ��ˣ���Ҫ���䰲�ŵ�������ʱ��ʱ����
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
	ofstream OutFile("�α�.txt");
	for (int i=0;i<8;i++)//ѧ��ѭ��
	{
		OutFile <<setw(10)<< "��"<<i+1<<"ѧ��"<<endl;
		for (int j=0;j<10;j++)//�ε�ѭ��
		{
			for (int k=0;k<5;k++)//���ѭ��
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
	ifstream OpenFile("�γ�.txt");
	ofstream OutFile("�α�.txt");
	int i = 0;
	string ch;
	graph g;
	g.getnum(OpenFile);
	OpenFile.close();
	OpenFile.open("�γ�.txt");
	g.get_data(OpenFile);
	g.sort();
	g.schedule();
	OpenFile.close();
	g.out();
	return 0;
}