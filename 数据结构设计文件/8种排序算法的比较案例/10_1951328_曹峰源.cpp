#include <iostream>
#include <ctime>
using namespace std;
//冒泡排序
void bubble_sort(int N)
{
	clock_t start, end;//定义时间量用于计算排序程序前后所用时间
	int* p = new int[N];//开辟动态数组
	srand(time(NULL));//利用时间设置产生随机数防止每一次程序运行产生的随机数相同
	if (p==NULL)//如果内存不够开辟失败的情况
	{
		cout << "内存不足";
		exit(0);
	}
	for (int i=0;i<N;i++)//产生随机数
	{
		*(p + i) = rand();
	}
	start = clock();
	int temp = 0;
	long long count = 0;
	for (int i=0;i<N-1;i++)//冒泡排序循环，一共进行N-1次，每一次都将未排序序列中最大的数通过交换放到数组的最后，这样经过N-1次后排序成功
	{
		for (int j=0;j<N-1-i;j++)
		{
			if (*(p+j)>*(p+j+1))
			{
				temp = *(p + j);
				*(p + j) = *(p + j + 1);
				*(p + j + 1) = temp;
				count++;//每次交换计数器增加一次
			}
		}
	}
	end = clock();
	delete[]p;//释放数组空间
	cout << "冒泡排序所用时间：";
	cout << (double)(end - start)/1000<<endl;
	cout << "冒泡排序交换次数：";
	cout << count<<endl<<endl;
}
//选择排序
void selection_sort(int N)
{
	clock_t start, end;
	int* p = new int[N];//建立动态数组
	srand(time(NULL));
	if (p == NULL)
	{
		cout << "内存不足";
		exit(0);
	}
	for (int i=0;i<N;i++)
	{
		*(p + i) = rand();
	}
	start = clock();
	int temp;
	long long count = 0;
	for (int i=0;i<N-1;i++)//一共经过N-1次循环，与冒泡排序相似，不同的是冒泡是通过交换来实现最大的数放到数组最后，选择排序是每一次找出最大的数
	{
		temp = 0;
		for (int j=0;j<N-i-1;j++)//通过二级循环找出未排序序列中最大的数
		{
			if (*(p+temp)<*(p+j+1))
			{
				temp = j + 1;
				count++;
			}
		}
		int wrap = 0;//将其交换到数组的最后位置
		wrap = *(p+N-1-i);
		*(p + N-1 - i) = *(p+temp);
		*(p + temp) = wrap;
		count++;//每一次交换计数器增加一次
	}
	end = clock();
	delete[]p;
	cout << "选择排序所用时间：";
	cout << (double)(end - start)/1000<<endl;
	cout << "选择排序交换次数：";
	cout << count<<endl<<endl;
}
//直接插入排序
void stright_insertion(int N)
{
	clock_t start, end;
	int* p = new int[N];
	srand(time(NULL));
	if (p == NULL)
	{
		cout << "内存不足";
		exit(0);
	}
	for (int i = 0; i < N; i++)
	{
		*(p + i) = rand();
	}
	start = clock();
	int temp;
	long long count = 0;
	for (int i=1;i<N;i++)//一共经过N-1次循环，从数组的第二个位置开始循环，将其插入到前面的符合升序要求的位置
	{
		int temp = *(p+i);
		int j = i;
		while (temp<*(p+j-1)&&j>0)//通过循环与前面已经排好的位置比较，直到插入到对应的位置
		{
			*(p +j) = *(p + j - 1);
			count++;//每次交换计数器加1
			j--;
		}
		*(p + j) = temp;
		count++;
	}
	end = clock();
	delete[]p;
	cout << "直接插入排序所用时间：";
	cout << (double)(end-start)/1000<<endl;
	cout << "直接插入排序交换次数：";
	cout << count<<endl<<endl;
}
//希尔排序
void shell_sort(int N)
{
	clock_t start, end;
	int* p = new int[N];
	srand(time(NULL));
	if (p == NULL)
	{
		cout << "内存不足";
		exit(0);
	}
	for (int i = 0; i < N; i++)
	{
		*(p + i) = rand();
	}
	start = clock();
	int gap = N / 2, temp = 0;
	long long count = 0;//初始化定义跨度为N/2
	while (gap>=1)//跳出循环的条件为gap变为1，即组数变为1
	{
		for (int i=gap;i<N;i++)//i=gap，从第一组的第二个元素开始
		{
			int j = i-gap;
			temp = *(p + i);
			for (j = i - gap; j >= 0 && temp < *(p+j); j = j - gap)//每一个元素都与之前组内的元素比较，思想与直接插入排序相同
			{
				*(p+j + gap) =*(p+j);
				count++;
			}
			*(p+j+gap) = temp;
			count++;
		}
		gap = gap / 2;//每一次循环过后gap减半
	}
	end = clock();
	delete[]p;
	cout << "希尔排序所用时间:";
	cout << (double)(end-start) / 1000<<endl;
	cout << "希尔排序交换次数：";
	cout << count<<endl<<endl;
}
//快速排序
long long quick_sort(int left,int right,int*p)
{
	int count = 0;
	if (left<right)
	{
		int pivotpos = left;
		int pivot = *(p+left);//以下标最小的位置值作为基准
		for (int i=left+1;i<=right;i++)
		{
			if (*(p+i)<pivot)//如果出现右侧值比基准小的情况
			{
				pivotpos++;//基准值应放到的位置向右移动一位
				if (pivotpos!=i)//如果这个值不等于当前i，说明前面有比基准值大的情况
				{
					int swap;//交换i位置与pivotpos位置的值，让比基准值大的值移到右边
					swap = *(p+pivotpos);
					*(p + pivotpos) = *(p + i);
					*(p + i) = swap;
					count++;
				}
			}
		}
		*(p + left) = *(p + pivotpos);//将基准值放到对应位置上
		*(p + pivotpos) = pivot;
		quick_sort(left,pivotpos,p);//两次递归函数实现快速排序
		quick_sort(pivotpos+1,right,p);
	}
	return count;//返回计数器的值
}
//堆的调整
long long heap_adjust(int *p,int parent,int N)
{
	//parent位置值的向下调整
	int temp = *(p+parent);
	int child = parent * 2 + 1;
	int count = 0;
	while (child<N)
	{
		if (child + 1 < N && *(p+child) < *(p+child + 1)) //如果右子女存在且比左子女大
		{
			child++;
		}
		if (temp >= *(p+child))//如果当前父母的值比子女的值大跳出循环
			break;
		*(p + parent) = *(p + child);
		count++;
		parent = child;//目前初始parent值应该存放的位置
		child = 2 * child + 1;
	}
	*(p + parent) = temp;//存放需要调整位置的值
	return count;
}
//堆排序
long long heap_sort(int* p,int N,int* q)
{
	int count = 0;
	for (int i = N / 2; i >= 0; i--)//对每一个非叶节点进行堆调整
	{
		count=count+heap_adjust(p, i, N);
	}
	for (int i = N - 1; i > 0; i--) //进行N-1次循环，每一次结束时对堆顶点进行堆调整，将每一次的最大值存入新开辟的q数组中
	{
		int temp = *(p+i);
		*(q + i) = *p;
		*(p+i) = *p;
		*p = temp;
		count++;
		count=count+heap_adjust(p, 0, i);
	}
	*q = *p;//最小值存进q数组的第一个位置
	return count;
}
//归并排序
void merge_sort(int* p,int* q,int start,int end,long long &count)
{
	if (start >= end)
		return ;
	int len = end - start, mid = len /2 + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	merge_sort(p, q, start1, end1,count);//不断递归到达分组只剩下一个值
	merge_sort(p, q, start2, end2,count);
	int k = start;
	while (start1 <= end1 && start2 <= end2)//对于每个组，内部排序是已经完成的，需要依次比较两个组的前置元素放到新的数组q中
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
	for (k = start; k <= end; k++)//把暂存的q里的值返回给p
		*(p+k) = *(q+k);
}
//基数排序
void radix_sort(int* p,int N)
{
	int maxdigit=0,maxnum=*p;
	int* q = new int[N];
	for (int i=0;i<N;i++)
	{
		if (*(p + i) > maxnum) maxnum = *(p + i);
	}
	while (maxnum%10!=0)//确定最大值的位数，来确定需要进行几次循环
	{
		maxnum = maxnum/10;
		maxdigit++;
	}
	int place[10];//创建0到9十个桶
	int radix = 1;//通过除以radix余数确定按第几位分类
	int i, j, k;
	for (i=0;i<maxdigit;i++)
	{
		for (j=0;j<10;j++)//首先先把每个桶的值清零
		{
			place[j] = 0;
		}
		for (j=0;j<N;j++)//对每一个值分类，分到该位数相同的桶中
		{
			int m=0;
			k=(p[j] / radix) % 10;
			place[k]++;
		}
		for (j=1;j<10;j++)//通过循环，让每一个place的值记录该桶中最后的元素对应的下标位置
		{
			place[j] = place[j - 1] + place[j];
		}
		for (j = N - 1; j >= 0; j--)//将每一个桶中的值返回给暂存数组
		{
			k = (p[j] / radix) % 10;
			q[place[k] - 1] = p[j];
			place[k]--;
		}
		for (j=0;j<N;j++)//暂存数组的值返回给原数组
		{
			p[j] = q[j];
		}
		radix = radix * 10;//每次循环乘以10
	}
	delete[]q;
}
int main()
{
	cout << "**             排序算法比较             **"<<endl;
	cout << "=========================================="<<endl;
	cout << "**            1 ---冒泡排序             **"<<endl;
	cout << "**            2 ---选择排序             **"<<endl;
	cout << "**            3 ---直接插入排序         **"<<endl;
	cout << "**            4 ---希尔排序             **"<<endl;
	cout << "**            5 ---快速排序             **"<<endl;
	cout << "**            6 ---堆排序               **"<<endl;
	cout << "**            7 ---归并排序             **"<<endl;
	cout << "**            8 ---基数排序             **"<<endl;
	cout << "**            9 ---退出程序             **"<<endl;
	cout << "=========================================="<<endl<<endl;
	cout << "请输入要产生的随机数的个数：";
	int N=0;
	cin >> N;
	cout << endl;
	int num;
	while (1)
	{
		cout << "请选择排序算法:";
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
				cout << "内存不足";
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
			cout << "快速排序所用时间：";
			cout << (double)(end - start) / 1000 << endl;
			cout << "快速排序交换次数：";
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
				cout << "内存不足";
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
			cout << "堆排序所用时间：";
			cout << (double)(end - start) / 1000 << endl;
			cout << "堆排序交换次数：";
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
				cout << "内存不足";
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
			cout << "归并排序所用时间：";
			cout << (double)(end - start) / 1000 << endl;
			cout << "归并排序交换次数：";
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
				cout << "内存不足";
				exit(0);
			}
			for (int i = 0; i < N; i++)
			{
				*(p + i) = rand();
			}
			start = clock();
			radix_sort(p,N);
			end = clock();
			cout << "基数排序所用时间：";
			cout << (double)(end - start) / 1000 << endl;
			cout << "基数排序交换次数：";
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