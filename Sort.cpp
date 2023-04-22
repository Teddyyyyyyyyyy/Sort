#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<iostream>
using namespace std;
//1.ֱ�Ӳ�������ֱ�Ӳ���������ǰѴ������Ԫ��������뵽һ���Ѿ��ź�������������У�ֱ�����еļ�¼������Ϊֹ���õ�һ���µ��������У�ʵ�����������˿���ʱ�������˲��������˼�룩
void InsertSort(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		//���˲�������
		//[0,end]����ֵΪ����
		int end = i;
		int tmp = arr[end + 1];
		while (end >= 0)
		{
			if (tmp < arr[end])
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else
			{
				break;//������break��ȥ��ȥ��ֵtmp��Ϊ�˷�ֹ���һ��end = -1��������ֵ
			}
		}
		arr[end + 1] = tmp;
	}
}
//2.ϣ������ϣ�������Ƕ�ֱ�Ӳ���������Ż������������Ƚ��ж��Ԥ����ʹ֮�ӽ�������Ϊ���ӽ�����ʹ��ֱ�Ӳ�������ǳ��죩
void ShellSort(int* arr, int size)
{
	int gap = size;//���Ԥ��+���һ��ֱ�Ӳ�������
	while (gap > 1)
	{
		gap = gap / 3 + 1;//�������һ�ν���gapΪ1����ֱ�Ӳ�������
		for (int i = 0; i < size - gap; i++)
		{
			int end = i;
			int tmp = arr[end + gap];
			while (end >= 0)
			{
				if (tmp < arr[end])
				{
					arr[end + gap] = arr[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			arr[end + gap] = tmp;
		}
	}
}
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//3.ѡ������ѡ��������δ�����������ҵ���С����Ԫ�أ���ŵ��������е���ʼλ�ã�Ȼ���Դ����ƣ�ֱ������Ԫ�ؾ�������ϣ�
void SelectSort(int* arr, int size)//�Ż�ѡ������
{
	int begin = 0;
	int end = size - 1;
	while (begin < end)
	{
		int mini = begin, maxi = begin;
		for (int i = begin + 1; i <= end; i++)
		{
			if (arr[i] < arr[mini])
			{
				mini = i;
			}
			if (arr[i] > arr[maxi])
			{
				maxi = i;
			}
		}
		Swap(&arr[mini], &arr[begin]);
		//���maxi = begin����һ��������begin��mini��ֵ����Ӱ��maxiָ���ֵ
		if (maxi == begin)
		{
			maxi = mini;
		}
		Swap(&arr[maxi], &arr[end]);
		begin++;
		end--;
	}
}
//4.ð������ð������Ҳ��ͨ�������Ƚ�����ֵ�ô�С��������������ֵ������ֵ������������ֵ���ŵ����ұߣ�
//ð�������Ż�(1�����Ѿ�����ú�ֱ�������������˺�������ñȽ� 2�������˱Ƚϴ�������ÿһ�ֵ����һ�ν����õ����һ�ν�������bounddar1����ȷ���Ƚ����ݵı߽磬
//֮��Ĵ�������Ƚ����̱Ƚϴ���������
void BubbleSort(int* arr, int size)
{
	int t;
	for (int i = 0; i < size - 1; i++)
	{
		bool rb = true;
		int boundary1 = size - 1;
		int boundary = 0;
		for (int j = 0; j < boundary1; j++) {
			if (arr[j] > arr[j + 1]) {
				t = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = t;
				rb = false;
				boundary = j;
			}
		}
		boundary1 = boundary;
		if (rb) {
			break;
		}
	}
}
//5.�鲢���򣨹鲢����������������кϲ����õ���ȫ��������У�����ʹÿ��������������ʹ�����жμ������������������ϲ���һ���������Ϊ��·�鲢��
void _MergeSort(int* arr, int begin, int end, int* tmp)
{
	if (begin >= end)
	{
		return;
	}

	//�ݹ�����������
	int mid = (end + begin) / 2;
	//[begin, mid][mid+1,end]
	_MergeSort(arr, begin, mid, tmp);
	_MergeSort(arr, mid + 1, end, tmp);

	//��������鲢����
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] <= arr[begin2])
		{
			tmp[i++] = arr[begin1++];
		}
		else
		{
			tmp[i++] = arr[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[i++] = arr[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[i++] = arr[begin2++];
	}

	//��������tmp�����ݷ��ؿ�����ԭ����
	memcpy(arr + begin, tmp + begin, (end - begin + 1) * sizeof(int));
}

void MergeSort(int* arr, int size)//�鲢����
{
	int* tmp = (int*)malloc(sizeof(int) * size);
	if (tmp == NULL)
	{
		perror("malloc:fail");
		exit(-1);
	}
	int begin = 0;
	int end = size - 1;
	_MergeSort(arr, begin, end, tmp);
}
//6.��������ͳ����ͬԪ�س��ִ��� ����ͳ�ƵĽ�������л��յ�ԭ���������� ��������ֻ�����ڷ�Χ�������ظ����ݽϸߵ����ݣ�
//��������ֻ�����ڷ�Χ�������ظ����ݽϸߵ�����
void CountSort(int* arr, int size)//��������
{
	int min = arr[0];
	int max = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	//��������count
	int range = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * range);
	if (count == NULL)
	{
		perror("malloc:fail");
		exit(-1);
	}
	memset(count, 0, sizeof(int) * range);

	//��ʼ����
	for (int i = 0; i < size; i++)
	{
		count[arr[i] - min]++;
	}

	//��д����
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (count[i]--)
		{
			arr[j++] = i + min;
		}
	}
}

//7.�������򣨿��������Ƕ�ð�������㷨��һ�ָĽ���ͬð������һ������������Ҳ���ڽ�������ͨ��Ԫ��֮��ıȽϺͽ���λ�����ﵽ�����Ŀ�ġ�
//��ͬ���ǣ�ð��������ÿһ��ֻ��һ��Ԫ��ð�ݵ����е�һ�ˣ�������������ÿһ����ѡһ����׼Ԫ�أ����������������Ԫ���ƶ�������һ�ߣ�
//����С��Ԫ���ƶ������е���һ�ߣ��Ӷ������в������������֣�����˼·�ͽ������η�����
void Quick_Sort(int* arr, int begin, int end) {
	if (begin > end)
		return;
	int tmp = arr[begin];
	int i = begin;
	int j = end;
	while (i != j) {
		while (arr[j] >= tmp && j > i)
			j--;
		while (arr[i] <= tmp && j > i)
			i++;
		if (j > i) {
			int t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}
	arr[begin] = arr[i];
	arr[i] = tmp;
	Quick_Sort(arr, begin, i - 1);
	Quick_Sort(arr, i + 1, end);
}
//8.������
//�ڶ������㷨�У�����ʹ�õ������ѡ�����Ĵ����Ǹ���һ����������һ�����ѡ�left(heap, location)��right(heap, location)�ֱ𷵻�����heap��location�����Һ��ӵ�������
//max_heapify(heap, i)��ȷ��heap�����i�����Һ��Ӷ��������ѻ���bulid_max_heap(heap)��heap���鹹��һ�����ѡ�heapsort(heap)�Ƕ�heap���ѽ�������



/*
����һ��NUM�������ѣ�
*/
#include<iostream>
#include<ctime>
using namespace std;

const int NUM = 10;
int HEAPNUM = NUM;

void print(int p[], int n)
{
	for (int i = 1; i <= n; i++)
	{
		cout << "heap[" << i << "] = " << p[i] << endl;
	}
}

int left(int heap[], int i)
{
	return 2 * i;
}

int right(int heap[], int i)
{
	return 2 * i + 1;
}

void max_heapify(int heap[], int location)
{
	int largest = 0, l, r, temp;
	l = left(heap, location);
	r = right(heap, location);

	if (l <= HEAPNUM && heap[l] > heap[location])
	{
		largest = l;
	}
	else
		largest = location;
	if (r <= HEAPNUM && heap[r] > heap[largest])
	{
		largest = r;
	}
	if (location != largest)
	{
		temp = heap[location];
		heap[location] = heap[largest];
		heap[largest] = temp;
		max_heapify(heap, largest);
	}
}

void bulid_max_heap(int heap[])
{
	//Ҷ�ӽڵ㲻��max_heapify�������ǽڵ�����һ��
	for (int i = NUM / 2; i >= 1; i--)
	{
		max_heapify(heap, i);
	}
}

void heapsort(int heap[])
{
	int temp = 0;
	for (int i = NUM; i >= 2; i--)
	{
		temp = heap[i];
		heap[i] = heap[1];
		heap[1] = temp;
		HEAPNUM = HEAPNUM - 1;
		max_heapify(heap, 1);
	}
}

int main()
{
	int heap[NUM + 1] = { 0 };
	srand(time(NULL));
	for (int i = 1; i <= NUM; i++)
	{
		heap[i] = rand() % 100;
	}
	cout << "-------------random number is: " << endl;
	print(heap, NUM);
	bulid_max_heap(heap);
	cout << "-------------max heap is: " << endl;
	print(heap, NUM);
	heapsort(heap);
	cout << "-------------sort number is: " << endl;
	print(heap, NUM);
	return 0;
}