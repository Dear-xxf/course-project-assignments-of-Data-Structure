#include <iostream>
#include <cstring>
using namespace std;
class node
{
	friend class familytree;
	friend class stack;
private:
	string name;
	node* next = NULL;//next指针用于确定栈中的顺序
	node* firstson=NULL;//保存该结点的长子
	node* nextbrother=NULL;//保存该结点的下一个兄弟
};
class stack//定义栈类用于树进行遍历时使用
{
private:
	node* top;
public:
	stack() { top = NULL; }
	~stack() { top = NULL; }
	bool isempty();
	void push(node* p);
	void empty();
	node* pop();
};
bool stack::isempty()//不为空时返回1，为空时返回0
{
	if (top==NULL) return false;
	else return true;
}
void stack::empty()//因为栈是使用的原来树中的数据，不能随意释放掉，置空就使top指针指向空就可以了
{
	top = NULL;
}
void stack::push(node* p)//进栈操作
{
	p->next = top;
	top = p;
}
node* stack::pop()//出栈操作
{
	node* p = top;
	top = top->next;
	return p;
}
class familytree
{
private:
	node* first=NULL;//根结点
	node* current = NULL;
	stack s;//定义栈s
	void destory(node* p)//用于将p结点及以下的空间都释放掉
	{
		if (p != NULL)
		{
			if(p->firstson!=NULL)destory(p->firstson);
			if(p->nextbrother!=NULL)destory(p->nextbrother);
			delete p;
		}
	}
public:
	familytree() //初始化界面
	{
		cout << "**           家谱管理系统           **" << endl;
		cout << "======================================" << endl;
		cout << "**         请选择要执行的操作:        " << endl;
		cout << "**          A---完善家谱            **" << endl;
		cout << "**          B---添加家庭成员        **" << endl;
		cout << "**          C---解散局部家庭        **" << endl;
		cout << "**          D---更改家庭成员姓名    **" << endl;
		cout << "**          E---退出程序            **" << endl;
		cout << "首先建立一个家谱！"<<endl;
		cout << "请输入祖先的姓名：";
		string name;
		cin >> name;
		create(name);
		cout << "此家谱的祖先是：";
		putname(first);
		cout << endl;
		cout << endl;
	}
	~familytree() 
	{
		destory(first);
	}
	bool traversal(string name);//用于树的遍历
	void create(string name);//用于树的创建
	void putname(node* p);//用于树成员姓名的输出
	void addfamily();//用于树成员增添家庭
	void addpeople();//用于树中成员增添子女
	void delfamily();//用于树中成员解散家庭
	void changename();//用于树中成员更改姓名
};
bool familytree::traversal(string name)//遍历函数，如果没有该元素就返回false
{
	s.empty();
	current=first;
	while (current!=NULL)
	{
		if (current->name == name) return true;
		if (current->nextbrother != NULL)
		{ 
			s.push(current->nextbrother); 
		}
		if (current->firstson != NULL) { current = current->firstson; }
		else 
		{ 
			if (s.isempty()!= 0)
			{
				current=s.pop();
			}
			else current = NULL;
		}
	}
	if (current == NULL) 
	{
		cout << "未能找到该成员" << endl<<endl;
		return 0;
	}
}
void familytree::create(string name)//树初始化
{
	first = new node;
	first->name = name;
	current = first;
}
void familytree::putname(node* p)//将p结点的name打印出来
{
	cout << p->name;
}
void familytree::addfamily()//建立家庭操作
{
	cout << "请输入要建立家庭的人的姓名：";
	string name;
	cin >> name;
	if (traversal(name) == 0)  return;//如果没有找到，退出函数
	cout << "请输入"<<name<<"的儿女人数：";
	int num;
	cin >> num;
	if (num == 0)
	{
		cout << "该成员无子女"<<endl;
		cout << endl;
		return;
	}
	cout << "请依次输入"<<name<<"的儿女的姓名：";
	string sonname;
	cin >> sonname;
	node* p = new node;
	p->name = sonname;
	current->firstson = p;
	for (int i=1;i<num;i++)
	{
		cout << " ";
		string nextname;
		cin >> nextname;
		node* q=new node;
		q->name = nextname;
		p->nextbrother = q;
		p = p->nextbrother;
	}
	putname(current);
	p = current->firstson;
	cout << "的第一代子孙是";
	while (p!=NULL)
	{
		putname(p);
		cout << " ";
		p = p->nextbrother;
	}
	cout << endl;
	cout << endl;
}
void familytree::addpeople()//向家庭中添加成员的操作
{
	cout << "请输入要添加的儿子（或女儿）的人的姓名：";
	string name;
	cin >> name;
	if (traversal(name) == 0) return;
	cout << "请输入"<<name<<"新添加的儿子（或女儿）的姓名：";
	string sonname;
	cin >> sonname;
	node* p;
	p = current->firstson;
	node* q = new node;
	q->name = sonname;
	if(p==NULL)
	{
		current->firstson = q;
	}
	else
	{
		while (p->nextbrother!=NULL)
		{
			p = p->nextbrother;
		}
		p->nextbrother = q;
	}
	cout <<name<< "的第一代子孙是：";
	p = current->firstson;
	while (p!=NULL)
	{
		cout << p->name << " ";
		p = p->nextbrother;
	}
	cout << endl;
	cout << endl;
}
void familytree::delfamily()//解散部分家庭的操作
{
	cout << "请输入要解散家庭的人的姓名：";
	string name;
	cin >> name;
	cout << "要解散家庭的人是："<<name<<endl;
	if(traversal(name)==0) return;
	node* p;
	p = current->firstson;
	if (p == NULL)
	{
		cout << "该成员没有子孙"<<endl;
		return;
	}
	cout << name << "的第一代子孙是：";
	while (p!=NULL)
	{
		cout << p->name<<" ";
		p = p->nextbrother;
	}
	p = current->firstson;
	destory(p);//调用destory()函数
	current->firstson = NULL;
	cout << endl;
	cout << endl;
}
void familytree::changename()//更改家庭成员姓名
{
	cout << "请输入要更改姓名的人的目前姓名：";
	string name;
	cin >> name;
	if(traversal(name)==0) return;
	cout << "请输入更改后的名字：";
	string change;
	cin >> change;
	cout << name << "已更名为" << change;
	current->name = change;
	cout << endl<<endl;
}
int main()
{
	familytree family;//建立一个家谱树
	char judge;//定义操作码
	cout << "请选择要执行的操作：";
	while (cin>>judge)
	{
		switch (judge)
		{
		case 'A':
		{
			family.addfamily();
			break;
		}
		case 'B':
		{
			family.addpeople();
			break;
		}
		case 'C':
		{
			family.delfamily();
			break;
		}
		case 'D':
		{
			family.changename();
			break;
		}
		case 'E':
		{
			system("pause");
			return 0;
		}
		default:
		{
			cout << "操作码有误！" << endl;
			break;
		}
		}
		cout << "请选择要执行的操作：";
	}
}