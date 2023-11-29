#pragma once
#include <cassert>

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
private:
	T m_data;
	int m_priority;
	LinkNode* m_next;	// Self-referencial Pointer
	LinkNode* m_previous;
};

template<class T> class LinkIterator 
{
	// New Addition
	friend class LinkedList<T>;

	LinkIterator();
	~LinkIterator() {}

	void operator=(LinkNode<T>* node);

	T& operator*();

	void operator++();

	void operator++(int);

	void operator--();

	void operator--(int);

	bool operator!=(LinkNode<T>* node);

	bool operator==(LinkNode<T>* node);

	bool isValid();
private:
	LinkNode<T>* m_node;	// Pointer to a node in the linked list
};

template<class T> class LinkedList 
{
public:

	LinkedList();

	~LinkedList();
	

private:
	int m_size;					// Holds the size of the linked list
	LinkNode<T>* m_root;		// Point to the root of the linked list
	LinkNode<T>* m_lastNode;	// Point to the last node of the linked list
};