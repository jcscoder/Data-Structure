// 图_邻接矩阵_邻接表.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define INFINITY 100000
#define DIRECTED 0 /* 有向图 */
#define UN_DIRECTED 1 /* 无向图 */

/* 图的邻接矩阵实现 */

typedef int Vertex; /* 定义顶点 */
typedef int DataType; /* 顶点存储的数据类型 */
typedef int WeightType; /* 定义边的权重类型 */
typedef struct ENode *PtrToENode;
struct ENode { /* 定义边结点 */
	Vertex V1, V2; /* 边的两个顶点 */
	WeightType Weight; /* 边的权重 */
};
typedef PtrToENode Edge;

/* 定义图结点（邻接矩阵表示）*/
typedef struct MGNode * PtrToMGNode;
struct MGNode {
	int Nv; /* 顶点数量 */
	int Ne; /* 边数 */
	WeightType **G; /* 邻接矩阵的二维数组 */
	DataType *Data; /* 顶点存储的数据 */
	int flag; /* 记录为有向图或无向图 */
	bool *Visited; /* 记录顶点是否访问过 */
};
typedef PtrToMGNode MGraph; /* 由邻接矩阵表示的图 */

MGraph CreateMGraph(int VNum, int flag)
{	/* 创建、初始化并返回有VNum个顶点的图（邻接矩阵表示）*/
	MGraph Graph = (MGraph)malloc(sizeof(struct MGNode));
	Graph->Nv = VNum;
	Graph->Ne = 0; /* 初始未插入边时有0条边 */
	Graph->G = (WeightType **)malloc(VNum * sizeof(WeightType*)); /* 邻接矩阵的二维数组 */
	Graph->Visited = (bool*)malloc(VNum * sizeof(bool)); /* 是否访问过 */
	Vertex v, w;
	for (v = 0; v < VNum; v++) {
		Graph->G[v] = (WeightType *)malloc(VNum * sizeof(WeightType));
		for (w = 0; w < VNum;w++) 
			Graph->G[v][w] = INFINITY; /* 任意两顶点之间的边的权重初始化为正无穷 */
		Graph->Visited[v] = false; /* 顶点初始未访问过 */
	}
	Graph->Data = (DataType *)malloc(VNum * sizeof(DataType));
	Graph->flag = flag;
	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{	/* 在图中插入边 */
	Graph->G[E->V1][E->V2] = E->Weight;
	Graph->Ne++;
	/* 无向图还要插入边V2->V1 */
	if (Graph->flag == UN_DIRECTED) {
		Graph->G[E->V2][E->V1] = E->Weight;
		Graph->Ne++;
	}
}

MGraph BuildMGraph()
{	/* 通过输入数据创建一个由邻接矩阵表示的图 */
	int VNum, ENum, flag;
	printf("输入图的顶点数：\n");
	scanf("%d", &VNum);
	do {
		printf("若是有向图则输入%d，无向图输入%d：\n", DIRECTED, UN_DIRECTED);
		scanf("%d", &flag);
	} while (flag != DIRECTED && flag != UN_DIRECTED);
	MGraph Graph = CreateMGraph(VNum, flag);
	printf("输入边数：\n");
	scanf("%d", &ENum);
	for (int i = 0; i < ENum; i++) {
		Edge E = (Edge)malloc(sizeof(struct ENode));
		printf("输入第%d条边的两个顶点：\n", i);
		scanf("%d %d", &E->V1, &E->V2);
		printf("输入边%d->%d的权重：\n", E->V1, E->V2);
		scanf("%d", &E->Weight);
		InsertEdge(Graph, E);
	}
	return Graph;
}

void Visit(MGraph Graph, Vertex V)
{	/* 访问顶点的函数 */
	printf("正在访问顶点: %d\n", V);
	Graph->Visited[V] = true;
}

void Set_Un_Visit(MGraph Graph)
{	/* 将图的每一个顶点设置为没有访问过 */
	for (Vertex V = 0; V < Graph->Nv; V++) {
		Graph->Visited[V] = false;
	}
}

void DFS(MGraph Graph, Vertex V, void(*Visit)(MGraph, Vertex))
{	/* 用深度优先搜索遍历图 */
	Visit(Graph, V);
	for (Vertex W = 0; W < Graph->Nv; W++) /* 图的每一个顶点 */
		if (Graph->G[V][W] < INFINITY && !Graph->Visited[W]) /* 若V->W存在边&&W未被访问过 */
			DFS(Graph, W, Visit);
}

/* BFS需要队列 */
/* 定义队列存储单元的结点 */
typedef Vertex ElemType; /* 队列存储图的顶点 */
struct PNode {
	ElemType Data;
	struct PNode *Next;
};
typedef struct PNode * Position;

/* 队列 */
typedef struct QNode *PtrToQNode;
struct QNode {
	Position Front, Rear;
};
typedef PtrToQNode Queue;

Queue CreateQueue()
{	/* 返回一个空队列 */
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}

void EnQueue(Queue Q, ElemType X)
{	/* 入队列 */
	Position P = (Position)malloc(sizeof(struct PNode));
	P->Data = X;
	if (Q->Front == NULL) /* 队列空 */
		Q->Front = Q->Rear = P;
	else {
		Q->Rear->Next = P;
		Q->Rear = P;
	}
	Q->Rear->Next = NULL;
}

#define ERROR -1
ElemType DeQueue(Queue Q)
{	/* 出队列 */
	if (Q->Front == NULL) /* 队列空 */
		return ERROR;
	Position FirstCell = Q->Front;
	if (Q->Front == Q->Rear) /* 队列只有一个元素 */
		Q->Front = Q->Rear = NULL;
	else {
		Q->Front = Q->Front->Next;
	}
	ElemType Data = FirstCell->Data;
	free(FirstCell);
	return Data;
}

void BFS(MGraph Graph, void(*Visit)(MGraph, Vertex))
{	/* 用广度优先搜索遍历图 */
	Queue Q = CreateQueue();
	Vertex V = 0;
	EnQueue(Q, V);
	Visit(Graph, V);
	while (Q->Front != NULL) {/* 队列不空 */
		V = DeQueue(Q);
		for (Vertex W = 0; W < Graph->Nv; W++) {
			if (Graph->G[V][W] < INFINITY && !Graph->Visited[W]) {/* W与V相邻&&W未被访问过 */
				Visit(Graph, W);
				EnQueue(Q, W);
			}
		}
	}
}

/* 最短路径问题 */

Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{	/* 返回未收录的顶点中dist最小者 */
	Vertex MinV;
	int MinDist = INFINITY;
	for (Vertex V = 0; V < Graph->Nv; V++) {
		if (!collected[V] && dist[V] < MinDist) { /* 若V未收录过&&V的dist值更小 */
			MinDist = dist[V];
			MinV = V;
		}
	}
	if (MinDist < INFINITY)
		return MinV;
	return ERROR;
}

bool Dijkstra(MGraph Graph, WeightType *dist, Vertex *path, Vertex S)
{	/* 单源最短路径 */
	int * collected = (int*)malloc(Graph->Nv * sizeof(int)); /* 记录顶点是否访问过 */
	for (Vertex V = 0; V < Graph->Nv; V++) {
		dist[V] = Graph->G[S][V]; /* 源S到顶点V的距离 */
		if (dist[V] < INFINITY) /* S->V之间存在边 */
			path[V] = S; /* Ｓ到Ｖ的路径经过Ｓ */
		else
			path[V] = -1; /* 初始化 */
		collected[V] = false; /* 初始化 */
	}
	dist[S] = 0;
	collected[S] = true; /* 收录S */
	while (true) {
		Vertex V = FindMinDist(Graph, dist, collected); /* 未收录顶点中dist最小者 */
		if (V == ERROR)
			break;
		collected[V] = true; /* 收录V */
		for (Vertex W = 0; W < Graph->Nv; W++) {
			if (Graph->G[V][W] < INFINITY && !collected[W]) /* V->W存在边&&W未收录 */
				if (Graph->G[V][W] < 0) /* 有负边 */
					return false;
				if (dist[V] + Graph->G[V][W] < dist[W]) {
					dist[W] = dist[V] + Graph->G[V][W];
					path[W] = V;
				}
		}
	} //while
	return true;
}



void DijkstraPrint(int path[], Vertex V, Vertex S)
{	/* Dijkstar输出结果的递归函数 */
	if (V == S)
		printf("%d", S);
	else {
		DijkstraPrint(path, path[V], S);
		printf("->%d", V);
	}
}

/* 多源最短路径 */
bool Floyd(MGraph Graph, WeightType **D, Vertex **path)
{	/*  多源最短路径 */
	for (Vertex V = 0; V < Graph->Nv; V++)/* 初始化 */
		for (Vertex W = 0; W < Graph->Nv; W++) {
			if (V == W)
				D[V][W] = 0;
			else
				D[V][W] = Graph->G[V][W];
			path[V][W] = -1;
		}
	for (Vertex k = 0; k < Graph->Nv; k++)
		for (Vertex i = 0; i < Graph->Nv; i++)
			for (Vertex j = 0; j < Graph->Nv; j++)
				if (i != j && D[i][k] + D[k][j] < D[i][j]) { /* 从i到k的距离+从k到j的距离 < 从i到j的距离 */
					D[i][j] = D[i][k] + D[k][j];
					path[i][j] = k;
				}
	return false;
}

void FloydPrint(Vertex**path, Vertex V, Vertex W)
{	/* 输出Floyd的结果（V到W的最短路径）的递归函数 */
	if (path[V][W] != -1) {
		Vertex k = path[V][W];
		FloydPrint(path, V, k);
		printf("->%d", k);
		FloydPrint(path, k, W);
	}
}

/* 以下是最小生成树(MST) */

WeightType FindMinDist(MGraph Graph, WeightType*dist)
{	/* 返回距离最小生成树最小的未收录顶点 */
	WeightType Min = INFINITY;
	Vertex MinV, V;
	for (V = 0; V < Graph->Nv; V++)
		if (dist[V] != 0 && dist[V] < Min) {/* V未被收录&&V与MST的距离<Min */
			Min = dist[V];
			MinV = V;
		}
	if (Min == INFINITY)
		return ERROR;
	return MinV;
}

/* 邻接表表示图，用于存储最小生成树 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjVertex; /* 邻接点 */
	WeightType Weight;
	PtrToAdjVNode Next;
};
typedef PtrToAdjVNode AdjList;

