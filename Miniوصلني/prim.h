#pragma once
#include<vector>
#include<iostream>
#include<queue>
#include<functional>
#include<map>

using namespace std;

class prim
{
	int size;
	int node;
	vector< vector< pair<int, int> > > adjlist;
	map<string, int> mapp;
	map<string, bool> validation;
	bool *visited;
	int *cost;
	long long final_result;
	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > >pq;
public:
	prim(int inp_node);
	void transform();
	void AddEdge();
	void prim_function();
	void result();
	~prim(void);
};

