#ifndef DIRECTIONUTILS_HEADER
#define DIRECTIONUTILS_HEADER

#include <map>
#include <utility>
namespace DirectionUtils {

  /**
   * @brief Inverts a direction integer, returning the integer representing the opposite direction.
   * @param `direction` The current direction. 
   * @returns The integer representing the direction opposite `direction`. 
  **/
  const int invertDirection(const int currentDirection);

  /**
   * @brief Returns the delta position for a given direction.
   * @param `direction` The direction integer [0, 5] in which the agent will move. 
   * @returns Pair of ints representing the change in each axis {q, r}. 
  **/
  const std::pair<int, int> getDeltaPosition(const int direction);
  
  /**
   * @brief Returns the direction for a given delta position.
   * @param `delta_position` Pair of ints representing how position has changed due to a move. 
   * @returns Integer representing the direction [0, 5] that would have caused this change in position.
  **/
  const int getDirection(const std::pair<int, int> delta_position);
  
  /**
   * @brief Transforms the direction by a given input direction, returning the direction transformed to the relative coordinate frame.
   * @param `input_direction` Integer representing the current direction before transformation.
   * @param `transform_direction` Integer representing the direction of the relative coordinate frame.
   * @returns Integer representing the transformed direction [0, 5] found after the rotation is performed.
  **/
  const int transformDirectionGlobalToRelative(const int input_direction, const int transform_direction);
  
  /**
   * @brief Transforms the direction by a given input direction, returning the direction transformed to the global coordinate frame.
   * @param `current_direction` Integer representing the current direction before transformation.
   * @param `transform_direction` Integer representing the direction of the relative coordinate frame.
   * @returns Integer representing the transformed direction [0, 5] found after the rotation is performed.
  **/
  const int transformDirectionRelativeToGlobal(const int input_direction, const int transform_direction);
}

#endif // !DIRECTIONUTILS_HEADER
