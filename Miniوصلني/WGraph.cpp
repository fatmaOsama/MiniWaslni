#include "WGraph.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

#define INF INT_MAX

WGraph::WGraph(){}

void WGraph::AddNode(string x,int s) {
	AdjList.resize(s);
	int node = Dictionery[x];
	AdjList[node].push_back({ -1, -1 });
}

WGraph::WGraph(int s)
{
	AdjList.resize(s);
}

void WGraph::UpdateDictionery(int n){
	for (int i = Dictionery.size(); i < n; i++){
		string temp;
		cin >> temp;
		Dictionery[temp] = i;
	}
}

void WGraph::UpdateCost(string Start, string End, int NewCost){
	int start = Dictionery[Start], end = Dictionery[End];
	for (int i = 0; i < AdjList[start].size(); i++){
		if (AdjList[start][i].second == end){
			AdjList[start][i].first = NewCost;
		}
	}
	if (!d){
		for (int i = 0; i < AdjList[end].size(); i++){
			if (AdjList[end][i].second == start){
				AdjList[end][i].first = NewCost;
			}
		}
	}
}
void WGraph::AddEdge(int weight, string  from, string  to, bool directed){
	int f = Dictionery[from], t = Dictionery[to];
	AdjList[f].push_back(make_pair(weight, t));
	if (!directed){
		AdjList[t].push_back(make_pair(weight, f));
	}
}

void WGraph::DeleteGraph(){
	for (int i = 0; i < AdjList.size(); i++){
		AdjList[i].clear();
	}
	AdjList.clear();
}

void WGraph::Display(){
	for (int i = 0; i < AdjList.size(); i++){
		for (int j = 0; j < AdjList[i].size(); j++){
			cout << "( " << AdjList[i][j].first << "," <<Convert( AdjList[i][j].second) << " )";
			if (j == AdjList[i].size() - 1) cout << endl;
		}
	}
}

void WGraph::Dijkstra(string Start,string End){
	int start = Dictionery[Start], end = Dictionery[End];
	Intialize();
	///*if (AdjList[start].size() == 0 || AdjList[end].size() == 0){
	//	return;
	//}*/
	Cost[start] = 0;
	q.push(make_pair(0, start));
	PrevNode[start] = -1;
	while (!q.empty()){
		int prev = q.top().second;
		Checker[prev] = 1;
		q.pop();
		for (int i = 0; i < AdjList[prev].size(); i++){
			pair<int, int> temp = AdjList[prev][i];
			if (temp.first == -1) continue;
			if (Cost[temp.second] > temp.first + Cost[prev]){
				Cost[temp.second] = Cost[prev] + temp.first;
				PrevNode[temp.second] = prev;
				q.push(AdjList[prev][i]);
			}
		}
	}
}

void WGraph::checker(string  town1, string town2){
	int end = Dictionery[town1];
	if ((Cost[end] == 0 || Cost[end] == INF ) && town1 != town2){
		cout << "can't reach this town" << endl;
	}
	else{
		cout << "the total cost is : ";
		if (Cost[end] == INF) cout << 0 << endl;
		else cout << Cost[end] << endl;
		cout << "the shortest path is : " << endl;
		ShortestDisplay(end);
	}
}

void WGraph::ShortestDisplay(int end){
	if (end == -1) return;
	ShortestDisplay(PrevNode[end]);
	cout << Convert(end) << "	";
}

string WGraph::Convert(int n){
	map<string, int > ::iterator it = Dictionery.begin();
	while (it != Dictionery.end()){
		if (it->second == n){
			return it->first;
		}
		it++;
	}
}

void WGraph::Intialize(){
	for (int i = 0; i < AdjList.size(); i++){
		for (int j = 0; j < AdjList[i].size(); j++){
			Checker[AdjList[i][j].second] = 0;
			Cost[AdjList[i][j].second] = INF;
			PrevNode[AdjList[i][j].second] = -1;
		}
	}

}

