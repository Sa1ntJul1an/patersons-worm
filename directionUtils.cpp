#include "directionUtils.h"
#include <map>

namespace {
  const std::map<int, std::pair<int, int>> directionToDeltaPosMap = {
    {0, {1, 0}},
    {1, {1, -1}},
    {2, {0, -1}},
    {3, {-1, 0}},
    {4, {-1, 1}},
    {5, {0, 1}}
  };

  const std::map<std::pair<int, int>, int> deltaPosToDirectionMap = {
    {{1, 0}, 0},
    {{1, -1}, 1},
    {{0, -1}, 2},
    {{-1, 0}, 3},
    {{-1, 1}, 4},
    {{0, 1}, 5}
  };

  const std::map<int, int> invertDirectionMap = {
    {0, 3},
    {1, 4},
    {2, 5},
    {3, 0},
    {4, 1},
    {5, 2}
  };
}

namespace DirectionUtils {

  const int invertDirection(const int currentDirection) {
    // return -1 for bad inputs
    if (currentDirection > 5 || currentDirection < 0) {
      return -1;
    }

    return invertDirectionMap.at(currentDirection);
  }

  const int getDirection(const std::pair<int, int> delta_position) {
    // return -1 for bad inputs
    if (delta_position.first > 1 || delta_position.first < -1) {
      return -1;
    }
    if (delta_position.second > 1 || delta_position.second < -1) {
      return -1;
    }

    return deltaPosToDirectionMap.at(delta_position);
  }

  const std::pair<int, int> getDeltaPosition(const int direction) {
    // return {-1, -1} for bad input 
    if (direction > 5 || direction < 0) {
      return {-1, -1};
    }

    return directionToDeltaPosMap.at(direction);
  }
  
  const int transformDirection(const int current_direction, const int transform_direction) {
    // return -1 for bad inputs
    if (current_direction > 5 || current_direction < 0) {
      return -1;
    }
    if (transform_direction > 5 || transform_direction < 0) {
      return -1;
    }

    // if the current direction is greater than or equal to the transform direction, we can simply subtract current from transform to transform it
    if (current_direction >= transform_direction) {
      return current_direction - transform_direction;
    }
    
    // - if the current direction is lesser than the transform direction, we have to underflow as directions below 0 wrap around beginning at 5. 
    // - this logic handles that
    int delta = transform_direction - current_direction;
    return 6 - delta;
  }

}
