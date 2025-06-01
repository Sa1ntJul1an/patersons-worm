#ifndef ASTAR_HEADER
#define ASTAR_HEADER

#include <queue>

# include "search.h"

// A* Search

class AStarSearch : public Search{
    public:
        AStarSearch(Cell *, Cell *, const std::vector<std::vector<Cell*>>&);

        void update();

        void initialize();

    private:
        // custom comparator for priority queue, will ensure that nodes with least distance to start are returned first (higher priority)
        struct compareNodeDistance {
            bool operator()(Cell* a, Cell* b) const {
                return (a->getFScore() > b->getFScore());
            }
        };

        enum class heuristics {
            manhattan_distance,
            euclidean_distance
        }; 

        heuristics _heuristic_choice = heuristics::euclidean_distance;

        float manhattanDistance(Cell *);

        float euclideanDistance(Cell *);

        float heuristic(Cell *);

        bool neighborExistsInQueue(Cell *);
       
        std::priority_queue<Cell *, std::vector<Cell *>, compareNodeDistance> _nodes;
};

#endif /* !ASTAR_HEADER */