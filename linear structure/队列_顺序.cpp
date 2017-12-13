// 队列_shunxucunchu.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;//队列存储的元素类型
typedef int Position;//队列中的元素位置
/* 定义队列 */
typedef struct QNode *PtrToQNode;
struct QNode
{
	ElemType *Data;//存储元素的数组 
	Position Front, Rear;//队列的头、尾
	int Max_Size;//队列存储的最大容量
};
typedef PtrToQNode Queue;

/* 创建一个空队列，其容量为 Max_Size */
Queue CreateQueue(int Max_Size) {
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (ElemType *)malloc((Max_Size + 1) * sizeof(ElemType));//定义长度为Max_Size + 1的数组
	Q->Front = Q->Rear = 0;//初始头、尾位置均为0
	Q->Max_Size = Max_Size + 1;
	return Q;
}

/* 判断队列是否为空 */
bool IsEmpty(Queue Q) {
	return Q->Front == Q->Rear;//队列头、尾相等
}

/* 判断队列是否满 */
bool IsFull(Queue Q) {
	return (Q->Rear + 1) % Q->Max_Size == Q->Front;//队列尾的下一个元素为队列头，循环队列中位置为P的元素的下一个元素的位置为(P + 1)%Q->Max_Size
}

/* 队列插入元素 */
bool EnQueue(Queue Q, ElemType Item) {
	if (IsFull(Q))
		return false;
	Q->Rear = (Q->Rear + 1) % Q->Max_Size;
	Q->Data[Q->Rear] = Item;
	return true;
}

/* 删除队列元素 */
#define ERROR -1
ElemType DeQueue(Queue Q) {
	if (IsEmpty(Q))
		return ERROR;
	Q->Front = (Q->Front + 1) % Q->Max_Size;
	return Q->Data[Q->Front];
}

/* 主函数，测试队列的顺序存储实现  */
int main()
{
	int N;//队列的容量
	scanf("%d", &N);
	Queue Q = CreateQueue(N);
	for (int i = 0; i <= N; i++) {//i=N时测试队列满的情况下的插入
		EnQueue(Q, i);
	}
	for (int i = 0; i <= N; i++) {//i=N时测试队列空的情况下的删除
		ElemType Item = DeQueue(Q);
		printf("%d\n", Item);
	}
    return 0;
}

