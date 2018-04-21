#ifndef I_Graph_H
#define I_Graph_H
#include <vector>

struct IGraph {
	virtual ~IGraph() {}
	//dobavleniye rebra ot from k to
	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

	virtual std::vector <int> GetNextVertices(int vertex) const = 0;
	virtual std::vector <int> GetPrevVertices(int vertex) const = 0;
};

#endif
