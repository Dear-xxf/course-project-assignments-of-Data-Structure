#include <iostream>
using namespace std;
class node
{
	//成为链表的友元类
	friend class linklist;
private:
	int length = 0;//定义该段的长度
	node* next = NULL;//定义并初始化下一个指针
};
class linklist
{
private:
	node* first;//头指针
	node* current;//用于移动的current指针
public:
	linklist()//构造函数
	{
		first = new node;
		current = first;
	}
	~linklist()//析构函数
	{
		current = first->next;
		delete first;
		while (current != NULL)
		{
			node* p = current;
			current = current->next;
			delete p;
		}
	}
	void insert(int length);//用于在链表的最后插入结点，结点的length值为参量
	bool del(int length);//用于删除链表中出现的第一个length值等于参量的结点
	bool findmin(int& x);//找到链表中length最小的值，并将其赋值给x
	bool isempty();//判断链表是否为空
};
void linklist::insert(int length)
{
	current = first;
	while (current->next != NULL)
	{
		current = current->next;
	}
	node* p = new node;
	p->length = length;
	current->next = p;
}
bool linklist::del(int length)
{
	current = first;
	while (current->next != NULL)
	{
		if (current->next->length == length)
		{
			break;
		}
		current = current->next;
	}
	if (current->next == NULL)
	{
		return false;
	}
	node* p = current->next;
	current->next = current->next->next;
	delete p;
	return true;
}
bool linklist::findmin(int& x)
{
	current = first->next;
	if (current == NULL)
	{
		return false;
	}
	x = current->length;
	while (current != NULL)
	{
		if (current->length < x)
		{
			x = current->length;
		}
		current = current->next;
	}
	return true;
}
bool linklist::isempty()//为空时返回0，不为空时返回1
{
	current = first->next;
	if (current == NULL) return false;
	else return true;
}
//cutprice类用于将计算过程封装起来，调用cutprice类使用calprice函数即可计算最小值
class cutprice
{
private:
	linklist s;
public:
	cutprice() {}
	~cutprice() {}
	void calprice();
};
void cutprice::calprice()
{
	int N;
	cin >> N;//输入要分割的木头块数
	int length, price = 0, count = 0;
	while (count < N)//循环输入每一块的权值，即长度
	{
		cin >> length;
		s.insert(length);
		count++;
	}
	int num = 0, getnum = 0, NUM = 0;
	while (s.isempty() != 0)//循环，条件为链表s不为空
	{
		if (getnum == 2)//当从链表中取数的次数达到两次时
		{
			price = price + NUM;//price的值加上NUM
			num = 0;//三个暂存空间的值全部清零
			NUM = 0;
			getnum = 0;
		}
		else if (getnum == 1)//当取值次数为1时
		{
			s.findmin(num);//继续取一次值
			s.del(num);//将取完的该结点删除
			NUM = NUM + num;//NUM的值极为这两次取值之和
			s.insert(NUM);//将值为NUM的结点插入链表
			getnum++;
		}
		else {
			s.findmin(num);//getnum值为0时取链表中的最小值
			s.del(num);//将结点删除
			NUM = num;
			getnum++;
		}
	}
	//输出price的值即为要求的最小价格
	cout << price << endl;
}
int main()
{
	cutprice cut;
	cut.calprice();
	system("pause");
	return 0;
}