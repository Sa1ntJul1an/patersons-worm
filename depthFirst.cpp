#include <iostream>

#include "depthFirst.h"
#include "cell.h"

DepthFirstSearch::DepthFirstSearch(Cell * start, Cell * goal, const std::vector<std::vector<Cell*>>& stateSpace) : Search(start, goal, stateSpace){
    _stateSpace = stateSpace;
    _start = start;
    _goal = goal;
}

void DepthFirstSearch::update(){
    if (_frontier.empty()){
        std::cout << "Frontier empty..." << std::endl;
        _searchComplete = true;
        return;
    }

    Cell* currentCell = _frontier.top();
    _frontier.pop();
    currentCell->setFrontier(false);

     _backtrackPath(currentCell);

    if (currentCell == _goal){
        _searchComplete = true;
        _goalReached = true;
        return;
    }
    std::vector<Cell*> neighbors = currentCell->getNeighbors();
    int numNeighbors = neighbors.size();

    for (int i = 0; i < numNeighbors; i ++){
        Cell * neighbor = neighbors[i];
        if (!neighbor->isExplored()){
            neighbor->setExplored(true);
            neighbor->setParent(currentCell);
            neighbor->setFrontier(true);
            _frontier.push(neighbor);
        }
    }
}

void DepthFirstSearch::initialize(){

    std::cout << "Initializing depth first search..." << std::endl;

    this->_populateNeighbors();

    _frontier.push(_start);
    _start->setExplored(true);

    std::cout << "Node tree created, beginning search." << std::endl;
}