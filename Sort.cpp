#include<stdio.h>
#include<cstring>
#include<stdlib.h>
#include<iostream>
using namespace std;
//1.直接插入排序（直接插入排序就是把待排序的元素逐个插入到一个已经排好序的有序序列中，直到所有的记录插入完为止，得到一个新的有序序列，实际中我们玩扑克牌时，就用了插入排序的思想）
void InsertSort(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		//单趟插入排序
		//[0,end]区间值为有序
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
				break;//在这里break出去再去赋值tmp是为了防止最后一次end = -1进不来赋值
			}
		}
		arr[end + 1] = tmp;
	}
}
//2.希尔排序（希尔排序是对直接插入排序的优化，它对序列先进行多次预排序使之接近有序，因为最后接近有序使用直接插入排序非常快）
void ShellSort(int* arr, int size)
{
	int gap = size;//多次预排+最后一次直接插入排序
	while (gap > 1)
	{
		gap = gap / 3 + 1;//控制最后一次进来gap为1进行直接插入排序
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
//3.选择排序（选择排序在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后以此类推，直到所有元素均排序完毕）
void SelectSort(int* arr, int size)//优化选择排序
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
		//如果maxi = begin，上一步交换了begin和mini的值，会影响maxi指向的值
		if (maxi == begin)
		{
			maxi = mini;
		}
		Swap(&arr[maxi], &arr[end]);
		begin++;
		end--;
	}
}
//4.冒泡排序（冒泡排序也是通过遍历比较左右值得大小，例如排升序即左值大于右值交换，最后最大值即排到最右边）
//冒泡排序优化(1：在已经排序好后直接输出结果减少了后面的无用比较 2：减少了比较次数，由每一轮的最后一次交换得到最后一次交换次数bounddar1用其确定比较数据的边界，
//之后的次数无需比较缩短比较次数操作）
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
//5.归并排序（归并排序将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为二路归并）
void _MergeSort(int* arr, int begin, int end, int* tmp)
{
	if (begin >= end)
	{
		return;
	}

	//递归找有序区间
	int mid = (end + begin) / 2;
	//[begin, mid][mid+1,end]
	_MergeSort(arr, begin, mid, tmp);
	_MergeSort(arr, mid + 1, end, tmp);

	//左右区间归并有序
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

	//辅助数组tmp中数据返回拷贝到原数组
	memcpy(arr + begin, tmp + begin, (end - begin + 1) * sizeof(int));
}

void MergeSort(int* arr, int size)//归并排序
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
//6.计数排序（统计相同元素出现次数 根据统计的结果将序列回收到原来的序列中 计数排序只适用于范围集中且重复数据较高的数据）
//计数排序只适用于范围集中且重复数据较高的数据
void CountSort(int* arr, int size)//计数排序
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

	//计数数组count
	int range = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * range);
	if (count == NULL)
	{
		perror("malloc:fail");
		exit(-1);
	}
	memset(count, 0, sizeof(int) * range);

	//开始计数
	for (int i = 0; i < size; i++)
	{
		count[arr[i] - min]++;
	}

	//回写排序
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (count[i]--)
		{
			arr[j++] = i + min;
		}
	}
}

//7.快速排序（快速排序是对冒泡排序算法的一种改进，同冒泡排序一样，快速排序也属于交换排序，通过元素之间的比较和交换位置来达到排序的目的。
//不同的是，冒泡排序在每一轮只把一个元素冒泡到数列的一端，而快速排序在每一轮挑选一个基准元素，并让其他比它大的元素移动到数列一边，
//比它小的元素移动到数列的另一边，从而把数列拆解成了两个部分，这种思路就叫做分治法。）
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
//8.推排序
//在堆排序算法中，我们使用的是最大堆。下面的代码是给定一组数，构造一个最大堆。left(heap, location)和right(heap, location)分别返回数组heap中location的左右孩子的索引。
//max_heapify(heap, i)是确保heap数组的i的左右孩子都满足最大堆化。bulid_max_heap(heap)将heap数组构造一个最大堆。heapsort(heap)是对heap最大堆进行排序。



/*
构造一个NUM个数最大堆；
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
	//叶子节点不用max_heapify，所以是节点数的一半
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