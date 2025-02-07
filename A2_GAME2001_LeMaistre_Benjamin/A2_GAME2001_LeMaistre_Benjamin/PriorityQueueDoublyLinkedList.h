#pragma once
#include <cassert>

// Template Class Declarations
template <class T> class LinkIterator;
template <class T> class LinkedList;

// Define a node
template <class T>
class LinkNode
{
public:
	// Give access to the private member variables
	friend class LinkIterator<T>;
	friend class LinkedList<T>;

	int getPriority() 
	{
		return m_priority;
	}

	T getData()
	{
		return m_data;
	}

private:
	T m_data;
	int m_priority;		//priority of the node will be used to order the linked list with priority queue
	LinkNode* m_next;	// Self-referencial Pointer
	LinkNode* m_previous;
};

// Define an iterator
template <class T>
class LinkIterator
{
public:
	// New Addition
	friend class LinkedList<T>;

	LinkIterator()
	{
		m_node = nullptr;
	}
	~LinkIterator() {}
	// ----------- OVERLOADED OPERATORS ------------------

	// Assignmnet operator (=) <-- Set the iterator to point to a node  // a = b
	void operator=(LinkNode<T>* node)
	{
		m_node = node;
	}
	// Incremental operator (++) Prefix and Postfox <-- Move the iterator to the next node
	void operator++()	// Prefix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_next;
	}
	void operator++(int) // Postfix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_next;
	}
	// Decremental Operator (--) Prefix and Postfix
	void operator--()	// Prefix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_previous;
	}
	void operator--(int)	// Postfix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_previous;
	}
	// Comparison Operator (!= & ==) <-- Check whether the node we are pointing too is equal to a node we pass in
	bool operator!=(LinkNode<T>* node)
	{
		return (m_node != node);
	}
	bool operator==(LinkNode<T>* node)
	{
		return (m_node == node);
	}
	bool isValid()
	{
		return (m_node != NULL);
	}
	
	//returns the node that the iterator is using 
	LinkNode<T>* getNode() 
	{
		return m_node;
	}

private:
	LinkNode<T>* m_node;	// Pointer to a node in the linked list
};

// Define a linked list itself
template <class T>
class LinkedList
{
public:
	// Constructor and Destructor
	LinkedList() : m_size(0), m_root(nullptr), m_lastNode(nullptr) {}
	~LinkedList()
	{
		while (m_root)
		{
			Pop_Back();
		}
	}
	// --------------- POSITIONING FUNCTIONS ----------------------
	LinkNode<T>* Begin()
	{
		assert(m_root != nullptr);
		return m_root;
	}
	LinkNode<T>* End()
	{
		return nullptr;
	}
	LinkNode<T>* Last()
	{
		assert(m_lastNode != nullptr);
		return m_lastNode;
	}
	// --------------- PRIORITY QUEUE FUNCTIONS --------------------
	void Insert_Before(LinkIterator<T>& it, T newData, int priority)
	{
		assert(it.m_node != nullptr);

		LinkNode<T>* node = new LinkNode<T>;
		assert(node != nullptr);

		node->m_data = newData;
		node->m_priority = priority;
		node->m_next = it.m_node;
		node->m_previous = it.m_node->m_previous;

		if (node->m_previous != nullptr)
		{
			// Point the previous node to the new node
			node->m_previous->m_next = node;
		}

		it.m_node->m_previous = node;

		// Check to see if the iterator was pointing to the root
		if (it.m_node == m_root)
		{
			m_root = node;
		}

		m_size++;
	}

	void Insert_After(LinkIterator<T>& it, T newData, int priority)
	{
		assert(it.m_node != nullptr);

		LinkNode<T>* node = new LinkNode<T>;
		assert(node != nullptr);

		node->m_data = newData;
		node->m_priority = priority;
		node->m_next = it.m_node->m_next;
		node->m_previous = it.m_node;

		if (node->m_next != nullptr)
		{
			node->m_next->m_previous = node;
		}

		it.m_node->m_next = node;

		// Check if the new node is the last node in the list.
		if (it.m_node == m_lastNode)
		{
			m_lastNode = node;	// Set m_lastNode to be the new node 
		}

		m_size++;
	}

	// --------------- LINKED LIST OPERATIONS ---------------------
	void Push_Front(T newData, int priority)
	{
		// Create a new node (new root node)
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != nullptr);
		node->m_data = newData;
		node->m_priority = priority;
		node->m_next = nullptr;
		node->m_previous = nullptr;

		if (m_root != nullptr) // Linked List has at least 1 item
		{
			node->m_next = m_root;
			m_root->m_previous = node;
			m_root = node;
		}
		else // Linked list is empty
		{
			m_root = node;
			m_lastNode = node;
		}

		m_size++;
	}
	void Pop_Front()
	{
		assert(m_root != nullptr);

		// Create a temp that will allow us to delete the content as needed
		LinkNode<T>* temp = m_root;

		// Reroute pointers
		m_root = m_root->m_next;

		if (m_root != nullptr)
		{
			m_root->m_previous = nullptr;
		}
		else
		{
			m_lastNode = nullptr;
		}

		delete temp;
		temp = nullptr;

		m_size = (m_size == 0 ? m_size : m_size - 1);
	}
	void Push_Back(T newData, int priority)
	{
		// Create a standalone LinkNode object
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != nullptr);
		node->m_data = newData;
		node->m_priority = priority;
		node->m_next = nullptr;
		node->m_previous = nullptr;

		// Add the new LinkNode to the existing LinkedList
		if (m_lastNode != nullptr) // LinkedList is populated. Push to the end of the list.
		{
			m_lastNode->m_next = node;
			node->m_previous = m_lastNode;
		}
		else // An empty linked list
		{
			m_root = node;
		}

		m_lastNode = node;

		m_size++;
	}
	void Pop_Back()
	{
		assert(m_root != nullptr);

		// Check if there is only 1 node (aka just a root)
		if (m_root->m_next == nullptr)
		{
			delete m_root;
			m_root = nullptr;
			m_lastNode = nullptr;
		}
		else // Linked list has 2 or more items
		{
			LinkNode<T>* prevNode = m_lastNode->m_previous;

			// The previous while loop simply positioned the pointer to the 2nd last node in the list. We don't need traversal here.
			prevNode->m_next = nullptr;
			delete m_lastNode;
			m_lastNode = prevNode;
			prevNode = nullptr;
		}

		m_size = (m_size == 0 ? m_size : m_size - 1);	// Prevent negative sizes
	}

	int GetSize()
	{
		return m_size;
	}

private:
	int m_size;					// Holds the size of the linked list
	LinkNode<T>* m_root;		// Point to the root of the linked list
	LinkNode<T>* m_lastNode;	// Point to the last node of the linked list
};
