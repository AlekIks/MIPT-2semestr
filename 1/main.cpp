#include "Graphs.cpp"
#include <iostream>
#include <ctime>
using namespace std;

void PrintGraph (IGraph* g) {
	int n = g -> VerticesCount();
	
	for (int i = 0; i < n; i ++) {
		cout << "	Следующие за вершиной " << i << " это вершины: ";
		vector <int> loc = g -> GetNextVertices(i);
		int t = loc.size();
		for (int j = 0; j < t; j ++) {
			cout << loc [j] << " ";
		}
		cout << endl;
		loc = g -> GetPrevVertices(i);
		t = loc.size();
		cout << "	Предыдущие для вершины " << i << " это вершины: ";
		for (int j = 0; j < t; j ++) {
			cout << loc [j] << " ";
		}
		cout << endl;
	}
}

void GraphWork (IGraph* g) {
	int n = g -> VerticesCount();
	for (int i = 0; i < n; i ++) {
		vector <int> loc = g -> GetNextVertices(i);
		loc = g -> GetPrevVertices(i);
	}
}



int main () {
	int n = 0, m = 0;
	freopen ("test.in", "r", stdin);
	freopen ("result.out", "w", stdout);
	
	int tests = 0;
	cin >> tests;
	
	clock_t start, finish;
	
	for (int j = 0; j < tests; j ++) {
		cout << "ТЕСТ "<< j + 1 << endl;
		cout << "///////////////////////////////////////////////" << endl;
		
		cin >> n >> m;
		ListGraph list1(n);
		
		int a = 0, b = 0;
		
		for (int i = 0; i < m; i ++) {
			cin >> a >> b;
			list1.AddEdge(a, b);
		}
		
		cout << "Время создания через IGraph:" << endl;
		cout << "	ListGraph:	";
		start = clock();
		ListGraph list2(&list1);
		finish = clock();
		cout << 1.0 * (finish - start) / CLOCKS_PER_SEC << endl;
		
		cout << "	MatrixGraph:	";
		start = clock();
		MatrixGraph mat(&list1);
		finish = clock();
		cout << 1.0 * (finish - start) / CLOCKS_PER_SEC << endl;
		
		cout << "	SetGraph:	";
		start = clock();
		SetGraph setg(&list1);
		finish = clock();
		cout << 1.0 * (finish - start) / CLOCKS_PER_SEC << endl;
		
		cout << "	ArcGraph:	";
		start = clock();
		ArcGraph arcg(&list1);
		finish = clock();
		cout << 1.0 * (finish - start) / CLOCKS_PER_SEC << endl;
		
		cout << endl << "Время печати графов и корректность работы:" << endl;
		cout << "	ListGraph:" << endl;
		start = clock();
		GraphWork (&list2);
		finish = clock();
		cout <<endl << "	Время работы:	" << 1.0 * (finish - start) / CLOCKS_PER_SEC << endl << endl;
		
		cout << "	MatrixGraph:" << endl;
		start = clock();
		GraphWork (&mat);
		finish = clock();
		cout <<endl << "	Время работы:	" << 1.0 * (finish - start) / CLOCKS_PER_SEC << endl << endl;
		
		cout << "	SetGraph:" << endl;
		start = clock();
		GraphWork (&setg);
		finish = clock();
		cout <<endl << "	Время работы:	" << 1.0 * (finish - start) / CLOCKS_PER_SEC << endl << endl;
		
		cout << "	ArcGraph:" << endl;
		start = clock();
		GraphWork (&arcg);
		finish = clock();
		cout <<endl << "	Время работы:	" << 1.0 * (finish - start) / CLOCKS_PER_SEC << endl << endl;
	}
		
	return 0;
}
