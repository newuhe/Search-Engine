#include "Graph.h"

template<class T,class E>
Graph<T,E>::Graph(int sz )
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = (int **)new int *[maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new int[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : 100;
}

template<class T, class E>
bool Graph<T,E>::insertVertex(const T & vertex)
{
	if (numVertices == maxVertices) return false;
	VerticesList[numVertices] = vertex;
	numVertices++;
	return true;
}

template<class T, class E>
bool Graph<T,E>:: insertEdge(int v1, int v2, E cost)
{
	if (v1>-1 && v1<numVertices&&v2>-1 && v2 < numVertices&&Edge[v1][v2] == 100)
	{
		Edge[v1][v2] =cost;
		numEdges++;
		return true;
	}
	else return false;
}

template<class T, class E>
int Graph<T,E>::getFirstNeighbour(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < 100) return col;
	}
	return -1;
}

template<class T, class E>
int Graph<T,E>::getNextNeighbour(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col == w + 1; col < numVertices; col++)
			if (Edge[v][col]>0 && Edge[v][col] < 100) return col;
	}
	return -1;
}



template<class T, class E>
int Graph<T,E>::getOutDegree(int v)
{
	int outdegree=0;
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < 100) outdegree++;
	}
	return outdegree;
}

template<class T, class E>
int Graph<T, E>::getInDegree(int v)
{
	int indegree = 0;
	if (v != -1)
	{
		for (int row = 0; row < numVertices; row++)
			if (Edge[row][v] > 0 && Edge[row][v] < 100) indegree++;
	}
	return indegree;
}

template<class T, class E>
int Graph<T,E>::getWeight(int v1, int v2)
{
	int w;
	w = Edge[v1][v2];
	return w;
}