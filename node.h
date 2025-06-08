#ifndef NODE_HEADER
#define NODE_HEADER

#include <map>
#include <utility>
#include <set>

class Node{
  public:
    Node(std::pair<int, int> coords);
    std::pair<int, int> getPosition() const;
    std::set<int> getConfiguration(int direction);
    void addEaten(Node* neighbor);
    void addEaten(int direction);
    bool isEaten(int direction);

  private:
    std::pair<int, int> _position;
    std::set<int> _configuration;                           // set of ints, each int that exists in this set corresponds to an eaten path in that direction
};

#endif /* !NODE_HEADER */
