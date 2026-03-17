#include "./graph.h"
#include "graph.h"
#include <deque>

static std::deque<int> queue;

/// @brief init an adjacent list
/// @param relation int **, relation between vertex and vertex
/// @param total int, len(relation)
/// @param rowLens int *, rowLen[i] = len(relation[i]) = 1, 2 
/// @param amount int, amount of vertex
/// @example input: {{1},{2,3}}, 2, {1,2}, 3
graph::graph(int **relation, int total, int* rowLens,int amount) {
	vertices = new vertex[amount];
	this->amount = amount;
	for(int i=0;i<amount;++i){
		vertices[i].from=i;
	}
	for(int i=0;i<total;++i){
		if(rowLens[i]<2){
			continue;
		}
		vertex &from = vertices[relation[i][0]];
		edge * e = new edge(relation[i][1]);
		e->next =from.first;
		from.first=e;
	}
}

graph::~graph() {
	for(int i = 0;i<amount;++i){
		for(edge* cur = vertices[i].first;cur!=nullptr;){
			edge * nxt = cur->next;
			delete cur;
			cur = nxt;
		}
	}
	delete[] vertices;
}

void graph::_bfs(int from,int * visited){
	queue.push_back(from);
	visited[from] = 1;
	while(!queue.empty()){
		int from = queue.front();
		queue.pop_front();
		for(edge * cur = vertices[from].first;cur!=nullptr;cur=cur->next){
			if(!visited[cur->to]){
				queue.push_back(cur->to);
				visited[cur->to]=1;
			}
		}
	}
}
/// @brief entrance of true bfs
/// @return amount of connected components
int graph::bfsEntrance() {
	int cnt = 0;
	int * visited = new int[amount];
	for(int i=0;i<amount;++i){
		visited[i]=0;
	}
	for(int i=0;i<amount;++i){
		if(visited[i] == 0){
			++cnt;
			_bfs(i,visited);
		}
	}
	delete []visited;
	return cnt;
}
