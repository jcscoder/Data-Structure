// 栈_链式存储.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define ERROR -1

typedef int ElemType;//栈存储的元素

/* 定义栈 */
typedef struct SNode *PtrToSNode;
struct SNode {
	ElemType Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;

/* 创建一个空栈 */
Stack Create(){
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;//栈的头指针
}

/* 判断栈是否为空 */
bool IsEmpty(Stack S) {
	return S->Next == NULL;
}

/* 链式存储的栈没有固定的最大容量 */

/* 在栈顶压入元素, 插在头指针后 */
bool Push(Stack S, ElemType Item) {
	Stack TmpCell = (Stack)malloc(sizeof(struct SNode));
	if (!TmpCell)
		return false;
	TmpCell->Data = Item;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
	return true;
}

/* 栈顶元素出栈 */
ElemType Poll(Stack S) {
	if (IsEmpty(S))
		return ERROR;
	Stack FirstCell = S->Next;
	ElemType Data = FirstCell->Data;
	S->Next = FirstCell->Next;
	free(FirstCell);
	return Data;
}

/* 返回栈顶元素但不出栈 */
ElemType Peek(Stack S) {
	if (IsEmpty(S))
		return ERROR;
	Stack FirstCell = S->Next;
	return FirstCell->Data;
}

/* 主函数 测试栈的链表实现 */
int main()
{
	Stack S = Create();
	int N = 100;
	for (int i = 0; i < N; i++)
		Push(S, i);
	for (int i = 0; i <= N; i++) {
		cout << Peek(S) << " ";
		Poll(S);
	}
    return 0;
}

