#pragma once
#include <iostream>

// TODO
// so this will require some work
// + add iterators
// + copy-swap idiom for assignment operator
// + unfuck it in general

template <typename T>
struct Node
{
	explicit Node(T element, Node<T>* pNext = nullptr)
		: data(element)
		, pNext(pNext)
	{
	}
	T data;
	Node* pNext;
};

template <typename T>
class LinkedList
{
public:
	using NodeType = Node<T>;
	
	LinkedList()
		: m_pHead(nullptr)
		, m_Size(0)
	{
	}
	~LinkedList()
	{
		// TODO: with iterators, do while node != last
		for (size_t i = 0; i < m_Size; i++)
		{
			NodeType* pNextNode(m_pHead->pNext);
			delete m_pHead;
			m_pHead = pNextNode;
		}
	}
	LinkedList(const LinkedList& other)
		: m_pHead(nullptr)
		, m_Size(0)
	{
		NodeType* pTemp = other.m_pHead;
		NodeType* pCurrentNode = nullptr;

		if (pTemp != nullptr)
		{
			m_pHead = new NodeType(pTemp->data);
			pCurrentNode = m_pHead;

			pTemp = pTemp->pNext;
		}

		while (pTemp != nullptr)
		{
			auto pNewNode = new NodeType(pTemp->data);
			pCurrentNode->pNext = pNewNode;
			pTemp = pTemp->pNext;
		}
	}
	LinkedList& operator=(const LinkedList& other)
	{
		std::swap(other.m_pHead, m_pHead);
		return *this;
	}
	LinkedList(LinkedList&& other) noexcept
		: m_pHead{ other.m_pHead }
		, m_Size{ other.m_Size }
	{
		other.m_pHead = nullptr;
		other.m_Size = 0;
	}
	LinkedList& operator=(LinkedList&& other) noexcept
	{
		if (&other != this)
		{
			Wipe();
			m_pHead = other.m_pHead;
			m_Size = other.m_Size;
			other.m_pHead = nullptr;
			other.m_Size = 0;
		}
		return *this;
	}

	// Wrap the value in a new Node object and add it as first Node of the list
	void PushFront(T element)
	{
		auto pNewNode = new NodeType(element, m_pHead);
		m_pHead = pNewNode;
		++m_Size;
	}

	void PopFront()
	{
		if (m_Size == 0)
			return;

		NodeType* pTempNode = m_pHead;
		m_pHead = m_pHead->pNext;
		delete pTempNode;

		--m_Size;
	}

	// Remove all Nodes having this value
	void Remove(T element)
	{
		if (m_pHead == nullptr)
			return;

		while (m_pHead->data == element)
			PopFront();

		if (m_pHead->pNext == nullptr)
			return;

		NodeType* pCurrentNode = m_pHead->pNext;
		NodeType* pPreviousNode = m_pHead;
		for (size_t i = 0; i < m_Size; i++)
		{
			if (pCurrentNode->data == element)
			{
				pPreviousNode->pNext = pCurrentNode->pNext;
				delete pCurrentNode;
				--m_Size;
				pCurrentNode = pPreviousNode->pNext;
			}


			if (pCurrentNode == nullptr)
				return;

			pCurrentNode = pCurrentNode->pNext;
			pPreviousNode = pPreviousNode->pNext;
		}
	}

	// Create Node and insert after specified Node 
	void InsertAfter(NodeType* pBefore, T element)
	{
		auto pNewNode = new NodeType(element, pBefore->pNext);
		pBefore->pNext = pNewNode;
		++m_Size;
	}

	void PushBack(T element)
	{
		if (m_Size == 0)
			PushFront(element);
		else
		{
			NodeType* pNode = m_pHead;
			// TODO: change this to use iterators, so just lastNode->next = new node 
			for (; pNode->pNext != nullptr; pNode = pNode->pNext)
			{
			}

			pNode->pNext = new NodeType(element);
			++m_Size;
		}
	}

	void PopBack()
	{
		if (m_Size == 0)
			return;

		NodeType* pNode = m_pHead;
		// TODO: change this to use iterators, so just lastNode->next = new node 
		for (; pNode->pNext->pNext != nullptr; pNode = pNode->pNext)
		{
		}
		delete pNode->pNext;
		pNode->pNext = nullptr;
		--m_Size;
	}

	[[nodiscard]] constexpr auto Size() const noexcept -> size_t { return m_Size; }
	[[nodiscard]] constexpr auto Begin() const noexcept -> NodeType* { return m_pHead; }

private:
	NodeType* m_pHead;
	size_t m_Size;

	void Wipe()
	{
		if (m_Size == 0)
			return;

		NodeType* pCurrent = m_pHead;
		while (pCurrent->pNext != nullptr)
		{
			if (m_Size == 0)
				return;

			NodeType* pTempNode = pCurrent;
			pCurrent = pCurrent->pNext;
			delete pTempNode;

			--m_Size;
		}
		delete pCurrent;
	}
};

template <typename T>
// Send the values of the list to the out object, use a space as element separator
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
{
	Node<T>* pNode = list.Begin();
	while (pNode != nullptr)
	{
		out << pNode->data << " ";
		pNode = pNode->pNext;
	}
	return out;
}
