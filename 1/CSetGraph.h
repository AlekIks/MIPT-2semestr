#ifndef Set_Graph_H
#define Set_Graph_H
#include "IGraph.h"
#include <unordered_set>

class SetGraph : public IGraph {
public:
	//kolichestvo vershin
    SetGraph (int n);
    SetGraph (const IGraph* other);
    
    //ot IGrapha
    void AddEdge (int from, int to) override;
    
    int VerticesCount() const override;
   
    std::vector <int> GetNextVertices (int vertex) const override;
    std::vector <int> GetPrevVertices (int vertex) const override;
private:
	int num = 0;
	std::vector<std::unordered_set<int> > nexts;
	std::vector<std::unordered_set<int> > previouses;
};
#endif
