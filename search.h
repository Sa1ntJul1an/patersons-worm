#ifndef SEARCH_HEADER
#define SEARCH_HEADER

#include "cell.h"
#include "searchAlgorithms.h"

class Search{
    public:
        Search(Cell *, Cell *, const std::vector<std::vector<Cell*>>&);

        bool isGoalReached();

        bool isSearchComplete();

        virtual void update() = 0;      // pure virtual function where each derived class can implement the update procedure

        virtual void initialize() = 0;

    protected:
        int _width;
        int _height;

        bool _goalReached;
        bool _searchComplete;

        Cell * _start;
        Cell * _goal;

        Cell * _previous_popped_cell;

        std::vector<std::vector<Cell*>> _stateSpace;

        void _populateNeighbors();

        void _backtrackPath(Cell *);
};


#endif /* !SEARCH_HEADER */