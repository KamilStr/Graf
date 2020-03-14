#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "fGrafy.h"

using namespace std;
void Print(Graph* map, char* path);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		perror("\nUsage: Dijkstra <map_in> <output_file>\n\n");
		return 1;
	}

	FILE* fin = NULL;

	if ((fin = fopen(argv[1], "r")) == NULL)
	{
		perror("Blad odczytu");
		return 1;
	}


	int V = 0;
	fscanf(fin, "%d", &V);

	Graph* Map = newGraph(V);

	int from;
	int to;
	double distance;
	int type; // 0 - dom; 1 - sklep
	while (!feof(fin))
	{
		fscanf_s(fin, "%d %d %lf %d", &from, &to, &distance, &type);
		addEdge(Map, from, to, distance, type);
	}
	fclose(fin);

	bool* mark = (bool*)calloc(1, V);
	if (!mark)
	{
		perror("Blad w przydzielaniu pamieci\n");
		return -1;
	}
	
	DFS(Map, mark, 0);
	free(mark);
	Print(Map, argv[2]);

	FreeGraph(Map);
	

	return 0;
}

void Print(Graph* map, char* path)
{

	FILE* fout = NULL;

	if ((fout = fopen(path, "w")) == NULL)
	{
		perror("Blad odczytu");
		return;
	}

	for (int i = 0; i < map->VertexNumber; i++)
	{
		if (!map->VertexTab[i]->type)
		{
			double length = Dijkstra(map, map->VertexNumber, i);
			fprintf(fout, "Dom nr %d: najblizszy sklep - %d, odleglosc - %3.1lfkm.\nNajkrotsza droga: %d",
				i, map->VertexTab[i]->closerShop, length, i);
			printPath(fout, map->VertexTab[i]->path, map->VertexTab[i]->closerShop, i);
			fprintf(fout, "  Czas przejscia: %4.1lfmin\n\n", map->VertexTab[i]->timeToShop / 2);
		}
	}
	fclose(fout);
}