#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
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

  const int RENDER_WIDTH = 1000;
  const int RENDER_HEIGHT = 700;

  // SEARCH RENDER WINDOW
  // =======================================================================
  RenderWindow renderWindow(VideoMode(RENDER_WIDTH, RENDER_HEIGHT), "Paterson's Worm");
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

  Text haltedText;
  haltedText.setFillColor(Color::Black);
  haltedText.setFont(font);
  haltedText.setCharacterSize(100);
  
  FloatRect textRect;

  Color simRunningBackgroundColor = Color::Black;
  Color simHaltedBackgroundColor = Color(120, 0, 0);
  Color backgroundColor = Color::Black;

  /*std::vector<int> rulesList = {1, 0, 5, 1};*/
  /*std::vector<int> rulesList = {1, 0, 4, 0, 1, 5};*/
  std::vector<int> rulesList = {1, 0, 4, 0, 1, 0, 1};
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
    if (iterating && !worm->isHalted()) {
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
    renderWindow.clear(backgroundColor);
    
    if (worm->isHalted()) {
      backgroundColor = simHaltedBackgroundColor;
      if (worm->isStarved()) {
        haltedText.setString("Worm Starved");
      } else if (worm->isNType()) {
        haltedText.setString("N-Type Worm");
      } else if (worm->isImpossiblePath()) {
        haltedText.setString("Impossible Path");
      }
      textRect = haltedText.getLocalBounds();
      haltedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
      haltedText.setPosition(RENDER_WIDTH / 2.0f, RENDER_HEIGHT / 4.0f);
      renderWindow.draw(haltedText);
    } else {
      backgroundColor = simRunningBackgroundColor;
    }
    
    iterationText.setString("Iteration: " + to_string(iteration));
    renderWindow.draw(iterationText);
    environment.draw();

    renderWindow.display();
  }

  return 0;
}
