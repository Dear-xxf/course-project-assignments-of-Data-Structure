#include <iostream>
using namespace std;
class node//创建用于存放数据的结点类
{
	friend class queue;
private:
	int data;
	node* next=NULL;
};
class queue//创建队列类
{
private:
	node* front;
	node* rear;
public:
	queue()//构造函数
	{
		front = new node;
		rear = front;
	}
	~queue() //析构函数
	{
		while (front!=rear)//将队列中当前每一个结点都释放掉
		{
			int x = 0;
			dequeue(x);
		}
	}
	bool isempty();//判断队列是否为空
	void inqueue(int p);//进队列的函数
	bool dequeue(int &x);//出队列的函数
};
bool queue::isempty()
{
	if (front == rear)//front指针与rear指针指向同一个地址时，队列为空
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
	queue a, b;//建立两个队列
	int N;
	while (cin >> N)//输入总顾客的人数
	{
		if (N > 0) break;
		else
		{
			cout << "请输入正确的人数"<<endl;
		}
	}
	int num=0,data;
	while (num<N)//输入每个顾客的编号，编号为奇数的进入a队列，为偶数的进入b队列
	{
		cin >> data;
		if (data % 2 == 0)
		{
			b.inqueue(data);
		}
		else a.inqueue(data);
		num++;
	}
	int count = 0;//记录已经输出的次数
	while (a.isempty()!=0&&b.isempty()!=0)//a队列与b队列都不为0时
	{
		if (count==0)//count为0说明b队列还在处理业务，将a队列的输出
		{
			int x=0;
			a.dequeue(x);
			cout << x << ' ';
			count++;
		}
		else//不为0说明a与b队列都处理完当前业务了，都进行输出
		{
			int x = 0;
			a.dequeue(x);
			cout << x << ' ';
			b.dequeue(x);
			cout << x << ' ';
			count = 0;
		}
	}
	while (a.isempty() == 0 && b.isempty() != 0)//a队列为空后，将b队列中剩余元素输出
	{
		int x = 0;
		b.dequeue(x);
		cout << x << ' ';
	}
	while (a.isempty() != 0 && b.isempty() == 0)//b队列为空后，将a队列中剩余元素输出
	{
		int x = 0;
		a.dequeue(x);
		cout << x << ' ';
	}
	cout << endl;
	system("pause");
	return 0;
}