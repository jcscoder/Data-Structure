// 线性表_链式.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

/* 定义链表结点 */
typedef int ElemType;//链表存储的元素类型
typedef struct LNode *PtrToLNode;
struct LNode {
	ElemType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

/* 创建链表 */
List CreateList()
{
	List L = (List)malloc(sizeof(struct LNode));
	return L;
}

/* 查找链表中的元素的位置 */
Position Find(List L, ElemType X) {
	Position P = L;
	while (P && P->Data != X) //P存在&&P指向的Data != X
		P = P->Next;
	return P;//若X不存在，则P迭代至ＮＵＬＬ时跳出循环，返回NULL
}

/* 在链表的位置P之前插入元素X，即插入后链表的P位置为X */
bool Insert(List L, Position P, ElemType X) {
	Position Pre;
	for (Pre = L; Pre && Pre->Next != P; Pre = Pre->Next)//查找P的前一位置Pre
		;
	if (!Pre) {//若P不存在则Pre为NULL
		cout << "插入位置错误!\n";
		return false;
	}
	Position Tmp = (Position)malloc(sizeof(struct LNode));
	Tmp->Data = X;
	Tmp->Next = P;
	Pre->Next = Tmp;
	return true;
}

/* 删除并返回链表中位置Ｐ的元素　*/
ElemType Delete(List L, Position P) {
	Position Pre;
	for (Pre = L; Pre && Pre->Next != P; Pre = Pre->Next)//查找P的前一位置Pre
		;
	if (!Pre || !P) {//P不存在（则Pre为NULL） || P为NULL， 删除位置错误
		cout << "删除位置错误!\n";
		return NULL;
	}
	ElemType X = P->Data;
	Pre->Next = P->Next;
	free(P);
	return X;
}


int main()
{
    return 0;
}

