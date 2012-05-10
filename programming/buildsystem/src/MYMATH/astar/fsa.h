/**
 * \file MYMATH/astar/fsa.h
 * \brief Header file, contains: \ref fixedsizeallocator
 *
 * Path finding is achieved by using an adapted implementation of the STL A* Search implementation
  fixedsizeallocator class<br><br>

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

#ifndef FSA_H
#define FSA_H

/**
 * \brief Class representing the fixedsizeallocator
 *
 * This class is a constant time O(1) memory manager for objects of
 * a specified type. The type is specified using a template class.
 *
 * TODO Description<br>
 * bugs: none found<br>
 */
template <class user_type> class fixedsizeallocator : public mathobject{

public:
	// Constants
	enum
	{
		FSA_DEFAULT_SIZE = 1000
	};

  /**
   * \brief Structure representing a single element of the \ref fixedsizeallocator
   *
   * This class enables us to transparently manage the extra data
   * needed to enable the user class to form part of the double-linked
   * list class
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
	struct fsa_element
	{
		user_type UserType;

		fsa_element *pPrev;
		fsa_element *pNext;
	};

public: // methods
	fixedsizeallocator( unsigned int MaxElements ) :
	m_pFirstUsed( NULL )
	{
		// Allocate enough memory for the maximum number of elements
	  this->m_MaxElements=MaxElements;
		char *pMem = new char[ m_MaxElements * sizeof(fsa_element) ];

		m_pMemory = (fsa_element *) pMem;

		// Set the free list first pointer
		m_pFirstFree = m_pMemory;

		// Clear the memory
		memset( m_pMemory, 0, sizeof( fsa_element ) * m_MaxElements );

		// Point at first element
		fsa_element *pElement = m_pFirstFree;

		// Set the double linked free list
		for( unsigned int i=0; i<m_MaxElements; i++ )
		{
			pElement->pPrev = pElement-1;
			pElement->pNext = pElement+1;

			pElement++;
		}

		// first element should have a null prev
		m_pFirstFree->pPrev = NULL;
		// last element should have a null next
		(pElement-1)->pNext = NULL;

	}


	~fixedsizeallocator()
	{
		// Free up the memory
		delete [] m_pMemory;
	}

	// Allocate a new user_type and return a pointer to it
	user_type *alloc()
	{

		fsa_element *pNewNode = NULL;

		if( !m_pFirstFree )
		{
			return NULL;
		}
		else
		{
			pNewNode = m_pFirstFree;
			m_pFirstFree = pNewNode->pNext;

			// if the new node points to another free node then
			// change that nodes prev free pointer...
			if( pNewNode->pNext )
			{
				pNewNode->pNext->pPrev = NULL;
			}

			// node is now on the used list

			pNewNode->pPrev = NULL; // the allocated node is always first in the list

			if( m_pFirstUsed == NULL )
			{
				pNewNode->pNext = NULL; // no other nodes
			}
			else
			{
				m_pFirstUsed->pPrev = pNewNode; // insert this at the head of the used list
				pNewNode->pNext = m_pFirstUsed;
			}

			m_pFirstUsed = pNewNode;
		}

		return reinterpret_cast<user_type*>(pNewNode);
	}

	// Free the given user type
	// For efficiency I don't check whether the user_data is a valid
	// pointer that was allocated. I may add some debug only checking
	// (To add the debug check you'd need to make sure the pointer is in
	// the m_pMemory area and is pointing at the start of a node)
	void free( user_type *user_data )
	{
		fsa_element *pNode = reinterpret_cast<fsa_element*>(user_data);

		// manage used list, remove this node from it
		if( pNode->pPrev )
		{
			pNode->pPrev->pNext = pNode->pNext;
		}
		else
		{
			// this handles the case that we delete the first node in the used list
			m_pFirstUsed = pNode->pNext;
		}

		if( pNode->pNext )
		{
			pNode->pNext->pPrev = pNode->pPrev;
		}

		// add to free list
		if( m_pFirstFree == NULL )
		{
			// free list was empty
			m_pFirstFree = pNode;
			pNode->pPrev = NULL;
			pNode->pNext = NULL;
		}
		else
		{
			// Add this node at the start of the free list
			m_pFirstFree->pPrev = pNode;
			pNode->pNext = m_pFirstFree;
			m_pFirstFree = pNode;
		}

	}

	// For debugging this displays both lists (using the prev/next list pointers)
	void Debug()
	{
		printf( "free list " );

		fsa_element *p = m_pFirstFree;
		while( p )
		{
			printf( "%x!%x ", p->pPrev, p->pNext );
			p = p->pNext;
		}
		printf( "\n" );

		printf( "used list " );

		p = m_pFirstUsed;
		while( p )
		{
			printf( "%x!%x ", p->pPrev, p->pNext );
			p = p->pNext;
		}
		printf( "\n" );
	}

	// Iterators

	user_type *GetFirst()
	{
		return reinterpret_cast<user_type *>(m_pFirstUsed);
	}

	user_type *GetNext( user_type *node )
	{
		return reinterpret_cast<user_type *>
			(
				(reinterpret_cast<fsa_element *>(node))->pNext
			);
	}

public: // data

private: // methods

private: // data

	fsa_element *m_pFirstFree;
	fsa_element *m_pFirstUsed;
	unsigned int m_MaxElements;
	fsa_element *m_pMemory;

};

#endif // defined FSA_H
