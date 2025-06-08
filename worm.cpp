#include "worm.h"
#include <iostream>
#include <queue>
#include <set>
#include <string>

#include "directionUtils.h"
#include "node.h"

Worm::Worm(Node* initialNode,  int initialDirection, std::queue<int> rules) {
  _halted = false;
  _n_type = false;
  _starved = false;
  _impossible_path = false;
  _rules = rules;
  _currentNode = initialNode;
  _currentDirection = initialDirection;
};

Node* Worm::getCurrentNode() {
  return _currentNode;  
}

int Worm::getCurrentDirection() {
  return _currentDirection;
}

int Worm::chooseDirection() {
  if (_halted) {
    return -1;
  }

  // called in loop to advance to next iteration
  std::set<int> nodeConfiguration = _currentNode->getConfiguration(_currentDirection);
  int direction;

  std::cout << "Position: {" << std::to_string(_currentNode->getPosition().first) << ", " << std::to_string(_currentNode->getPosition().second) << "}\n";

  if (nodeConfiguration.size() == 5) {   // implicit rule of Paterson's worm: if there is only 1 possible way out, take that path and do not consume rule
    for (int i = 0; i <= 5; i++) {
      if (nodeConfiguration.find(i) == nodeConfiguration.end()) {   // direction does not exist in set, last possible path
        std::cout << "Only 1 possible path remaining: " + std::to_string(i) << "\n"; 
        return i;
      }
    }
  } else if (nodeConfiguration.size() == 6) {   // all paths are eaten, worm has starved
    _starved = true;
    _halted = true;
    std::cout << "Worm starved.\n"; 
    return -1;
  } else {
    // decide direction to move by consulting mapped rules, or map new rule if configuration has not been encountered 
    if (_ruleMap.find(nodeConfiguration) == _ruleMap.end()) {     // we have not seen this configuration before, grab new rule from ruleset
      std::cout << "New configuration encountered. Selecting next rule.\n";
      if (_rules.empty()) {                                         // n-type worm: we have no more rules to map to configurations
        std::cout << "Ruleset empty. N-type worm.\n";
        _n_type = true;
        _halted = true;
        return -1;
      }

      direction = _rules.front();       // we have rules left to grab, so grab next one
      _rules.pop();

      std::cout << "New rule chosen: " + std::to_string(direction) << "\n";

      _ruleMap[nodeConfiguration] = direction;      // map configuration to this direction for future lookups
    } else {                    // we have seen this config before, grab the direction from mapped rules
      direction = _ruleMap[nodeConfiguration];
    }
    std::cout << "input direction: " << direction << ", current direction: " << _currentDirection << "\n";
    direction = DirectionUtils::transformDirectionRelativeToGlobal(direction, _currentDirection);

    if (_currentNode->isEaten(direction)) {   // if our chosen rule says to take a path that is eaten, automaton halts
      _halted = true;
      _impossible_path = true;
      std::cout << "Impossible path.\n";
      return -1;
    }
  }

  std::cout << "output direction: " << direction << "\n";

  _currentDirection = direction;
  return direction;
}

void Worm::moveToNode(Node* node) {
  _currentNode = node;
}
