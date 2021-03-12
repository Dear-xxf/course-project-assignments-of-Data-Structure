#include <iostream>
using namespace std;
class graph
{
private:
	int numofvertex;//ͼ�е�ĸ���
	int numofedge;//ͼ�бߵĸ���
	char* avertex;//��ŵ������
	int** aedge;//��űߵĶ�ά����
	int* primedge;//�����С�������ߵ�����
	char* primu;//�����С���������
	char* primv;//�����С�������յ�
public:
	graph() { numofvertex = 0; numofedge = 0; }
	~graph()
	{
		delete[]avertex; //�ͷŵ�����
		for (int i = 0; i < numofvertex; i++)//�ͷű�����
		{
			delete[]aedge[i];
		}
		delete[]aedge;
	}
	int getnumofvertex() { return numofvertex; }//�õ���ĸ���
	int getnumofedge() { return numofedge; }//�õ��ߵĸ���
	void create(int n);//���ڿ���һ����СΪn���������洢�������
	void insertedge(char u, char v, int cost);//��ͼ�в����
	void prim(char u);//prim�㷨ʵ����С������
	void printprim();//����С��������ӡ����
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
			cout << "����ĵ��Ѿ�����" << endl;
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
		cout << "��ͼ��û�е�"<<u << endl;
		return;
	}
	for (int i = 0; i < numofvertex; i++)
	{
		if (avertex[i] == v) { y = i; break; }
	}
	if (y == -1)
	{
		cout << "��ͼ��û�е�"<<v << endl;
		return;
	}
	if (cost<=0)
	{
		cout << "�ñߵ�ȨֵΥ����";
		return;
	}
	aedge[x][y] = cost;
	aedge[y][x] = cost;
	numofedge++;
}
void graph::prim(char u)
{
	int num1 = getnumofedge();//num1����ͼ�бߵĸ���
	int num2 = getnumofvertex();//num2����ͼ�е�ĸ���
	primedge = new int[num2 - 1];//primedge���ڴ����С�������ߵ�����
	primu = new char[num2 - 1];//���ڴ����С��������������
	primv = new char[num2 - 1];//���ڴ����С�������յ������
	int* p = new int[num1];//����һ����СΪ�߸���������
	int* q = new int[num2];//����һ����СΪ�����������
	int i = 0, j = 0, k = 0;
	for (i = 0; i < numofvertex; i++)
	{
		if (avertex[i] == u)break;
	}
	if (i == numofvertex)
	{
		cout << "�������ʼ��������" << endl;
		return;
	}
	i = 0;
	for (k = 0; k < num1; k++)//��p������ÿ��ֵ���ȸ�Ϊ0
	{
		p[k] = 0;
	}
	k = 0;
	for (i = 0; i < numofvertex; i++)//�ֽ����u�����б߽���p����
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
		while (j < num1)//ͳ������p�������ж�������
		{
			if (p[j] == 0) break;
			j++;
		}
		count = j;//countΪ��ǰp�������ж��ٱ�
		for (j = 0; j < count; j++)
		{
			if (p[min] > p[j]) { min = j; }
		}
		int mincost = p[min];//�õ���С���������佻��������p�еĿ���λ��
		p[min] = p[count - 1];
		p[count - 1] = mincost;
		int m = 0, n = 0;
		for (m = 0; m < numofvertex; m++)//�õ�ԭ�߾����е������յ����Ϣ����������յ㲻����prim�㷨�������
		{
			for (n = m; n < numofvertex; n++)
			{
				if (aedge[m][n] == mincost)//��aedge�������ҵ�����Сֵ��λ��
				{
					if (q[m] == 1 && q[n] == 1) { p[count - 1] = 0; i--; }//�������Сֵ���������Ѿ���ͨ�ˣ��ͽ��ñ�ɾ����i--
					else//���û����ͨ
					{
						p[count - 1] = 0;//�Ƚ��ñ�ɾ��
						q[m] = 1; q[n] = 1;//��������Ϊ��ͨ
						primedge[k] = mincost;//��ص���������ֵ�����ض�����洢
						primu[k] = avertex[m]; primv[k] = avertex[n];
						k++;
						for (int s = n; s < numofvertex; s++)//����һ������ͨ�ı߽���p����
						{
							if (aedge[n][s] != 0) { p[count - 1] = aedge[n][s]; count++; }
						}
					}
				}
			}
		}
	}
	cout << "����prim��С��������" << endl << endl;
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
	cout << "**          �������ϵͳ          **" << endl;
	cout << "====================================" << endl;
	cout << "**        A--������������         **" << endl;
	cout << "**        B--��ӵ����ı�         **" << endl;
	cout << "**        C--������С������       **" << endl;
	cout << "**        D--��ʾ��С������       **" << endl;
	cout << "**        E--�˳�  ����           **" << endl;
	cout << "====================================" << endl;
	graph g;
	cout << "��ѡ�������";
	char order;
	while (cin >> order)
	{
		switch (order)
		{
		case 'A':
		{
			cout << "�����붥��ĸ�����";
			int N;
			while (cin >> N)
			{
				if (N > 0) break;
				else cout << "����ĵ�ĸ���������Ҫ��";
			}
			cout << "�������������������ƣ�";
			g.create(N);
			cout << endl;
			break;
		}
		case 'B':
		{
			while (1)
			{
				cout << "�������������㼰�ߣ�";
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
			cout << "��������ʼ���㣺";
			char u;
			cin >> u;
			g.prim(u);
			break;
		}
		case 'D':
		{
			cout << "��С�������Ķ��㼰��Ϊ��" << endl;
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
		default:cout << "����Ĳ���������" << endl; break;
		}
		cout << "��ѡ�������";
	}
	return 0;
}