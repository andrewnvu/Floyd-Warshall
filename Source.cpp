/*Name:			Andrew Vu
  Contact: 		avu916@csu.fullerton.edu
  Description:	The following program tests the Floyd-Warshall algorithm upon a Pitchers puzzle.
				There are three pitchers that can, respectively, hold 16, 9 or 7 quarts.
				We are trying to find the optimal number of steps to get from one configuration to another.
				Floyd-Warshall's algorithm will help us find that optimal number.
				i.e. (16,0,0) to (8,8,0) = 15 steps

  References:	geeksforgeeks.org
*/



#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

// Number of vertices/Configurations
#define V 32

// Infinity represents edges which two vertices are not connected
#define INF 99999


void floydWarshall(int graph[][V]);
void printSolution(int steps[][V]);

int main()
{
	//Constructed a 32x32 matrix, please look at ScratchWork.pdf and Matrix.xlsx as to see how I constructed this matrix
	int graph[V][V] = {
	{   0,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF,    1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{   1,     0,    1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,    1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{   1,     1,    0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF,  INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{   1,   INF,  INF,   0,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,    1,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{   1,   INF,  INF,   1,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF,  INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{   1,   INF,  INF, INF, INF,   0,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,    1, INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{   1,   INF,  INF, INF, INF,   1,   0, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF,  INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF },
	{   1,   INF,  INF, INF, INF, INF, INF,   0,   1, INF, INF, INF, INF, INF, INF, INF, INF,    1, INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{   1,   INF,  INF, INF, INF, INF, INF,   1,   0, INF, INF, INF, INF, INF,   1, INF, INF,  INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF },
	{   1,   INF,  INF, INF, INF, INF, INF, INF, INF,   0,   1, INF, INF, INF, INF, INF, INF,    1, INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF, INF },
	{   1,   INF,  INF, INF, INF, INF, INF, INF, INF,   1,   0, INF, INF, INF,   1, INF, INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF },
	{   1,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   1, INF, INF, INF, INF,    1, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF, INF },
	{   1,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,   0, INF,   1, INF, INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF },
	{   1,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   1, INF, INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF, INF },
	{   1,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,   0, INF, INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1 },
	{   1,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   1,    1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF },
	{ INF,     1,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,   1,   0,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1 },
	{   1,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,    0,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF,    1,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1 },
	{ INF,   INF,    1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,    1, INF,   0,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,  INF,   1,   1,   0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,    1, INF, INF, INF,   0,   1, INF, INF, INF, INF, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF,   1, INF, INF,  INF, INF, INF, INF,   1,   0, INF, INF, INF, INF, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,    1, INF, INF, INF, INF, INF,   0,   1, INF, INF, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF,   1, INF, INF,  INF, INF, INF, INF, INF, INF,   1,   0, INF, INF, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF, INF, INF,    1, INF, INF, INF, INF, INF, INF, INF,   0,   1, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF,   1, INF, INF,  INF, INF, INF, INF, INF, INF, INF, INF,   1,   0, INF, INF, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF, INF, INF,    1, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   1, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,   1, INF, INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,   0, INF, INF,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF, INF, INF,    1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0,   1,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,   1, INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1,   0,   1 },
	{ INF,   INF,  INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   1, INF, INF,    1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF,   0 },
	};

	// Prints the solution																																			
	floydWarshall(graph);

	system("PAUSE");
	return 0;
}

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall(int graph[][V])
{
	//steps represents the output matrix
	int steps[V][V], i, j, k;

	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			steps[i][j] = graph[i][j];

	for (k = 0; k < V; k++)
	{
		for (i = 0; i < V; i++)
		{
			for (j = 0; j < V; j++)
			{
				if (steps[i][k] + steps[k][j] < steps[i][j])
					steps[i][j] = steps[i][k] + steps[k][j];
			}
		}
	}

	// Print the shortest distance matrix
	printSolution(steps);
}

void printSolution(int steps[][V])
{
	//lists out every possible pitcher configurations 
	string vertexList[V] = {
		"  (0,9,7)", "  (1,8,7)", "  (1,9,6)", "  (2,7,7)", "  (2,9,5)", "  (3,6,7)", "  (3,9,4)", "  (4,5,7)", "  (4,9,3)", "  (5,4,7)",
		" (5,9,2)", " (6,3,7)", " (6,9,1)", " (7,2,7)", " (7,9,0)"," (8,1,7)", " (8,8,O)", " (9,0,7)", " (9,7,0)", "(10,0,6)", "(10,6,0)",
		"(11,0,5)", "(11,5,0)", "(12,0,4)", "(12,4,0)", "(13,0,3)", "(13,3,0)", "(14,0,2)", "(14,2,0)", "(15,0,1)", "(15,1,0)", "(16,0,0)"
	};

	//description
	printf("Following matrix shows the shortest distances "
		"between every pair of vertices or configuration\n"
		"The number of above the line of the matrix represents the states of the three pitchers\n"
		"You can reference the vertex list on the left hand side as a key\n"
		"Matrix entries represent the optimal number of steps from the ROW to COLUMN\n"
		"PLEASE NOTE *** The number only represents the CONFIGURATION and only that!\n\n"
		"\n\t     ");

	//displays state number representing columns
	for (int i = 0; i < V; i++) {
		printf("%7d", i);
	}
	//for easier viewing experience
	cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
		<< "---------------------------------------------------------";
	cout << endl;
	for (int i = 0; i < V; i++)
	{
		//displays vertices on the left hand side
		cout << i << ": " << vertexList[i] << "|";

		for (int j = 0; j < V; j++)
		{
			if (steps[i][j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", steps[i][j]);
		}
		printf("\n");
	}
	cout << endl << endl;
}