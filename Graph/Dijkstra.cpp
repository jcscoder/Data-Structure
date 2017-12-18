// Dijkstra.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#define DIRECTED 1
#define UNDIRECTED 0
#define infinity 10000

#define ERROR -1
int minDist(int *dist, bool *collected, int nv)
{	/* Returns the vertex(integer) with the minmum dist[i] and collected[i] == false*/
	int min = infinity, minV;
	for (int i = 0; i < nv; i ++)
		if (!collected[i] && dist[i] < min) {
			min = dist[i];
			minV = i;
		}
	if (min == infinity)
		return ERROR;
	return minV;
}

void dpath(int *path, int s, int v)
{	/* output the path */
	if (path[v] == s)
		cout << s << "->" << v;
	else {
		dpath(path, s, path[v]);
		cout << "->" << v;
	}
}

void dijkstra(int **graph, int nv)
{	/* Dijkstra */
	cout << "Enter a vertex as the source:\n";
	int s;
	cin >> s;
	int *dist = (int *)malloc(nv * sizeof(int)); /* currently shortest distance between every vertexes and the source */
	int *path = (int *)malloc(nv * sizeof(int)); /* path with the shortest distance from source to every vertexes */
	bool *collected = (bool *)malloc(nv * sizeof(bool)); /* true if the vertex had been collected */
	for (int i = 0; i < nv; i++) {//Initialize
		dist[i] = graph[s][i];
		path[i] = (graph[s][i] < infinity) ? s : -1;
		collected[i] = false;
	}
	dist[s] = 0;//distance between source and itself
	path[s] = s;
	collected[s] = true; //collects the source
	while (true) {
		int min = minDist(dist, collected, nv); /* The vertex with the minmum dist and had not yet been collected */
		if (min == ERROR)/* All the vertexes connected had been collected */
			break;
		/* collects 'min' */
		collected[min] = true;
		for (int v = 0; v < nv; v++) {//traverse every vertex 
			if (graph[min][v] < infinity && !collected[v])/* if there is an edge between 'min' and 'v' && v had not been collected */
				if (graph[min][v] < 0) {
					cout << "ERROR";
					return;
				}
				if (dist[min] + graph[min][v] < dist[v]) { /* */
					dist[v] = dist[min] + graph[min][v];
					path[v] = min;
				}
		}
	}
	for (int v = 0; v < nv; v++) {
		cout << "The shortest distance between " << s << "and" << v << "is: " << dist[v] << "\n";
		dpath(path, s, v);
		cout << "\n";
	}
}

int main()
{
	/* Initialize a graph by the user input */
	cout << "This program calculates the minmum distance between a vertex in a graph and a source vertex by using the dijkstra\n";
	int flag;
	do {
		cout << "Enter '" << DIRECTED << "'if the graph is directed, or '" << UNDIRECTED << "' if the graph is undirected:\n";
		cin >> flag;
	} while (flag != DIRECTED && flag != UNDIRECTED);
	cout << "Enter the number of vertexes in the graph:\n";
	int nv; /* the number of vertexes in the graph */
	cin >> nv;
	int ** graph = (int **)malloc(nv * sizeof(int *));/* Initialize the graph */
	for (int i = 0; i < nv; i++) {
		graph[i] = (int *)malloc(nv * sizeof(int));
		for (int j = 0; j < nv; j++)
			graph[i][j] = infinity;
	}
	cout << "Enter the number of edges in the graph:\n";
	int ne;
	cin >> ne;
	for (int i = 0; i < ne; i++) {
		cout << "Enter the 2 vertexes of the " << i << "th edge:\n";
		int v1, v2;
		cin >> v1 >> v2;
		cout << "Enter the weight of the edge" << v1 << "->" << v2 << " (and " << v2 << "->" << v1 << "if undirected):\n";
		int weight;
		cin >> weight;
		graph[v1][v2] = weight;//weight of v1 -> v2
		if (flag == UNDIRECTED)
			graph[v2][v1] = weight;//weight of v2 -> v1
	}
	dijkstra(graph, nv);
    return 0;
}

