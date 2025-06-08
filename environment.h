
#ifndef ENVIRONMENT_HEADER
#define ENVIRONMENT_HEADER

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <map>
#include <utility>
#include <vector>
#include "node.h"
#include "worm.h"

class Environment {
  public: 
    Environment(sf::RenderWindow& renderWindow, Worm* worm);
    ~Environment();
    
    void update();
    void draw();

  private:
    std::pair<int, int> _getNewCoords(std::pair<int, int> currentCoords, int direction);
    Node* _getNode(std::pair<int, int> coords);
    sf::Vertex _getVertex(Node* node);

    std::map<std::pair<int, int>, Node*> _nodesMap;
    std::set<Node*> _allNodes;
    std::vector<Node*> _visitedNodes;

    sf::RenderWindow& _renderWindow;

    Worm* _worm;

    // RENDERING CONFIG
    const float _lineLength = 20.0;
    float _triangleHeight = (_lineLength * std::sqrt(3.0)) / 2.0;
    const sf::Color _lineColor = sf::Color::White;
};


#endif // !ENVIRONMENT_HEADER
