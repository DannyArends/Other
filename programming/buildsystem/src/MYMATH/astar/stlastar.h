/**
 * \file MYMATH/astar/stlastar.h
 * \brief Header file, contains: \ref astarsearch
 *
 * Pathfinding is achieved by using an adapted implementation of the STL A* Search implementation
  astarsearch class<br><br>

  This class is a constant time O(1) memory manager for objects of <br>
  a specified type. The type is specified using a template class.<br>

  Memory is allocated from a fixed size buffer which you can specify in the<br>
  class constructor or use the default.<br>

  Using GetFirst and GetNext it is possible to iterate through the elements<br>
  one by one, and this would be the most common use for the class. <br>

  I would suggest using this class when you want O(1) add and delete<br>
  and you don't do much searching, which would be O(n). Structures such as binary <br>
  trees can be used instead to get O(logn) access time. <br>
 * (C)2001-2005 Justin Heyes-Jones & Adapted (c) 2010 Danny Arends<br>
 *
 **/

// fast fixed size memory allocator, used for fast node memory management
#include "fsa.h"

// Fixed size memory allocator can be disabled to compare performance
// Uses std new and delete instead if you turn it off
#define USE_FSA_MEMORY 1

/**
 * \brief The AStar search class. user_state is the users state space type
 *
 * TODO Description<br>
 * bugs: none found<br>
 */
