#pragma once
#include <iostream>

template <typename T>
struct Node
{
	explicit Node(T element, Node* pNext = nullptr)
		: element{ element }
		, pNext{ pNext }
	{
	}
	T element;
	Node* pNext;
};

template <typename T>
class LinkedList
{
public:
	LinkedList()
		: m_pFirstNode(nullptr)
		, m_Size(0)
	{
	}
	~LinkedList()
	{
		for (size_t i{}; i < m_Size; i++)
		{
			Node<T>* pNextNode{ m_pFirstNode->pNext };
			delete m_pFirstNode;
			m_pFirstNode = pNextNode;
		}
	}
	LinkedList(const LinkedList& other)
		: m_pFirstNode{ nullptr }
		, m_Size{ 0 }
	{
		for (Node<T>* pNode = other.m_pFirstNode; pNode != nullptr; pNode = pNode->pNext)
			PushBack(pNode->value);
	}
	LinkedList& operator=(const LinkedList& other)
	{
		if (&other != this)
		{
			Wipe();
			m_Size = 0;
			m_pFirstNode = nullptr;
			for (Node<T>* pNode = other.m_pFirstNode; pNode != nullptr; pNode = pNode->pNext)
				PushBack(pNode->element);

			//*this = LinkedList(other);
		}
		return *this;
	}
	LinkedList(LinkedList&& other) noexcept
		: m_pFirstNode{ other.m_pFirstNode }
		, m_Size{ other.m_Size }
	{
		other.m_pFirstNode = nullptr;
		other.m_Size = 0;
	}
	LinkedList& operator=(LinkedList&& other) noexcept
	{
		if (&other != this)
		{
			Wipe();
			m_pFirstNode = other.m_pFirstNode;
			m_Size = other.m_Size;
			other.m_pFirstNode = nullptr;
			other.m_Size = 0;
		}
		return *this;
	}

	// Wrap the value in a new Node object and add it as first Node of the list
	void PushFront(T element)
	{
		Node<T>* pNewNode{ new Node<T>(element, m_pFirstNode) };
		m_pFirstNode = pNewNode;
		++m_Size;
	}

	void PopFront()
	{
		if (m_Size == 0)
			return;

		Node<T>* pTempNode{ m_pFirstNode };
		m_pFirstNode = m_pFirstNode->pNext;
		delete pTempNode;

		m_Size--;
	}

	// Remove all Nodes having this value
	void Remove(T element)
	{
		if (m_pFirstNode == nullptr)
			return;

		while (m_pFirstNode->element == element)
			PopFront();

		if (m_pFirstNode->pNext == nullptr)
			return;

		Node<T>* pCurrentNode{ m_pFirstNode->pNext };
		Node<T>* pPreviousNode{ m_pFirstNode };
		for (size_t i{}; i < m_Size; i++)
		{
			if (pCurrentNode->element == element)
			{
				pPreviousNode->pNext = pCurrentNode->pNext;
				delete pCurrentNode;
				m_Size--;
				pCurrentNode = pPreviousNode->pNext;
			}


			if (pCurrentNode == nullptr)
				return;

			pCurrentNode = pCurrentNode->pNext;
			pPreviousNode = pPreviousNode->pNext;
		}
	}

	// Create Node and insert after specified Node 
	void InsertAfter(Node<T>* pBefore, T element)
	{
		Node<T>* pNewNode{ new Node<T>(element, pBefore->pNext) };
		pBefore->pNext = pNewNode;
		m_Size++;
	}

	void PushBack(T element)
	{
		if (m_Size == 0)
			PushFront(element);
		else
		{
			Node<T>* pNode = m_pFirstNode;
			for (; pNode->pNext != nullptr; pNode = pNode->pNext)
			{
			}

			pNode->pNext = new Node<T>(element);
			m_Size++;
		}
	}

	void PopBack()
	{
		if (m_Size == 0)
			return;

		Node<T>* pNode = m_pFirstNode;
		for (; pNode->pNext->pNext != nullptr; pNode = pNode->pNext)
		{
		}
		delete pNode->pNext;
		pNode->pNext = nullptr;
		m_Size--;
	}

	// Return number of Node objects in the list
	size_t Size() const
	{
		return m_Size;
	}

	// Return pointer to first Node
	Node<T>* Begin() const
	{
		return m_pFirstNode;
	}

private:
	Node<T>* m_pFirstNode;
	size_t m_Size;

	// Your helper functions

	void Wipe()
	{
		if (m_Size == 0)
			return;

		Node<T>* pNode = m_pFirstNode;
		while (pNode->pNext != nullptr)
		{
			if (m_Size == 0)
				return;

			Node<T>* pTempNode{ pNode };
			pNode = pNode->pNext;
			delete pTempNode;

			m_Size--;
		}
		delete pNode;
	}
};

template <typename T>
// Send the values of the list to the out object, use a space as element separator
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
{
	Node<T>* pNode = list.Begin();
	while (pNode != nullptr)
	{
		out << pNode->element << " ";
		pNode = pNode->pNext;
	}
	return out;
}
