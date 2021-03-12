#include <iostream>
#include <cstring>
using namespace std;
class node
{
	friend class familytree;
	friend class stack;
private:
	string name;
	node* next = NULL;//nextָ������ȷ��ջ�е�˳��
	node* firstson=NULL;//����ý��ĳ���
	node* nextbrother=NULL;//����ý�����һ���ֵ�
};
class stack//����ջ�����������б���ʱʹ��
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
bool stack::isempty()//��Ϊ��ʱ����1��Ϊ��ʱ����0
{
	if (top==NULL) return false;
	else return true;
}
void stack::empty()//��Ϊջ��ʹ�õ�ԭ�����е����ݣ����������ͷŵ����ÿվ�ʹtopָ��ָ��վͿ�����
{
	top = NULL;
}
void stack::push(node* p)//��ջ����
{
	p->next = top;
	top = p;
}
node* stack::pop()//��ջ����
{
	node* p = top;
	top = top->next;
	return p;
}
class familytree
{
private:
	node* first=NULL;//�����
	node* current = NULL;
	stack s;//����ջs
	void destory(node* p)//���ڽ�p��㼰���µĿռ䶼�ͷŵ�
	{
		if (p != NULL)
		{
			if(p->firstson!=NULL)destory(p->firstson);
			if(p->nextbrother!=NULL)destory(p->nextbrother);
			delete p;
		}
	}
public:
	familytree() //��ʼ������
	{
		cout << "**           ���׹���ϵͳ           **" << endl;
		cout << "======================================" << endl;
		cout << "**         ��ѡ��Ҫִ�еĲ���:        " << endl;
		cout << "**          A---���Ƽ���            **" << endl;
		cout << "**          B---��Ӽ�ͥ��Ա        **" << endl;
		cout << "**          C---��ɢ�ֲ���ͥ        **" << endl;
		cout << "**          D---���ļ�ͥ��Ա����    **" << endl;
		cout << "**          E---�˳�����            **" << endl;
		cout << "���Ƚ���һ�����ף�"<<endl;
		cout << "���������ȵ�������";
		string name;
		cin >> name;
		create(name);
		cout << "�˼��׵������ǣ�";
		putname(first);
		cout << endl;
		cout << endl;
	}
	~familytree() 
	{
		destory(first);
	}
	bool traversal(string name);//�������ı���
	void create(string name);//�������Ĵ���
	void putname(node* p);//��������Ա���������
	void addfamily();//��������Ա�����ͥ
	void addpeople();//�������г�Ա������Ů
	void delfamily();//�������г�Ա��ɢ��ͥ
	void changename();//�������г�Ա��������
};
bool familytree::traversal(string name)//�������������û�и�Ԫ�ؾͷ���false
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
		cout << "δ���ҵ��ó�Ա" << endl<<endl;
		return 0;
	}
}
void familytree::create(string name)//����ʼ��
{
	first = new node;
	first->name = name;
	current = first;
}
void familytree::putname(node* p)//��p����name��ӡ����
{
	cout << p->name;
}
void familytree::addfamily()//������ͥ����
{
	cout << "������Ҫ������ͥ���˵�������";
	string name;
	cin >> name;
	if (traversal(name) == 0)  return;//���û���ҵ����˳�����
	cout << "������"<<name<<"�Ķ�Ů������";
	int num;
	cin >> num;
	if (num == 0)
	{
		cout << "�ó�Ա����Ů"<<endl;
		cout << endl;
		return;
	}
	cout << "����������"<<name<<"�Ķ�Ů��������";
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
	cout << "�ĵ�һ��������";
	while (p!=NULL)
	{
		putname(p);
		cout << " ";
		p = p->nextbrother;
	}
	cout << endl;
	cout << endl;
}
void familytree::addpeople()//���ͥ����ӳ�Ա�Ĳ���
{
	cout << "������Ҫ��ӵĶ��ӣ���Ů�������˵�������";
	string name;
	cin >> name;
	if (traversal(name) == 0) return;
	cout << "������"<<name<<"����ӵĶ��ӣ���Ů������������";
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
	cout <<name<< "�ĵ�һ�������ǣ�";
	p = current->firstson;
	while (p!=NULL)
	{
		cout << p->name << " ";
		p = p->nextbrother;
	}
	cout << endl;
	cout << endl;
}
void familytree::delfamily()//��ɢ���ּ�ͥ�Ĳ���
{
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	string name;
	cin >> name;
	cout << "Ҫ��ɢ��ͥ�����ǣ�"<<name<<endl;
	if(traversal(name)==0) return;
	node* p;
	p = current->firstson;
	if (p == NULL)
	{
		cout << "�ó�Աû������"<<endl;
		return;
	}
	cout << name << "�ĵ�һ�������ǣ�";
	while (p!=NULL)
	{
		cout << p->name<<" ";
		p = p->nextbrother;
	}
	p = current->firstson;
	destory(p);//����destory()����
	current->firstson = NULL;
	cout << endl;
	cout << endl;
}
void familytree::changename()//���ļ�ͥ��Ա����
{
	cout << "������Ҫ�����������˵�Ŀǰ������";
	string name;
	cin >> name;
	if(traversal(name)==0) return;
	cout << "��������ĺ�����֣�";
	string change;
	cin >> change;
	cout << name << "�Ѹ���Ϊ" << change;
	current->name = change;
	cout << endl<<endl;
}
int main()
{
	familytree family;//����һ��������
	char judge;//���������
	cout << "��ѡ��Ҫִ�еĲ�����";
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
			cout << "����������" << endl;
			break;
		}
		}
		cout << "��ѡ��Ҫִ�еĲ�����";
	}
}