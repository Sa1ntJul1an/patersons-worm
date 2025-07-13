#ifndef WORM_HEADER
#define WORM_HEADER 

#include <exception>
#include <map>
#include <queue>
#include <set>
#include <vector>

#include "logger.h"
#include "node.h"

class Worm {
  public:
    Worm(Node* initialNode, int initialDirection, std::queue<int> rules);
    Node* getCurrentNode();
    int getCurrentDirection();
    int chooseDirection();
    void moveToNode(Node* node);
    bool isHalted();
    bool isStarved();
    bool isNType();
    bool isImpossiblePath();

  private:
    std::set<int> _mapConfiguration(int currentDirection);

    Node* _currentNode;

    std::queue<int> _rules;
    std::map<std::set<int>, int> _ruleMap;

    int _currentDirection;

    bool _halted;           // halted for ANY reason (starved, bad rule, no more rules)
    bool _impossible_path;  // impossible path (next rule requires move that is already eaten)
    bool _starved;          // starved (no possible paths)
    bool _n_type;           // n-type: no more rules but we have encountered new config (need longer ruleset)

    Logger _logger = Logger("worm", 0, false, true, "logs/worm.txt");
};

#endif // !WORM_HEADER
