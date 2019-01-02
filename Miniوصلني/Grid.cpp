#include "Grid.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;


Grid::Grid(int r, int c)
{
	row = r;
	column = c;
	grid = new Node*[row];
	for (int i = 0; i < row; i++){
		grid[i] = new Node[column];
	}
	//Intialize
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			grid[i][j].f = 10000;
			grid[i][j].g = 0; 
			grid[i][j].test = 0;
			grid[i][j].parentX = -1;
			grid[i][j].parentY = -1;
			grid[i][j].x = i;
			grid[i][j].y = j;
		}
	}
}

void Grid::IsValid(int sX,int sY,int eX, int eY){
	if (sX > row || sX <= 0){
		while (true){
			cout << "Invalid start x position, please try again..";
			cin >> sX;
			if (sX <= row && sX>0) break;
		}
	}
	if (sY > column || sY <= 0){
		while (true){
			cout << "Invalid start y position, please try again..";
			cin >> sY;
			if (sY <= column && sX>0) break;
		}
	}
	if (eX > row || eX <= 0){
		while (true){
			cout << "Invalid end x position, please try again..";
			cin >> eX;
			if (eX <= row && eX>0) break;
		}
	}
	if (eY > column || eY <= 0){
		while (true){
			cout << "Invalid end y position, please try again..";
			cin >> eY;
			if (eY <= column && eX>0) break;
		}
	}
}

void Grid::InputGrid(){
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			cin >> grid[i][j].value; //wether it's an obstical(1) or available node(0)
		}
		cout << endl;
	}
}

int Grid::Heuristic(Node current, Node goal){
	return(abs(current.x - goal.x) + abs(current.y - goal.y));
}

void Grid::Setter(Node* temp, int i, int j, int gConstant, int goalX, int goalY){
	if (grid[i][j].test == 1){
		return;
	}
	else{
		int fNew = temp->g + gConstant + Heuristic(grid[i][j], grid[goalX][goalY]);
		if (grid[i][j].f > fNew){
			grid[i][j].g = temp->g + gConstant;
			grid[i][j].f = fNew;
			grid[i][j].parentX = temp->x;
			grid[i][j].parentY = temp->y;
			//cout << "TEMP	" << temp->x << "	" << temp->y << "	" << temp->f <<"	"<<temp->parentX<<"	"<<temp->parentY<< endl;
			//cout << "GRID	" << i << "	" << j << "	" << grid[i][j].f <<"	"<< grid[i][j].parentX<<"	"<<grid[i][j].parentY<<endl << endl;
			pqGrid.push_back(&grid[i][j]);
			sort(pqGrid.begin(), pqGrid.end(), SORT());
		}

	}
}

void Grid::AStar(int startX, int startY, int goalX, int goalY){
	startX--, startY--, goalX--, goalY--;
	if (grid[startX][startY].value == '1' || grid[goalX][goalY].value == '1'){
		cout << "Start or End are obstacles, can't generate a path" << endl;
		return;
	}
	grid[startX][startY].f = 0, grid[startX][startY].g = 0;
	pqGrid.push_back(&grid[startX][startY]);
	sort(pqGrid.begin(), pqGrid.end(), SORT());
	while (!pqGrid.empty()){
		Node* temp = pqGrid[0];
		pqGrid.erase(pqGrid.begin());
		temp->test = 1;
		if (temp->x == goalX && temp->y == goalY) break; //EARLY EXIT !
		int i = temp->x + 1, j = temp->y - 1;
		if (i < row && j >= 0 && grid[i][j].value == '0'){  //1
			Setter(temp, i, j, 14, goalX, goalY);
		}
		j = temp->y + 1;
		if (i < row && j < column && grid[i][j].value == '0'){  //2
			Setter(temp, i, j, 14, goalX, goalY);
		}
		j = temp->y;
		if (i < row && grid[i][j].value == '0'){ //3
			Setter(temp, i, j, 10, goalX, goalY);
		}
		i = temp->x - 1, j = temp->y - 1;
		if (i >= 0 && j >= 0 && grid[i][j].value == '0'){ //4
			Setter(temp, i, j, 14, goalX, goalY);
		}
		j = temp->y;
		if (i >= 0 && grid[i][j].value == '0'){  //5
			Setter(temp, i, j, 10, goalX, goalY);
		}
		j = temp->y + 1;
		if (i >= 0 && j < column && grid[i][j].value == '0'){//6
			Setter(temp, i, j, 14, goalX, goalY);
		}
		i = temp->x, j = temp->y + 1;
		if (j < column && grid[i][j].value == '0'){ //7
			Setter(temp, i, j, 10, goalX, goalY);
		}
		j = temp->y - 1;
		if (j >= 0 && grid[i][j].value == '0'){ //8
			Setter(temp, i, j, 10, goalX, goalY);
		}
	}

	//Display
	stack<pair<int, int>> container;
	while (true){
		grid[goalX][goalY].value = '*';
		if (startX == goalX && startY == goalY){
			container.push(make_pair(goalX, goalY));
			break;
		}
		else{
			container.push(make_pair(goalX, goalY));
			int n = grid[goalX][goalY].parentX, m = grid[goalX][goalY].parentY;
			goalX = n, goalY = m;
		}
	}
	while (!container.empty()){
		pair<int, int> temp = container.top();
		container.pop();
		cout << "(" << temp.first + 1 << "," << temp.second + 1 << ")	";
	}
	cout << endl;
}

void Grid::trial(){
	grid[0][0].g = 100;
	pqGrid.push_back(&grid[0][0]);
	sort(pqGrid.begin(), pqGrid.end(), SORT());
	grid[0][0].g = 220;
	Node* temp = pqGrid[0];
	pqGrid.erase(pqGrid.begin());
	cout << grid[0][0].g << " " << temp->g << endl;

}

void Grid::Display(){
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			cout << grid[i][j].value <<" ";
		}
		cout << endl;
	}
}

Grid::~Grid()
{
	for (int i = 0; i < row; i++){
		delete[] grid[i];
	}
	delete[] grid;
}
