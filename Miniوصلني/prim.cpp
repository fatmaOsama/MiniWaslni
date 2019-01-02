#include "prim.h"
#include<vector>
#include<queue>
#include<algorithm>
#include<iostream>
#include<functional>
#include<string>
#include<map>

using namespace std;


prim::prim(int inp_node)
{
	node = inp_node;
	size = 50000;
	final_result = 0;
	adjlist.resize(size);
	visited = new bool[size];
	cost = new int[size];
	for (int i = 0; i<size; i++){ visited[i] = false; }
	for (int i = 0; i<size; i++){ cost[i] = 1000000000; }
}

void prim::transform()
{
	cout << "enter towns name \n";
	string town;
	for (int i = 0; i<node; i++){
		cin >> town;
		mapp[town] = i;
		validation[town] = true;
	}
}

void prim::AddEdge()
{
	int last, current, cost;
	string from, to;
	char choice;
	bool valid = true;
	while (true){
		cout << "Do you want to add an edge ? \n (y/n)" << endl;
		valid = true;
		while (valid == true){
			cin >> choice;
			if (choice == 'n' || choice == 'N' || choice == 'Y' || choice == 'y'){ valid = false; }
			else{
				cout << "Invalid choice , please try again " << endl;
			}
		}
		if (choice == 'n' || choice == 'N'){ break; }
		else{
			cout << "Enter the current place :" << endl;
			valid = true;
			while (valid == true){
				cin >> from;
				if (validation[from] == false){
					cout << "Invalid town , please try again" << endl;
				}
				else{ valid = false; }
			}
			cout << endl << "Enter the destination :" << endl;
			valid = true;
			while (valid == true){
				cin >> to;
				if (validation[to] == false){
					cout << "Invalid town , please try again" << endl;
				}
				else{ valid = false; }
			}
			cout << endl << "Enter the cost :" << endl;
			cin >> cost;
			cout << endl;
			last = mapp[from];
			current = mapp[to];
			adjlist[current].push_back(make_pair(cost, last));
			adjlist[last].push_back(make_pair(cost, current));

		}
	}
}
void prim::prim_function()
{
	pq.push(make_pair(0, 0));
	cost[0] = 0;
	while (!pq.empty()){
		int current_node = pq.top().second;
		int current_cost = pq.top().first;
		pq.pop();
		if (visited[current_node] == false){
			visited[current_node] = true;
			final_result += (current_cost);
			for (int i = 0; i != adjlist[current_node].size(); i++){
				if (visited[adjlist[current_node][i].second] == false && adjlist[current_node][i].first<cost[adjlist[current_node][i].second]){
					pq.push(adjlist[current_node][i]);
					cost[adjlist[current_node][i].second] = adjlist[current_node][i].first;
				}
			}
		}
	}
}

void prim::result()
{
	cout << "The total distance is : " << final_result << endl;
}


prim::~prim(void)
{
	delete visited;
	delete cost;
}
