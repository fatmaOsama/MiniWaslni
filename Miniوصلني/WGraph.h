#pragma once
#include <vector>
#include <queue>
#include <map>
#include <stack>
using namespace std;

struct Compare
{
	bool operator()(pair<int, int> m, pair<int, int>n)
	{
		return m.first < n.first;
	}
};


class WGraph
{
	int ID;
	map<int, int> Cost, Checker;
	map<int, int > PrevNode;
	vector< vector<pair<int, int >> > AdjList;
	priority_queue<pair <int, int >, vector<pair<int, int >>, Compare > q;
	int AdjMatrix1[100][100] = {};
	string ThePath[100][100];
	map<string, int>Nodes;
	stack<string>THEFINALPATH;
public:
	bool d;
	map<string, int> Dictionery;
	void AddNode(string,int);
	WGraph();
	WGraph(int);
	void UpdateDictionery(int);
	void AddEdge(int, string, string, bool);
	void Display();
	void Dijkstra(string,string);
	void checker(string town1 , string town2);
	void Intialize();
	string Convert(int);
	void ShortestDisplay(int);
	void DeleteNode();
	void DeleteEdge();
	void DeleteGraph();
	void UpdateCost(string ,string ,int);
	string ReturnKey(int value);
	int Adj_matrix();
	void Warshall_Floyd();
	~WGraph();
};

