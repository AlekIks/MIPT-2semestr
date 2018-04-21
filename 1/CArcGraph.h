#ifndef Arc_Graph_H
#define Arc_Graph_H
#include "IGraph.h"

class ArcGraph : public IGraph {
public:
	//kolichestvo vershin
    ArcGraph (int n);
    ArcGraph (const IGraph* other);
    
    //ot IGrapha
    void AddEdge (int from, int to) override;
    
    int VerticesCount() const override;
   
    std::vector <int> GetNextVertices (int vertex) const override;
    std::vector <int> GetPrevVertices (int vertex) const override;
private:
	int num = 0;
	std::vector <std::pair <int, int> > pairs;
};
#endif
