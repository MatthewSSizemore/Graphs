// Matthew Sizemore
// CIS 2207 N02
// 19/SP
// Graphs 

#pragma once

#include <string>
#include <fstream>
using namespace std;

class Graph
{
private:
	int maxSize;		//Maximum Size
	int size;			// Current size
	int edges;			// number of edges
	int **graph;		// Adjacency Matrix
	bool isDirected;	// Is this a directed or undirected graph

	void printWeight(int *);

	void newMaxSize(int);
	void shortestPath(int, int, bool *, int *);

	int getWeight(int vertex1, int vertex2);

public:
	Graph();
	~Graph();

	//int **graph;		// Adjacency Matrix

	void print();
	bool addVertex();
	bool addEdge(int, int, int);
	bool removeVertex();
	bool removeVertex(int);
	bool removeEdge(int, int);
	void flip() { isDirected = !isDirected; }

	void clear();
	void shortestPath(int vertex1, int vertex2);

	// Homework:

	/// <summary>
	/// first clears then reads in a graph from a specified file
	/// </summary>
	bool read(string);

	/// <summary>
	/// writes the graph to a specified text file
	/// </summary>
	bool write(string);
	

};

