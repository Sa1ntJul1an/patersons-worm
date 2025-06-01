#include <iostream>
#include <math.h>

#include "aStar.h"
#include "cell.h"


AStarSearch::AStarSearch(Cell * start, Cell * goal, const std::vector<std::vector<Cell*>>& stateSpace) : Search(start, goal, stateSpace){
    _stateSpace = stateSpace;
    _start = start;
    _goal = goal;
}


void AStarSearch::update(){
    if (_nodes.empty()){
        std::cout << "Frontier empty..." << std::endl;
        _searchComplete = true;
        return;
    }

    Cell * currentNode = _nodes.top();
    _nodes.pop();

    currentNode->setFrontier(false);
    currentNode->setExplored(true);

    _backtrackPath(currentNode);

    if (currentNode == _goal){
        _searchComplete = true;
        _goalReached = true;
        return;
    }

    for (Cell * neighbor : currentNode->getNeighbors()){
        float gScore = currentNode->getGScore() + 1;      // currently, all state transitions have cost = 1
        if (gScore < neighbor->getGScore()){
            neighbor->setParent(currentNode);
            neighbor->setGScore(gScore);
            neighbor->setFScore(gScore + heuristic(neighbor));

            if(!neighborExistsInQueue(neighbor)){
                neighbor->setFrontier(true);
                _nodes.push(neighbor);
            }
        }
    }
}

void AStarSearch::initialize(){

    std::cout << "Initializing A* search..." << std::endl;

    this->_populateNeighbors();

    _start->setFScore(heuristic(_start));
    _start->setGScore(0);

    _nodes.push(_start);
    _start->setExplored(true);

    std::cout << "Node tree created, beginning search." << std::endl;
}

float AStarSearch::manhattanDistance(Cell* cell){
    float delta_x, delta_y;
    float cell_x, cell_y;
    float goal_x, goal_y;

    cell_x = static_cast<float>(cell->getPosition()[0]);
    cell_y = static_cast<float>(cell->getPosition()[1]);

    goal_x = static_cast<float>(_goal->getPosition()[0]);
    goal_y = static_cast<float>(_goal->getPosition()[1]);

    delta_x = abs(goal_x - cell_x);
    delta_y = abs(goal_y - cell_y);

    return delta_x + delta_y;
}


float AStarSearch::euclideanDistance(Cell * cell){
    float delta_x, delta_y;
    float cell_x, cell_y;
    float goal_x, goal_y;

    cell_x = static_cast<float>(cell->getPosition()[0]);
    cell_y = static_cast<float>(cell->getPosition()[1]);

    goal_x = static_cast<float>(_goal->getPosition()[0]);
    goal_y = static_cast<float>(_goal->getPosition()[1]);

    delta_x = abs(goal_x - cell_x);
    delta_y = abs(goal_y - cell_y);

    return ((std::sqrt(std::pow(delta_x, 2) + std::pow(delta_y, 2))));
}


float AStarSearch::heuristic(Cell * cell){
    switch(_heuristic_choice){
        case heuristics::euclidean_distance:
            return euclideanDistance(cell);
        case heuristics::manhattan_distance:
            return manhattanDistance(cell);
        default:
            return euclideanDistance(cell);
    }
}


bool AStarSearch::neighborExistsInQueue(Cell * neighbor){
    std::vector<Cell *> temp;

    bool existsInQueue = false;

    while (!_nodes.empty()){
        Cell * cell = _nodes.top();
        _nodes.pop();

        temp.push_back(cell);  // store cell in temp storage

        if (cell == neighbor){
            existsInQueue = true;
        }
    }

    for (Cell* cell : temp){        // reconstruct nodes priority queue
        _nodes.push(cell);
    }

    return existsInQueue;
}