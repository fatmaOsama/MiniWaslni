#pragma once
#include <iostream>
#include <queue>
#include <limits>
using namespace std;


class Node{
public:
	int f, g;
	char value;
	int x, y;
	int parentX, parentY;
	bool test;
	Node(){};
	~Node(){};
};

struct SORT
{
	bool operator()(Node* m, Node* n)
	{
		return m->f < n->f;
	}
};

class Grid
{
	int row, column;
	Node **grid;
	vector<Node*> pqGrid;

public:
	Grid(int, int);
	void InputGrid();
	void IsValid(int, int, int, int);
	int Heuristic(Node, Node);
	void AStar(int, int, int, int);
	void Setter(Node*, int, int, int, int, int);
	void Display();
	void trial();
	~Grid();
};

