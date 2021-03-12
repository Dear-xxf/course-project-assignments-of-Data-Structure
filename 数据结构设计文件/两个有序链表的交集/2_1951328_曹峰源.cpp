#include <iostream>
using namespace std;
template <class T>
//定义节点类，作为链表类的友元函数，number用于保存数据，next指针用于指向下一个节点
class node {
	template <class T>
	friend class linklist;
private:
	T number=0;
	node<T>* next = NULL;
};
//定义链表类
template <class T>
class linklist {
	//私有成员用于储存头指针first以及用于移动的指针current
private:
	node<T>* first;
	node<T>* current;
public:
	//构造函数用于创建头结点以及让current指针指向头结点用作初始化
	linklist<T>()
	{
		first = new node<T>;
		current = first;
	};
	//析构函数，先把头结点delete掉，再遍历链表，将所有节点释放掉
	~linklist<T>()
	{
		current = first->next;
		delete first;
		while (current != NULL)
		{
			class node<T>* p = current->next;
			delete current;
			current = p;
		}
	};
	//得到头指针的函数
	node<T>* getfirst();
	//用于插入的函数，根据题目需要只插入在链表最后
	void insert(T a);
	//create函数用于链表元素的输入
	void create();
	//该函数用于打印链表中的所有元素
	void display()
	{
		current = first->next;
		while (current != NULL)
		{
			cout << current->number << " ";
			current = current->next;
		}
	}
	//该函数用于两个有序链表的交集
	void combination(node<T>* secondfirst, node<T>* thirdfirst);
};
//得到头指针
template<class T>
node<T>* linklist<T>::getfirst()
{
	return first;
}
template <class T>
void linklist<T>:: insert(T a)
{
	//先将current指针指向头结点
	current = first;
	//遍历链表，让current指针指向链表最后一个节点
	while (current->next != NULL)
	{
		current = current->next;
	}
	//插入新节点
	node<T>* newnode = new node<T>;
	newnode->number = a;
	newnode->next = current->next;
	current->next = newnode;
}
template <class T>
void linklist<T>::create()
{
	T n;
	//输入n，当n为-1时，跳出循环，停止输入
	while (cin >> n)
	{
		//先将current指针指向头结点
		current = first;
		//遍历链表，让current指针指向链表最后一个节点
		while (current->next != NULL)
		{
			current = current->next;
		}
		if (n != -1&&current->number<=n)
		{
			insert(n);
		}
		else if (n!=-1&&current->number>n)
		{
			cout << "输入的链表不是升序序列！";
			exit(0);
		}
		else break;
	}
}
template <class T>
//将第二个、第三个链表的头指针作为参量
void linklist<T>::combination(node<T>* secondfirst, node<T>* thirdfirst)
{
	current = first->next;
	//创建一个secondcurrent指针指向第二个链表头指针的下一个节点
	node<T>* secondcurrent = secondfirst->next;
	//创建一个thirdcurrent指针指向第三个链表的头结点
	node<T>* thirdcurrent;
	thirdcurrent = thirdfirst;
	//count用于计数，当count为0时说明没有一个节点数据是相同的，此时输出NULL
	int count = 0;
	while (current != NULL && secondcurrent != NULL)
	{
		//当一个节点的元素比另一个大时，小的那个节点指针右移
		if (current->number > secondcurrent->number)
		{
			secondcurrent = secondcurrent->next;
		}
		else if (current->number < secondcurrent->number)
		{
			current = current->next;
		}
		//出现相等的情况时，将这个节点的元素保存在新的链表中
		else
		{
			node<T>* newnode = new node<T>;
			newnode->number = current->number;
			newnode->next = thirdcurrent->next;
			thirdcurrent->next = newnode;
			thirdcurrent = thirdcurrent->next;
			current = current->next;
			secondcurrent = secondcurrent->next;
			count++;
		}
	}
	if (count == 0) cout << "NULL";
}
int main()
{
	linklist<double> list1, list2, list3;
	list1.create();
	list2.create();
	node<double>* p = list2.getfirst();
	node<double>* q = list3.getfirst();
	list1.combination(p, q);
	list3.display();
	cout << endl;
	system("pause");
	return 0;
}