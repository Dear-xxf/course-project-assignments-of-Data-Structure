#include <iostream>
using namespace std;
template <class T>
//����ڵ��࣬��Ϊ���������Ԫ������number���ڱ������ݣ�nextָ������ָ����һ���ڵ�
class node {
	template <class T>
	friend class linklist;
private:
	T number=0;
	node<T>* next = NULL;
};
//����������
template <class T>
class linklist {
	//˽�г�Ա���ڴ���ͷָ��first�Լ������ƶ���ָ��current
private:
	node<T>* first;
	node<T>* current;
public:
	//���캯�����ڴ���ͷ����Լ���currentָ��ָ��ͷ���������ʼ��
	linklist<T>()
	{
		first = new node<T>;
		current = first;
	};
	//�����������Ȱ�ͷ���delete�����ٱ������������нڵ��ͷŵ�
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
	//�õ�ͷָ��ĺ���
	node<T>* getfirst();
	//���ڲ���ĺ�����������Ŀ��Ҫֻ�������������
	void insert(T a);
	//create������������Ԫ�ص�����
	void create();
	//�ú������ڴ�ӡ�����е�����Ԫ��
	void display()
	{
		current = first->next;
		while (current != NULL)
		{
			cout << current->number << " ";
			current = current->next;
		}
	}
	//�ú�������������������Ľ���
	void combination(node<T>* secondfirst, node<T>* thirdfirst);
};
//�õ�ͷָ��
template<class T>
node<T>* linklist<T>::getfirst()
{
	return first;
}
template <class T>
void linklist<T>:: insert(T a)
{
	//�Ƚ�currentָ��ָ��ͷ���
	current = first;
	//����������currentָ��ָ���������һ���ڵ�
	while (current->next != NULL)
	{
		current = current->next;
	}
	//�����½ڵ�
	node<T>* newnode = new node<T>;
	newnode->number = a;
	newnode->next = current->next;
	current->next = newnode;
}
template <class T>
void linklist<T>::create()
{
	T n;
	//����n����nΪ-1ʱ������ѭ����ֹͣ����
	while (cin >> n)
	{
		//�Ƚ�currentָ��ָ��ͷ���
		current = first;
		//����������currentָ��ָ���������һ���ڵ�
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
			cout << "������������������У�";
			exit(0);
		}
		else break;
	}
}
template <class T>
//���ڶ����������������ͷָ����Ϊ����
void linklist<T>::combination(node<T>* secondfirst, node<T>* thirdfirst)
{
	current = first->next;
	//����һ��secondcurrentָ��ָ��ڶ�������ͷָ�����һ���ڵ�
	node<T>* secondcurrent = secondfirst->next;
	//����һ��thirdcurrentָ��ָ������������ͷ���
	node<T>* thirdcurrent;
	thirdcurrent = thirdfirst;
	//count���ڼ�������countΪ0ʱ˵��û��һ���ڵ���������ͬ�ģ���ʱ���NULL
	int count = 0;
	while (current != NULL && secondcurrent != NULL)
	{
		//��һ���ڵ��Ԫ�ر���һ����ʱ��С���Ǹ��ڵ�ָ������
		if (current->number > secondcurrent->number)
		{
			secondcurrent = secondcurrent->next;
		}
		else if (current->number < secondcurrent->number)
		{
			current = current->next;
		}
		//������ȵ����ʱ��������ڵ��Ԫ�ر������µ�������
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