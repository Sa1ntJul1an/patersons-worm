#ifndef BREADTHFIRST_HEADER
#define BREADTHFIRST_HEADER

#include <queue>

# include "search.h"

// Breadth First Search

class BreadthFirstSearch : public Search{
    public:
        BreadthFirstSearch(Cell *, Cell *, const std::vector<std::vector<Cell*>>&);

        void update();

        void initialize();

    private:
        std::queue<Cell*> _frontier;
};

#endif /* !BREADTHFIRST_HEADER */