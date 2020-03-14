#include "fPrior.h"
void UpdateDown(Queue* el, int l, int p)
{
	if (l == p) return;
	int v = l;
	int right = 2 * v + 1;
	QItem* x = el->queue[v];
	while (right <= p)
	{
		if (right < p)
			if (el->queue[right]->nPrio > el->queue[right + 1]->nPrio) right++;
		if (x->nPrio < el->queue[right]->nPrio) break;
		el->queue[v] = el->queue[right];
		v = right;
		right = 2 * v + 1;
	}
	el->queue[v] = x;
}


void UpdateUp(Queue* el, int l, int p)
{
	if (l == p) return;

	int i = p;
	int j = (i - 1) / 2;
	QItem* tmp = el->queue[i];

	while (i > l && tmp->nPrio < el->queue[j]->nPrio)
	{
		el->queue[i] = el->queue[j];
		i = j;
		j = (i - 1) / 2;
	}

	el->queue[i] = tmp;

}


Queue* Init(int nSize)
{
	Queue* p = (Queue*)calloc(1, sizeof(Queue));

	if (!p)
	{
		printf("nie udalo sie stworzyc elementu");
		return 0;
	}

	p->queue = (QItem**)calloc(nSize, sizeof(QItem*));

	if (!p->queue)
	{
		printf("nie udalo sie stworzyc kolejki");
		free(p);
		return 0;

	}

	p->CurrSize = 0;
	p->nSize = nSize;
	return p;

}


void EnQueue(Queue* el, int nKey, double nPrio)
{
	if (el->CurrSize == el->nSize)
	{
		printf("kolejka jest pelna");
		return;

	}
	QItem* p = (QItem*)malloc(sizeof(QItem));

	if (!p)
	{
		printf("nie udalo sie stworzyc elementu");
		return;

	}

	p->nKey = nKey;
	p->nPrio = nPrio;

	el->queue[el->CurrSize] = p;
	UpdateUp(el, 0, el->CurrSize++);




}


int DeQueue(Queue* el)
{
	if (isEmptyQueue(el))
	{
		printf("kolejka jest pusta");
		return 0;

	}

	int p = el->queue[0]->nKey; // zdejmuje 1 element

	free(el->queue[0]);

	el->queue[0] = el->queue[--(el->CurrSize)];
	UpdateDown(el, 0, el->CurrSize);
	return p;

}

void FreeQueue(Queue** q)
{
	Queue* el = *q;
	QItem** p = el->queue;

	for (int i = 0; i < el->CurrSize; i++)
	{
		free(*p++); // zwalniam elementy tablicy

	}
	free(el->queue);// zwalniam tablice
	free(el);// zwalniam cala kolejke

	*q = NULL;

}

int isEmptyQueue(Queue* el)
{
	return !el->CurrSize;
}
