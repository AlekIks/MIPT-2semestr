#include "CListGraph.h"
#include <cassert>

///////////////////////////////////////////////////////
//CONSTRUCTOR BY NUMBER OF VERTEXES

ListGraph::ListGraph(int n) :
	nexts (n, std::vector <int> ()),
	previouses (n, std::vector <int> ()),
	num (n)
{
	assert (n == nexts.size() && n == previouses.size());
};

///////////////////////////////////////////////////////
//CONSTRUCTOR BY IGHRAPH

ListGraph::ListGraph(const IGraph* other) :
    num (other->VerticesCount()),
    nexts (num, std::vector <int> ()),
    previouses (num, std::vector <int> ())
{
	for(int i = 0; i < num; i ++) {
		nexts[i] = other->GetNextVertices(i);
		previouses[i] = other->GetPrevVertices(i); 
	}	
};

///////////////////////////////////////////////////////
//orientirovannyi
void ListGraph::AddEdge (int from, int to) {
	assert (from < num && to < num && from > -1 && to > -1);
	if (from != to) {
		nexts [from].push_back (to);
		previouses [to].push_back (from);
	}
}

std::vector <int> ListGraph::GetNextVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	return nexts [vertex];
}
 
std::vector <int> ListGraph::GetPrevVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	return  previouses [vertex];
}

int ListGraph::VerticesCount() const {
	assert (num == nexts.size() && num == previouses.size());
	return num;
}

