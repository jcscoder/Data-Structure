# 拓扑排序与关键活动
----
#### 参考 一道 题目：
# 7-11 关键活动（30 分）
[ 原题地址](https://pintia.cn/problem-sets/15/problems/719)

###  题目 要求

* 作者: DS课程组

* 单位: 浙江大学

* 时间限制: 400ms

* 内存限制: 64MB

* 代码长度限制: 16KB







假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。

比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，各门课程可以看成是子任务。有些课程可以同时开设，比如英语和C程序设计，它们没有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比如C程序设计和数据结构两门课，必须先学习前者。

但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。比如方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务A”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。

任务调度问题中，如果还给出了完成每个子任务需要的时间，则我们可以算出完成整个工程需要的最短时间。在这些子任务中，有些任务即使推迟几天完成，也不会影响全局的工期；但是有些任务必须准时完成，否则整个项目的工期就要因此延误，这种任务就叫“关键活动”。

请编写程序判定一个给定的工程项目的任务调度是否可行；如果该调度方案可行，则计算完成整个工程项目需要的最短时间，并输出所有的关键活动。

## 输入格式:

输入第1行给出两个正整数N(≤100)和M，其中N是任务交接点（即衔接相互依赖的两个子任务的节点，例如：若任务2要在任务1完成后才开始，则两任务之间必有一个交接点）的数量。交接点按1~N编号，M是子任务的数量，依次编号为1~M。随后M行，每行给出了3个正整数，分别是该任务开始和完成涉及的交接点编号以及该任务所需的时间，整数间用空格分隔。

## 输出格式:

如果任务调度不可行，则输出0；否则第1行输出完成整个工程项目需要的时间，第2行开始输出所有关键活动，每个关键活动占一行，按格式“V->W”输出，其中V和W为该任务开始和完成涉及的交接点编号。关键活动输出的顺序规则是：任务开始的交接点编号小者优先，起点编号相同时，与输入时任务的顺序相反。

## 输入样例:
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2


## 输出样例:
17
1->2
2->4
4->6
6->7

##  代码：


### C++

[7-11 关键活动（30 分）.cpp ](https://github.com/jerrykcode/Data-Structure/blob/master/Graph-Topological%20Sort-Key%20Activity/7-11%20%E5%85%B3%E9%94%AE%E6%B4%BB%E5%8A%A8%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <algorithm>

int **input; //The input order of the activity v -> w, using in the compare function

bool compare(pair<int, int> a, pair<int, int>b)
{
	return a.first != b.first ? a.first < b.first : input[a.first][a.second] > input[b.first][b.second];
}

void top_sort(int **time, int *inDegree, int *outDegree, int n)
{
	queue<int> q;
	int count = 0;
	for (int i = 0; i < n; i++) 
		if (inDegree[i] == 0) {
			q.push(i);
			count++;
		}
	int *earliest = new int[n]; //The earliest starting time of each vertex 每个顶点的最早开始时间
	fill(earliest, earliest + n, 0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int w = 0; w < n; w++) 
			if (time[v][w] != -1) { //An activity of v-> w exists
				/* If the earliest starting time of v + time[v][w] larger than the starting time of
				w, then w can not start so early. */
				if (earliest[v] + time[v][w] > earliest[w]) earliest[w] = earliest[v] + time[v][w];
				if (--inDegree[w] == 0) {
					q.push(w);
					count++;
				}
			}
	}
	if (count < n) { //loop exists
		cout << 0 << endl;
		return;
	}
	int max = 0;
	for (int v = 0; v < n; v++)
		if (outDegree[v] == 0 && earliest[v] > max)
			max = earliest[v];
	cout << max << endl;
	vector<pair<int, int>> keyActivies;
	int *latest = new int[n]; //The latest ending time of each vertex 每个顶点的最晚结束时间
	fill(latest, latest + n, max);
	for (int v = 0; v < n; v ++)
		if (outDegree[v] == 0) 
			q.push(v);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int w = 0; w < n; w++) 
			if (time[w][v] != -1) { //Activity of w -> v exists
				/*If the latest ending time of v - time[w][v] smaller than the ending time of
				w, then w can not end so late. */
				if (latest[v] - time[w][v] < latest[w]) latest[w] = latest[v] - time[w][v];
				if (latest[v] - time[w][v] - earliest[w] == 0) keyActivies.push_back({ w, v }); //w->v is a key activity
				if (--outDegree[w] == 0) 
					q.push(w);
			}
	}
	sort(keyActivies.begin(), keyActivies.end(), compare);
	for (auto it = keyActivies.begin(); it != keyActivies.end(); it++) 
		printf("%d->%d\n", it->first + 1, it->second + 1);
}

int main()
{
	int n, m;
	cin >> n >> m;
	//AOE graph 活动在边上
	int *inDegree = new int[n]; //入度
	int *outDegree = new int[n]; //出度
	int **time = new int*[n]; //The lasting time of the activity v -> w
	input = new int*[n]; //The input order of the activity v -> w
	for (int i = 0; i < n; i++) {
		inDegree[i] = outDegree[i] = 0;
		time[i] = new int[n];
		input[i] = new int[n];
		for (int j = 0; j < n; j++)
			time[i][j] = input[i][j] = -1; //Initialize
	}
	for (int i = 0; i < m; i++) { //Inserts Edge(activities)
		int v, w, t;
		cin >> v >> w >> t;
		v--;
		w--;
		time[v][w] = t;
		input[v][w] = i; //Input order 输入顺序，输出时需要此顺序
		inDegree[w]++;
		outDegree[v]++;
	}
	top_sort(time, inDegree, outDegree, n);
    return 0;
}
```


### Java

[KeyActivity.java ](https://github.com/jerrykcode/Data-Structure/blob/master/Graph-Topological%20Sort-Key%20Activity/KeyActivity.java)


```Java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.LinkedList;
import java.util.Queue;

