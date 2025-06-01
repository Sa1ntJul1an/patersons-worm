#ifndef WORM_HEADER
#define WORM_HEADER 

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "node.h"

class Worm {
  public:
    Worm(sf::RenderWindow& renderWindow, std::vector<Node> nodes);

    void update();

  private:
    sf::RenderWindow& _renderWindow;

    bool _starved;
};

#endif // !WORM_HEADER
