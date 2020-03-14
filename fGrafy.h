#ifndef _Graph_
#define _Graph_

#define SPEED 4

typedef struct Vertex
{
	int dest;
	double distance;
	double time;
	int type;
	int closerShop;
	int* path;
	double timeToShop;
	Vertex* pNext;
} Vertex;

typedef Vertex* VertexList;

typedef struct 
{
	int VertexNumber;
	VertexList* VertexTab;
} Graph;

void Visit(VertexList p);
Graph* newGraph(int V);
void addEdge(Graph* Graph, int from, int to, double distance, int type);
double Dijkstra(Graph* village, int nSize, int nFirst);
void DFS(Graph* village, bool* mark, int nr);
void printPath(FILE* file, int* prev, int from, int to);
void FreeGraph(Graph* graph);
#endif