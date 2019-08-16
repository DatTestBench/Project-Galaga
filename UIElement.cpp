#include "pch.h"
#include "UIElement.h"
#include "utils.h"
#include <functional>
#include "InputHandling.h"
#include "ResourceManager.h"
#include "UIManager.h"
UIElement::UIElement(const std::string& tag, const Vector2f& pos, float width, float height)
	: m_Tag{ tag }
	, m_Pos{ pos }
	, m_Width { width }
	, m_Height { height }
	, m_pTexture { nullptr }
	, m_pUIManager { UIManager::Get()}
{


	LoadFunctionMap();

	m_Hitbox.push_back(m_Pos + Vector2f{ - m_Width / 2.f,  -m_Height / 2.f });
	m_Hitbox.push_back(m_Pos + Vector2f{ m_Width / 2.f, -m_Height / 2.f });
	m_Hitbox.push_back(m_Pos + Vector2f{ m_Width / 2.f, m_Height / 2.f });
	m_Hitbox.push_back(m_Pos + Vector2f{ - m_Width / 2.f, m_Height / 2.f });
}


void UIElement::Draw() const
{
	utils::SetColor(Color4f{ 0, 0, 1, 1 });
	utils::DrawPolygon(m_Hitbox);
}

void UIElement::Update(float dT)
{
	HandleInput(InputHandling::Get()->MousePos());
}


#pragma region Workers
void UIElement::HandleInput(const Vector2f& inputPos)
{
	if(utils::IsPointInPolygon(inputPos, m_Hitbox) && SDL_GetMouseState(nullptr, nullptr) == SDL_BUTTON_LEFT)
	{
		GetActionFunctionp(m_Tag)();
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
	}
}
#pragma endregion TypeSpecificActionFunctions

void UIElement::LoadFunctionMap()
{
	m_FunctionMap["BTNPause"] = []()
	{
		UIManager::Get()->Add( new UIElement ("SCRNMenu", Vector2f{ 960, 540 }, 200, 200));
	};


	m_FunctionMap["SCRNMenu"] = []()
	{
		std::cout << "Screen" << std::endl;
	};
}
