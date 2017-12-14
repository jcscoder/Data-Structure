// 堆.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

typedef int ElemType;/* 堆存储的元素类型 ElementType of the (Min)Heap */

typedef struct HNode *PtrToHNode;
struct HNode {
	ElemType *Data;/* Dates in the heap */
	int Size; 
	int Capacity;
};
typedef PtrToHNode Heap;

Heap CreateHeap(int Max_Size)
{	/* 返回空堆 Returns an empty heap with a capacity of Max_Size */
	Heap H = (Heap)malloc(sizeof(struct HNode));
	H->Data = (ElemType*)malloc((Max_Size + 1) * sizeof(ElemType)); /* array of Max_Size + 1 */
	H->Size = 0;
	H->Capacity = Max_Size;
	H->Data[0] = -1; /* 定义哨兵 < 所有元素. Data[0] < all elements in the heap */
	return H;
}

void Insert(Heap H, ElemType item)
{	/* 插入元素 Inserts an element into the heap */
	int i;
	if (H->Size == H->Capacity) {
		cout << "堆满";
		return;
	}
	i = ++H->Size;
	for (; H->Data[i / 2] > item; i /= 2) 
		H->Data[i] = H->Data[i / 2];
	H->Data[i] = item;
}

ElemType DeleteMin(Heap H)
{	/* 删除并返回堆顶最小元素 Deletes and returns the minimum element in the heap */
	int Parent, Child;
	int min = H->Data[1];
	int X = H->Data[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;//Left Child
		if (Child != H->Size && H->Data[Child + 1] < H->Data[Child])//Right child exists && right child < left child
			Child++; //Change "Child" to right child
		if (X <= H->Data[Child])
			break;
		H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
	return min;
}

int main()
{
	int N;
	cin >> N;
	Heap H = CreateHeap(N);
	for (int i = 0; i < N; i++)
		Insert(H, rand());
	for (int i = 0; i < N; i++)
		cout << DeleteMin(H) << "\n";
    return 0;
}

