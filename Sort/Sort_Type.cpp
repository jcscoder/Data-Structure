// Sort_Type.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
void swap(ElemType *a, ElemType *b) {
	ElemType temp = *a;
	*a = *b;
	*b = temp;
}
/* 排序函数接口 */
/* 冒泡排序 */
void Bubble_Sort(ElemType arr[], int N) {
	for (int p = 0; p < N; p++) {
		int flag = 0;
		for (int i = 0; i < N - p - 1; i++) 
			if (arr[i] > arr[i + 1]) {
				swap(arr + i, arr + i + 1);//swap arr[i]&arr[i + 1]
				flag = 1;
			}
		if (flag == 0)
			break;
	}
}

/* 插入排序 */
void Insertion_Sort(ElemType arr[], int N) {
	for (int p = 1; p < N; p++) {
		ElemType temp = arr[p];
		int i;
		for (i = p; i > 0 && arr[i - 1] > temp; i--)
			arr[i] = arr[i - 1];
		arr[i] = temp;
	}
}

/* 希尔排序 */
void Shell_Sort(ElemType arr[], int N) {
	int Si, D;
	int Sedgewick[] = {        // Sedgewick增量  
		1073643521, 603906049, 268386305, 150958081, 67084289,
		37730305, 16764929, 9427969, 4188161, 2354689,
		1045505, 587521, 260609, 146305, 64769,
		36289, 16001, 8929, 3905, 2161,
		929, 505, 209, 109, 41,
		19, 5, 1, 0 };   
	for (Si = 0; Sedgewick[Si] >= N; Si++)
		;
	for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si]) {
		for (int p = D; p < N; p += D) {
			ElemType temp = arr[p];
			int i;
			for (i = p; i > 0 && arr[i - D] > temp; i -= D)
				arr[i] = arr[i - D];
			arr[i] = temp;
		}
	}
}

/* 堆排序 */
/* 在有N个元素的数组中找到arr[p]在以arr[p]为根的子堆(最大堆)中的位置 */
void PercDown(ElemType arr[], int p, int N) {
	ElemType Item = arr[p];
	int Parent, Child;
	for (Parent = p; Parent * 2 + 1 < N; Parent = Child) {
		Child = Parent * 2 + 1;//左孩子
		if ((Child != N - 1) && (arr[Child + 1] > arr[Child]))//右孩子存在&&右孩子的值>左孩子
			Child++;//Child更新为右孩子
		if (Item >= arr[Child])
			break;
		arr[Parent] = arr[Child];
	}
	arr[Parent] = Item;
}

void Heap_Sort(ElemType arr[], int N) {
	for (int i = N/2 - 1; i >= 0; i--)//建立最大堆
		PercDown(arr, i, N);
	for (int i = N - 1; i > 0; i--) {
		swap(&arr[0], &arr[i]);
		PercDown(arr, 0, i);
	}
}

/* 归并排序 */

void Merge(ElemType arr[], ElemType temp[], int L, int R, int REnd) {
	int LEnd = R - 1;
	int i = L, j = R;
	int count = L;
	while (i <= LEnd && j <= REnd) {
		if (arr[i] <= arr[j])
			temp[count++] = arr[i++];
		else
			temp[count++] = arr[j++];
	}
	while (i <= LEnd)
		temp[count++] = arr[i++];
	while (j <= REnd)
		temp[count++] = arr[j++];
	for (int k = L; k <=REnd; k++)
		arr[k] = temp[k];
}

void Msort(ElemType arr[], ElemType temp[], int L, int R) {
	int Center = (L + R) / 2;
	if (L < R) {
		Msort(arr, temp, L, Center);
		Msort(arr, temp, Center + 1, R);
		Merge(arr, temp, L, Center + 1, R);
	}
}

void Merge_Sort(ElemType arr[], int N) {
	ElemType * temp = (ElemType *)malloc(N * sizeof(ElemType));
	if (temp != NULL) {
		Msort(arr, temp, 0, N - 1);
		free(temp);
	}
}

/* 主函数 */
int main()
{
	ElemType N;
	scanf_s("%d", &N);
	ElemType *arr = (ElemType *)malloc(N * sizeof(ElemType));
	for (int i = 0; i < N; i++)
		scanf_s("%d", arr + i);
	//排序
	//Bubble_Sort(arr, N);
	//Insertion_Sort(arr, N);
	//Shell_Sort(arr, N);
	//Heap_Sort(arr, N);
	Merge_Sort(arr, N);
	//输出
	for (int i = 0; i < N - 1; i++)
		printf("%d ", arr[i]);
	printf("%d", arr[N - 1]);
    return 0;
}

