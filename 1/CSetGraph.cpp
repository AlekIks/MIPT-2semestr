#include "CSetGraph.h"
#include <cassert>

///////////////////////////////////////////////////////
//CONSTRUCTOR BY NUMBER OF VERTEXES

SetGraph::SetGraph(int n) :
	nexts (n, std::unordered_set<int> ()),
	previouses (n, std::unordered_set<int> ()),
	num (n)
{
	assert (n == nexts.size() && n == previouses.size());
};


///////////////////////////////////////////////////////
//orientirovannyi
void SetGraph::AddEdge (int from, int to) {
	assert (from < num && to < num && from > -1 && to > -1);
	if (from != to) {
		nexts [from].insert (to); 
		previouses [to].insert (from);
	}
}

std::vector <int> SetGraph::GetNextVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	std::vector <int> ans;
	for (std::unordered_set<int>::const_iterator it = nexts [vertex].begin(); it != nexts [vertex].end(); it ++)
		ans.push_back(*it);
	return ans;
}
 
std::vector <int> SetGraph::GetPrevVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	std::vector <int> ans;
	for (std::unordered_set<int>::const_iterator it = previouses [vertex].begin(); it != previouses [vertex].end(); it ++)
		ans.push_back(*it);
	return ans;
}

int SetGraph::VerticesCount() const {
	assert (num == nexts.size() && num == previouses.size());
	return num;
}


///////////////////////////////////////////////////////
//CONSTRUCTOR BY IGHRAPH

SetGraph::SetGraph(const IGraph* other) :
    num (other->VerticesCount()),
    nexts (num, std::unordered_set<int> ()),
    previouses (num, std::unordered_set<int> ())
{
	for(int i = 0; i < num; i ++) {
		for (int j : other->GetNextVertices(i)) {
			nexts[i].insert(j);
		}
		for (int j : other->GetPrevVertices(i)){
			previouses[i].insert(j);
		}
	}	
};

