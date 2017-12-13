// 栈_顺序存储.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define ERROR -1

typedef int ElemType;//栈存储的元素类型
typedef int Position;//元素在栈存储元素的数组中的位置
/* 定义堆栈 */
typedef struct SNode *PtrToSNode;
struct SNode {
	ElemType * Data;//存储元素的数组
	Position Top;//栈顶元素位置
	int Max_Size;//栈的最大容量
};
typedef PtrToSNode Stack;

/* 创建并返回一个空栈 */
Stack Create(int Max_Size) {
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElemType*)malloc(Max_Size * sizeof(ElemType));
	S->Max_Size = Max_Size;
	S->Top = -1;//空栈
	return S;
}

/* 判断栈是否满 */
bool IsFull(Stack S) {
	return S->Top == S->Max_Size - 1;
}

/* 判断栈是否为空 */
bool IsEmpty(Stack S) {
	return S->Top == -1;
}

/* 元素Item入栈 */
bool Push(Stack S, ElemType Item) {
	if (IsFull(S))
		return false;
	S->Data[++S->Top] = Item;
	return true;
}

/* 栈顶元素出栈并返回 */
ElemType Poll(Stack S) {
	if (IsEmpty(S))
		return ERROR;
	return S->Data[S->Top--];
}

/* 查看但不删除栈顶元素 */
ElemType Peek(Stack S) {
	if (IsEmpty(S))
		return ERROR;
	return S->Data[S->Top];
}

/* 主函数，测试栈的顺序实现 */
int main()
{
	int N;//栈的容量
	cout << "输入栈的容量:\n";
	scanf_s("%d", &N);
	Stack S = Create(N);//创建容量为Ｎ的空栈
	for (int i = 0; i <= N; i++)//i循环到N时测试栈满时调用Push
		Push(S, i);
	for (int i = 0; i <= N; i++) {//i=N时测试栈空时调用Peek和Poll
		cout << Peek(S)<<" ";
		Poll(S);
	}
    return 0;
}

