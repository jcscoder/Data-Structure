// 队列_链式存储.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


typedef int ElemType;//队列存储的元素
/* 定义队列中的结点 */
typedef struct PNode *PtrToPNode;
struct PNode
{
	ElemType Data;
	PtrToPNode Next;
};
typedef PtrToPNode Position;

/* 定义队列 */
typedef struct QNode *PtrToQNode;
struct QNode
{
	Position Front, Rear;//队列的头、尾
};
typedef PtrToQNode Queue;

/* 创建空队列 */
Queue CreateQueue() {
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}

/* 判断队列是否为空 */
bool IsEmpty(Queue Q) {
	return Q->Front == NULL;
}

/* 队列插入元素 */
bool EnQueue(Queue Q, ElemType Item) {
	Position P = (Position)malloc(sizeof(struct PNode));
	P->Data = Item;
	if (IsEmpty(Q)) {
		Q->Front = Q->Rear = P;
	}
	else {
		Q->Rear->Next = P;
		Q->Rear = P;
	}
	Q->Rear->Next = NULL;
	return true;
}

/* 队列删除元素 */
#define ERROR -1
ElemType DeQueue(Queue Q) {
	if (IsEmpty(Q))
		return ERROR;
	Position FirstCell = Q->Front;
	if (Q->Front == Q->Rear) {//队列只有一个元素
		Q->Front = Q->Rear = NULL;
	}
	else {
		Q->Front = Q->Front->Next;
	}
	ElemType Data = FirstCell->Data;
	free(FirstCell);
	return Data;
}

int main()
{
	int N;
	scanf("%d", &N);
	Queue Q = CreateQueue();
	for (int i = 0; i < N; i++)
		EnQueue(Q, i);
	for (int i = 0; i <= N; i++) {
		printf("%d\n", DeQueue(Q));
	}
    return 0;
}

