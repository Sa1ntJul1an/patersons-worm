#include <SFML/Graphics.hpp>
#include <cmath>
#include <queue>
#include <string>

#include "node.h"
#include "worm.h"
#include "environment.h"

// mingw32-make.exe

using namespace sf;
using namespace std;

int main(){

  bool iterating = false;
  int iteration = 0;

  // SEARCH RENDER WINDOW
  // =======================================================================
  RenderWindow renderWindow(VideoMode(1000, 700), "Search Algorithm");
  renderWindow.setFramerateLimit(60);
  // =======================================================================

  Font font;
  FileInputStream fontIn;
  fontIn.open("slkscr.ttf");
  font.loadFromStream(fontIn);

  Text iterationText;
  iterationText.setFillColor(Color::Red);
  iterationText.setPosition(10, 10);
  iterationText.setFont(font);
  iterationText.setCharacterSize(30);
  
  std::vector<int> rulesList = {1, 0, 5, 1};
  queue<int> rules;
  for (int rule : rulesList) {
    rules.push(rule);
  }

  int initDirection = 0;

  Node * initialNode = new Node({0, 0});
  Worm* worm = new Worm(initialNode, initDirection, rules);
  Environment environment = Environment(renderWindow, worm);

  bool keyboard_held = false;

  while(renderWindow.isOpen()){

    // KEYBOARD EVENTS =========================================
    if (Keyboard::isKeyPressed(Keyboard::Space)){   // space to start search
      if (!keyboard_held) {
        iterating = !iterating;
        keyboard_held = true;
      }
    } else {
      keyboard_held = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::R)){       // R to reset
      iteration = 0;
      iterating = false;
    }
    // ==========================================================

    // update iteration here 
    if (iterating) {
      environment.update();
      iteration++;
    }

    // CLOSE WINDOWS IF X PRESSED
    // ==========================================================
    Event renderWindowEvent;

    while(renderWindow.pollEvent(renderWindowEvent)){
      if(renderWindowEvent.type == Event::Closed){
        renderWindow.close();
      }
    }
    // ==========================================================


    // DRAW
    // ==========================================================
    renderWindow.clear();

    iterationText.setString("Iteration: " + to_string(iteration));
    renderWindow.draw(iterationText);
    environment.draw();

    renderWindow.display();
  }

  return 0;
}
