#ifndef DEPTHFIRST_HEADER
#define DEPTHFIRST_HEADER

#include <stack>

# include "search.h"

// Depth First Search

class DepthFirstSearch : public Search{
    public:
        DepthFirstSearch(Cell *, Cell *, const std::vector<std::vector<Cell*>>&);

        void update();

        void initialize();

    private:
        std::stack<Cell*> _frontier;
};

#endif /* !DEPTHFIRST_HEADER */