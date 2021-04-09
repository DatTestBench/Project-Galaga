#include "pch.h"
#include "UIManager.h"
#include "utils.h"
#include "Game.h"
UIManager* UIManager::m_pUIManager = nullptr;

UIManager::UIManager()
	: m_UIElements{}
{
	
}


UIManager::~UIManager()
{
	for (size_t idx{}; idx < Size(); idx++)
	{
		delete m_UIElements[idx];
		m_UIElements[idx] = nullptr;
	}
	delete m_pHud;
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

	if (*m_pGameState == GameState::menu)
	{
		m_pStartScreen->DrawC(Point2f{ m_WindowSize.x / 2.f, m_WindowSize.y / 2.f }, m_WindowSize.x, m_WindowSize.y);
	}

	if (*m_pGameState == GameState::playing)
	{
		m_pHud->Draw();
		Scoreboard::Get()->Draw();
	}

	if (*m_pGameState == GameState::paused)
	{
		m_pPauseScreen->DrawC(Point2f{ m_WindowSize.x / 2.f, m_WindowSize.y / 2.f }, m_WindowSize.x, m_WindowSize.y);
	}

	if (*m_pGameState == GameState::death)
	{
		m_pEndScreen->DrawC(Point2f{ m_WindowSize.x / 2.f, m_WindowSize.y / 2.f }, m_WindowSize.x, m_WindowSize.y);
		
	}

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

#pragma region Getters

size_t UIManager::Size() const
{
	return size_t(m_UIElements.size());
}

Vector2f UIManager::GetWindowSize() const
{
	return m_WindowSize;
}

GameState* UIManager::GetGameState() const
{
	return m_pGameState;
}

bool UIManager::GetClick() const
{
	return m_Click;
}
#pragma endregion Getters

#pragma region Setters
void UIManager::SetGameState(GameState* pGameState)
{
	m_pGameState = pGameState;
}
void UIManager::SetWindowSize(const Vector2f& window)
{
	m_WindowSize = window;
}

void UIManager::LoadManager(const Vector2f& window)
{
	m_WindowSize = window;
	m_pHud = new HUD(window.x, window.y);
	m_pHud->SetLock(GameObjectManager::Get()->GetPlayer());
	m_pStartScreen = ResourceManager::Get()->GetTexturep("TextStartScreen");
	m_pEndScreen = ResourceManager::Get()->GetTexturep("TextEndScreen");
	m_pPauseScreen = ResourceManager::Get()->GetTexturep("TextPauseScreen");
}

void UIManager::SetClick(bool isClick)
{
	m_Click = isClick;
}
#pragma endregion Setters

#pragma region Changers
void UIManager::ChangeGameState(const GameState& GameState)
{
	*m_pGameState = GameState;
}
#pragma endregion Changers


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