public class KeyActivity {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		StreamTokenizer st = new StreamTokenizer(
				new BufferedReader(new InputStreamReader(System.in)));
		st.nextToken();
		int nCheck = (int) st.nval;//The number of check points
		int time[][] = new int[nCheck][nCheck];//The lasting time of an activity between 2 check points
		int input[][] = new int[nCheck][nCheck];//The input order of each activity
		int inDegree[] = new int[nCheck];
		int outDegree[] = new int[nCheck];
		init(time, input, inDegree, outDegree);//Initialize arrays
		st.nextToken();
		int nActivity = (int) st.nval;//The number of activities
		for (int i = 0; i < nActivity; i ++) {
			st.nextToken();
			int x = (int) st.nval - 1;//One of the 2 check points of an activity
			st.nextToken();
			int y = (int) st.nval - 1;//Another check point of the activity
			st.nextToken();
			int lastingTime = (int) st.nval;//The lasting time of the activity
			time[x][y] = lastingTime;
			input[x][y] = i;//The i-th input
			inDegree[y] ++;
			outDegree[x] ++;//x->y, x out, y in
		}
		top(time, input, inDegree, outDegree);//find out the key activities
	}

	/* Initialize the graph and arrays. */
	private static void init(int[][] time, int[][] input, int[] inDegree, int[] outDegree) {
		// TODO Auto-generated method stub
		int nCheck = time.length;
		for (int i = 0; i < nCheck; i ++) {
			for (int j = 0; j < nCheck; j ++) 
				time[i][j] = input[i][j] = -1;
			inDegree[i] = outDegree[i] = 0;
		}
	}
	
	/* Top sort, find out the key activities. */
	private static void top(int[][] time, int[][] input, int[] inDegree, int[] outDegree) {
		// TODO Auto-generated method stub
		int nCheck = time.length;//The number of check points
		int count = 0;
		Queue <Integer> queue = new LinkedList<Integer>();
		int earliest[] = new int[nCheck];//The earliest starting time of each check points
		for (int v = 0; v < nCheck; v ++) {//v: Vertexes(check points) of the graph
			earliest[v] = 0;//Initialize
			if (inDegree[v] == 0) {
				queue.offer(v);
				count ++;
			}
		}
		while (! queue.isEmpty()) {
			int v = queue.poll();
			for (int w = 0; w < nCheck; w ++) 
				if (time[v][w] != -1) {//In the graph, v->w has edge
					/* If the earliest starting time of v + the time of activity between 
					 * v->w lager than the earliest starting time of w, 
					 * so w can not start so early*/
					if (earliest[v] + time[v][w] > earliest[w])
						earliest[w] = earliest[v] + time[v][w];
					if (--inDegree[w] == 0) {					
						queue.offer(w);							
						count ++;
					}
				}
		}//while
		if (count < nCheck) {
			System.out.println("0");
			return ;
		}
		//else
		int max = 0;
		for (int v = 0; v < nCheck; v ++) {
			if (outDegree[v] == 0) {
				queue.offer(v);
				if (earliest[v] > max)//Find the maximum earliest starting time of the
					max = earliest[v]; //check points with "outDegree" zero
			}
		}
		System.out.println(max);
		int latest[] = new int[nCheck];//The latest ending time of each check points
		for (int v = 0; v < nCheck; v ++)
			latest[v] = max;//Initialize
		while (!queue.isEmpty()) {
			int v = queue.poll();
			for (int w = 0; w < nCheck; w ++) {
				if (time[w][v] != -1) {//w->v has edge in the graph
					/* If the latest ending time of v - the time of activity between
					 * w->v smaller than the latest ending time of w,
					 * then w can not end so late*/
					if (latest[v] - time[w][v] < latest[w]) 
						latest[w] = latest[v] - time[w][v];
					/* If the latest ending time of v - the earliest starting time of
					 * w - the time of the activity between w->v greater than 0,
					 * then w->v is not key activity*/
					if (latest[v] - earliest[w] - time[w][v] > 0)
						time[w][v] = -1;//w->v is not key activity
					if (--outDegree[w] == 0)
						queue.offer(w);
				}
			}
		}//while
		for (int v = 0; v < nCheck; v ++) {
			count = 0;
			for (int w = 0; w < nCheck; w ++) 
				if (time[v][w] != -1)//v->w is key activity
					count ++;
			if (count == 0)
				continue;
			int arr[] = new int[count];
			count = 0;
			for (int w = 0; w < nCheck; w ++)
				if (time[v][w] != -1)
					arr[count ++] = w;
			sort(arr, input, v);
			for (int i = 0; i < count; i ++)
				System.out.println((v + 1) + "->" + (arr[i] + 1));
		}
	}

	/* Sorts. */
	private static void sort(int[] arr, int[][] input, int v) {
		// TODO Auto-generated method stub
		int si, d;
		int sedgewick[] = {41, 19, 5, 1, 0};
		int n = arr.length;
		for (si = 0; sedgewick[si] >= n; si ++)
			;
		for (d = sedgewick[si]; d > 0; d = sedgewick[++si]) {
			for (int p = d; p < n; p +=d) {
				int temp = arr[p];
				int i;
				for (i = p; i > 0 && input[v][arr[i - d]] < input[v][temp]; i -= d)
					arr[i] = arr[i - d];
				arr[i] = temp;
			}
		}
	}

}
```