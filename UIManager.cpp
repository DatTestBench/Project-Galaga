#include "pch.h"
#include "UIManager.h"
#include "utils.h"

UIManager* UIManager::m_pUIManager = nullptr;

UIManager::UIManager()
	:m_UIElements{}
{
	
}


UIManager::~UIManager()
{
	for (size_t idx{}; idx < Size(); idx++)
	{
		delete m_UIElements[idx];
		m_UIElements[idx] = nullptr;
	}
}

#pragma region SingletonFunctionality
UIManager* UIManager::Get()
{
	if (m_pUIManager == nullptr)
		m_pUIManager = new UIManager();
	return m_pUIManager;
}

void UIManager::Destroy()
{
	delete UIManager::Get();
}
#pragma endregion SingletonFunctionality

#pragma region Workers
void UIManager::Update(float dT)
{
	HandleDeletion();
	HandleAdd();

	for (UIElement *pUIElement : m_UIElements)
	{
		pUIElement->Update(dT);
	}
}

void UIManager::Draw() const
{
	for (UIElement *pUIElement : m_UIElements)
	{
		pUIElement->Draw();
	}
}



#pragma endregion Workers



#pragma region ItemCreationManipulation

void UIManager::Add(UIElement* pUIElement)
{
	m_AddBuffer.Add(pUIElement);
}

void UIManager::Delete(UIElement* pUIElement)
{
	m_DeleteBuffer.Add(pUIElement);
}
#pragma endregion ItemCreationManipulation

void UIManager::Click(bool state)
{
	m_Click = state;
}

#pragma region Workers

size_t UIManager::Size() const
{
	return size_t(m_UIElements.size());
}

#pragma endregion Workers

#pragma region InternalItemManipulation
void UIManager::HandleAdd()
{
	m_UIElements.insert(std::end(m_UIElements), std::begin(m_AddBuffer.buffer), std::end(m_AddBuffer.buffer));
	m_AddBuffer.Reset();
}

void UIManager::HandleDeletion()
{
	std::sort(m_UIElements.begin(), m_UIElements.end(), [](UIElement* a, UIElement* b)
	{
		return a->GetFlag() < b->GetFlag();
	});
	for (size_t idx{}; idx < m_DeleteBuffer.buffer.size(); idx++)
	{
		delete m_UIElements.back();
		m_UIElements.back() = nullptr;
		m_UIElements.pop_back();
	}
	m_DeleteBuffer.Reset();
}

#pragma endregion InternalItemManipulation