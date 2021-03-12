#include <iostream>
#include <string>
using namespace std;
//链表节点类用student来命名
class student{
	friend class examination;
private:
	int ticket_number=0;
	string name="0";
	string gender="0";
	int age=0;
	string job = "0";
	student* next=NULL;
public:
	student() {};
	~student() {};
};
class examination
{
private:
	student* first;
	student* current;
public:
	examination()
	{
		first = new student;
		int number;
		cout << "首先请建立考试系统" << endl;
		cout << "请输入考生人数" << " ";
		while (cin >> number)
		{
			if (number > 0) {
				cout << "请依次输入考生的考号、姓名、性别、年龄、报考类别！" << endl;
				break;
			}
			else {
				cout << "请输入一个正整数！" << endl;
				cout << "请输入考生人数" << " ";
			}
		}
		for (int i=0;i<number;i++)
		{
			//每一个新节点开创空间
			student* p = new student;
			cin >> p->ticket_number;
			cin >> p->name;
			cin >> p->gender;
			cin >> p->age;
			cin >> p->job;
			judge(p);
			current = first;
			while (current->next!=NULL)
			{
				current = current->next;
			}
			current->next = p;
		}
	}
	~examination()
	{
		current = first->next;
		delete first;
		student* p;
		while (current != NULL)
		{
			p = current->next;
			delete current;
			current = p;
		}
	}
	void insert();
	void display();
	void find(int target);//通过考号来查询
	void change(int target);//通过考号来替换
	void del(int target);//通过考号来删除
	bool judge(student* p);
};
//插入函数
void examination::insert()
{
	cout << "请依次输入要插入考生的考号、姓名、性别、年龄及报考类别！"<<endl;
	student* p = new student;
	cin >> p->ticket_number;
	cin >> p->name;
	cin >> p->gender;
	cin >> p->age;
	cin >> p->job;
	judge(p);
	int location;
	cout << "请输入您要插入的考生的位置：";
	while (cin >> location)
	{
		int i = 1;
		current = first;
		while (i < location && current != NULL)
		{
			current = current->next;
			i++;
		}
		if (current == NULL)
		{
			cout << "你输入的位置不合法，请重新输入！" << endl;
			cout << "请输入您要插入的考生的位置：";
		}
		else break;
	}
	p->next = current->next;
	current->next = p;
}
void examination::del(int target)
{
	//遍历链表找到要删除的节点的上一个节点
	current = first;
	while (current->next != NULL && current->next->ticket_number != target)
	{
		current = current->next;
	}
	//如果没有找到输出提示语句
	if (current->next == NULL)
		cout << "找不到匹配的数据" << endl;
	//找到符合的元素后，将符合条件的节点删除
	else {
		student* p = current->next;
		current->next = current->next->next;
		delete p;
		cout << "该条信息已被删除" << endl;
	}
}
//查询函数满足用考号查询
void examination::find(int target)
{
	//对链表进行遍历，找到符合条件的节点再跳出循环，如果最后没有发现符合条件的，输出提示信息促使用户检查输入的信息无误
	current = first->next;
	while (current != NULL && current->ticket_number != target)
	{
		current = current->next;
		if (current == NULL)
		{
			cout << "没有找到该对象，请确认输入的信息无误" << endl;
		}
	}
	//找到符合条件的节点后，将该节点的数据输出
	if (current != NULL)
	{
		cout << "您要查找的数据为：" << endl;
		cout << current->ticket_number << " ";
		cout << current->name << " ";
		cout << current->gender << " ";
		cout << current->age << " ";
		cout << current->job << endl;
	}
}
//该函数为修改函数，满足根据考号修改
void examination::change(int target)
{
	//遍历链表找到符合条件的节点的上一个节点
	current = first;
	while (current->next != NULL && current->next->ticket_number != target)
	{
		current = current->next;
	}
	//如果指向NULL，说明该链表中没有该元素
	if (current->next == NULL)
		cout << "找不到匹配的数据" << endl;
	//找到符合的节点后，将节点的数据放到新开辟的空间中，将新开辟的空间插入链表，delete掉原节点
	else {
		student* p = new student;
		student* q = current->next;
		p->next = q->next;
		current->next = p;
		if (q != NULL) delete q;
		cout << "请输入您要替换的内容" << " ";
		cin >> p->ticket_number;
		cin >> p->name;
		cin >> p->gender;
		cin >> p->age;
		cin >> p->job;
		judge(p);
		cout << "内容替换完成" << endl;
	}
}
//将链表中每个元素打印出来
void examination::display()
{
	current = first->next;
	while (current != NULL)
	{
		cout << current->ticket_number << " ";
		cout << current->name << " ";
		cout << current->gender << " ";
		cout << current->age << " ";
		cout << current->job << endl;
		current = current->next;
	}
}
bool examination::judge(student* p)
{
	current = first->next;
	while (current != NULL)
	{
		if (current->ticket_number == p->ticket_number) break;
		current = current->next;
	}
	if (current != NULL)
	{
		cout << "您输入的考号与已存在的重复" << endl;
		cout << current->ticket_number << " ";
		cout << current->name << " ";
		cout << current->gender << " ";
		cout << current->age << " ";
		cout << current->job << endl;
		cout << "请选择：1.重新输入该学号 2.修改已存在的学号" << endl;
		int num;
		while (cin >> num)
		{
			if (num == 1)
			{
				cin >> p->ticket_number;
				if(judge(p)!=0)break;
			}
			else if (num == 2)
			{
				current = first->next;
				while (current->ticket_number != p->ticket_number)
				{
					current = current->next;
				}
				cin >> current->ticket_number;
				student* q = current;
				if (judge(q)!=0&&q->ticket_number!=p->ticket_number) break; 
			}
			else
			{
				cout << "输入操作无效" << endl;
				cout << "请选择：1.重新输入该学号 2.修改已存在的学号";
			}
		}
		return true;
	}
}
int main()
{
	//创建链表类
	examination tju;
	int order_number;
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl;
	//while循环进行操作
	while (cin >> order_number)
	{
		switch (order_number)
		{
		//输入1的时候进行插入操作
		case 1: {
			tju.insert();
			break;
		}
	    //输入2的时候进行删除操作，进一步分类通过考号或姓名进行操作
		case 2:
		{
			cout << "您要删除的数据考号为：";
			int number;
			cin >> number;
			tju.del(number);
			break;
		}
		//输入3的时候进行查找操作
		case 3:
		{
			cout << "您要查找的数据考号为：";
			int number;
			cin >> number;
			tju.find(number);
			break;
		}
		//输入4的时候进行修改操作
		case 4:
		{
			cout << "您要修改的数据考号为：";
			int number;
			cin >> number;
			tju.change(number);
			break;
		}
		//输入5的时候将链表中数据打印出来
		case 5:
		{
			tju.display();
			break;
		}
		//输入0的时候取消操作
		case 0:
		{
			cout << "取消操作" << endl;
			exit(0);
			system("pause");
			break;
		}
		//输入这以外的其他数，判定为错误操作，输出提示语句报错
		default:
		{
			cout << "您输入的操作有误，请重新选择您要进行的操作" << endl;
			break;
		}
		}
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl;
	}
	return 0;
}