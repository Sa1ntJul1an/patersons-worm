#include "worm.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "node.h"

Worm::Worm(sf::RenderWindow& renderWindow, std::vector<Node> nodes) : _renderWindow(renderWindow) {
  _starved = false;
};

void Worm::update() {
  // called in main loop to advance to next iteration

}
