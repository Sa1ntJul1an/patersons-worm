# Paterson's Worm
Paterson's worm implementations, C++ and SFML

## Algorithm 
### Overview
This algorithm consists of an **infinite state space** and a single agent, known as the **worm**.  The state space is a triangular grid, where each intersection (**node**) has **6 paths** to take to neighboring nodes.  For each update of the algorithm, the worm moves to a new state (new node) by following one of the 6 paths according to a pre-defined **ruleset**.  Once a worm travels across a path, the path is **eaten** and cannot be traversed again by the worm.  The simulation ends if a worm encounters a node where all 6 paths are eaten (**starvation**), or halts due to one of the following conditions: 
* The worm encounters a new configuration and has no remaining remaining rules in the ruleset (**n-category**).  An n-category worm needs more rules in the ruleset, and has technically not *died* as in the case of starvation.
* The worm encounters a new configuration, and the next rule in the ruleset dictates that the worm must travel on a path that has already been consumed.  This move is not allowed, and therefore the simulation ends. 

### Ruleset 
The ruleset is a configurable parameter set before the algorithm begins that determines the behavior the worm will demonstrate when it encounters an unseen configuration.  A configuration refers to the distribution of un-consumed paths at a given node, relative to the coordinate frame of the worm.  The simplest configuration is a node where no path has been cosumed other than the path that the worm took to get to the node.  Another example configuration is where the path directly in front of the worm is the only path that has been consumed (not including the path that the worm took to get to this node, as this is implied for every configuration).  The worm will always begin in the simplest configuration as the state space is initially untouched (has no consumed paths).  

Each integer in the ruleset determines the direction the worm will move.  The integers can range from 0 to 5, as there are 6 possible paths the worm could take from a given node.  For this implementation, the rules are defined such that the integer corresponds to the path that is reached by multiplying the rule by 60 degrees clockwise.  So a rule of 0 is (0 * 60) = 0 degrees, meaning the worm will travel forward.  A rule of 4 is (4 * 60) = 240 degrees meaning the worm will travel along the path that is 240 degrees clockwise from its current direction, or 120 degrees counterclockwise (up and to the left if the axis is pointing to the right). 

As the worm encounters novel configurations, it chooses the next rule in the ruleset and performs that move. It then associates that configuration with the rule that was taken, and will always use that rule when it encounters the same configuration.

### Update Logic 
For each iteration, the worm will take an action based on its current state, the rulset, and some implicit rules.  If the simulation has just begun, all node configurations are novel as the worm has not encountered any.  Therefore, it will choose the first rule in the ruleset and move according to that rule.  Traditionally the first rule is 1.  As described above, a rule of 1 means that the worm will take the path that is 60 degrees clockwise from its starting direction (down and to the right if 0 degrees is to the right).  The worm will then evaluate the configuration that exists at the new node.  If the configuration has been seen before, it will follow the rule that is associated with that configuration.  If this path that must be taken according to the rule is already consumed, the simluation halts.  If the configuration has not been seen before, the worm will take the next un-mapped rule from the ruleset (moving from left to right in the ruleset), move according to the rule, and then map that configuration to that rule in case it is encountered again.  This continues until one of the halting conditions described above is reached.  In some cases, the worm will never halt and will travel for infinite iterations.

#### Special Case
Paterson's worm has an implicit rule which states that if there is no choice for the worm there is **no rule consumption**.  This means that if the worm enters a node that has only one un-consumed path, it will always take that path and not consume another rule from the ruleset (no rule mapping occurs).   

## Example Ruleset 
**{1, 2, 4, 3}**

Assume the worm begins facing to the right.  This is 0 degrees. 

The worm will begin in a fresh state space with no paths consumed.  As no nodes have been visited, the worm will choose the first rule in the ruleset, in this case a 1.  The worm will move (1 * 60) = 60 degrees clockwise (down and to the right).  The worm will associate the rule 1 with the simplest configuration, which is that where no paths (other than the entry path) have been consumed.  

The new node that the worm lands on will also be untouched, as the worm has only explored two nodes.  Since this configuration is mapped to the rule 1, the worm will again move according to the rule 1 (60 degrees clockwise).  This will occur until the worm has traced out a hexagon, as each time it will move to the node to its right (rule 1). 

Once it reaches the node where it began after completing a full loop, it will have encountered a new configuration as the path forward was previously consumed.  At this point, it will go to the next rule in the ruleset, which is 2.  The worm will move according to a rule of 2 (2 * 60 = 120 degrees clockwise).  

This will repeat indefinitely until a halting condition is encountered.


## Resources
* [Paterson's worm description by Ed Pegg](https://www.mathpuzzle.com/MAA/01-Paterson%27s%20Worms/mathgames_10_24_03.html)
* [Paterson's worm Wikipedia page](https://en.wikipedia.org/wiki/Paterson%27s_worms)
* [compiler link for SFML](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z)
