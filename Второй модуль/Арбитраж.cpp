/*
Необходимо написать торгового советника для поиска арбитража. 
Определение. Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах. Например, есть следующие курсы валют (на 03.05.2015):
GBP/USD: 0.67
RUB/GBP: 78.66
USD/RUB: 0.02
Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4%. Время работы - O(VE).
Формат входных данных.
Первая строка содержит число N - количество возможных валют (размер таблицы котировок) Далее следует построчное представление таблицы. Диагональные элементы (i, i) пропущены (подразумевается, что курс валюты к себе же 1.0). В элементе таблицы (i, j) содержится обменный курс i->j. Если обмен в данном направлении не производится, то -1.
Формат выходных данных.
Выведите YES, если арбитраж есть, и NO, иначе.
in
4
      32.1  1.50 78.66
0.03        0.04  2.43
0.67 21.22       51.89
0.01    -1  0.02
out
YES

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
	
	virtual void AddEdge(int from, int to, double wei) = 0;

	virtual int VerticesCount() const  = 0;

	virtual vector <double> GetNextVertices(int vertex) const = 0;
	virtual vector <double> GetPrevVertices(int vertex) const = 0;
};


///////////////////////////////////////////////////////
//MATRIX GRAPH

class MatrixGraph : public IGraph {
public:
	//kolichestvo vershin
	MatrixGraph (int n);
    
	void AddEdge (int from, int to, double wei) override;
    
	int VerticesCount() const override;
   
	vector <double> GetNextVertices (int vertex) const override;
	vector <double> GetPrevVertices (int vertex) const override;
private:
	int num = 0;
	vector<vector<double> > mat;
};


MatrixGraph::MatrixGraph(int n) :
	mat (n, vector <double>(n, 0)),
	num (n)
{
};


void MatrixGraph::AddEdge (int from, int to, double wei) {
	assert (from < num && to < num && from > -1 && to > -1);
	if (from != to) {
		mat [from][to] = wei;
	}
}


vector <double> MatrixGraph::GetNextVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	vector <double> ans;
	for (int i = 0; i < num; i ++) {
		ans.push_back(mat [vertex][i]);
	}
	return ans;
}


vector <double> MatrixGraph::GetPrevVertices (int vertex) const {
	assert (vertex < num && vertex > -1);
	vector <double> ans;
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

bool Has_Arbitrazh (const IGraph* g) {
	
    const int num = g -> VerticesCount();
    
	for (int k = 0; k < num;  k ++) {
		
        vector<double> dist (num, -1);
        
        dist [k] = 1;
        
        //n-1 phases of Forda-Bellman
        for (int i = 0; i < num - 1; i ++) {
            for (int j = 0; j < num; j ++) {
                vector <double> loc = g -> GetNextVertices(j);
                for (int t = 0; t < num; t ++) {
                	//relax
                    if (dist[t] != -1 && dist[j] < dist[t] * loc [t])
                        dist[j] = dist[t] * loc [t];
                }
            }
        }
        //phase №n to check if there is a minus cycle
        for (int i = 0; i < num ; i ++) {
            vector <double> loc = g -> GetNextVertices(i);
            for (int t = 0; t < num; t ++) {
                    if (dist[t] != -1.0 && dist[i] < dist[t] * loc [t])
                        return true;
            }
        }
    }
    return false;
}

////////////
//PRINT MATRIX
void print_matrix(const vector<vector<double> > v) {
	const int num = v.size();
	
	for (int i = 0; i < num; i ++) {
		for (double elem : v [i]) {
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
	
	double wei = 0;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			if (i != j) {
				cin >> wei;
				mat.AddEdge(i, j, wei);
			}
		}
	}
	
	if (Has_Arbitrazh (&mat))
		cout << "YES";
	else
		cout << "NO";
		
	return 0;
}

