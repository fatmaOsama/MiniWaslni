#include <iostream>
#include "WGraph.h"
#include "prim.h"
#include "Grid.h"
#include <string>
using namespace std;

int main(){


	int cost = 1, Id, TownNumber, algo;
	bool directed;
	string town1, town2;
	cout << "Enter the graph ID : ";
	cin >> Id;
	cout << "\n If you want to use Dijkstra press 1\n If you want to use Prim's algorithm press 2\n If you want to use A* press 3\n If you want to use Floyd Warshel press 4\n";
	cin >> algo;
	if (algo == 2){  //prim
		cout << "enter the number of towns " << endl;
		int num;
		cin >> num;
		prim problem(num);
		problem.transform();
		problem.AddEdge();
		problem.prim_function();
		problem.result();
	}
	else if (algo == 3){ //A*
		int row, col;
		cout << "Enter the size of your grid :";
		cin >> row >> col;
		Grid g(row, col);
		cout << "Enter your " << row << "x" << col << " grid" << endl;
		g.InputGrid();
		cout << "Enter the start and end x y positions :";
		int sX, sY, eX, eY;
		cin >> sX >> sY >> eX >> eY;
		g.IsValid(sX, sY, eX, eY);
		g.AStar(sX, sY, eX, eY);
		g.Display();
	}
	else if (algo == 4){  //Floyd
		WGraph f;
		f.Warshall_Floyd();
	}
	else if (algo == 1){ //Dijkstra
		cout << "If the graph is directed press '1' else press '0' : ";
		cin >> directed;
		cout << "Enter the number of towns : ";
		cin >> TownNumber;
		WGraph g(TownNumber);
		g.d = directed;
		cout << "Enter the names of the towns : ";
		g.UpdateDictionery(TownNumber);
		cout << "If you want to stop enter STOP..." << endl;
		while (true){
			cout << "Enter the current town,destination town and the cost " << endl;
			cin >> town1;
			if (town1 == "STOP" || town1 == "stop") break;
			cin >> town2 >> cost;
			g.AddEdge(cost, town1, town2, directed);
		}
		while (true){
			g.Intialize();
			cout << "To find the shortest path press 1\nTo delete a node press 2\nTo delete an edge press 3\nTo add a node press 4\nTo add an edge press5\nTo display press 6\nTo exit press 7" << endl;
			cout << "To delete graph press 8" << endl;
			cout << "To update a cost press 9" << endl;
			int choice;
			cin >> choice;
			if (choice == 7) break;
			else if (choice == 6){
				g.Display();
			}
			else if (choice == 1){
				cout << "Enter start and end towns : ";
				cin >> town1 >> town2;
				g.Dijkstra(town1,town2);
				g.checker(town2,town1);
				cout << endl;
			}
			else if (choice == 2){
				g.DeleteNode();
			}
			else if (choice == 3){
				g.DeleteEdge();
			}
			else if (choice == 4){
				cout << "Enter the node name: ";
				cin >> town1;
				g.Dictionery[town1] = TownNumber;
				TownNumber++;
				g.AddNode(town1,TownNumber);
			}
			else if (choice == 5){
				cout << "Enter the current town,destination town and the cost " << endl;
				cin >> town1;
				cin >> town2 >> cost;
				g.AddEdge(cost, town1, town2, directed);
			}
			else if (choice == 8){
				g.DeleteGraph();
			}
			else if (choice == 9){
				cout << "Enter the current node , destination node and the new cost : " << endl;
				cin >> town1 >> town2;
				int newCost;
				cin >> newCost;
				g.UpdateCost(town1, town2, newCost);
			}
			else cout << "Out of range,please try again.." << endl;
		}
	}
	else {
		cout << "OUT OF RANGE" << endl;
	}
	system("pause");
	return 0;
}
