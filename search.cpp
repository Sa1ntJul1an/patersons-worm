#include <math.h>

#include "search.h"
#include "cell.h"
#include "searchAlgorithms.h"

Search::Search(Cell * start, Cell * goal, const std::vector<std::vector<Cell*>>& stateSpace){
    _start = start;
    _goal = goal;
    _stateSpace = stateSpace;

    _goalReached = false;
    _searchComplete = false;

    _previous_popped_cell = nullptr;
}

bool Search::isGoalReached(){
    return this->_goalReached;
}

bool Search::isSearchComplete(){
    return this->_searchComplete;
}

void Search::_populateNeighbors(){
    _width = _stateSpace.size();
    _height = _stateSpace[0].size();

    for (int row = 0; row < _width; row++){
        for (int col = 0; col < _height; col++){
            Cell* currentCell = _stateSpace.at(row).at(col);

            if (currentCell->isObstacle()){
                continue;
            }

            for (int row_offset = -1; row_offset <= 1; row_offset++){
                for (int col_offset = -1; col_offset <= 1; col_offset++){
                    if (row + row_offset >= 0 && row + row_offset <= _width - 1){
                        if (col + col_offset >= 0 && col + col_offset <= _height - 1){

                            if (abs(row_offset) == abs(col_offset)){
                                continue;
                            }
                            
                            Cell* neighbor = _stateSpace[row + row_offset][col + col_offset];

                            if (!(neighbor->isObstacle())){
                                currentCell->addNeighbor(neighbor);
                            }

                        }
                    }
                }
            }

        }
    }
}

void Search::_backtrackPath(Cell * currentCell){
    
    // clear previous path if it existed
    if (_previous_popped_cell != nullptr){
        while (_previous_popped_cell != nullptr){
            _previous_popped_cell->setPath(false);
            _previous_popped_cell = _previous_popped_cell->getParent();
        }
    }

    // store pointer to beginning of current path so it can be cleared next iteration
    _previous_popped_cell = currentCell;

    // draw path points for current node back to start
    Cell * cell = currentCell;
    while (cell != nullptr){
        cell->setPath(true);
        cell = cell->getParent();
    }
}