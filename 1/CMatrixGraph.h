#ifndef Matrix_Graph_H
#define Matrix_Graph_H
#include "IGraph.h"
class MatrixGraph : public IGraph {
public:
	//kolichestvo vershin
    MatrixGraph (int n);
    MatrixGraph (const IGraph* other);
    
    //ot IGrapha
    void AddEdge (int from, int to) override;
    
    int VerticesCount() const override;
   
    std::vector <int> GetNextVertices (int vertex) const override;
    std::vector <int> GetPrevVertices (int vertex) const override;
private:
	int num = 0;
	std::vector<std::vector<bool> > mat;
};
#endif