void WGraph::DeleteNode(){
	cout << "Enter the node's name:";
	string delNode;
	cin >> delNode;
	int node = Dictionery[delNode];
	AdjList[node].clear();
	for (int i = 0; i < AdjList.size(); i++){
		for (int j = 0; j < AdjList[i].size(); j++){
			if (AdjList[i][j].second == node){
				AdjList[i].erase(AdjList[i].begin() + j);
			}
		}
	}
	Dictionery.erase(delNode);
}

void WGraph::DeleteEdge(){
	cout << "Enter the Node and it's destination node :";
	string source, dest;
	cin >> source >> dest;
	int s = Dictionery[source], d = Dictionery[dest];
	for (int i = 0; i < AdjList[s].size(); i++){
		if (AdjList[s][i].second == d){
			AdjList[s].erase(AdjList[s].begin() + i);
			break;
		}
	}
	if (!d){
		for (int i = 0; i < AdjList[d].size(); i++){
			if (AdjList[d][i].second == s){
				AdjList[d].erase(AdjList[d].begin() + i);
				break;
			}
		}
	}
}

void WGraph::Warshall_Floyd(){
	int x = Adj_matrix();
	for (int k = 0; k < x; k++){
		for (int i = 0; i < x; i++){
			for (int j = 0; j<x; j++){
				if (AdjMatrix1[i][j]>AdjMatrix1[i][k] + AdjMatrix1[k][j]){
					AdjMatrix1[i][j] = AdjMatrix1[i][k] + AdjMatrix1[k][j];
					ThePath[i][j] = ThePath[k][j];
				}
			}
		}
	}
	for (int i = 0; i < x; i++){
		for (int j = 0; j < x; j++){
			if (AdjMatrix1[i][j] == 0)
				ThePath[i][j] = '-';
		}
	}
	cout << "PLEASE ENTER A START NODE AND A DESTENATION NODE: " << endl;
	string start, des;
	cin >> start >> des;
	string CurrentNode = des;
	cout << "The shortest path between them is: ";
	cout << AdjMatrix1[Nodes[start]][Nodes[des]] << endl;
	while (CurrentNode != start){
		THEFINALPATH.push(CurrentNode);
		CurrentNode = ThePath[Nodes[start]][Nodes[CurrentNode]];
	}
	THEFINALPATH.push(start);
	cout << "The path is : ";
	while (!THEFINALPATH.empty()){
		cout << THEFINALPATH.top() << " ";
		THEFINALPATH.pop();
	}
	cout << endl;
}

int WGraph::Adj_matrix(){
	cout << "Please enter the number of nodes:  ";
	int x;
	string a;
	cin >> x;
	cout << "Enter the nodes ";
	for (int i = 0; i < x; i++){
		cin >> a;
		Nodes[a] = i;
	}
	int cost;
	string node1, node2;
	bool b;
	for (int i = 0; i < x; i++){
		for (int j = 0; j < x; j++){
			if (AdjMatrix1[i][j] == 0 && i != j){
				AdjMatrix1[i][j] = 100;

			}
			ThePath[i][j] = '-';
		}
	}
	cout << "If it is directed enter '1' else enter '0' : ";
	cin >> b;
	while (true){
		cout << "Enter 2 nodes and the cost between them : " << endl;
		cin >> node1;
		if (node1[0] == '0'){
			break;
		}
		cin >> node2 >> cost;
		AdjMatrix1[Nodes[node1]][Nodes[node2]] = cost;
		ThePath[Nodes[node1]][Nodes[node2]] = node1;
		if (!b){
			AdjMatrix1[Nodes[node2]][Nodes[node1]] = cost;
			ThePath[Nodes[node2]][Nodes[node1]] = node2;
		}

	}

	/*for (int i = 0; i < x; i++){
	for (int j = 0; j < x; j++){
	cout<<AdjMatrix1[i][j]<< " ";
	}
	cout << endl;
	}*/
	return x;
}

string WGraph::ReturnKey(int value){
	map <string, int>::iterator it;
	for (it = Nodes.begin(); it != Nodes.end(); it++){
		if (it->second == value){
			return it->first;
		}
	}

	return "z";
}

WGraph::~WGraph()
{
}

