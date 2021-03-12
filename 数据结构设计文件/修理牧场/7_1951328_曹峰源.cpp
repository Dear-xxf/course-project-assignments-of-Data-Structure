#include <iostream>
using namespace std;
class node
{
	//��Ϊ�������Ԫ��
	friend class linklist;
private:
	int length = 0;//����öεĳ���
	node* next = NULL;//���岢��ʼ����һ��ָ��
};
class linklist
{
private:
	node* first;//ͷָ��
	node* current;//�����ƶ���currentָ��
public:
	linklist()//���캯��
	{
		first = new node;
		current = first;
	}
	~linklist()//��������
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
	void insert(int length);//������������������㣬����lengthֵΪ����
	bool del(int length);//����ɾ�������г��ֵĵ�һ��lengthֵ���ڲ����Ľ��
	bool findmin(int& x);//�ҵ�������length��С��ֵ�������丳ֵ��x
	bool isempty();//�ж������Ƿ�Ϊ��
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
bool linklist::isempty()//Ϊ��ʱ����0����Ϊ��ʱ����1
{
	current = first->next;
	if (current == NULL) return false;
	else return true;
}
//cutprice�����ڽ�������̷�װ����������cutprice��ʹ��calprice�������ɼ�����Сֵ
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
	cin >> N;//����Ҫ�ָ��ľͷ����
	int length, price = 0, count = 0;
	while (count < N)//ѭ������ÿһ���Ȩֵ��������
	{
		cin >> length;
		s.insert(length);
		count++;
	}
	int num = 0, getnum = 0, NUM = 0;
	while (s.isempty() != 0)//ѭ��������Ϊ����s��Ϊ��
	{
		if (getnum == 2)//����������ȡ���Ĵ����ﵽ����ʱ
		{
			price = price + NUM;//price��ֵ����NUM
			num = 0;//�����ݴ�ռ��ֵȫ������
			NUM = 0;
			getnum = 0;
		}
		else if (getnum == 1)//��ȡֵ����Ϊ1ʱ
		{
			s.findmin(num);//����ȡһ��ֵ
			s.del(num);//��ȡ��ĸý��ɾ��
			NUM = NUM + num;//NUM��ֵ��Ϊ������ȡֵ֮��
			s.insert(NUM);//��ֵΪNUM�Ľ���������
			getnum++;
		}
		else {
			s.findmin(num);//getnumֵΪ0ʱȡ�����е���Сֵ
			s.del(num);//�����ɾ��
			NUM = num;
			getnum++;
		}
	}
	//���price��ֵ��ΪҪ�����С�۸�
	cout << price << endl;
}
int main()
{
	cutprice cut;
	cut.calprice();
	system("pause");
	return 0;
}