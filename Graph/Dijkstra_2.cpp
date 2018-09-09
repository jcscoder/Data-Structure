#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
#define INSERT_EDGE(v, w, weight) graph[v][w] = graph[w][v] = weight
//#define INPUT
#define NO_VERTEX -1
#define INFINTE 10000
typedef int Vertex;
typedef Vertex ** Graph;
typedef vector<Vertex> Path;
 //Compiler version g++ 6.3.0

class Dijkstra {
public:
	Dijkstra() : inf(INFINTE) {}
	~Dijkstra() {
		freeMemory();
	}
	
	int ShortestDist(Graph graph,
                 int nVertexes,
                 Vertex src,
                 Vertex des,
                 Path& outputPath);
	void SetInf(int inf);
private:
	Vertex minDistVertex(int nVertexes);
	void freeMemory();
	void getOutputPath(Path& outputPath, Vertex src, Vertex des);
	
	int *dist;
	Vertex *path;
	bool *collected;
	int inf;
};

void Dijkstra::SetInf(int inf) {
	this->inf = inf;
}

int Dijkstra::ShortestDist(Graph graph,
                    int nVertexes,
                    Vertex src,
                    Vertex des,
                    Path& outputPath)
{
	dist = new int[nVertexes];
	path = new Vertex[nVertexes];
	collected = new bool[nVertexes];
	
	for (Vertex v = 0; v < nVertexes; v++) {
		dist[v] = graph[src][v];
		path[v] = dist[v] < inf ? src : NO_VERTEX;
		collected[v] = false;
	}
	dist[src] = 0;
	path[src] = NO_VERTEX;
	collected[src] = true;
	
	while (true) {
		Vertex minV = minDistVertex(nVertexes);
		if (minV == NO_VERTEX || minV == des) {
			break;
		}
		collected[minV] = true;
		for (Vertex v =0; v < nVertexes; v++)
			if (!collected[v] && graph[minV][v] < inf) 
				if (dist[minV] + graph[minV][v] < dist[v]) {
					dist[v] = dist[minV] + graph[minV][v];
					path[v] = minV;
				}
	}
	
	getOutputPath(outputPath, src, des);
	int res = dist[des];
	freeMemory();
	return res;
}

Vertex Dijkstra::minDistVertex(int nVertexes) {
	Vertex minV = NO_VERTEX;
	int minDist = inf;
	for (Vertex v = 0; v < nVertexes; v++) {
		if (!collected[v] && dist[v] < minDist) {
			minV = v;
			minDist = dist[v];
		}
	}
	return minV;
}

void Dijkstra::getOutputPath(Path& outputPath, Vertex src, Vertex des) {
	stack<Vertex> s;
	Vertex tmp = des;
	while (tmp != src) {
		s.push(tmp);
		tmp = path[tmp];
	}
	outputPath.push_back(src);
	while (!s.empty()) {
		outputPath.push_back(s.top());
		s.pop();
	}
}

void Dijkstra::freeMemory() {
	if (dist != NULL) {
		free(dist);
		dist = NULL;
	}
	if (path != NULL) {
		free(path);
		path = NULL;
	}
	if (collected != NULL) {
		free(collected);
		collected = NULL;
	}
}

 int main()
 {
 	cout << "Dijkstra" << endl;
 	Dijkstra d;
 	int inf = INFINTE;
 	d.SetInf(inf);
 	int n, m;
 #ifdef INPUT
 	cout << "Enter the number of the vertexes:" << endl;
 	cin >> n;
 	cout << "Enter the number of the edges:" << endl;
 	cin >> m;
 #else
 	n = 8;
 	m = 10;
 #endif
 	
 	Graph graph = new Vertex *[n];
 	for (int i = 0; i < n; i++) {
 		graph[i] = new Vertex[n];
 		memset(graph[i], inf, n * sizeof(Vertex));
 	}
 	
 #ifdef INPUT
 	int v, w, weight;
 	for (int i = 0; i < m; i++) {
 		cout << "Enter the vertexes of the edge " << i << ":" << endl;
 		cin >> v >> w;
 		cout << "Enter the weight of this edge:" << endl;
 		cin >> weight;
 		INSERT_EDGE(v, w, weigth);
 	}
 #else 
 	INSERT_EDGE(0, 1, 1);
 	INSERT_EDGE(1, 2, 2);
 	INSERT_EDGE(1, 6, 3);
 	INSERT_EDGE(2, 6, 2);
 	INSERT_EDGE(2, 5, 7);
 	INSERT_EDGE(5, 3, 3);
 	INSERT_EDGE(6, 3, 6);
 	INSERT_EDGE(3, 7, 4);
 	INSERT_EDGE(6, 4, 11);
 	INSERT_EDGE(4, 7, 9);
 #endif
 
 	Vertex src, des;
 	
 #ifdef INPUT
 	cout << "Enter the source and the destination:" << endl;
 	cin >> src >> des;
 #else
 	src = 0;
 	des = 7;
 #endif
 	Path path;
 	int dist = d.ShortestDist(graph, n, src, des, path);
 	cout << "The shortest distance between " << src << " and " << des << " is " << dist << ". " << endl;
 	cout << "The path is:" << endl;
 	for (Vertex v : path) {
 		cout << v;
 		if (v != des) cout << " -> ";
 	}
 	cout << endl;
	 return 0;
 }
