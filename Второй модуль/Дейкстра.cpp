/*
Требуется отыскать самый выгодный маршрут между городами. Требуемое время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними. Оптимизируйте ввод
Формат входных данных.
Первая строка содержит число N - количество городов. Вторая строка содержит число M - количество дорог. Каждая следующая строка содержит описание дороги (откуда, куда, время в пути). Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.
in
6
9
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
0 2

out
9

*/
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <stdio.h>
using namespace std;

///////////////////////////////////////////////////////
//IGRAPH
struct IGraph {
	virtual ~IGraph() {}
	//dobavleniye rebra ot from k to
	virtual void AddEdge(int from, int to, int wei) = 0;

	virtual int VerticesCount() const  = 0;

	virtual vector <int> GetNextVertices(int vertex) const = 0;
	virtual vector <int> GetNextWeights(int vertex) const = 0;
};

///////////////////////////////////////////////////////
//LIST GRAPH

class ListGraph : public IGraph{
public:
	ListGraph (int n);
    
	void AddEdge (int from, int to, int wei) override;
    
	int VerticesCount() const override;
   
	vector <int> GetNextVertices (int vertex) const override;
	vector <int> GetNextWeights (int vertex) const override;
private:
	int num = 0;
	vector<vector<int> > nexts;
	vector<vector<int> > weight;
};

///////////////////////////////////////////////////////
//CONSTRUCTOR BY NUMBER OF VERTEXES

ListGraph::ListGraph(int n) :
	nexts (n, vector <int> ()),
	weight (n, vector <int> ()),
	num (n)
{
	assert (n == nexts.size() && n == weight.size());
};


void ListGraph::AddEdge (int from, int to, int wei) {
	assert (from < num && to < num && from > -1 && to > -1 && wei > -1);
	if (from != to) {
		nexts [from].push_back (to);
		nexts [to].push_back (from);
		weight [from].push_back (wei);
		weight [to].push_back (wei);
	}
}

vector <int> ListGraph::GetNextVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	return nexts [vertex];
}

vector <int> ListGraph::GetNextWeights (int vertex) const {
	assert (vertex < num && vertex > -1);
	return weight [vertex];
}

int ListGraph::VerticesCount() const {
	assert (num == nexts.size() && num == weight.size());
	return num;
}


long long FindMinWay (IGraph* g, int start, int end) {
	
	long long INF = 2500000001LL;
	int num = g -> VerticesCount();
	vector <long long> dist (num + 1, INF);
	
	//distance + vertex
	set <pair<long long, int> >s;
	set <pair<long long, int> >::iterator it;
	
	dist [start] = 0;
	for ( int i = 0; i < num; i ++)
		s.insert (make_pair (dist [i], i));

	while (!s.empty()) {
		it = s.begin ();
		long long loc_min_dist = (*it).first;
		int loc_v = (*it).second;
		
        
		s.erase (it);
		if (loc_min_dist == INF)
			break;
		vector <int> weight = g -> GetNextWeights(loc_v);
        vector <int> nexts = g -> GetNextVertices(loc_v);
		int t = nexts.size ();
        
		for ( int i = 0; i < t; i ++) {
			int to = nexts [i];
			it = s.find (make_pair (dist [to], to));
			if (it != s.end() && dist [to] > loc_min_dist + weight [i]) {
				dist [to] = loc_min_dist + weight [i];
				s.erase (it);
				s.insert (make_pair (dist [to], to));
			}
		}
	}
	assert (dist [end] != INF);
	return dist [end];
}

///////////////////////////////////////////
//MAIN

bool readelem(int &elem) {
	int chr = getchar_unlocked();
	int a = 0;
	for (; !('0' <= chr && chr <= '9'); chr = getchar_unlocked()) {
	if (chr == EOF)
		return false;
	}
	for (; '0' <= chr && chr <= '9' ; chr = getchar_unlocked()) {
		a = a * 10 + chr - '0';
	}
	elem = a;
	return true;
}

int main () {
	cin.tie(NULL);
	ios_base::sync_with_stdio (false);
	ios::sync_with_stdio(false);
	int n = 0, m = 0;
    
	readelem(n);
	readelem(m);
    
	ListGraph list(n);
	
	int a = 0, b = 0, wei = 0;
	for (int i = 0; i < m; i ++) {
		readelem(a);
		readelem(b);
		readelem(wei);
		list.AddEdge(a, b, wei);
	}
    
	readelem(a);
	readelem(b);
    
	cout << FindMinWay(&list, a, b);
	return 0;
}
 
