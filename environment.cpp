#include "environment.h"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <utility>
#include "directionUtils.h"
#include "worm.h"
#include "node.h"

Environment::Environment(sf::RenderWindow& renderWindow, Worm* worm) : _renderWindow(renderWindow) {
  _worm = worm;

  Node* initNode = _worm->getCurrentNode();
  _allNodes.insert(initNode);

  // create node traveled from for initial state based on initial direction (node will be in direction opposite worm's current direction)
  std::pair<int, int> traveledFromCoords = _getNewCoords(initNode->getPosition(), DirectionUtils::invertDirection(_worm->getCurrentDirection()));
  Node* traveledFromNode = _getNode(traveledFromCoords);
  initNode->addEaten(traveledFromNode);
  _visitedNodes.push_back(traveledFromNode);
  _visitedNodes.push_back(_worm->getCurrentNode());
}

Environment::~Environment() {
  for (Node* node : _allNodes) {
    delete node;
  }

  delete _worm;
}

void Environment::update() {
  int direction = _worm->chooseDirection();
  /*std::cout << "chosen global direction " << std::to_string(direction) << "\n";*/
  if (direction < 0) {
    // sim has halted
    _logger.info("Sim halted.");
    return;
  }

  Node* currentNode = _worm->getCurrentNode();

  std::pair<int, int> newPosition = _getNewCoords(currentNode->getPosition(), direction);

  Node* newNode = _getNode(newPosition);
  _allNodes.insert(newNode);                // keep track of node pointer so that it can be freed later
  _visitedNodes.push_back(newNode);  

  currentNode->addEaten(newNode);
  currentNode = newNode;
  _worm->moveToNode(currentNode);
}

void Environment::draw() {
  for (int i = 0 ; i < _visitedNodes.size(); i++) {
    Node* prevNode = _visitedNodes[i];
    if (i + 1 >= _visitedNodes.size()) {
      return;
    }
    Node* nextNode = _visitedNodes[i + 1];
    std::pair<int, int> prevCoord = prevNode->getPosition();
    std::pair<int, int> nextCoord = nextNode->getPosition();
    sf::Vertex line[] = {
      _getVertex(prevNode),
      _getVertex(nextNode)
    };

    _renderWindow.draw(line, 2, sf::Lines);
  }
}

// get new coordinates given current coordinates and a travel direction 
std::pair<int, int> Environment::_getNewCoords(std::pair<int, int> currentCoords, int direction) {
  std::pair<int, int> newCoords = currentCoords;
  std::pair<int, int> deltaPos = DirectionUtils::getDeltaPosition(direction);
  
  newCoords.first += deltaPos.first;
  newCoords.second += deltaPos.second;

  return newCoords;
}

Node* Environment::_getNode(std::pair<int, int> coords) {
  if (_nodesMap.find(coords) != _nodesMap.end()) {      // if we have already created a node at these indices, retrieve it from the map
    return _nodesMap[coords];
  }

  // else, this node does not yet exist in this map (we have never visited it).  Need to create a new one
  Node* node = new Node(coords);
  _nodesMap[coords] = node;
  return node;
}

// convert node coordinates to pixel coordinates
sf::Vertex Environment::_getVertex(Node* node) {
  std::pair<int, int> nodeCoords = node->getPosition();
  
  float x_base = _lineLength * (static_cast<float>(nodeCoords.first) + 0.5f * nodeCoords.second);
  float y_base = _triangleHeight * nodeCoords.second;

  sf::Vector2f globalCoords = sf::Vector2f(x_base, y_base);

  // center on render window 
  globalCoords.x += _renderWindow.getSize().x / 2.0f;
  globalCoords.y = (_renderWindow.getSize().y / 2.0f) - globalCoords.y;

  return sf::Vertex(globalCoords, _lineColor);

  /*sf::Vector2f globalCoords = sf::Vector2f(nodeCoords.first * _lineLength, nodeCoords.second * _triangleHeight);*/
  /*if (nodeCoords.second & 1) {     // shift odd rows over half of triangle side length*/
  /*  globalCoords.x += _lineLength / 2.0;*/
  /*}*/
  /**/
  /*globalCoords.x += _renderWindow.getSize().x / 2.0;*/
  /*globalCoords.y = (_renderWindow.getSize().y / 2.0) - globalCoords.y;*/
  /**/
}
