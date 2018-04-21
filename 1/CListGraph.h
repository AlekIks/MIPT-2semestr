#ifndef List_Graph_H
#define List_Graph_H
#include "IGraph.h"
class ListGraph : public IGraph {
public:
	//kolichestvo vershin
    ListGraph (int n);
    ListGraph (const IGraph* other);
    
    void AddEdge (int from, int to) override;
    
    int VerticesCount() const override;
   
    std::vector <int> GetNextVertices (int vertex) const override;
    std::vector <int> GetPrevVertices (int vertex) const override;
private:
	int num = 0;
	std::vector<std::vector<int> > nexts;
	std::vector<std::vector<int> > previouses;
};
#endif
