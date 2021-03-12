#include <iostream>
#include <string>
using namespace std;
//����ڵ�����student������
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
		cout << "�����뽨������ϵͳ" << endl;
		cout << "�����뿼������" << " ";
		while (cin >> number)
		{
			if (number > 0) {
				cout << "���������뿼���Ŀ��š��������Ա����䡢�������" << endl;
				break;
			}
			else {
				cout << "������һ����������" << endl;
				cout << "�����뿼������" << " ";
			}
		}
		for (int i=0;i<number;i++)
		{
			//ÿһ���½ڵ㿪���ռ�
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
	void find(int target);//ͨ����������ѯ
	void change(int target);//ͨ���������滻
	void del(int target);//ͨ��������ɾ��
	bool judge(student* p);
};
//���뺯��
void examination::insert()
{
	cout << "����������Ҫ���뿼���Ŀ��š��������Ա����估�������"<<endl;
	student* p = new student;
	cin >> p->ticket_number;
	cin >> p->name;
	cin >> p->gender;
	cin >> p->age;
	cin >> p->job;
	judge(p);
	int location;
	cout << "��������Ҫ����Ŀ�����λ�ã�";
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
			cout << "�������λ�ò��Ϸ������������룡" << endl;
			cout << "��������Ҫ����Ŀ�����λ�ã�";
		}
		else break;
	}
	p->next = current->next;
	current->next = p;
}
void examination::del(int target)
{
	//���������ҵ�Ҫɾ���Ľڵ����һ���ڵ�
	current = first;
	while (current->next != NULL && current->next->ticket_number != target)
	{
		current = current->next;
	}
	//���û���ҵ������ʾ���
	if (current->next == NULL)
		cout << "�Ҳ���ƥ�������" << endl;
	//�ҵ����ϵ�Ԫ�غ󣬽����������Ľڵ�ɾ��
	else {
		student* p = current->next;
		current->next = current->next->next;
		delete p;
		cout << "������Ϣ�ѱ�ɾ��" << endl;
	}
}
//��ѯ���������ÿ��Ų�ѯ
void examination::find(int target)
{
	//��������б������ҵ����������Ľڵ�������ѭ����������û�з��ַ��������ģ������ʾ��Ϣ��ʹ�û�����������Ϣ����
	current = first->next;
	while (current != NULL && current->ticket_number != target)
	{
		current = current->next;
		if (current == NULL)
		{
			cout << "û���ҵ��ö�����ȷ���������Ϣ����" << endl;
		}
	}
	//�ҵ����������Ľڵ�󣬽��ýڵ���������
	if (current != NULL)
	{
		cout << "��Ҫ���ҵ�����Ϊ��" << endl;
		cout << current->ticket_number << " ";
		cout << current->name << " ";
		cout << current->gender << " ";
		cout << current->age << " ";
		cout << current->job << endl;
	}
}
//�ú���Ϊ�޸ĺ�����������ݿ����޸�
void examination::change(int target)
{
	//���������ҵ����������Ľڵ����һ���ڵ�
	current = first;
	while (current->next != NULL && current->next->ticket_number != target)
	{
		current = current->next;
	}
	//���ָ��NULL��˵����������û�и�Ԫ��
	if (current->next == NULL)
		cout << "�Ҳ���ƥ�������" << endl;
	//�ҵ����ϵĽڵ�󣬽��ڵ�����ݷŵ��¿��ٵĿռ��У����¿��ٵĿռ��������delete��ԭ�ڵ�
	else {
		student* p = new student;
		student* q = current->next;
		p->next = q->next;
		current->next = p;
		if (q != NULL) delete q;
		cout << "��������Ҫ�滻������" << " ";
		cin >> p->ticket_number;
		cin >> p->name;
		cin >> p->gender;
		cin >> p->age;
		cin >> p->job;
		judge(p);
		cout << "�����滻���" << endl;
	}
}
//��������ÿ��Ԫ�ش�ӡ����
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
		cout << "������Ŀ������Ѵ��ڵ��ظ�" << endl;
		cout << current->ticket_number << " ";
		cout << current->name << " ";
		cout << current->gender << " ";
		cout << current->age << " ";
		cout << current->job << endl;
		cout << "��ѡ��1.���������ѧ�� 2.�޸��Ѵ��ڵ�ѧ��" << endl;
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
				cout << "���������Ч" << endl;
				cout << "��ѡ��1.���������ѧ�� 2.�޸��Ѵ��ڵ�ѧ��";
			}
		}
		return true;
	}
}
int main()
{
	//����������
	examination tju;
	int order_number;
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)" << endl;
	//whileѭ�����в���
	while (cin >> order_number)
	{
		switch (order_number)
		{
		//����1��ʱ����в������
		case 1: {
			tju.insert();
			break;
		}
	    //����2��ʱ�����ɾ����������һ������ͨ�����Ż��������в���
		case 2:
		{
			cout << "��Ҫɾ�������ݿ���Ϊ��";
			int number;
			cin >> number;
			tju.del(number);
			break;
		}
		//����3��ʱ����в��Ҳ���
		case 3:
		{
			cout << "��Ҫ���ҵ����ݿ���Ϊ��";
			int number;
			cin >> number;
			tju.find(number);
			break;
		}
		//����4��ʱ������޸Ĳ���
		case 4:
		{
			cout << "��Ҫ�޸ĵ����ݿ���Ϊ��";
			int number;
			cin >> number;
			tju.change(number);
			break;
		}
		//����5��ʱ�����������ݴ�ӡ����
		case 5:
		{
			tju.display();
			break;
		}
		//����0��ʱ��ȡ������
		case 0:
		{
			cout << "ȡ������" << endl;
			exit(0);
			system("pause");
			break;
		}
		//��������������������ж�Ϊ��������������ʾ��䱨��
		default:
		{
			cout << "������Ĳ�������������ѡ����Ҫ���еĲ���" << endl;
			break;
		}
		}
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)" << endl;
	}
	return 0;
}