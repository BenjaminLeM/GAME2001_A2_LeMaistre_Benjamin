#pragma once

#include "PriorityQueueDoublyLinkedList.h"



template<class T>
class PriorityQueue
{
public:
	PriorityQueue(int size)
	{
		assert(size > 0);
		m_size = size;
	}

	~PriorityQueue() {}

	void push(T val, int priority)
	{
		assert(m_elements.GetSize() < m_size);

		if (m_elements.GetSize() == 0)
		{
			m_elements.Push_Back(val, priority);

		}
		else
		{
			LinkIterator<T> it;
			it = m_elements.Begin();

			while (it.isValid())
			{
				//if new input priority is greater than the selected node then move to next node 
				if (it.getNode()->getPriority() > priority)
				{
					break;
				}
				it++;
			}
			if (it.isValid())
			{
				m_elements.Insert_Before(it, val, priority);
			}
			else
			{
				m_elements.Push_Back(val, priority);
			}
		}
	}

	void pop()
	{
		m_elements.Pop_Front();
	}

	T& front()
	{
		LinkIterator<T> it;
		it = m_elements.Begin();

		return *it;
	}
	
	int frontPriority()
	{
		LinkIterator<T> it;
		it = m_elements.Begin();
		return it.getNode()->getPriority();
	}
	
	T& back()
	{
		LinkIterator<T> it;
		it = m_elements.Last();

		return *it;
	}
	
	int backPriority()
	{
		LinkIterator<T> it;
		it = m_elements.Last();
		return it.getNode()->getPriority();
	}
	// Helper functions
	int GetSize()
	{
		return m_elements.GetSize();
	}

	int GetMaxSize()
	{
		return m_size;
	}

	bool isEmpty()
	{
		return (m_elements.GetSize() == 0);
	}
	
	void Resize(int size)
	{
		assert(size > 0);
		m_size = size;
	}
private:
	LinkedList<T> m_elements; // Priority Queue Linked List
	int m_size;
};