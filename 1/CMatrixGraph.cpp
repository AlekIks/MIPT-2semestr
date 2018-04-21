#include "CMatrixGraph.h"
#include <cassert>

///////////////////////////////////////////////////////
//CONSTRUCTOR BY NUMBER OF VERTEXES

MatrixGraph::MatrixGraph(int n) :
	mat (n, std::vector <bool> (n, false)),
	num (n)
{
};

///////////////////////////////////////////////////////
//CONSTRUCTOR BY IGHRAPH

MatrixGraph::MatrixGraph(const IGraph* other) :
    num (other->VerticesCount()),
    mat (num, std::vector <bool> (num, false))
{
	for(int i = 0; i < num; i ++) {
		for (int j : other->GetNextVertices(i)) {
			mat [i][j] = true;
		}
		for (int j : other->GetPrevVertices(i)) {
			mat [j][i] = true;
		}
	}	
};

///////////////////////////////////////////////////////
//orientirovannyi
void MatrixGraph::AddEdge (int from, int to) {
	assert (from < num && to < num && from > -1 && to > -1);
	if (from != to) {
		mat [from][to] = true;
	}
}

std::vector <int> MatrixGraph::GetNextVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	std::vector <int> ans;
	for (int i = 0; i < num; i ++) {
		if (mat [vertex][i]) {
			ans.push_back(i);
		}
	}
	return ans;
}
 
std::vector <int> MatrixGraph::GetPrevVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	std::vector <int> ans;
	for (int i = 0; i < num; i ++) {
		if (mat [i][vertex]) {
			ans.push_back(i);
		}
	}
	return ans;
}

int MatrixGraph::VerticesCount() const {
	return num;
}

