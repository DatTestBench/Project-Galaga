#include "GameLogic/UIElement.h"
#include <functional>
#include "Core/Game.h"
#include "Core/InputHandling.h"
#include "GameLogic/UIManager.h"
#include "Helpers/utils.h"
#include "Resources/ResourceManager.h"

UIElement::UIElement(const std::string& tag, const Vector2f& pos, float width, float height, bool hasLogic)
	: m_Tag{ tag }
	, m_Pos{ pos }
	, m_Width { width }
	, m_Height { height }
	, m_pTexture { ResourceManager::Get()->GetTexture("Text" + tag) }
	, m_IsActive{ true }
	, m_pUIManager { UIManager::Get()}
	, m_Window{ UIManager::Get()->GetWindowSize() }
	, m_HasLogic{ hasLogic }
{

	if (m_HasLogic)
	{
		LoadFunctionMap();
		m_Hitbox.push_back(m_Pos + Vector2f{ - m_Width / 2.f,  -m_Height / 2.f });
		m_Hitbox.push_back(m_Pos + Vector2f{ m_Width / 2.f, -m_Height / 2.f });
		m_Hitbox.push_back(m_Pos + Vector2f{ m_Width / 2.f, m_Height / 2.f });
		m_Hitbox.push_back(m_Pos + Vector2f{ - m_Width / 2.f, m_Height / 2.f });
	}
}


void UIElement::Draw() const
{
	if (m_IsActive)
	{
		//utils::SetColor(Color4f{ 0, 0, 1, 1 });
		//utils::DrawPolygon(m_Hitbox);
		m_pTexture->DrawC(m_Pos.ToPoint2f());
	}
}

void UIElement::Update(float /*dT*/)
{
	if (!m_pUIManager->GetClick())
	{
		m_IsClicked = false;
	}
	if (m_IsActive && m_HasLogic)
	{
		HandleInput(InputHandling::Get()->MousePos());
	}
}


#pragma region Workers
void UIElement::HandleInput(const Vector2f& inputPos)
{
	if(utils::IsPointInPolygon(inputPos, m_Hitbox) && SDL_GetMouseState(nullptr, nullptr) == SDL_BUTTON_LEFT && ! m_IsClicked)
	{
		GetActionFunctionp(m_Tag)();
		m_IsClicked = true;
	}
}


#pragma endregion Workers

#pragma region Getters

bool UIElement::GetFlag()
{
	return m_DelFlag;
}

#pragma endregion Getters



#pragma region TypeSpecificActionFunctions

std::function<void()> UIElement::GetActionFunctionp(const std::string& key)
{
	std::map<std::string, std::function<void()>>::const_iterator cit = m_FunctionMap.find(key);
	if (cit != m_FunctionMap.cend())
	{
		//std::cout << "Function: " << key << " called" << std::endl;
		return cit->second;
	}
	else
	{
		//std::cout << "Function: " << key << " was not found" << std::endl;
		return nullptr;
	}
}
#pragma endregion TypeSpecificActionFunctions

void UIElement::LoadFunctionMap()
{
	m_FunctionMap["BTNPause"] = [this]()
	{
		if (*UIManager::Get()->GetGameState() == GameState::paused)
		{
			UIManager::Get()->ChangeGameState(GameState::playing);
		}
		else if (*UIManager::Get()->GetGameState() == GameState::playing)
		{
			UIManager::Get()->ChangeGameState(GameState::paused);
		}
		else
		{
			m_IsActive = false;
		}
		ResourceManager::Get()->PlaySoundEffect("SEButton", 0, 50);
	};

	m_FunctionMap["BTNStart"] = [this]()
	{
		std::cout << "Game Started" << std::endl;
		UIManager::Get()->ChangeGameState(GameState::playing);
		UIManager::Get()->Add(new UIElement("BTNPause", Vector2f{ 22 * (m_Window.x / 24), 22 * (m_Window.y / 24) }, 64, 64));
		ResourceManager::Get()->PlaySoundEffect("SEButton", 0, 50);
		m_IsActive = false;

	};
}
