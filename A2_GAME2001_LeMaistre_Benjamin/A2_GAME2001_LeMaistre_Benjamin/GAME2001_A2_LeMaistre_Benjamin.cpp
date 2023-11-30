#include <iostream>
#include "PriorityQueue.h"
using namespace std;




class NetworkMessage
{
public:
	NetworkMessage() : m_id(0) {}
	NetworkMessage(int id) : m_id(id) {}
	~NetworkMessage() {}

	int GetID()
	{
		return m_id;
	}
private:
	int m_id;
};

int main() 
{
	cout << "Priority queue data structure example!" << endl << endl;

	const int SIZE = 10;
	PriorityQueue<NetworkMessage> que(SIZE);

	que.push(NetworkMessage(474), 34);
	que.push(NetworkMessage(478), 15);
	que.push(NetworkMessage(286), 4);
	que.push(NetworkMessage(362), 2);
	que.push(NetworkMessage(76), 1);
	que.push(NetworkMessage(28), 47);
	que.push(NetworkMessage(9), 23);
	que.push(NetworkMessage(437), 17);
	que.push(NetworkMessage(285), 42);
	que.push(NetworkMessage(36), 21);

	// Display the priority queue
	cout << "Priority queue content (Size: " << que.GetSize() << ") : " << endl;

	while (que.isEmpty() == false)
	{
		cout << "  Priority: " << que.frontPriority();
		cout << "  ID: " << que.front().GetID();
		cout << endl;

		que.pop();
	}

	cout << endl;

	if (que.isEmpty() == true)
	{
		cout << "The container is empty." << endl;
	}
	else
	{
		cout << "The container is NOT empty." << endl;
	}

	return 0;
}