// AVLTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

typedef int ElemType;/* AVL树存储的元素类型 */
/* 定义AVL树结点 */
typedef struct TNode *PtrToTNode;
struct TNode {
	ElemType Data;
	int Height;
	PtrToTNode Left;
	PtrToTNode Right;
};
typedef PtrToTNode Position;
typedef PtrToTNode AVLTree;


int Max(int a, int b)
{	/* 返回两个整形中的较大者 */
	return (a > b) ? a : b;
}

int GetHeight(AVLTree AVLT)
{	/* 返回树高 */
	if (!AVLT) /* 树空 */
		return 0; /* 空树高度为0 */
	return Max(GetHeight(AVLT->Left), GetHeight(AVLT->Right)) + 1; /* 返回左、右自树中较大的高度+1 */
}

/* 树旋转 */
#define ERROR NULL
AVLTree LLRotation(AVLTree AVLT)
{	/* 对AVLT进行左单旋（LL旋转），返回旋转后的根结点 */
	if (!AVLT || !AVLT->Left)
		return ERROR;
	AVLTree B = AVLT->Left;
	AVLT->Left = B->Right;
	B->Right = AVLT;
	AVLT->Height = Max(GetHeight(AVLT->Left), GetHeight(AVLT->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), GetHeight(AVLT)) + 1;
	return B;
}

AVLTree RRRotation(AVLTree AVLT)
{	/* 对AVLT进行右单旋（RR旋转），返回旋转后的根结点 */
	if (!AVLT || !AVLT->Right)
		return ERROR;
	AVLTree B = AVLT->Right;
	AVLT->Right = B->Left;
	B->Left = AVLT;
	AVLT->Height = Max(GetHeight(AVLT->Left), GetHeight(AVLT->Right)) + 1;
	B->Height = Max(GetHeight(AVLT), GetHeight(B->Right)) + 1;
	return B;
}

AVLTree LRRotation(AVLTree AVLT)
{	/* 对AVLT进行左右双旋（LR旋转），返回旋转后的根结点 */
	if (!AVLT || !AVLT->Left || !AVLT->Left->Right)
		return ERROR;
	AVLT->Left = RRRotation(AVLT->Left);
	return LLRotation(AVLT);
}

AVLTree RLRotation(AVLTree AVLT)
{	/* 对AVLT进行右左双旋（RL旋转），返回旋转后的根结点 */
	if (!AVLT || !AVLT->Right || !AVLT->Right->Left)
		return ERROR;
	AVLT->Right = LLRotation(AVLT->Right);
	return RRRotation(AVLT);
}

/* 以上是树旋转，以下是插入 */

AVLTree Insert(AVLTree AVLT, ElemType X)
{	/* 插入元素 */
	if (!AVLT) { /* AVL树空，生成并返回一个结点的AVL树 */
		AVLT = (AVLTree)malloc(sizeof(struct TNode));
		AVLT->Data = X;
		AVLT->Height = 0;
		AVLT->Left = AVLT->Right = NULL;
	}
	else {
		if (X < AVLT->Data) { /* 插入AVLT的左子树 */
			AVLT->Left = Insert(AVLT->Left, X);
			if (GetHeight(AVLT->Left) - GetHeight(AVLT->Right) >= 2) { /* 不平衡发生在AVLT的左子树上 */
				if (X < AVLT->Left->Data) /* X在AVLT的左子树的左边 */
					AVLT = LLRotation(AVLT); /* 左单旋 */
				else /* X在AVLT的左子树的右边 */
					AVLT = LRRotation(AVLT); /* 左右双旋 */
			}
		}
		else if (X > AVLT->Data) { /* 插入AVLT的右子树 */
			AVLT->Right = Insert(AVLT->Right, X);
			if (GetHeight(AVLT->Left) - GetHeight(AVLT->Right) <= -2) { /* 不平衡发生在AVLT的右子树上 */
				if (X < AVLT->Right->Data) /* X在AVLT的右子树的左子树上 */
					AVLT = RLRotation(AVLT);
				else /* X在AVLT的右子树的右子树上 */
					AVLT = RRRotation(AVLT);
			}
		}
		AVLT->Height = Max(GetHeight(AVLT->Left), GetHeight(AVLT->Right)) + 1;
	}
	return AVLT;
}

int main()
{
	int N;
	cin >> N;
	AVLTree AVLT = NULL;
	for (int i = 0; i < N; i++) {
		ElemType X;
		cin >> X;
		AVLT = Insert(AVLT, X);
	}
	cout <<AVLT->Data;
    return 0;
}





