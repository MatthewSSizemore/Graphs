// Matthew Sizemore
// CIS 2207 N02
// 19/SP
// Graphs 

#include "Graph.h"

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

Graph::Graph()
{
	size = 0;
	maxSize = 3;
	isDirected = false;

	graph = new int *[maxSize];

	for (int index = 0; index < maxSize; index++)
	{
		graph[index] = new int[maxSize];

		for (int jndex = 0; jndex < maxSize; jndex++)
			graph[index][jndex] = 0;
	}
}


Graph::~Graph()
{
	for (int index = 0; index < maxSize; index++)
		delete[] graph[index];

	delete[] graph;
}

void Graph::print()
{
	int width = 0;

	for (int index = 0; index < size; index++)
		for (int jndex = 0; jndex < size; jndex++)
			if (log10(graph[index][jndex]) > width)
				width = log10(graph[index][jndex]);

	width++;

	cout << "\n\nSize: " << size << endl;
	cout << "Edges: " << edges << endl;
	//	cout << "Width: " << width << endl;
	if (isDirected)
		cout << "Directed: true" << endl;
	else
		cout << "Directed: false" << endl;


	cout << setw(log10(size) + 1) << " " << "  ";
	for (int jndex = 0; jndex < size; jndex++)
		cout << setw(width + 1) << jndex << "  ";
	cout << endl;

	for (int index = 0; index < size; index++)
	{
		cout << setw(log10(size) + 1) << index << " | ";

		for (int jndex = 0; jndex < size; jndex++)
			cout << setw(width) << graph[index][jndex] << " | ";

		cout << endl;
	}
	cout << endl << endl << endl;
}

void Graph::newMaxSize(int newMaxSize)
{
	if (maxSize >= newMaxSize)
	{
		cerr << "Already large enough..." << endl;
		return;
	}

	int **newMatrix = new int *[newMaxSize];

	for (int index = 0; index < newMaxSize; index++)
	{
		newMatrix[index] = new int[newMaxSize];

		for (int jndex = 0; jndex < newMaxSize; jndex++)
			newMatrix[index][jndex] = 0;
	}

	for (int index = 0; index < size; index++)
		for (int jndex = 0; jndex < size; jndex++)
			newMatrix[index][jndex] = graph[index][jndex];

	for (int index = 0; index < size; index++)
		delete[] graph[index];

	delete[] graph;

	graph = newMatrix;

	maxSize = newMaxSize;
}

bool Graph::addVertex()
{
	// Is there room?
	if (size == maxSize)
	{
		newMaxSize(size * 2);
	}

	// add vertex to end of vertices
	size++;

	return true;
}

bool Graph::addEdge(int vertex1, int vertex2, int weight)
{
	if (vertex1 == vertex2)
	{
		cerr << "Can not have Vertex1 = Vertex2" << endl;
		return false;
	}

	if (vertex1 < 0 || vertex1 >= size)
	{
		cerr << "Vertex 1 is out of bounds" << endl;
		return false;
	}

	if (vertex2 < 0 || vertex2 >= size)
	{
		cerr << "Vertex 2 is out of bounds" << endl;
		return false;
	}

	if (weight <= 0)
	{
		cerr << "Edge Weight is out of bounds" << endl;
		return false;
	}

	if (isDirected)
	{
		graph[vertex1][vertex2] = weight;
		edges++;
	}
	else
	{
		graph[vertex1][vertex2] = weight;
		graph[vertex2][vertex1] = weight;
		edges++;
	}

	return true;
}


bool Graph::removeEdge(int vertex1, int vertex2)
{
	if (graph[vertex1][vertex2] == 0)
	{
		cerr << "Not needed, already empty" << endl;
		return false;
	}

	if (isDirected)
	{
		graph[vertex1][vertex2] = 0;
		edges--;
	}
	else
	{
		graph[vertex1][vertex2] = 0;
		graph[vertex2][vertex1] = 0;
		edges--;
	}

	return true;
}

// Removes the last vertex
bool Graph::removeVertex()
{
	if (size == 0)
	{
		cerr << "You have an empty graph alread" << endl;
		return false;
	}

	// find any graph edge who has a vertex >= size and remove it.
	for (int index = 0; index < size; index++)
		if (graph[size - 1][index] > 0 || graph[index][size - 1] > 0)
		{
			// We have a choice, either remove it or throw an error
			// Remove it
			removeEdge(index, size - 1);
		}

	size--;

	return true;
}

// Removes the nth vertex
bool Graph::removeVertex(int vertex)
{
	if (size == 0)
	{
		cerr << "You have an empty graph already" << endl;
		return false;
	}
	if (vertex < 0 || vertex >= size)
	{
		cerr << "Vertex is out of bounds" << endl;
		return false;
	}

	if (vertex == size - 1)
		return removeVertex();

	for (int index = vertex; index < size - 1; index++)
		for (int jndex = 0; jndex < size; jndex++)
		{
			if (index != jndex)
			{
				//				cout << index << "," << jndex << " << " << index +1 << "," << jndex << endl;
				graph[index][jndex] = graph[index + 1][jndex];
				graph[jndex][index] = graph[jndex][index + 1];
			}
		}

	//	print();

	return removeVertex();
	//	return true;
}

