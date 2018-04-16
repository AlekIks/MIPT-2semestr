/*
Полный ориентированный взвешенный граф задан матрицей смежности. 
Постройте матрицу кратчайших путей между его вершинами.
Гарантируется, что в графе нет циклов отрицательного веса.
//
// Студент: Погребная Александра, 795
*/
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

MatrixGraph::MatrixGraph(int n) :
	mat (n, vector <int>(n, 0)),
	num (n)
{
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
vector<vector<int>> Floyd (const IGraph* g) {
	const int num = g -> VerticesCount();
	
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
void print_matrix(const vector<vector<int> > v) {
	const int num = v.size();
	
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
		for (int j = 0; j < n; j ++) {
			cin >> wei;
			mat.AddEdge(i, j, wei);
		}
	}
	
	vector<vector<int> > ans = Floyd (&mat);
	print_matrix (ans);
		
	return 0;
}

