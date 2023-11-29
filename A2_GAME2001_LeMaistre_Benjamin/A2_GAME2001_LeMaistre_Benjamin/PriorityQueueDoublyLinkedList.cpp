#include "PriorityQueueDoublyLinkedList.h"


LinkIterator<class T>::LinkIterator()
{
	m_node = nullptr;
}
// ----------- OVERLOADED OPERATORS ------------------
	// Assignmnet operator (=) <-- Set the iterator to point to a node  // a = b
void LinkIterator <class T>::operator=(LinkNode<T>* node)
{
	m_node = node;
}
// Dereferencing operator (*) <-- Read the data stored on the node being pointed too // itr*
T& LinkIterator <class T>::operator*()
{
	assert(m_node != nullptr);
	return m_node->m_data;
}
// Incremental operator (++) Prefix and Postfox <-- Move the iterator to the next node
void LinkIterator <class T>::operator++() 
{
	assert(m_node != nullptr);
	m_node = m_node->m_next;
}

void LinkIterator <class T>::operator++(int) // Postfix
{
	assert(m_node != nullptr);
	m_node = m_node->m_next;
}
// Decremental Operator (--) Prefix and Postfix
void LinkIterator <class T>::operator--()	// Prefix
{
	assert(m_node != nullptr);
	m_node = m_node->m_previous;
}
void LinkIterator <class T>::operator--(int)	// Postfix
{
	assert(m_node != nullptr);
	m_node = m_node->m_previous;
}
// Comparison Operator (!= & ==) <-- Check whether the node we are pointing too is equal to a node we pass in
bool LinkIterator <class T>::operator!=(LinkNode<T>* node)
{
	return (m_node != node);
}
bool LinkIterator <class T>::operator==(LinkNode<T>* node)
{
	return (m_node == node);
}
bool LinkIterator <class T>::isValid()
{
	return (m_node != NULL);
}

