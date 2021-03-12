#include <iostream>
#include <assert.h>
#include <cmath>
using namespace std;
template <class T>
//��ģ�嶨��node�����洢����
class node
{
	//������Ԫ��
	friend class stack;
	friend class linklist;
	friend class calculator;
private:
	//data����Ҫ�����ݣ�icp��isp�ڱ��ʽ��������׺ת��׺ʱʹ��
	T data = '0';
	int isp = 0;
	int icp = 0;
	node<T>* next = NULL;
};
//����ջ�����ں�׺���ʽ����ʱʹ��
class stack
{
	//������Ԫ��
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
	void push(int p);//ջ���뺯��
	int pop();//ջ��������
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
//�������������ڴ洢�ַ�������׺���ʽ
class linklist
{
	//������Ԫ��
	friend class calculator;
private:
	node<char>* first;//ͷָ��
	node<char>* current;//�����ƶ���currentָ��
public:
	//���캯��
	linklist()
	{
		first = new node<char>;
		current = first;
	};
	//��������
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
	void insert(char p);//�������������λ�ü���һ��Ԫ��
	void del();//���ڽ��������һ��Ԫ��ɾ����currentָ��ָ��ɾ������������Ԫ��
	void establish();//��������
	node<char>* getfirst();//����������������ͷָ��
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
	//�Ƚ����������е�Ԫ��ɾ��
	while (current != first)
	{
		del();
	}
	//�������в���elementԪ�أ�ֱ������"="
	char element;
	while (cin >> element)
	{
		if (element == '=')
		{
			break;
		}
		insert(element);
	}
	//���ǵ�Ŀ�������Ӧ��ֻ�������ʼ�����ź���
	//�ȶԱ��ʽ�ʼ�����ж�
	current = first->next;
	//�����"+"�����"+"ɾ�������������ʽû��Ӱ��
	if (current->data == '+')
	{
		node<char>* a = new node<char>;
		a = current;
		current = current->next;
		first->next = current;
		delete a;
	}
	//�����"-"��������ǰ���������Ϊ"0"�Ľ��
	else if (current->data == '-')
	{
		node<char>* a = new node<char>;
		a->data = '0';
		a->next = current;
		first->next = a;
	}
	else {}
	//�����ź��"+"��"-"�����ж�
	current = first->next;
	while (current != NULL)
	{
		if (current->data == '(')
		{
			//�����"+"��������ڵ�ɾ��
			if (current->next->data == '+')
			{
				node<char>* a = new node<char>;
				a = current->next;
				current->next = current->next->next;
				delete a;
			}
			//�����"-"����ǰ����Ͻ��Ԫ��Ϊ"0"
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
//����calculator�����ڼ���
class calculator
{
private:
	stack s;//����ջs
	linklist h;//��������h
public:
	calculator() {};//���캯��
	~calculator() {};//��������
	bool remix(node<char>* t);//���ڽ���׺���ʽ����Ϊ��׺���ʽ��������h
	void calculate();//������ʽ��ֵ
};
bool calculator::remix(node<char>* t)
{
	node<char>* p;
	p = t->next;
	//��ÿһ������icp��ջ������������isp��ջ������������ֵ
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
	linklist s1;//����һ������s1��������ʱ�������
	while (p != NULL)
	{
		//����׺���ʽ���б������������ֵ���ͽ���h����
		if (p->data <= 57 && p->data >= 48)
		{
			h.insert(p->data);
			p = p->next;
		}
		//����������ַ������
		else
		{
			//�����ǰ���ջ������������s1�е�ջ������������s1ջ
			if (p->icp > s1.current->isp)
			{
				s1.insert(p->data);
				s1.current->icp = p->icp;
				s1.current->isp = p->isp;
				p = p->next;
			}
			//���С�ڣ�s1��ǰ��ջ,h��ջ
			else if (p->icp < s1.current->isp)
			{
				char d = s1.current->data;
				s1.del();
				h.insert(d);
			}
			//���ڵ������˵�������ų����ˣ�����ɾ������׺���ʽ�в����������
			else
			{
				s1.del();
				p = p->next;
			}
		}
	}
	//��s1ʣ���Ԫ��ɾ������hջ�У����������������˵������ı��ʽ����
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
void calculator::calculate()//���ڼ���õ��ĺ�׺���ʽ
{
	node<char>* p = new node<char>;
	p = h.first->next;
	while (p != NULL)
	{
		//��������������ջs������Ԫ�ص�����������Ӧ�ļ���
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
		//�������ֵ�����sջ
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
		cout << "����ı��ʽ�д���" << endl;
	}
	cout << "�Ƿ������y,n��?" << endl;
	char judge;
	while (cin>>judge)//whileѭ����������ʽ
	{
		if (judge=='y')
		{
			g.establish();
			node<char>* j;
			j = g.getfirst();
			if (cal.remix(j)==1)//���remix����ֵΪ1�Ļ�˵�����ʽû�д��󣬽��м���
			{
				cal.calculate();
			}
			else {//�����0��˵�����ʽ����
				cout << "����ı��ʽ�д���" << endl;
			}
		}
		else
		{
			cout << "�������" << endl;
			break;
		}
		cout << "�Ƿ������y,n��?" << endl;
	}
	return 0;
}