void Graph::clear()
{
	for (int index = 0; index < size; index++)
		for (int jndex = 0; jndex < size; jndex++)
			graph[index][jndex] = 0;

	size = 0;
	edges = 0;
}

void Graph::printWeight(int *weight)
{
	for (int index = 0; index < size; index++)
		cout << weight[index] << " ";
	cout << endl;
}

void Graph::shortestPath(int vertex1, int index, bool *visited, int *weight)
{
	for (int jndex = 0; jndex < size; jndex++)
	{
		if (!visited[jndex] && graph[index][jndex] != 0)
		{
			visited[jndex] = true;
			weight[jndex] = graph[index][jndex];
		}
	}

	printWeight(weight);
}

void Graph::shortestPath(int vertex1, int vertex2)
{
	int *newWeight = new int[size];
	bool *visited = new bool[size];


	for (int index = 0; index < size; index++)
	{
		if (index == vertex1)
			newWeight[index] = 0;
		else
			newWeight[index] = 1000000;

		visited[index] = false;
	}

	for (int index = 0; index < size; index++)
	{
		if (!visited[index] && graph[vertex1][index] != 0)
			shortestPath(vertex1, index, visited, newWeight);
	}

	printWeight(newWeight);

	cout << "Found weight of " << newWeight[vertex1] << endl;

}


bool Graph::read(string filename)
{
	int numVertices = 0;
	char directed = false;

	if (filename.length() > 0)
	{
		filename = ((filename.find(".txt") != string::npos) ? filename : (filename + ".txt")); // if filename does not have '.txt' at the end add it

		ifstream myfile(filename);

		if (myfile.is_open())
		{
			myfile >> numVertices;
			myfile >> directed;

			clear();

			if (directed == 'd' || directed == 'D')
			{
				flip();
			}

			for (int i = 0; i < numVertices; i++)
			{
				addVertex();
			}


			for (int i = 0; i < numVertices; i++)
			{
				int v1;
				int v2;
				int wt;

				myfile >> v1;
				myfile >> v2;
				myfile >> wt;

				addEdge(v1, v2, wt);
			}
			
			myfile.close();
		}
		else
		{
			cerr << "Unable to open file";
		}

		return true;
	}
	else
	{
		cerr << "Filename can't be empty" << endl;
		return false;
	}
}


bool Graph::write(string filename)
{

	if (filename.length() > 0)
	{		
		filename = (filename.find(".txt") != string::npos) ? filename : (filename + ".txt"); // if filename does not have '.txt' at the end add it

		ofstream myfile(filename);

		if (myfile.is_open())
		{

			cout << size << endl; 
			myfile << size << endl; 

			if (!isDirected)
			{
				cout << "U" << endl;
				myfile << "U" << endl;
			}
			else
			{
				cout << "D" << endl;
				myfile << "D" << endl;
			}

			Graph tempGraph;
			tempGraph.flip(); // make it directed
			for (int i = 0; i < size; i++) // add the same number of vertices as graph to tempGraph
				tempGraph.addVertex();

			for (int index = 0; index < size; index++)
			{
				for (int jndex = 0; jndex < size; jndex++)
				{
					if (graph[index][jndex] > 0 && index <= tempGraph.size && jndex <= tempGraph.size)
					{
						if (tempGraph.getWeight(index, jndex) == 0 && tempGraph.getWeight(jndex, index) == 0)
						{
							tempGraph.addEdge(index, jndex, graph[index][jndex]);
						}
					}
				}
			}

			for (int index = 0; index < size; index++)
			{
				for (int jndex = 0; jndex < size; jndex++)
				{
					if (tempGraph.graph[index][jndex] > 0)
					{
						cout << index << " " << jndex << " " << tempGraph.graph[index][jndex] << endl;
						myfile << index << " " << jndex << " " << tempGraph.graph[index][jndex] << endl;
					}
				}
			}
			

			myfile.close();
		}
		else
		{
			cerr << "Unable to open file" << endl;
			return false;
		}
		
		return true;
	}
	else
	{
		cerr << "Filename can't be empty" << endl;
		return false;
	}
}

/// <summary>
/// gets the weight from the specified vertices. If a vertex doesn't exist it will return '-1'
/// </summary>
int Graph::getWeight(int vertex1, int vertex2)
{

	if (vertex1 == vertex2)
	{
		//cerr << "Can not have Vertex1 = Vertex2" << endl;
		return -1;
	}

	if (vertex1 < 0 || vertex1 >= size)
	{
		//cerr << "Vertex 1 is out of bounds" << endl;
		return -1;
	}

	if (vertex2 < 0 || vertex2 >= size)
	{
		//cerr << "Vertex 2 is out of bounds" << endl;
		return -1;
	}

	if (graph[vertex1][vertex2] <= 0)
	{
		//cerr << "Edge Weight is out of bounds" << endl;
		return 0;
	}

	
	return graph[vertex1][vertex2];		
}