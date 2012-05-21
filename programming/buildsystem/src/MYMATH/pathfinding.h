/**
 * \file MYMATH/pathfinding.h
 * \brief Header file, for MYMATH/pathfinding.cpp
 *
 * (C)2001-2005 Justin Heyes-Jones & Adapted (c) 2010 Danny Arends<br>
 *
 **/

#ifndef PATHFINDING_H_
  #define PATHFINDING_H_
  #include "MYMATH.h"
  #include "astar/stlastar.h"

  #define DEBUG_LISTS 0
  #define DEBUG_LIST_LENGTHS_ONLY 0

  /**
   * \brief Class representing a node used in pathfinding
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class pathfindingnode : public mathobject{
  public:
    unsigned int x;
    unsigned int y;
    /**
     * A node as used by the A* path finding algorithm.<br>
     * bugs: none found<br>
     */
    pathfindingnode() { x = y = 0; }
    pathfindingnode( unsigned int px, unsigned int py ) { x=px; y=py; }

    float GoalDistanceEstimate( pathfindingnode &nodeGoal );
    bool IsGoal( pathfindingnode &nodeGoal );
    bool GetSuccessors( astarsearch<pathfindingnode> *as, pathfindingnode *parent_node);
    float GetCost( pathfindingnode &successor );
    bool IsSameState( pathfindingnode &rhs );

    void PrintNodeInfo();
    void SaveNode(int step,int num);
  };

  int search(int num);
#endif
