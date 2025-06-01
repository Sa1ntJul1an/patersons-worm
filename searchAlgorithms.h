#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H

enum class SearchAlgorithm;
/**
 * Defines different search types for searchFactory depending on which algorithms have been implemented
*/

enum class SearchAlgorithm {
    BreadthFirst,
    DepthFirst,
    AStar
};

#endif // SEARCHALGORITHMS_H