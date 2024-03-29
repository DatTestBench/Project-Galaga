#include "GameLogic/UIManager.h"

#include <algorithm>

#include "Helpers/utils.h"
#include "Core/Game.h"

UIManager* UIManager::m_pUIManager = nullptr;

UIManager::UIManager()
	: m_Click(false)
	, m_pGameState(nullptr)
	, m_pEndScreen(nullptr)
	, m_pHud(nullptr)
	, m_pStartScreen(nullptr)
	, m_pPauseScreen(nullptr)
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
	delete Get();
}
#pragma endregion SingletonFunctionality

#pragma region Workers
void UIManager::Update(const float dT)
{
	HandleDeletion();
	HandleAdd();

	for (UIElement* pUIElement : m_UIElements)
		pUIElement->Update(dT);
}

void UIManager::Draw() const
{
	if (*m_pGameState == GameState::menu)
		m_pStartScreen->DrawC(Point2f{ m_WindowSize.x / 2.f, m_WindowSize.y / 2.f }, m_WindowSize.x, m_WindowSize.y);

	if (*m_pGameState == GameState::playing)
	{
		m_pHud->Draw();
		Scoreboard::Get()->Draw();
	}

	if (*m_pGameState == GameState::paused)
		m_pPauseScreen->DrawC(Point2f{ m_WindowSize.x / 2.f, m_WindowSize.y / 2.f }, m_WindowSize.x, m_WindowSize.y);

	if (*m_pGameState == GameState::death)
		m_pEndScreen->DrawC(Point2f{ m_WindowSize.x / 2.f, m_WindowSize.y / 2.f }, m_WindowSize.x, m_WindowSize.y);

	for (const UIElement* pUIElement : m_UIElements)
		pUIElement->Draw();
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

void UIManager::Click(const bool state)
{
	m_Click = state;
}

#pragma region Getters

size_t UIManager::Size() const
{
	return m_UIElements.size();
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
	m_pStartScreen = ResourceManager::Get()->GetTexture("TextStartScreen");
	m_pEndScreen = ResourceManager::Get()->GetTexture("TextEndScreen");
	m_pPauseScreen = ResourceManager::Get()->GetTexture("TextPauseScreen");
}

void UIManager::SetClick(const bool isClick)
{
	m_Click = isClick;
}
#pragma endregion Setters

#pragma region Changers
void UIManager::ChangeGameState(const GameState& GameState) const
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
	std::ranges::sort(m_UIElements, [] (const UIElement* a, const UIElement* b)
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