/* 定义图结点 */
typedef struct LGNode *PtrToLGNode;
struct LGNode {
	int Nv; /* 顶点数 */
	int Ne; /* 边数 */
	AdjList *G; /* 邻接表 */
	int flag;
};
typedef PtrToLGNode LGraph;

/* 创建图 */
LGraph CreateLGraph(int VNum, int flag)
{	/* 返回含有VNum个顶点、没有边的图 */
	LGraph Graph = (LGraph)malloc(sizeof(struct LGNode));
	Graph->Nv = VNum;
	Graph->Ne = 0;
	Graph->G = (AdjList *)malloc(VNum * sizeof(AdjList));
	for (Vertex V = 0; V < VNum; V++) {
		Graph->G[V] = (AdjList)malloc(sizeof(struct AdjVNode));
		Graph->G[V]->Next = NULL;
	}
	Graph->flag = flag;
	return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{	/* 在由邻接表表示的图中插入边 */
	PtrToAdjVNode Cell = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	Cell->Next = Graph->G[E->V1]->Next;
	Graph->G[E->V1]->Next = Cell;
	Graph->Ne++;
	/* 若是无向图 */
	if (Graph->flag == UN_DIRECTED) {
		PtrToAdjVNode Cell0 = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
		Cell->Next = Graph->G[E->V2]->Next;
		Graph->G[E->V2]->Next = Cell;
		Graph->Ne;
	}
}

LGraph BuildLGraph()
{	/* 由输入建立一个邻接表表示的图 */
	int VNum;
	printf("输入顶点数：\n");
	scanf("%d", &VNum);
	int flag;
	do {
		printf("\n若是有向图输入%d，无向图输入%d：\n", DIRECTED, UN_DIRECTED);
		scanf("%d", &flag);
	} while (flag != DIRECTED && flag != UN_DIRECTED);
	LGraph Graph = CreateLGraph(VNum, flag);
	printf("输入边数：\n");
	int ENum;
	scanf("%d", &ENum);
	for (int i = 0; i < ENum; i++) {
		printf("输入第%d条边的两个顶点：\n", i);
		Edge E = (Edge)malloc(sizeof(struct ENode));
		scanf("%d %d", &E->V1, &E->V2);
		printf("输入边%d->%d的权重：\n", E->V1, E->V2);
		scanf("%d", &E->Weight);
		InsertEdge(Graph, E);
	}
	return Graph;
}

/* 以上建立邻接表图 */
/* 定义并查集，用以合并森林 */
typedef Vertex SetName; /* 用根结点的下标作为集合名 */
typedef Vertex *SetType; /* 并查集，即每个顶点的Parent结点 */
void InitVSet(SetType S, int N)
{	/* 初始化并查集 */
	S = (SetType)malloc(N * sizeof(Vertex));
	for (Vertex V = 0; V < N; V++)/* 初始化 */
		S[V] = -1;
}

void Union(SetType S, SetName Root1, SetName Root2)
{	/* 合并两个根结点为Root1和Root2的集合 */
	if (S[Root1] > S[Root2]) {	/* S[根结点]存储根结点对应集合的大小的负值，S[Root1] 〉S[Root2]说明S2更大 */
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
	else {
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}
}

SetName Find(SetType S, Vertex V)
{	/* 返回顶点V的根的下标 */
	if (S[V] < 0)
		return V;
	else
		return S[V] = Find(S, S[V]);/* 路径压缩 */
}

bool CheckCycle(SetType S, Vertex V1, Vertex V2)
{	/* 检查两个顶点是否连通 */
	Vertex Root1 = Find(S, V1);
	Vertex Root2 = Find(S, V2);
	if (Root1 == Root2) /* 已连通 */
		return false;
	Union(S, Root1, Root2);
	return true;
}

/* 以上定义并查集 */
/* 定义存储边，按照边的权重大小排序的最小堆 */
void PercDown(Edge ESet, int p, int N)
{	/* 在有N个元素的数组ESet中找到ESet[p]在以p为根的子堆中的位置 */
	int Parent, Child;
	struct ENode E = ESet[p];
	for (Parent = p; Parent * 2 + 1 < N; Parent = Child) {
		Child = Parent * 2 + 1; /* 左孩子 */
		if (Child != N - 1 && ESet[Child].Weight > ESet[Child + 1].Weight) /* 右孩子存在&&右孩子的权重更小 */
			Child++; /* 更新Child为右孩子 */
		if (E.Weight <= ESet[Child].Weight)
			break;
		ESet[Parent] = ESet[Child];
	}
	ESet[Parent] = E;
}

void InitESet(LGraph Graph, Edge ESet)
{	/* 初始化边集合，Kruskal算法用邻接表存储图较好 */
	ESet = (Edge)malloc(Graph->Nv * sizeof(struct ENode));/* 存储边的数组 */
	int ECount = 0; /* 边的计数器 */
	for (Vertex V = 0; V < Graph->Nv; V++) 
		for (AdjList W = Graph->G[V]->Next; W; W = W->Next)
			if (V < W->AdjVertex) {
				ESet[ECount].V1 = V;
				ESet[ECount].V2 = W->AdjVertex;
				ESet[ECount++].Weight = W->Weight;
			}
	for (ECount = Graph->Ne / 2; ECount >= 0; ECount--) /* 初始化为最小堆 */
		PercDown(ESet, ECount, Graph->Ne);
}

void Swap(Edge a, Edge b)
{
	Edge Tmp = (Edge)malloc(sizeof(struct ENode));
	*Tmp = *a;
	*a = *b;
	*b = *Tmp;
	free(Tmp);
}

int GetEdge(Edge ESet, int CurrentSize)
{	/* 返回ESet中权重最小的边在ESet中的下标 */
	Swap(&ESet[0], &ESet[CurrentSize - 1]);
	PercDown(ESet, 0, CurrentSize - 1);
	return CurrentSize - 1;
}

int Kruskal(LGraph Graph, LGraph MST)
{	/* 用Kruskal算法计算最小生成树的总权重，最小生成树存储在LGraph MST里 */
	WeightType TotalWeight = 0; /* 总权重 */
	int ECount = 0;
	SetType VSet = NULL;
	InitVSet(VSet, Graph->Nv); /* 初始化顶点并查集 */
	Edge ESet = NULL;
	InitESet(Graph, ESet); /* 初始化边集 */
	MST = CreateLGraph(Graph->Nv, UN_DIRECTED);/* 最小生成树包含全部顶点 */
	int NextEdge = Graph->Ne;
	while (ECount < Graph->Nv - 1) {
		NextEdge = GetEdge(ESet, NextEdge);
		if (NextEdge < 0)
			break;
		if (CheckCycle(VSet, ESet[NextEdge].V1, ESet[NextEdge].V2)) {
			/* 如果插入边ESet[NextEdge]不构成回路 */
			InsertEdge(MST, ESet + NextEdge);
			TotalWeight += ESet[NextEdge].Weight;
			ECount++;
		}
	}//while
	if (ECount < Graph->Ne - 1)
		return -1;
	return TotalWeight;
}

void TestKruskal()
{	/* 测试Kruskal算法 */
	LGraph Graph = BuildLGraph();
	LGraph MST = NULL;
	WeightType Weight = Kruskal(Graph, MST);
	printf("最小生成树的总权重：%d\n", Weight);
}

int FindMin(MGraph Graph, int *dist)
{	/* 从未收录的顶点中返回dist值最小的 */
	Vertex MinV;
	int Min = INFINITY; /* Initialize */
	for (Vertex V = 0; V < Graph->Nv; V ++)
		if (dist[V] > 0 && dist[V] < Min) { /* dist[V] == 0 <=> V已被收录 */
			Min = dist[V];
			MinV = V;
		}
	if (Min == INFINITY)
		return ERROR;
	return MinV;
}

WeightType Prim(MGraph Graph, LGraph MST)
{	/* 最小生成树Prim算法， 返回MST的权重，MST存储在邻接表表示的图LGraph MST里 */
	int *dist = (int *)malloc(Graph->Nv * sizeof(int)); /* 每个顶点与最小生成树的距离 */
	int *parent = (int *)malloc(Graph->Nv * sizeof(int)); /* 每个顶点的父结点 */
	int VCount = 0; /* 计数器 收录的顶点数量 */
	int S = 0; /* Source */
	for (Vertex V = 0; V < Graph->Nv; V++) {
		dist[V] = Graph->G[S][V];
		if (Graph->G[S][V] < INFINITY) /* S与V相邻 */
			parent[V] = S; /* V */
		else
			parent[V] = -1;
	}
	dist[S] = 0;
	parent[S] = -1;
	VCount++;/* 收录Ｓ */
	int total = 0; /* MST的总权重 */
	while (true) {
		Vertex Min = FindMin(Graph, dist); /* 从MST未收录的顶点中找到dist最小的 */
		if (Min == ERROR) /* 不存在最小的,说明连通的图结点中所有结点均收录 */
			break;
		/* 收录Min */
		Edge E = (Edge)malloc(sizeof(struct ENode));
		E->V1 = parent[Min];
		E->V2 = Min;
		E->Weight = dist[Min];
		InsertEdge(MST, E);
		total += dist[Min];
		dist[Min] = 0;
		VCount++; /* 收录Min */
		for (Vertex V = 0; V < Graph->Nv; V++) {
			if (Graph->G[Min][V] < INFINITY && dist[V] > 0)  /* V与Min相邻＆＆V未被收录 */
				if (Graph->G[Min][V] < dist[V]) { /* Min已被收录入MST, 若Min与V的距离<当前V与MST的最小距离, */
					dist[V] = Graph->G[Min][V];		/* 当前V与MST的最小距离更新为Min与V的距离 */
					parent[V] = Min;
				}
		}
	}//while
	if (VCount < Graph->Nv) /* 收录的顶点数量<图的顶点数, 说明图不连通 */
		return ERROR;
	return total;
}

/* 主函数 */
int main()
{
	MGraph Graph = BuildMGraph();
	printf("DFS遍历：\n");
	DFS(Graph, 0, Visit);
	Set_Un_Visit(Graph);
	printf("BFS遍历: \n");
	BFS(Graph, Visit);
	/* 测试最短路径 */
	/* 单源最短路径 */
	{	printf("单源最短路径：\n");
		printf("输入一个顶点作为源: \n");
		Vertex S;
		scanf("%d", &S);
		WeightType *dist = (WeightType *)malloc(Graph->Nv * sizeof(WeightType));
		Vertex *path = (Vertex *)malloc(Graph->Nv * sizeof(Vertex));
		Dijkstra(Graph, dist, path, S);
		for (Vertex V = 0; V < Graph->Nv; V++) {
			if (dist[V] == INFINITY) {
				printf("%d和%d不连通！\n", S, V);
				continue;
			}
			printf("%d->%d的最短路径为%d\n", S, V, dist[V]);
			printf("%d->%d的最短路径：", S, V);
			DijkstraPrint(path, V, S);
			printf("\n");
		}
	}
	/* 多源最短路径 */
	{	printf("多源最短路径：\n");
		WeightType **D = (WeightType**)malloc(Graph->Nv * sizeof(WeightType*));
		Vertex **path = (Vertex**)malloc(Graph->Nv * sizeof(Vertex*));
		for (int i = 0; i < Graph->Nv; i++) {
			D[i] = (WeightType*)malloc(Graph->Nv * sizeof(WeightType));
			path[i] = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
		}
		Floyd(Graph, D, path);
		for (Vertex V = 0; V < Graph->Nv; V++) {
			for (Vertex W = 0; W < Graph->Nv; W++) {
				if (D[V][W] == INFINITY) {
					printf("%d和%d不连通！\n", V, W);
					continue;
				}
				printf("%d->%d的最短路径长度：%d\n",V, W, D[V][W]);
				printf("%d->%d的最短路径：", V, W);
				printf("%d", V);
				FloydPrint(path, V, W);
				printf("->%d", W);
				printf("\n");
			}
		}
	}
	/* 测试最小生成树MST */
	LGraph MST = CreateLGraph(Graph->Nv, Graph->flag); /* 最小生成树存储在邻接表表示的图里　*/
	printf("图的最小生成树(MST)的总权重为%d\n", Prim(Graph, MST));
	/* 测试Kruskal */
	printf("\n以下测试Kruskal最小生成树算法，先创建一个邻接表表示的图");
	TestKruskal();
    return 0;
}

