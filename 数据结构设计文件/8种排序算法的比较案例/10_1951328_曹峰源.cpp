#include <iostream>
#include <ctime>
using namespace std;
//ð������
void bubble_sort(int N)
{
	clock_t start, end;//����ʱ�������ڼ����������ǰ������ʱ��
	int* p = new int[N];//���ٶ�̬����
	srand(time(NULL));//����ʱ�����ò����������ֹÿһ�γ������в������������ͬ
	if (p==NULL)//����ڴ治������ʧ�ܵ����
	{
		cout << "�ڴ治��";
		exit(0);
	}
	for (int i=0;i<N;i++)//���������
	{
		*(p + i) = rand();
	}
	start = clock();
	int temp = 0;
	long long count = 0;
	for (int i=0;i<N-1;i++)//ð������ѭ����һ������N-1�Σ�ÿһ�ζ���δ����������������ͨ�������ŵ�����������������N-1�κ�����ɹ�
	{
		for (int j=0;j<N-1-i;j++)
		{
			if (*(p+j)>*(p+j+1))
			{
				temp = *(p + j);
				*(p + j) = *(p + j + 1);
				*(p + j + 1) = temp;
				count++;//ÿ�ν�������������һ��
			}
		}
	}
	end = clock();
	delete[]p;//�ͷ�����ռ�
	cout << "ð����������ʱ�䣺";
	cout << (double)(end - start)/1000<<endl;
	cout << "ð�����򽻻�������";
	cout << count<<endl<<endl;
}
//ѡ������
void selection_sort(int N)
{
	clock_t start, end;
	int* p = new int[N];//������̬����
	srand(time(NULL));
	if (p == NULL)
	{
		cout << "�ڴ治��";
		exit(0);
	}
	for (int i=0;i<N;i++)
	{
		*(p + i) = rand();
	}
	start = clock();
	int temp;
	long long count = 0;
	for (int i=0;i<N-1;i++)//һ������N-1��ѭ������ð���������ƣ���ͬ����ð����ͨ��������ʵ���������ŵ��������ѡ��������ÿһ���ҳ�������
	{
		temp = 0;
		for (int j=0;j<N-i-1;j++)//ͨ������ѭ���ҳ�δ����������������
		{
			if (*(p+temp)<*(p+j+1))
			{
				temp = j + 1;
				count++;
			}
		}
		int wrap = 0;//���佻������������λ��
		wrap = *(p+N-1-i);
		*(p + N-1 - i) = *(p+temp);
		*(p + temp) = wrap;
		count++;//ÿһ�ν�������������һ��
	}
	end = clock();
	delete[]p;
	cout << "ѡ����������ʱ�䣺";
	cout << (double)(end - start)/1000<<endl;
	cout << "ѡ�����򽻻�������";
	cout << count<<endl<<endl;
}
//ֱ�Ӳ�������
void stright_insertion(int N)
{
	clock_t start, end;
	int* p = new int[N];
	srand(time(NULL));
	if (p == NULL)
	{
		cout << "�ڴ治��";
		exit(0);
	}
	for (int i = 0; i < N; i++)
	{
		*(p + i) = rand();
	}
	start = clock();
	int temp;
	long long count = 0;
	for (int i=1;i<N;i++)//һ������N-1��ѭ����������ĵڶ���λ�ÿ�ʼѭ����������뵽ǰ��ķ�������Ҫ���λ��
	{
		int temp = *(p+i);
		int j = i;
		while (temp<*(p+j-1)&&j>0)//ͨ��ѭ����ǰ���Ѿ��źõ�λ�ñȽϣ�ֱ�����뵽��Ӧ��λ��
		{
			*(p +j) = *(p + j - 1);
			count++;//ÿ�ν�����������1
			j--;
		}
		*(p + j) = temp;
		count++;
	}
	end = clock();
	delete[]p;
	cout << "ֱ�Ӳ�����������ʱ�䣺";
	cout << (double)(end-start)/1000<<endl;
	cout << "ֱ�Ӳ������򽻻�������";
	cout << count<<endl<<endl;
}
//ϣ������
void shell_sort(int N)
{
	clock_t start, end;
	int* p = new int[N];
	srand(time(NULL));
	if (p == NULL)
	{
		cout << "�ڴ治��";
		exit(0);
	}
	for (int i = 0; i < N; i++)
	{
		*(p + i) = rand();
	}
	start = clock();
	int gap = N / 2, temp = 0;
	long long count = 0;//��ʼ��������ΪN/2
	while (gap>=1)//����ѭ��������Ϊgap��Ϊ1����������Ϊ1
	{
		for (int i=gap;i<N;i++)//i=gap���ӵ�һ��ĵڶ���Ԫ�ؿ�ʼ
		{
			int j = i-gap;
			temp = *(p + i);
			for (j = i - gap; j >= 0 && temp < *(p+j); j = j - gap)//ÿһ��Ԫ�ض���֮ǰ���ڵ�Ԫ�رȽϣ�˼����ֱ�Ӳ���������ͬ
			{
				*(p+j + gap) =*(p+j);
				count++;
			}
			*(p+j+gap) = temp;
			count++;
		}
		gap = gap / 2;//ÿһ��ѭ������gap����
	}
	end = clock();
	delete[]p;
	cout << "ϣ����������ʱ��:";
	cout << (double)(end-start) / 1000<<endl;
	cout << "ϣ�����򽻻�������";
	cout << count<<endl<<endl;
}
//��������
long long quick_sort(int left,int right,int*p)
{
	int count = 0;
	if (left<right)
	{
		int pivotpos = left;
		int pivot = *(p+left);//���±���С��λ��ֵ��Ϊ��׼
		for (int i=left+1;i<=right;i++)
		{
			if (*(p+i)<pivot)//��������Ҳ�ֵ�Ȼ�׼С�����
			{
				pivotpos++;//��׼ֵӦ�ŵ���λ�������ƶ�һλ
				if (pivotpos!=i)//������ֵ�����ڵ�ǰi��˵��ǰ���бȻ�׼ֵ������
				{
					int swap;//����iλ����pivotposλ�õ�ֵ���ñȻ�׼ֵ���ֵ�Ƶ��ұ�
					swap = *(p+pivotpos);
					*(p + pivotpos) = *(p + i);
					*(p + i) = swap;
					count++;
				}
			}
		}
		*(p + left) = *(p + pivotpos);//����׼ֵ�ŵ���Ӧλ����
		*(p + pivotpos) = pivot;
		quick_sort(left,pivotpos,p);//���εݹ麯��ʵ�ֿ�������
		quick_sort(pivotpos+1,right,p);
	}
	return count;//���ؼ�������ֵ
}
//�ѵĵ���
long long heap_adjust(int *p,int parent,int N)
{
	//parentλ��ֵ�����µ���
	int temp = *(p+parent);
	int child = parent * 2 + 1;
	int count = 0;
	while (child<N)
	{
		if (child + 1 < N && *(p+child) < *(p+child + 1)) //�������Ů�����ұ�����Ů��
		{
			child++;
		}
		if (temp >= *(p+child))//�����ǰ��ĸ��ֵ����Ů��ֵ������ѭ��
			break;
		*(p + parent) = *(p + child);
		count++;
		parent = child;//Ŀǰ��ʼparentֵӦ�ô�ŵ�λ��
		child = 2 * child + 1;
	}
	*(p + parent) = temp;//�����Ҫ����λ�õ�ֵ
	return count;
}
//������
long long heap_sort(int* p,int N,int* q)
{
	int count = 0;
	for (int i = N / 2; i >= 0; i--)//��ÿһ����Ҷ�ڵ���жѵ���
	{
		count=count+heap_adjust(p, i, N);
	}
	for (int i = N - 1; i > 0; i--) //����N-1��ѭ����ÿһ�ν���ʱ�ԶѶ�����жѵ�������ÿһ�ε����ֵ�����¿��ٵ�q������
	{
		int temp = *(p+i);
		*(q + i) = *p;
		*(p+i) = *p;
		*p = temp;
		count++;
		count=count+heap_adjust(p, 0, i);
	}
	*q = *p;//��Сֵ���q����ĵ�һ��λ��
	return count;
}
//�鲢����
void merge_sort(int* p,int* q,int start,int end,long long &count)
{
	if (start >= end)
		return ;
	int len = end - start, mid = len /2 + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	merge_sort(p, q, start1, end1,count);//���ϵݹ鵽�����ֻʣ��һ��ֵ
	merge_sort(p, q, start2, end2,count);
	int k = start;
	while (start1 <= end1 && start2 <= end2)//����ÿ���飬�ڲ��������Ѿ���ɵģ���Ҫ���αȽ��������ǰ��Ԫ�طŵ��µ�����q��
	{
		if (*(p + start1) < *(p + start2))
		{
			*(q + k) = *(p + start1);
			start1++;
		}
		else { 
			*(q + k) = *(p + start2);
			start2++;
		}
		count++;
		k++;
	}
	while (start1 <= end1)
	{
		*(q + k) = *(p + start1);
		k++;
		start1++;
		count++;
	}
	while (start2 <= end2)
	{
		*(q + k) = *(p + start2);
		k++;
		start2++;
		count++;
	}
	for (k = start; k <= end; k++)//���ݴ��q���ֵ���ظ�p
		*(p+k) = *(q+k);
}
//��������
void radix_sort(int* p,int N)
{
	int maxdigit=0,maxnum=*p;
	int* q = new int[N];
	for (int i=0;i<N;i++)
	{
		if (*(p + i) > maxnum) maxnum = *(p + i);
	}
	while (maxnum%10!=0)//ȷ�����ֵ��λ������ȷ����Ҫ���м���ѭ��
	{
		maxnum = maxnum/10;
		maxdigit++;
	}
	int place[10];//����0��9ʮ��Ͱ
	int radix = 1;//ͨ������radix����ȷ�����ڼ�λ����
	int i, j, k;
	for (i=0;i<maxdigit;i++)
	{
		for (j=0;j<10;j++)//�����Ȱ�ÿ��Ͱ��ֵ����
		{
			place[j] = 0;
		}
		for (j=0;j<N;j++)//��ÿһ��ֵ���࣬�ֵ���λ����ͬ��Ͱ��
		{
			int m=0;
			k=(p[j] / radix) % 10;
			place[k]++;
		}
		for (j=1;j<10;j++)//ͨ��ѭ������ÿһ��place��ֵ��¼��Ͱ������Ԫ�ض�Ӧ���±�λ��
		{
			place[j] = place[j - 1] + place[j];
		}
		for (j = N - 1; j >= 0; j--)//��ÿһ��Ͱ�е�ֵ���ظ��ݴ�����
		{
			k = (p[j] / radix) % 10;
			q[place[k] - 1] = p[j];
			place[k]--;
		}
		for (j=0;j<N;j++)//�ݴ������ֵ���ظ�ԭ����
		{
			p[j] = q[j];
		}
		radix = radix * 10;//ÿ��ѭ������10
	}
	delete[]q;
}
int main()
{
	cout << "**             �����㷨�Ƚ�             **"<<endl;
	cout << "=========================================="<<endl;
	cout << "**            1 ---ð������             **"<<endl;
	cout << "**            2 ---ѡ������             **"<<endl;
	cout << "**            3 ---ֱ�Ӳ�������         **"<<endl;
	cout << "**            4 ---ϣ������             **"<<endl;
	cout << "**            5 ---��������             **"<<endl;
	cout << "**            6 ---������               **"<<endl;
	cout << "**            7 ---�鲢����             **"<<endl;
	cout << "**            8 ---��������             **"<<endl;
	cout << "**            9 ---�˳�����             **"<<endl;
	cout << "=========================================="<<endl<<endl;
	cout << "������Ҫ������������ĸ�����";
	int N=0;
	cin >> N;
	cout << endl;
	int num;
	while (1)
	{
		cout << "��ѡ�������㷨:";
		cin >> num;
		switch (num) {
		case 1:
			bubble_sort(N);
			break;
		case 2:
			selection_sort(N);
			break;
		case 3:
			stright_insertion(N);
			break;
		case 4:
			shell_sort(N);
			break;
		case 5:
		{
			int* p = new int[N];
			srand(time(NULL));
			clock_t start, end;
			if (p == NULL)
			{
				cout << "�ڴ治��";
				exit(0);
			}
			for (int i = 0; i < N; i++)
			{
				*(p + i) = rand();
			}
			start = clock();
			int left = 0, right = N - 1;
			long long count = quick_sort(left, right, p);
			end = clock();
			cout << "������������ʱ�䣺";
			cout << (double)(end - start) / 1000 << endl;
			cout << "�������򽻻�������";
			cout << count << endl << endl;
			break;
		}
		case 6:
		{
			int* p = new int[N];
			srand(time(NULL));
			clock_t start, end;
			if (p == NULL)
			{
				cout << "�ڴ治��";
				exit(0);
			}
			for (int i = 0; i < N; i++)
			{
				*(p + i) = rand();
			}
			start = clock();
			int* q = new int[N];
			long long count = heap_sort(p, N, q);
			end = clock();
			delete[]p;
			delete[]q;
			cout << "����������ʱ�䣺";
			cout << (double)(end - start) / 1000 << endl;
			cout << "�����򽻻�������";
			cout << count << endl << endl;
			break;
		}
		case 7:
		{
			int* p = new int[N];
			srand(time(NULL));
			clock_t start, end;
			if (p == NULL)
			{
				cout << "�ڴ治��";
				exit(0);
			}
			for (int i = 0; i < N; i++)
			{
				*(p + i) = rand();
			}
			start = clock();
			int* q = new int[N];
			long long count = 0;
			merge_sort(p,q,0,N-1,count);
			end = clock();
			delete[]p;
			delete[]q;
			cout << "�鲢��������ʱ�䣺";
			cout << (double)(end - start) / 1000 << endl;
			cout << "�鲢���򽻻�������";
			cout << count << endl << endl;
			break;
		}
		case 8:
		{
			int* p = new int[N];
			srand(time(NULL));
			clock_t start, end;
			long long count = 0;
			if (p == NULL)
			{
				cout << "�ڴ治��";
				exit(0);
			}
			for (int i = 0; i < N; i++)
			{
				*(p + i) = rand();
			}
			start = clock();
			radix_sort(p,N);
			end = clock();
			cout << "������������ʱ�䣺";
			cout << (double)(end - start) / 1000 << endl;
			cout << "�������򽻻�������";
			cout << count << endl << endl;
			delete[]p;
			break;
		}
		case 9:
			system("pause");
			exit(0);
		}
	}
	return 0;
}