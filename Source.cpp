// Matthew Sizemore
// CIS 2207 N02
// 19/SP
// Graphs 

#include "Graph.h"

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>

using namespace std;


// prototyes
void menu();


int main()
{
	Graph testGraph;
	// testGraph.flip();  // Uncomment to test directed graph
	
	testGraph.addVertex(); // 0
	testGraph.addVertex(); // 1
	testGraph.addVertex(); // 2
	testGraph.addVertex(); // 3
	testGraph.addVertex(); // 4
	testGraph.addVertex(); // 5

	testGraph.addEdge(0, 4, 9);
	testGraph.addEdge(0, 2, 7);
	testGraph.addEdge(2, 3, 1);
	testGraph.addEdge(2, 1, 5);
	testGraph.addEdge(2, 5, 2);

	
	testGraph.write("Input.txt");


	Graph testGraph2;
	testGraph2.read("Input");
	testGraph2.print();


	
	//menu();  // this can be uncommented if you would like to run process manually

	system("pause");
	return 0;
}


char getChoice()
{

	cout << "Choice: " << endl;
	cout << "\tQ -- Quit" << endl;
	cout << "\tP -- Print" << endl;
	cout << "\tN -- New Vertex" << endl;
	cout << "\tA -- New Edge" << endl;
	cout << "\tR -- Remove Edge" << endl;
	cout << "\tD -- Remove Vertex" << endl;
	cout << "\tL -- Load (Read) Graph" << endl;
	cout << "\tW -- Write Graph" << endl;
	cout << "\tS -- ShortestPath Test" << endl;
	cout << "\tF -- Flip Undirected / Directed Graph" << endl;

	cout << endl;
	cout << "Enter Choice: ";

	char c = _getch();

	while (!(
		c == 'P' || c == 'p' ||
		c == 'N' || c == 'n' ||
		c == 'A' || c == 'a' ||
		c == 'R' || c == 'r' ||
		c == 'D' || c == 'd' ||
		c == 'L' || c == 'l' ||
		c == 'W' || c == 'w' ||
		c == 'S' || c == 's' ||
		c == 'F' || c == 'f' ||
		c == 'Q' || c == 'q'
		))
	{
		cout << "Error, you entered a '" << c << "'" << endl;
		cout << "Enter Choice: ";
		c = _getch();
	}

	c = _toupper(c);

	cin.clear();
	return c;
}

void menu()
{
	Graph graph;
	char choice = getChoice();
	
	while (choice != 'Q')
	{
		int newValue;
		string newString;
		string filename;
		bool returnCode;
		int vertex1, vertex2, weight;

		cout << endl;

		switch (choice)
		{
		case 'P':
			graph.print();
			break;
		case 'N':
			returnCode = graph.addVertex();

			if (returnCode == true)
				cout << "Vertex Added" << endl;
			else
				cout << "Vertex Not Added" << endl;

			break;
		case 'A':
			cout << "Enter Vertex 1: ";
			cin >> vertex1;

			cout << "Enter Vertex 2: ";
			cin >> vertex2;

			cout << "Enter Weight: ";
			cin >> weight;

			returnCode = graph.addEdge(vertex1, vertex2, weight);

			if (returnCode)
				cout << "Edge Added" << endl;
			else
				cout << "Edge NOT Added" << endl;
			break;
		case 'R':
			cout << "Enter Vertex 1: ";
			cin >> vertex1;
			cout << "Enter Vertex 2: ";
			cin >> vertex2;

			returnCode = graph.removeEdge(vertex1, vertex2);

			if (returnCode)
				cout << "Edge Removed" << endl;
			else
				cout << "Edge NOT Removed" << endl;

			break;
		case 'D':
			cout << "Enter a Vertex to remove: ";
			cin >> vertex1;

			returnCode = graph.removeVertex(vertex1);

			if (returnCode)
				cout << "Vertex Removed" << endl;
			else
				cout << "Vertex NOT Removed" << endl;

			break;
		case 'L':
			cout << "Enter a filename to load from: ";
			cin >> filename;

			graph.read(filename);
			break;
		case 'W':
			cout << "Enter a filename to save to: ";
			cin >> filename;

			graph.write(filename);
			break;
		case 'S':
			cout << "Enter a start vertex: ";
			cin >> vertex1;
			cout << "enter an end vertex: ";
			cin >> vertex2;

			graph.shortestPath(vertex1, vertex2);
			break;
		case 'F':
			graph.flip();
			break;
		}


		choice = getChoice();
	}

}


