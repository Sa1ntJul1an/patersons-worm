#include "node.h"

#include <utility>
#include <set>
#include "directionUtils.h"

Node::Node(std::pair<int, int> coords){
  _position = coords;
}

std::pair<int, int> Node::getPosition() const {
    return this->_position;
}

std::set<int> Node::getConfiguration(int transform_direction) {
  std::set<int> transformedConfiguration;
  if (transform_direction == 0) {
    return _configuration;
  }
  for (int eaten_direction : _configuration) {
    transformedConfiguration.insert(DirectionUtils::transformDirection(eaten_direction, transform_direction));
  }
  return transformedConfiguration;
}

void Node::addEaten(Node* neighbor) {
  // find the direction traveled from to mark that path as eaten 
  std::pair<int, int> neighborPosition = neighbor->getPosition();
  
  int q, r, delta_q, delta_r;
  q = _position.first;
  r = _position.second;

  delta_q = neighborPosition.first - q; 
  delta_r = neighborPosition.second - r;

  int direction = DirectionUtils::getDirection({delta_q, delta_r});
  
  // the neighbor now has the path in the "opposite" direction marked as eaten
  neighbor->addEaten(DirectionUtils::invertDirection(direction));

  _configuration.insert(direction);
}

void Node::addEaten(int direction) {
  _configuration.insert(direction);
}

bool Node::isEaten(int direction) {
  // check if integer exists in configuration map. 
  // if it does, this path has been eaten. Else it has not
  if (_configuration.find(direction) == _configuration.end()) {   // int does not exist in config set, therefore this path has not been eaten
    return false;
  }

  return true;
}
