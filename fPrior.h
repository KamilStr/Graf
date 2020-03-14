#include<stdio.h>
#include<iostream>

typedef struct
{
	int nKey;
	double nPrio;

}QItem;

typedef struct
{
	QItem** queue;
	int nSize;
	int CurrSize;
}Queue;


Queue* Init(int nSize);
int isEmptyQueue(Queue* el);
void EnQueue(Queue* el, int nKey, double nPrio);
int DeQueue(Queue* el);
void FreeQueue(Queue** q);