template <class user_state> class astarsearch : public mathobject{

  public: // data

    enum{SEARCH_STATE_NOT_INITIALISED,SEARCH_STATE_SEARCHING,SEARCH_STATE_SUCCEEDED,SEARCH_STATE_FAILED,SEARCH_STATE_OUT_OF_MEMORY,SEARCH_STATE_INVALID};

  public:
    /**
     * \brief Internal AStar search 'node' class
     *
     * TODO Description<br>
     * bugs: none found<br>
     */
    class node
    {
      public:

        node *parent; // used during the search to record the parent of successor nodes
        node *child; // used after the search for the application to view the search in reverse

        float g; // cost of this node + it's predecessors
        float h; // heuristic estimate of distance to goal
        float f; // sum of cumulative cost of predecessors and self and heuristic

        node() : parent( 0 ), child( 0 ),	g( 0.0f ), h( 0.0f ),	f( 0.0f ){

        }
        user_state m_user_state;
    };

    /**
     * \brief Internal AStar search 'heapcompare' class
     *
     * For sorting the heap the STL needs compare function that lets us compare
     * the f value of two nodes
     *
     * TODO Description<br>
     * bugs: none found<br>
     */
    class heapcompare
    {
      public:

        bool operator() ( const node *x, const node *y ) const
        {
          return x->f > y->f;
        }
    };


  public: // methods


    // constructor just initialises private data
    astarsearch( int MaxNodes ) : m_FixedSizeAllocator( MaxNodes ), m_CancelRequest( false ){
      this->m_CurrentSolutionNode=NULL;
      this->m_AllocateNodeCount=0;
      this->m_State=SEARCH_STATE_NOT_INITIALISED;
      }

    // call at any time to cancel the search and free up all the memory
    void CancelSearch()
    {
      m_CancelRequest = true;
    }

    // Set Start and goal states
    void SetStartAndGoalStates( user_state &Start, user_state &Goal )
    {
      m_CancelRequest = false;

      m_Start = AllocateNode();
      m_Goal = AllocateNode();

      assert((m_Start != NULL && m_Goal != NULL));

      m_Start->m_user_state = Start;
      m_Goal->m_user_state = Goal;

      m_State = SEARCH_STATE_SEARCHING;

      // Initialise the AStar specific parts of the Start Node
      // The user only needs fill out the state information

      m_Start->g = 0;
      m_Start->h = m_Start->m_user_state.GoalDistanceEstimate( m_Goal->m_user_state );
      m_Start->f = m_Start->g + m_Start->h;
      m_Start->parent = 0;

      // Push the start node on the Open list

      m_OpenList.push_back( m_Start ); // heap now unsorted

      // Sort back element into heap
      push_heap( m_OpenList.begin(), m_OpenList.end(), heapcompare() );

      // Initialise counter for search steps
      m_Steps = 0;
    }

    // Advances search one step
    unsigned int SearchStep(){
      // Firstly break if the user has not initialised the search
      assert( (m_State > SEARCH_STATE_NOT_INITIALISED) &&
          (m_State < SEARCH_STATE_INVALID) );

      // Next I want it to be safe to do a searchstep once the search has succeeded...
      if( (m_State == SEARCH_STATE_SUCCEEDED) ||
          (m_State == SEARCH_STATE_FAILED)
      )
      {
        return m_State;
      }

      // Failure is defined as emptying the open list as there is nothing left to
      // search...
      // New: Allow user abort
      if( m_OpenList.empty() || m_CancelRequest )
      {
        FreeAllNodes();
        m_State = SEARCH_STATE_FAILED;
        return m_State;
      }

      // Incremement step count
      m_Steps ++;

      // Pop the best node (the one with the lowest f)
      node *n = m_OpenList.front(); // get pointer to the node
      pop_heap( m_OpenList.begin(), m_OpenList.end(), heapcompare() );
      m_OpenList.pop_back();

      // Check for the goal, once we pop that we're done
      if( n->m_user_state.IsGoal( m_Goal->m_user_state ) )
      {
        // The user is going to use the Goal node he passed in
        // so copy the parent pointer of n
        m_Goal->parent = n->parent;

        // A special case is that the goal was passed in as the start state
        // so handle that here
        if( false == n->m_user_state.IsSameState( m_Start->m_user_state ) )
        {
          FreeNode( n );

          // set the child pointers in each node (except Goal which has no child)
          node *nodeChild = m_Goal;
          node *nodeParent = m_Goal->parent;

          do
          {
            nodeParent->child = nodeChild;

            nodeChild = nodeParent;
            nodeParent = nodeParent->parent;

          }
          while( nodeChild != m_Start ); // Start is always the first node by definition

        }

        // delete nodes that aren't needed for the solution
        FreeUnusedNodes();

        m_State = SEARCH_STATE_SUCCEEDED;

        return m_State;
      }else{
        // We now need to generate the successors of this node
        // The user helps us to do this, and we keep the new nodes in
        // m_Successors ...

        m_Successors.clear(); // empty vector of successor nodes to n

        // User provides this functions and uses AddSuccessor to add each successor of
        // node 'n' to m_Successors
        bool ret = n->m_user_state.GetSuccessors( this, n->parent ? &n->parent->m_user_state : NULL );

        if( !ret )
        {

          typename vector< node * >::iterator successor;

          // free the nodes that may previously have been added
          for( successor = m_Successors.begin(); successor != m_Successors.end(); successor ++ )
          {
            FreeNode( (*successor) );
          }

          m_Successors.clear(); // empty vector of successor nodes to n

          // free up everything else we allocated
          FreeAllNodes();

          m_State = SEARCH_STATE_OUT_OF_MEMORY;
          return m_State;
        }

        // Now handle each successor to the current node ...
        for( typename vector< node * >::iterator successor = m_Successors.begin(); successor != m_Successors.end(); successor ++ )
        {

          // 	The g value for this successor ...
          float newg = n->g + n->m_user_state.GetCost( (*successor)->m_user_state );

          // Now we need to find whether the node is on the open or closed lists
          // If it is but the node that is already on them is better (lower g)
          // then we can forget about this successor

          // First linear search of open list to find node

          typename vector< node * >::iterator openlist_result;

          for( openlist_result = m_OpenList.begin(); openlist_result != m_OpenList.end(); openlist_result ++ )
          {
            if( (*openlist_result)->m_user_state.IsSameState( (*successor)->m_user_state ) )
            {
              break;
            }
          }

          if( openlist_result != m_OpenList.end() )
          {

            // we found this state on open

            if( (*openlist_result)->g <= newg )
            {
              FreeNode( (*successor) );

              // the one on Open is cheaper than this one
              continue;
            }
          }

          typename vector< node * >::iterator closedlist_result;

          for( closedlist_result = m_ClosedList.begin(); closedlist_result != m_ClosedList.end(); closedlist_result ++ )
          {
            if( (*closedlist_result)->m_user_state.IsSameState( (*successor)->m_user_state ) )
            {
              break;
            }
          }

          if( closedlist_result != m_ClosedList.end() )
          {

            // we found this state on closed

            if( (*closedlist_result)->g <= newg )
            {
              // the one on Closed is cheaper than this one
              FreeNode( (*successor) );

              continue;
            }
          }

          // This node is the best node so far with this particular state
          // so lets keep it and set up its AStar specific data ...

          (*successor)->parent = n;
          (*successor)->g = newg;
          (*successor)->h = (*successor)->m_user_state.GoalDistanceEstimate( m_Goal->m_user_state );
          (*successor)->f = (*successor)->g + (*successor)->h;

          // Remove successor from closed if it was on it

          if( closedlist_result != m_ClosedList.end() )
          {
            // remove it from Closed
            FreeNode(  (*closedlist_result) );
            m_ClosedList.erase( closedlist_result );

            // Fix thanks to ...
            // Greg Douglas <gregdouglasmail@gmail.com>
            // who noticed that this code path was incorrect
            // Here we have found a new state which is already CLOSED
            // anus

          }

          // Update old version of this node
          if( openlist_result != m_OpenList.end() )
          {

            FreeNode( (*openlist_result) );
            m_OpenList.erase( openlist_result );

            // re-make the heap
            // make_heap rather than sort_heap is an essential bug fix
            // thanks to Mike Ryynanen for pointing this out and then explaining
            // it in detail. sort_heap called on an invalid heap does not work
            make_heap( m_OpenList.begin(), m_OpenList.end(), heapcompare() );

          }

          // heap now unsorted
          m_OpenList.push_back( (*successor) );

          // sort back element into heap
          push_heap( m_OpenList.begin(), m_OpenList.end(), heapcompare() );

        }

        // push n onto Closed, as we have expanded it now

        m_ClosedList.push_back( n );

      } // end else (not goal so expand)

      return m_State; // Succeeded bool is false at this point.

    }

    // User calls this to add a successor to a list of successors
    // when expanding the search frontier
    bool AddSuccessor( user_state &State )
    {
      node *n = AllocateNode();

      if( n )
      {
        n->m_user_state = State;

        m_Successors.push_back( n );

        return true;
      }

      return false;
    }

    // Free the solution nodes
    // This is done to clean up all used node memory when you are done with the
    // search
    void FreeSolutionNodes()
    {
      node *n = m_Start;

      if( m_Start->child )
      {
        do
        {
          node *del = n;
          n = n->child;
          FreeNode( del );

          del = NULL;

        } while( n != m_Goal );

        FreeNode( n ); // Delete the goal

      }
      else
      {
        // if the start node is the solution we need to just delete the start and goal
        // nodes
        FreeNode( m_Start );
        FreeNode( m_Goal );
      }

    }

    // Functions for traversing the solution

    // Get start node
    user_state *GetSolutionStart()
    {
      m_CurrentSolutionNode = m_Start;
      if( m_Start )
      {
        return &m_Start->m_user_state;
      }
      else
      {
        return NULL;
      }
    }

    // Get next node
    user_state *GetSolutionNext()
    {
      if( m_CurrentSolutionNode )
      {
        if( m_CurrentSolutionNode->child )
        {

          node *child = m_CurrentSolutionNode->child;

          m_CurrentSolutionNode = m_CurrentSolutionNode->child;

          return &child->m_user_state;
        }
      }

      return NULL;
    }

    // Get end node
    user_state *GetSolutionEnd()
    {
      m_CurrentSolutionNode = m_Goal;
      if( m_Goal )
      {
        return &m_Goal->m_user_state;
      }
      else
      {
        return NULL;
      }
    }

    // Step solution iterator backwards
    user_state *GetSolutionPrev()
    {
      if( m_CurrentSolutionNode )
      {
        if( m_CurrentSolutionNode->parent )
        {

          node *parent = m_CurrentSolutionNode->parent;

          m_CurrentSolutionNode = m_CurrentSolutionNode->parent;

          return &parent->m_user_state;
        }
      }

      return NULL;
    }

    // For educational use and debugging it is useful to be able to view
    // the open and closed list at each step, here are two functions to allow that.

    user_state *GetOpenListStart()
    {
      float f,g,h;
      return GetOpenListStart( f,g,h );
    }

    user_state *GetOpenListStart( float &f, float &g, float &h )
    {
      iterDbgOpen = m_OpenList.begin();
      if( iterDbgOpen != m_OpenList.end() )
      {
        f = (*iterDbgOpen)->f;
        g = (*iterDbgOpen)->g;
        h = (*iterDbgOpen)->h;
        return &(*iterDbgOpen)->m_user_state;
      }

      return NULL;
    }

    user_state *GetOpenListNext()
    {
      float f,g,h;
      return GetOpenListNext( f,g,h );
    }

    user_state *GetOpenListNext( float &f, float &g, float &h )
    {
      iterDbgOpen++;
      if( iterDbgOpen != m_OpenList.end() )
      {
        f = (*iterDbgOpen)->f;
        g = (*iterDbgOpen)->g;
        h = (*iterDbgOpen)->h;
        return &(*iterDbgOpen)->m_user_state;
      }

      return NULL;
    }

    user_state *GetClosedListStart()
    {
      float f,g,h;
      return GetClosedListStart( f,g,h );
    }

    user_state *GetClosedListStart( float &f, float &g, float &h )
    {
      iterDbgClosed = m_ClosedList.begin();
      if( iterDbgClosed != m_ClosedList.end() )
      {
        f = (*iterDbgClosed)->f;
        g = (*iterDbgClosed)->g;
        h = (*iterDbgClosed)->h;

        return &(*iterDbgClosed)->m_user_state;
      }

      return NULL;
    }

    user_state *GetClosedListNext()
    {
      float f,g,h;
      return GetClosedListNext( f,g,h );
    }

    user_state *GetClosedListNext( float &f, float &g, float &h )
    {
      iterDbgClosed++;
      if( iterDbgClosed != m_ClosedList.end() )
      {
        f = (*iterDbgClosed)->f;
        g = (*iterDbgClosed)->g;
        h = (*iterDbgClosed)->h;

        return &(*iterDbgClosed)->m_user_state;
      }

      return NULL;
    }

    // Get the number of steps

    int GetStepCount() { return m_Steps; }

    void EnsureMemoryFreed()
    {
#if USE_FSA_MEMORY
      assert(m_AllocateNodeCount == 0);
#endif

    }

  private: // methods

    // This is called when a search fails or is cancelled to free all used
    // memory
    void FreeAllNodes()
    {
      // iterate open list and delete all nodes
      typename vector< node * >::iterator iterOpen = m_OpenList.begin();

      while( iterOpen != m_OpenList.end() )
      {
        node *n = (*iterOpen);
        FreeNode( n );

        iterOpen ++;
      }

      m_OpenList.clear();

      // iterate closed list and delete unused nodes
      typename vector< node * >::iterator iterClosed;

      for( iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed ++ )
      {
        node *n = (*iterClosed);
        FreeNode( n );
      }

      m_ClosedList.clear();

      // delete the goal

      FreeNode(m_Goal);
    }


    // This call is made by the search class when the search ends. A lot of nodes may be
    // created that are still present when the search ends. They will be deleted by this
    // routine once the search ends
    void FreeUnusedNodes()
    {
      // iterate open list and delete unused nodes
      typename vector< node * >::iterator iterOpen = m_OpenList.begin();

      while( iterOpen != m_OpenList.end() )
      {
        node *n = (*iterOpen);

        if( !n->child )
        {
          FreeNode( n );

          n = NULL;
        }

        iterOpen ++;
      }

      m_OpenList.clear();

      // iterate closed list and delete unused nodes
      typename vector< node * >::iterator iterClosed;

      for( iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed ++ )
      {
        node *n = (*iterClosed);

        if( !n->child )
        {
          FreeNode( n );
          n = NULL;

        }
      }

      m_ClosedList.clear();

    }

    // node memory management
    node *AllocateNode(){

#if !USE_FSA_MEMORY
      node *p = new Node;
      return p;
#else
      node *address = m_FixedSizeAllocator.alloc();

      if( !address )
      {
        return NULL;
      }
      m_AllocateNodeCount ++;
      node *p = new (address) node;
      return p;
#endif
    }

    void FreeNode( node *n ){
      m_AllocateNodeCount --;

#if !USE_FSA_MEMORY
      delete n;
#else
      m_FixedSizeAllocator.free( n );
#endif
    }

  private: // data

    // Heap (simple vector but used as a heap, cf. Steve Rabin's game gems article)
    vector< node* > m_OpenList;

    // Closed list is a vector.
    vector< node* > m_ClosedList;

    // Successors is a vector filled out by the user each type successors to a node
    // are generated
    vector< node* > m_Successors;

    // State
    unsigned int m_State;

    // Counts steps
    int m_Steps;

    // Start and goal state pointers
    node *m_Start;
    node *m_Goal;

    node *m_CurrentSolutionNode;

    // Memory
    fixedsizeallocator< node > m_FixedSizeAllocator;

    //Debug : need to keep these two iterators around
    // for the user Dbg functions
    typename vector< node * >::iterator iterDbgOpen;
    typename vector< node * >::iterator iterDbgClosed;

    // debugging : count memory allocation and free's
    int m_AllocateNodeCount;

    bool m_CancelRequest;

};




