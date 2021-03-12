#include <iostream>
#include <assert.h>
#include <cmath>
using namespace std;
template <class T>
//用模板定义node类来存储数据
class node
{
	//定义友元类
	friend class stack;
	friend class linklist;
	friend class calculator;
private:
	//data是需要的数据，icp与isp在表达式操作符中缀转后缀时使用
	T data = '0';
	int isp = 0;
	int icp = 0;
	node<T>* next = NULL;
};
//定义栈类用于后缀表达式计算时使用
class stack
{
	//定义友元类
	friend class calculator;
private:
	node<int>* top;
public:
	stack()
	{
		top = NULL;
	}
	~stack() {
		node<int>* p;
		while (top != NULL)
		{
			p = top;
			top = top->next;
			delete p;
		}
	};
	void push(int p);//栈弹入函数
	int pop();//栈弹出函数
};
void stack::push(int p)
{
	node<int>* q = new node<int>;
	q->data = p;
	q->next = top;
	top = q;
	assert(top != NULL);
}
int stack::pop()
{
	int p = top->data;
	node<int>* q = top;
	top = top->next;
	delete q;
	return p;
}
//定义链表类用于存储字符类型中缀表达式
class linklist
{
	//定义友元类
	friend class calculator;
private:
	node<char>* first;//头指针
	node<char>* current;//用于移动的current指针
public:
	//构造函数
	linklist()
	{
		first = new node<char>;
		current = first;
	};
	//析构函数
	~linklist()
	{
		current = first->next;
		delete first;
		while (current != NULL)
		{
			node<char>* p;
			p = current;
			current = current->next;
			delete p;
		}
	};
	void insert(char p);//用于在链表最后位置加入一个元素
	void del();//用于将链表最后一个元素删除，current指针指向删除后链表最后的元素
	void establish();//构造链表
	node<char>* getfirst();//这个函数返回链表的头指针
};
void linklist::insert(char p)
{
	current = first;
	while (current->next != NULL)
	{
		current = current->next;
	}
	node<char>* q = new node<char>;
	q->data = p;
	q->next = NULL;
	current->next = q;
	current = current->next;
}
void linklist::del()
{
	current = first->next;
	if (current == NULL)
	{
		current = first;
	}
	else if (current->next == NULL)
	{
		delete current;
		current = first;
		first->next = NULL;
	}
	else
	{
		while (current->next->next != NULL)
		{
			current = current->next;
		}
		delete current->next;
		current->next = NULL;
	}
}
void linklist::establish()
{
	//先将链表中所有的元素删除
	while (current != first)
	{
		del();
	}
	//向链表中插入element元素，直到输入"="
	char element;
	while (cin >> element)
	{
		if (element == '=')
		{
			break;
		}
		insert(element);
	}
	//考虑单目运算符，应该只出现在最开始和括号后面
	//先对表达式最开始进行判断
	current = first->next;
	//如果是"+"则将这个"+"删除，对算数表达式没有影响
	if (current->data == '+')
	{
		node<char>* a = new node<char>;
		a = current;
		current = current->next;
		first->next = current;
		delete a;
	}
	//如果是"-"，则在最前面加上数据为"0"的结点
	else if (current->data == '-')
	{
		node<char>* a = new node<char>;
		a->data = '0';
		a->next = current;
		first->next = a;
	}
	else {}
	//对括号后的"+"和"-"进行判断
	current = first->next;
	while (current != NULL)
	{
		if (current->data == '(')
		{
			//如果是"+"，将这个节点删除
			if (current->next->data == '+')
			{
				node<char>* a = new node<char>;
				a = current->next;
				current->next = current->next->next;
				delete a;
			}
			//如果是"-"，在前面加上结点元素为"0"
			else if (current->next->data == '-')
			{
				node<char>* a = new node<char>;
				a->data = '0';
				a->next = current->next;
				current->next = a;
			}
			else{}
		}
		current = current->next;
	}
	current = first;
	while (current->next != NULL)
	{
		current = current->next;
	}
}
node<char>* linklist::getfirst()
{
	return first;
}
//定义calculator类用于计算
class calculator
{
private:
	stack s;//定义栈s
	linklist h;//定义链表h
public:
	calculator() {};//构造函数
	~calculator() {};//析构函数
	bool remix(node<char>* t);//用于将中缀表达式调整为后缀表达式存入链表h
	void calculate();//计算表达式的值
};
bool calculator::remix(node<char>* t)
{
	node<char>* p;
	p = t->next;
	//将每一个结点的icp（栈内优先数）与isp（栈外优先数）赋值
	while (p != NULL)
	{
		if (p->data <= '9' && p->data >= '0') {}
		else
		{
			switch (p->data)
			{
			case '+': {
				p->icp = 2;
				p->isp = 3;
				break;
			}
			case'-': {
				p->icp = 2;
				p->isp = 3;
				break;
			}
			case'*': {
				p->icp = 4;
				p->isp = 5;
				break;
			}
			case'/': {
				p->icp = 4;
				p->isp = 5;
				break;
			}
			case'%': {
				p->icp = 4;
				p->isp = 5;
				break;
			}
			case'^': {
				p->icp = 6;
				p->isp = 7;
				break;
			}
			case'(': {
				p->icp = 8;
				p->isp = 1;
				break;
			}
			case')': {
				p->icp = 1;
				p->isp = 8;
				break;
			}
			}
		}
		p = p->next;
	}
	p = t->next;
	linklist s1;//建立一个链表s1，用于临时存放数据
	while (p != NULL)
	{
		//对中缀表达式进行遍历，如果是数值，就进入h链表
		if (p->data <= 57 && p->data >= 48)
		{
			h.insert(p->data);
			p = p->next;
		}
		//如果是运算字符的情况
		else
		{
			//如果当前结点栈内优先数大于s1中的栈外优先数，进s1栈
			if (p->icp > s1.current->isp)
			{
				s1.insert(p->data);
				s1.current->icp = p->icp;
				s1.current->isp = p->isp;
				p = p->next;
			}
			//如果小于，s1当前退栈,h进栈
			else if (p->icp < s1.current->isp)
			{
				char d = s1.current->data;
				s1.del();
				h.insert(d);
			}
			//等于的情况下说明是括号出现了，将其删除，后缀表达式中不会出现括号
			else
			{
				s1.del();
				p = p->next;
			}
		}
	}
	//将s1剩余的元素删掉进入h栈中，如果出现有括号则说明输入的表达式有误
	while (s1.current != s1.first)
	{
		if (s1.current->data=='('||s1.current->data==')')
		{
			return false;
		}
		char d = s1.current->data;
		h.insert(d);
		s1.del();
	}
	return true;
}
void calculator::calculate()//用于计算得到的后缀表达式
{
	node<char>* p = new node<char>;
	p = h.first->next;
	while (p != NULL)
	{
		//如果是运算符，则将栈s中两个元素弹出，进行相应的计算
		if (p->data == '+' || p->data == '-' || p->data == '*' || p->data == '/' || p->data == '%' || p->data == '^')
		{
			switch (p->data)
			{
			case '+':
			{
				int number1 = s.pop(), number2 = s.pop();
				int number3;
				number3 = number1 + number2;
				s.push(number3);
				break;
			}
			case '-':
			{
				int number1 = s.pop(), number2 = s.pop();
				int number3;
				number3 = number2 - number1;
				s.push(number3);
				break;
			}
			case '*':
			{
				int number1 = s.pop(), number2 = s.pop();
				int number3;
				number3 = number1 * number2;
				s.push(number3);
				break;
			}
			case '/':
			{
				int number1 = s.pop(), number2 = s.pop();
				int number3;
				number3 = number2 / number1;
				s.push(number3);
				break;
			}
			case '%':
			{
				int number1 = s.pop(), number2 = s.pop();
				int number3;
				number3 = number2 % number1;
				s.push(number3);
				break;
			}
			case '^':
			{
				int number1 = s.pop(), number2 = s.pop();
				int number3;
				number3 =pow( number2 ,number1);
				s.push(number3);
				break;
			}
			}
		}
		//如果是数值，则进s栈
		else {
			s.push(p->data - 48);
		}
		p = p->next;
	}
	cout << s.top->data<<endl;
}
int main()
{
	linklist g;
	calculator cal;
	g.establish();
	node<char>* j = new node<char>;
	j = g.getfirst();
	if (cal.remix(j) == 1)
	{
		cal.calculate();
	}
	else
	{
		cout << "输入的表达式有错误" << endl;
	}
	cout << "是否继续（y,n）?" << endl;
	char judge;
	while (cin>>judge)//while循环来计算表达式
	{
		if (judge=='y')
		{
			g.establish();
			node<char>* j;
			j = g.getfirst();
			if (cal.remix(j)==1)//如果remix返回值为1的话说明表达式没有错误，进行计算
			{
				cal.calculate();
			}
			else {//如果是0，说明表达式有误
				cout << "输入的表达式有错误" << endl;
			}
		}
		else
		{
			cout << "运算结束" << endl;
			break;
		}
		cout << "是否继续（y,n）?" << endl;
	}
	return 0;
}