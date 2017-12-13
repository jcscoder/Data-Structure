// 线性表_顺序实现.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using name space std;
#define ERROR -1

typedef int ElemType;//线性表存储的元素类型
typedef int Position;//顺序存储线性表的数组中的元素下标
typedef struct LNode * PtrToLNode;//线性表
struct LNode {
	ElemType * Data;//存储元素的数组
	Position Last;//数组的最后一个元素的下标
	int Capacity;//线性表的容量
};
typedef PtrToLNode List;

/* 建立一个顺序存储的线性表 */
List CreateList(int Max_Size) {
	List L = (List)malloc(sizeof(struct LNode));
	L->Data = (ElemType *)malloc(Max_Size * sizeof(ElemType));//Data数组存储容量为Max_Size
	L->Last = -1;//空数组
	L->Capacity = Max_Size;
	return L;
}

/* 若线性表为空，则返回true， else返回false */
bool IsEmpty(List L) {
	return L->Last == -1;
}

/* 若线性表已满，则return true， else return false */
bool IsFull(List L) {
	return L->Last + 1 == L->Capacity;//数组从0开始计数
}

/* 查找线性表中的元素的位置 */
Position Find(List L, ElemType X) {
	for (Position i = 0; i <= L->Last; i++) {
		if (L->Data[i] == X)
			return i;
	}
	return ERROR;
}

/* 在线性表的位置P前插入元素X，插入后L的位置P的元素为X */
bool Insert(List L, Position P, ElemType X) {
	if (IsFull(L)) {
		cout << "表满\n";
		return false;
	}
	if (P < 0 || P > L->Last + 1) {//合法插入位置为[0, L->Last + 1],即数组中第0个元素到最后一个元素的位置后一个
		cout << "插入位置不合法\n";
		return false;
	}
	for (Position i = L->Last; i >= P; i--) {//从P到L->Last的元素后移位置
		L->Data[i + 1] = L->Data[i];
	}
	L->Data[P] = X;//插入X
	L->Last++;
	return true;
}

/* 删除并返回在线性表中位置为P的元素 */
ElemType Delete_Position(List L, Position P) {
	if (IsEmpty(L)) {
		cout << "表空\n";
		return ERROR;
	}
	if (P < 0 || P > L->Last) {//合法删除位置为[0, L->Last]，即数组第0元素到数组最后一个元素
		cout << "删除位置不合法\n";
		return ERROR;
	}
	ElemType X = L->Data[P];
	for (Position i = P; i < L->Last; i++)//从P + 1到L->Last的元素位置前移
		L->Data[i] = L->Data[i + 1];
	L->Last--;
	return X;
}

/* 删除线性表中的元素X，并返回X的下标 */
Position Delete_Value(List L, ElemType X) {
	if (IsEmpty(L)) {
		cout << "表空\n";
		return ERROR;
	}
	Position P = Find(L, X);
	Delete_Position(L, P);
	return P;
}

/* 输出线性表 */
void Print(List L) {
	if (IsEmpty(L)) {
		cout << "表空\n";
		return;
	}
	for (Position P = 0; P < L->Last; P++)
		cout << L->Data[P];
	cout << L->Data[L->Last] << "\n";
}

/* 主函数 */
int main()
{
	int N;
	cin >> N;
	List L = CreateList(N);
	int flag;
	ElemType X;
	Position P;
	while (true) {
		printf("输入'0'停止，'1'插入元素，'2'按位置删除元素，'3'按值删除元素, '4'输出线性表\n");
		cin >> flag;
		if (flag == 0)
			break;
		switch (flag)
		{
		case 1:
		{
			printf("输入插入的位置和元素的值:\n");
			cin >> P >> X;
			Insert(L, P, X);
			break;
		}
		case 2:
		{
			printf("输入删除的元素位置:\n");
			cin >> P;
			Delete_Position(L, P);
			break;
		}
		case 3:
		{
			printf("输入删除的元素的值：\n");
			cin >> X;
			Delete_Value(L, X);
			break;
		}
		case 4:
		{
			Print(L);
			break;
		}
		default:
			break;
		}
	}
	return 0;
}

