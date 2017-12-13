// Binary_Search_Tree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

typedef int ElementType; /* BST存储的元素类型 */
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode { /* 树结点 */
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

Position Find(BinTree BST, ElementType X) 
{	/* 查找元素X在BST中所在的结点 */
	if (!BST)
		return NULL; /* 空树，查找失败 */
	if (X > BST->Data)
		return Find(BST->Right, X);
	if (X < BST->Data)
		return Find(BST->Left, X);
	return BST; /* X与BST->Data相同，查找成功 */
}

Position FindMin(BinTree BST)
{	/* 返回BST中最小元素所在的结点(迭代) */
	if (!BST)
		return NULL;
	while (BST->Left)
		BST = BST->Left;
	return BST;
}

Position FindMax(BinTree BST)
{	/* 返回BST中的最大元素所在的结点(递归) */
	if (!BST)
		return NULL;
	if (!BST->Right)
		return BST;
	return FindMax(BST->Right);
}

BinTree Insert(BinTree BST, ElementType X)
{	/* 在BST内插入元素X，返回插入后的BST */
	if (!BST) { /* BST空，新建结点 */
		BinTree BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
		return BST;
	}
	if (X > BST->Data)
		BST->Right = Insert(BST->Right, X);
	else if (X < BST->Data)
		BST->Left = Insert(BST->Left, X);
	/* else X == BST->Data, X已存在, 不需插入 */
	return BST;
}

BinTree Delete(BinTree BST, ElementType X)
{	/* 在BST内删除元素X并返回删除后的BST */
	if (!BST)
		printf("Not Found\n");
	else if (X > BST->Data)
		BST->Right = Delete(BST->Right, X);
	else if (X < BST->Data)
		BST->Left = Delete(BST->Left, X);
	else {/* X == BST->Data, 删除结点BST */
		BinTree Tmp = (BinTree)malloc(sizeof(struct TNode));
		if (BST->Left && BST->Right) {/* 若BST有左、右两个孩子 */
			Tmp = FindMin(BST->Right);/* Tmp结点包含右子树的最小元素，小于右子树中的其他结点的元素，大于左子树的所有结点的元素 */
			BST->Data = Tmp->Data;
			BST->Right = Delete(BST->Right, BST->Data);/* 删除右子树中最小元素结点 */
		}
		else {/* 有一个孩子或无孩子 */
			Tmp = BST;
			if (!BST->Left)
				BST = BST->Right;
			else if (!BST->Right)
				BST = BST->Left;
			free(Tmp);
		}
	}
	return BST;
}

void PreorderTraversal(BinTree BST)
{	/* 先序遍历 */
	if (BST) {
		printf("%d\n", BST->Data); /* 访问根结点 */
		PreorderTraversal(BST->Left);
		PreorderTraversal(BST->Right);
	}
}

void InorderTraversal(BinTree BST)
{	/* 中序遍历 */
	if (BST) {
		InorderTraversal(BST->Left);
		printf("%d\n", BST->Data);
		InorderTraversal(BST->Right);
	}
}

void LevelOrderTraversal(BinTree BST)
{	/* 层序遍历 */
	queue <BinTree> Q;
	if (!BST)	/* 空树 */
		return;
	Q.push(BST);
	while (!Q.empty()) {
		BinTree Tmp = Q.front();
		Q.pop();
		printf("%d\n", Tmp->Data);
		if (Tmp->Left)
			Q.push(Tmp->Left);
		if (Tmp->Right)
			Q.push(Tmp->Right);
	}
}

/* 主函数测试BST 改自 https://pintia.cn/problem-sets
   中国大学MOOC-陈越、何钦铭-数据结构-2017秋 04-树7 二叉搜索树的操作集 */
int main()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
	  	scanf("%d", &X);
		BST = Insert(BST, X);
	}
	printf("Preorder:"); PreorderTraversal(BST); printf("\n");
	MinP = FindMin(BST);
	MaxP = FindMax(BST);
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		Tmp = Find(BST, X);
		if (Tmp == NULL) printf("%d is not found\n", X);
		else {
			printf("%d is found\n", Tmp->Data);
			if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
			if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
		}
	}
	scanf("%d", &N);
	for (i = 0; i<N; i++) {
		scanf("%d", &X);
		BST = Delete(BST, X);
	}
	printf("Inorder:"); InorderTraversal(BST); printf("\n");
	printf("Levelorder: "); LevelOrderTraversal(BST); printf("\n");//增加测试层序遍历
    return 0;
}

