/**
 * \file MYMATH/pathfinding.cpp
 * \brief Code file, Implementation of class: \ref pathfindingnode
 *
 * Pathfinding is achieved by using an adapted implementation of the STL A* Search implementation
 * (C)2001 Justin Heyes-Jones & Adapted (c) 2010 Danny Arends
 *
 **/

#include "pathfinding.h"

/**
* C-routine that returns the cost of moving onto x,y<br>
* bugs: none found<br>
* @param x two dimensional x coordinate<br>
* @param y two dimensional y coordinate<br>
*/
int costfunction( int x, int y){
  return 9;
}

bool pathfindingnode::IsSameState( pathfindingnode &rhs ){
	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) && (y == rhs.y) ){
		return true;
	}else{
		return false;
	}
}

void pathfindingnode::PrintNodeInfo(){
//	char str[100];
//	sprintf( str, "Node position : (%d,%d)\n", x,y );

//	cout << str;
}

void pathfindingnode::SaveNode(int step,int num){
	if(step < 50){
//    user user = information[num].socketuser;
  //  int world = user_on_map(num);
    //printf("Node position : (%d,%d)\n", x,y );
  //  user.currentPath[step].x = x;
  //  user.currentPath[step].z = y;
 //   information[num].socketuser = user;
    }
}

float makeabsolute(float x){
  if(x < 0){
    return -x;
  }else{
    return x;
  }
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float pathfindingnode::GoalDistanceEstimate( pathfindingnode &nodeGoal )
{
	float xd = float( ( (float)x - (float)nodeGoal.x ) );
	float yd = float( ( (float)y - (float)nodeGoal.y) );

	return makeabsolute(xd) + makeabsolute(yd);

}

bool pathfindingnode::IsGoal( pathfindingnode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool pathfindingnode::GetSuccessors( astarsearch<pathfindingnode> *as, pathfindingnode *parent_node)
{

	int parent_x = -1;
	int parent_y = -1;

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}


	pathfindingnode NewNode;

	// push each possible move except allowing the search to go backwards
	int x=0;
	int y=0;
	if( (costfunction( x-1, y) < 9) && !((parent_x == x-1) && (parent_y == y)) ){
		NewNode = pathfindingnode( x-1, y );
		as->AddSuccessor( NewNode );
	}

	if( (costfunction( x, y-1) < 9) && !((parent_x == x) && (parent_y == y-1)) ){
		NewNode = pathfindingnode( x, y-1 );
		as->AddSuccessor( NewNode );
	}

	if( (costfunction( x+1, y) < 9)	&& !((parent_x == x+1) && (parent_y == y)) ){
		NewNode = pathfindingnode( x+1, y );
		as->AddSuccessor( NewNode );
	}


	if( (costfunction( x, y+1) < 9)	&& !((parent_x == x) && (parent_y == y+1)) ){
		NewNode = pathfindingnode( x, y+1 );
		as->AddSuccessor( NewNode );
	}

	if( (costfunction( x-1, y+1) < 9) && !((parent_x == x-1) && (parent_y == y+1)) ){
		NewNode = pathfindingnode( x-1, y+1 );
		as->AddSuccessor( NewNode );
	}

	if( (costfunction( x+1, y+1) < 9) && !((parent_x == x+1) && (parent_y == y+1)) ){
		NewNode = pathfindingnode( x+1, y+1 );
		as->AddSuccessor( NewNode );
	}

	if( (costfunction( x+1, y-1) < 9) && !((parent_x == x+1) && (parent_y == y-1)) ){
		NewNode = pathfindingnode( x+1, y-1 );
		as->AddSuccessor( NewNode );
	}

	if( (costfunction( x-1, y-1) < 9) && !((parent_x == x-1) && (parent_y == y-1)) ){
		NewNode = pathfindingnode( x-1, y-1 );
		as->AddSuccessor( NewNode );
	}

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float pathfindingnode::GetCost( pathfindingnode &successor){
	return (float) costfunction(x, y);

}


// Main

int search(int num)
{

//	user user = information[num].socketuser;
 //   int world = user_on_map(num);

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost
	// of travel across the terrain. Zero means the least possible difficulty
	// in travelling (think ice rink if you can skate) whilst 5 represents the
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...

	astarsearch<pathfindingnode> as(1500);

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 3;

	while(SearchCount < NumSearches){

		// Create a start state
		pathfindingnode nodeStart;
	//	nodeStart.x = user.x;
//		nodeStart.y = user.z;

		// Define the goal state
		pathfindingnode nodeEnd;
	//	nodeEnd.x = user.wanted_x;
	//	nodeEnd.y = user.wanted_z;
		// Check it we can move and that the tile moving to IS empty
		if(costfunction(nodeStart.x,nodeStart.y) == 9){
		  printf("Startpoint (%d,%d) invalid\n",nodeEnd.x,nodeEnd.y);
		  return 0;
        }
		if(costfunction(nodeEnd.x,nodeEnd.y) == 9){
		  printf("End point (%d,%d) unreachable\n",nodeEnd.x,nodeEnd.y);
		  return 0;
        }
		// Set Start and goal states
		as.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do{
			SearchState = as.SearchStep();
			SearchSteps++;

	#if DEBUG_LISTS
	   //     printf("Steps: %d\n", SearchSteps );
			int len = 0;
		//	cout << "Open:\n";
			pathfindingnode *p = as.GetOpenListStart();
			while( p ){
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY
				((pathfindingnode *)p)->PrintNodeInfo();
	#endif
				p = as.GetOpenListNext();
			}
      printf("Openlist#: %d\n", len );
			len = 0;

		//	cout << "Closed:\n";
			p = as.GetClosedListStart();
			while( p ){
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY
				p->PrintNodeInfo();
	#endif
				p = as.GetClosedListNext();
			}
      printf("Closedlist#: %d\n", len );
	//		cout << "Closed list has " << len << " nodes\n";
	#endif
		}
		while( SearchState == astarsearch<pathfindingnode>::SEARCH_STATE_SEARCHING );

		if( SearchState == astarsearch<pathfindingnode>::SEARCH_STATE_SUCCEEDED ){
	//		cout << "Search found goal state\n";
      pathfindingnode *node = as.GetSolutionStart();
      #if DISPLAY_SOLUTION
        //	cout << "Displaying solution\n";
      #endif
			int steps = 0;
			node->PrintNodeInfo();
			for( ;; ){
				node = as.GetSolutionNext();
        if( !node ){
						break;
        }
		//		node->PrintNodeInfo();
				node->SaveNode(steps,num);
				steps ++;
			};

		//		cout << "Solution steps " << steps << endl;
     //           information[num].socketuser.cur_step = 0;
          if(steps < 50){
       //           information[num].socketuser.max_steps = steps;
          }else{
         //         information[num].socketuser.max_steps = 50;
          }
				// Once you're done with the solution you can free the nodes up
			as.FreeSolutionNodes();
		}else if( SearchState == astarsearch<pathfindingnode>::SEARCH_STATE_FAILED ){
			printf("Search terminated. Did not find goal state (%d,%d)\n",nodeEnd.x,nodeEnd.y);
		}
		SearchCount ++;
		as.EnsureMemoryFreed();
	}
	return 0;
}

