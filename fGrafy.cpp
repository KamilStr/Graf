#include <stdio.h>
#include <stdlib.h>
#include "fGrafy.h"
#include "fPrior.h"

Graph* newGraph(int V)
{
	Graph* graf = (Graph*)malloc(sizeof(Graph));
	if (!graf)
	{
		perror("Blad w przydzielaniu pamieci\n");
		return 0;
	}
	graf->VertexNumber = V;

	graf->VertexTab = (VertexList*)malloc(V * sizeof(VertexList));
	if (!graf->VertexTab)
	{
		perror("Blad w przydzielaniu pamieci\n");
		return 0;
	}
	for (int i = 0; i < V; i++)
	{
		VertexList p = (Vertex*)calloc(1, sizeof(Vertex));
		if (!p)
		{
			perror("Blad w przydzielaniu pamieci\n");
			return 0;
		}
		graf->VertexTab[i] = p;
	}
	return graf;
}

void addEdge(Graph* Graph, int from, int to, double distance, int type)
{

	Vertex* p = (Vertex*)calloc(1, sizeof(Vertex));
	if (!p)
	{
		perror("Blad w przydzielaniu pamieci\n");
		return;
	}
	p->dest = to;
	p->distance = distance;
	p->type = type;
	p->path = (int*)calloc(Graph->VertexNumber, sizeof(int));

	if (!Graph->VertexTab[from]->distance)
		Graph->VertexTab[from] = p;
	else
	{
		p->pNext = Graph->VertexTab[from]->pNext;
		Graph->VertexTab[from]->pNext = p;
	}

}

double Dijkstra(Graph* village, int nSize, int nFirst)
{
	bool* mark = (bool*)calloc(village->VertexNumber, sizeof(bool));
	if (!mark)
	{
		perror("Blad w przydzielaniu pamieci\n");
		return -1;
	}
	double* PathLen = (double*)calloc(village->VertexNumber, sizeof(double));
	if (!PathLen)
	{
		perror("Blad w przydzielaniu pamieci\n");
		return -1;
	}
	double* times = (double*)calloc(village->VertexNumber, sizeof(double));
	if (!times)
	{
		perror("Blad w przydzielaniu pamieci\n");
		return -1;
	}
	Queue* q = Init(village->VertexNumber);
	for (int i = 0; i < village->VertexNumber; i++)
	{
		PathLen[i] = INT_MAX;
		village->VertexTab[nFirst]->path[i] = -1;
	}
	PathLen[nFirst] = 0;
	EnQueue(q, nFirst, 0);
	double x = 0;
	while (!(isEmptyQueue(q)))
	{
		int k = DeQueue(q);
		if (village->VertexTab[k]->type)
		{
			village->VertexTab[nFirst]->timeToShop = times[k];
			village->VertexTab[nFirst]->closerShop = k;			
			x = PathLen[k]; break;
		}
		VertexList p = village->VertexTab[k];
		while (p)
		{
			int nNode = p->dest;
			if ((PathLen[nNode] > PathLen[k] + p->distance) && !mark[k])
			{
				PathLen[nNode] = PathLen[k] + p->distance;
				times[nNode] = times[k] + p->time;
				village->VertexTab[nFirst]->path[nNode] = k;
				EnQueue(q, nNode, PathLen[nNode]);
			}
			p = p->pNext;
		}
		mark[k] = 1;
	}
	free(mark);
	free(PathLen);
	return x;
}
void DFS(Graph* village, bool* mark, int nr)
{
	
	mark[nr] = 1;

	VertexList p = village->VertexTab[nr];
	while (p)
	{
		p->time = (double)p->distance / SPEED * 60;
		if (!(mark[p->dest]))
			DFS(village, mark, p->dest);
		/*{
			mark[p->dest] = 1;
			EnQueue(q, p->dest, 0);
		}*/
		p = p->pNext;
	}
	
}


void printPath(FILE* file, int* prev, int from, int to)
{
	if (prev[from] != to)
		printPath(file, prev, prev[from], to);
	fprintf(file, "->%d", from);
}

void FreeGraph(Graph* Graph)
{
	for (int i = 0; i < Graph->VertexNumber; i++)
	{
		free(Graph->VertexTab[i]);
	}
	free(Graph->VertexTab);
	free(Graph);

}
