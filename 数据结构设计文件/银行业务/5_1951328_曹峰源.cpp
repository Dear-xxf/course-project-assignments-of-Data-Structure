#include <iostream>
using namespace std;
class node//�������ڴ�����ݵĽ����
{
	friend class queue;
private:
	int data;
	node* next=NULL;
};
class queue//����������
{
private:
	node* front;
	node* rear;
public:
	queue()//���캯��
	{
		front = new node;
		rear = front;
	}
	~queue() //��������
	{
		while (front!=rear)//�������е�ǰÿһ����㶼�ͷŵ�
		{
			int x = 0;
			dequeue(x);
		}
	}
	bool isempty();//�ж϶����Ƿ�Ϊ��
	void inqueue(int p);//�����еĺ���
	bool dequeue(int &x);//�����еĺ���
};
bool queue::isempty()
{
	if (front == rear)//frontָ����rearָ��ָ��ͬһ����ַʱ������Ϊ��
	{
		return false;
	}
	else return true;
}
void queue::inqueue(int p)
{
	node* q = new node;
	q->data = p;
	q->next = NULL;
	rear->next = q;
	rear = q;
}
bool queue::dequeue(int &x)
{
	if (front == rear) return false;
	node* p=front->next;
	x = p->data;
	front->next = front->next->next;
	if (p==rear)
	{
		rear = front;
	}
	delete p;
	return true;
}
int main()
{
	queue a, b;//������������
	int N;
	while (cin >> N)//�����ܹ˿͵�����
	{
		if (N > 0) break;
		else
		{
			cout << "��������ȷ������"<<endl;
		}
	}
	int num=0,data;
	while (num<N)//����ÿ���˿͵ı�ţ����Ϊ�����Ľ���a���У�Ϊż���Ľ���b����
	{
		cin >> data;
		if (data % 2 == 0)
		{
			b.inqueue(data);
		}
		else a.inqueue(data);
		num++;
	}
	int count = 0;//��¼�Ѿ�����Ĵ���
	while (a.isempty()!=0&&b.isempty()!=0)//a������b���ж���Ϊ0ʱ
	{
		if (count==0)//countΪ0˵��b���л��ڴ���ҵ�񣬽�a���е����
		{
			int x=0;
			a.dequeue(x);
			cout << x << ' ';
			count++;
		}
		else//��Ϊ0˵��a��b���ж������굱ǰҵ���ˣ����������
		{
			int x = 0;
			a.dequeue(x);
			cout << x << ' ';
			b.dequeue(x);
			cout << x << ' ';
			count = 0;
		}
	}
	while (a.isempty() == 0 && b.isempty() != 0)//a����Ϊ�պ󣬽�b������ʣ��Ԫ�����
	{
		int x = 0;
		b.dequeue(x);
		cout << x << ' ';
	}
	while (a.isempty() != 0 && b.isempty() == 0)//b����Ϊ�պ󣬽�a������ʣ��Ԫ�����
	{
		int x = 0;
		a.dequeue(x);
		cout << x << ' ';
	}
	cout << endl;
	system("pause");
	return 0;
}