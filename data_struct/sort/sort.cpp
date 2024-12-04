#include <bits/stdc++.h>
using namespace std;

template <class T>
/// @brief 插入元素
/// @param e 待插入元素
/// @param a 数组
/// @param i 记录个数
void Insert(const T &e, T *a, int i)
{
	a[0] = e;		 // 数据从1开始
	while (e < a[i]) // 从后往前找到插入位置
	{
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

template <class T>
/// @brief 插入排序
/// @param a 数组
/// @param n 数组长度
void InsertSort(T *a, const int n)
{
	for (int i = 2; i <= n; i++)
	{
		T temp = a[i];			// 待插入元素 从2 ~ n
		Insert(temp, a, i - 1); // 插入 从1 ~ n-1
	}
}

template <class T>
/// @brief 快速排序
/// @param a 数组
/// @param low 低位
/// @param high 高位
void QuickSort(T *a, const int low, const int high)
{
	if (low < high)
	{
		int i = low, j = high + 1;
		T temp = a[low];
		while (i < j) // 第一个左边不小于temp，右边不大于temp
		{
			do
				i++;
			while (a[i] < temp && i <= high);
			do
				j--;
			while (a[j] > temp && j >= low);
			if (i < j)
				swap(a[i], a[j]);
		}
		swap(a[low], a[j]);
		for (int k = 0; k < 9; k++)
			cout << a[k] << " ";
		cout << "i=" << i << " j=" << j;
		cout << endl;
		QuickSort(a, low, j - 1);
		QuickSort(a, j + 1, high);
	}
}

template <class T>
/// @brief 归并排序
class MergeSort
{
private:
	/// @brief 合并两个有序数组
	/// @param a 数组
	/// @param aBegin 开始位置
	/// @param mid 中间位置
	/// @param bEnd 结束位置
	void static merge(T *a, size_t aBegin, size_t mid, size_t bEnd)
	{
		size_t i = aBegin, j = mid + 1, k = 0;
		T *temp = new T[bEnd - aBegin + 1];
		while (i <= mid && j <= bEnd)
		{
			if (a[i] < a[j])
				temp[k++] = a[i++];
			else
				temp[k++] = a[j++];
		}
		copy(a + i, a + mid + 1, temp + k);
		copy(a + j, a + bEnd + 1, temp + k);
		copy(temp, temp + bEnd - aBegin + 1, a + aBegin);
	}

public:
	/// @brief 归并排序
	/// @param a 数组
	/// @param begin 开始位置
	/// @param end 结束位置
	void static mergeSort(T *a, size_t begin, size_t end)
	{
		if (begin < end)
		{
			size_t mid = (begin + end) / 2;
			mergeSort(a, begin, mid);
			mergeSort(a, mid + 1, end);
			merge(a, begin, mid, end);
		}
	}
};

template <class T>
/// @brief 堆排序
class HeapSort
{
private:
	/// @brief 调整节点root的位置
	/// @param a 数组
	/// @param i 调整位置
	/// @param n 数组长度
	void static adjust(T *a, size_t root, size_t n)
	{
		// 标程的交换次数少，速度快
		T parent = a[root];
		size_t j = 2 * root;
		for (; j <= n; j *= 2)
		{
			if (j < n && a[j] < a[j + 1])
				j++;
			if (parent >= a[j])
				break;
			a[j / 2] = a[j];
		}
		a[j / 2] = parent;
	}

public:
	/// @brief 堆排序
	/// @param a 数组
	/// @param n 数组长度
	void static heapSort(T *a, size_t n)
	{
		for (size_t i = n / 2; i > 0; i--)
			adjust(a, i, n);
		for (size_t i = n; i > 1; i--)
		{
			swap(a[1], a[i]);
			adjust(a, 1, i - 1);
		}
	}
};

template <class T>
/// @brief 基数排序
class RadixSort
{
private:
	/// @brief 提取数字的第 position 位（从右到左），基于 radix 进制
	/// @param number 数字
	/// @param position 位数
	/// @param radix 进制
	int static digit(int number, int position, int radix)
	{
		return (number / static_cast<int>(pow(radix, position))) % radix;
	}

public:
	/// @brief 基数排序
	/// @param a 数组
	/// @param d 位数
	/// @param r 进制
	/// @param n 数组长度
	void static radixSort(T *a, const int d, const int r, const int n)
	{
		int link[n];
		int f[r], e[r]; // f[i]指向第i个桶的第一个元素，e[i]指向第i个桶的最后一个元素
		for (int i = 0; i < n; i++)
			link[i] = i + 1;
		link[n - 1] = -1;
		int first = 0;
		for (int i = 0; i < d; i++)
		{
			fill(f, f + r, -1);
			// 按第i位数字分配到桶中
			for (int current = first; current != -1; current = link[current])
			{
				int k = digit(a[current], i, r);
				if (f[k] == -1)
					f[k] = current;
				else
					link[e[k]] = current;
				e[k] = current;
			}
			// 找到第一个非空桶的首尾元素
			int j = 0;
			while (f[j] == -1)
				j++;
			first = f[j];
			int last = e[j];
			// 将各个桶中的元素串联起来
			for (int k = j + 1; k < r; k++)
			{
				if (f[k] != -1)
				{
					link[last] = f[k];
					last = e[k];
				}
			}
			// 串联最后一个桶
			link[last] = -1;
		}
		T temp[n];
		int cnt = 0;
		for (int i = first; i != -1; i = link[i])
			temp[cnt++] = a[i];
		copy(temp, temp + n, a);
	}
	/// @brief 更短的基数排序
	/// @param a 数组
	/// @param d 位数
	/// @param r 进制
	/// @param n 数组长度
	void static shortRadixSort(T *a, int d, int r, int n)
	{
		for (int i = 0; i < d; i++)
		{
			int cnt[r] = {0};
			for (int j = 0; j < n; j++)
				cnt[digit(a[j], i, r)]++;
			for (int j = 1; j < r; j++)
				cnt[j] += cnt[j - 1];
			T b[n] = {0};
			for (int j = n - 1; j >= 0; j--)
				b[--cnt[digit(a[j], i, r)]] = a[j];
			copy(b, b + n, a);
		}
	}
};

signed main()
{
	int a[9] = {49, 38, 65, 97, 76, 13, 27, 49, 55};
	// RadixSort<int>::test_sort(a, 2, 10, 9);
	RadixSort<int>::radixSort(a, 2, 10, 9);
	for (int i = 0; i < 9; i++)
		cout << a[i] << " ";
}