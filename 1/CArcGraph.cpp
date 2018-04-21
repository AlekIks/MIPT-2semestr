#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstring>
using namespace std;

///////////////////////////////////////////////////////
//IGRAPH
struct IGraph {
	virtual ~IGraph() {}
	
	virtual void AddEdge(int from, int to, int wei) = 0;

	virtual int VerticesCount() const  = 0;

	virtual vector <int> GetNextVertices(int vertex) const = 0;
	virtual vector <int> GetPrevVertices(int vertex) const = 0;
};


///////////////////////////////////////////////////////
//MATRIX GRAPH

class MatrixGraph : public IGraph {
public:
	//kolichestvo vershin
    MatrixGraph (int n);
	
    void AddEdge (int from, int to, int wei) override;
	
    int VerticesCount() const override;
   
    vector <int> GetNextVertices (int vertex) const override;
    vector <int> GetPrevVertices (int vertex) const override;
private:
	int num = 0;
	vector<vector<int> > mat;
};


void MatrixGraph::AddEdge (int from, int to, int wei) {
	assert (from < num && to < num && from > -1 && to > -1);
	if (from != to) {
		mat [from][to] = wei;
	}
}

vector <int> MatrixGraph::GetNextVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	vector <int> ans;
	for (int i = 0; i < num; i ++) {
		ans.push_back(mat [vertex][i]);
	}
	return ans;
}
 
vector <int> MatrixGraph::GetPrevVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	vector <int> ans;
	for (int i = 0; i < num; i ++) {
		ans.push_back(mat [i][vertex]);
	}
	return ans;
}

int MatrixGraph::VerticesCount() const {
	return num;
}

///////////////////////////////////////////
//MAIN


/////////////
//FFLOYD
vector<vector<int>> Floyd (IGraph* g) {
	int num = g -> VerticesCount();
	
	vector<vector<int> > ans (num, vector <int>());
	for (int i = 0; i < num; i ++)
		ans [i] = g -> GetNextVertices(i);
	
	for (int k = 0; k < num; k ++) {
		for (int i = 0; i < num; i ++) {
			for (int j = 0; j < num; j ++)
				ans [i][j] = min (ans [i][j], ans [i][k] + ans [k][j]);
		}
	}
	return ans;
}

////////////
//PRINT MATRIX
void print_matrix(vector<vector<int> > v) {
	int num = v.size();
	
	for (int i = 0; i < num; i ++) {
		for (int elem : v [i]) {
			cout << elem << " ";
		}
		cout << endl;
	}	
}
///////////

int main () {
	int n = 0;
	cin >> n;
	
	MatrixGraph mat (n);
	
	int wei = 0;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; i < n; i ++) {
			cin >> wei;
			mat.AddEdge(i, j, wei);
		}
	}
	
	vector<vector<int> > ans = Floyd (&mat);
	print_matrix (ans);
		
	return 0;
}			
