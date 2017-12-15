// HuffmanTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

/* 定义Huffman树结点 */
typedef struct TNode *HTree;
struct TNode {
	char Data;
	int Weight; /* 权重 */
	HTree Left, Right;
};

/* 建立Huffman树 */
/* 定义存储树结点的最小堆 */
typedef struct HNode *MinHeap;
struct HNode {
	HTree *Data;
	int Size;
	int Capacity;
};

MinHeap CreateMinHeap(int MaxSize)
{	/* 返回一个容量为MaxSize的空的最小堆 */
	MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
	H->Data = (HTree *)malloc((MaxSize + 1) * sizeof(HTree));
	H->Capacity = MaxSize;
	H->Size = 0;
	HTree Min = (HTree)malloc(sizeof(struct TNode));
	Min->Left = Min->Right = NULL;
	Min->Weight = 0;
	H->Data[0] = Min;/* 定义哨兵，Min的权重小于所有元素的权重 */
	return H;
}

void Insert(MinHeap H, HTree T)
{	/* 在最小堆中插入元素 */
	int i;
	if (H->Size == H->Capacity)
		return;
	i = ++H->Size;
	for (; H->Data[i / 2]->Weight > T->Weight; i /= 2)//HTree的大小比较的是HTree的权重
		H->Data[i] = H->Data[i/2];
	H->Data[i] = T;
}

HTree DeleteMin(MinHeap H)
{	/* 删除并返回堆顶最小元素 */
	HTree Min = H->Data[1];
	HTree X = H->Data[H->Size--];
	int Parent, Child;
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;/* 左孩子 */
		if (Child != H->Size && H->Data[Child + 1]->Weight < H->Data[Child]->Weight) /* 右孩子存在&&右孩子的权重更小 */
			Child++; /* Child更新为右孩子 */
		if (X->Weight <= H->Data[Child]->Weight)
			break;
		H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
	return Min;
}

/* 最小堆定义结束 */

HTree CreateHTree(MinHeap H)
{	/* 根据存储树结点的最小堆创建Huffman树 */
	HTree HT;
	int Size = H->Size;
	for (int i = 1; i < Size; i++) { /* 循环Size-1次 */
		HT = (HTree)malloc(sizeof(struct TNode));
		HT->Left = DeleteMin(H);
		HT->Right = DeleteMin(H); /* 最小堆中最小的两个元素作为HT的左、右孩子 */
		HT->Weight = HT->Left->Weight + HT->Right->Weight;
		Insert(H, HT);
	}
	HT = DeleteMin(H);
	return HT;
}

void code(HTree HT, string hcode)
{	/* 返回Huffman树各结点的编码 */
	if (!HT->Left && !HT->Right) /* 叶子结点 */
		cout << HT->Data << "的编码为: " << hcode << "\n";
	else {
		code(HT->Left, hcode + "0");
		code(HT->Right, hcode + "1");
	}
}

int WPL(HTree HT, int depth)
{	/* 返回Huffman树的总权重 */
	if (!HT->Left && !HT->Right) /* 叶子结点 */
		return HT->Weight * depth;
	return WPL(HT->Left, depth + 1) + WPL(HT->Right, depth + 1);
}

int main()
{
	int N;
	do {
		cout << "输入需要编码的元素个数：";
		cin >> N;
	} while (N <= 0);
	MinHeap H = CreateMinHeap(N);
	for (int i = 0; i < N; i++) {
		cout << "输入第" << i + 1 << "个元素及其出现的次数：";
		char c;
		int weight;
		cin >> c >> weight;
		HTree HT = (HTree)malloc(sizeof(struct TNode));
		HT->Data = c;
		HT->Weight = weight;
		HT->Left = HT->Right = NULL;
		Insert(H, HT);
	}
	HTree HT = CreateHTree(H);
	code(HT, "");
	cout << "总权重WPL为："<<WPL(HT, 0);
    return 0;
}

