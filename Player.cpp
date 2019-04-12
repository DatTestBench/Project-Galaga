#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include <iostream>
#include "utils.h"
#include "Bullet.h"
#include <string>
#include"Game.h"


Player::Player(int health, float winHeight, const Point2f& pos, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture}
	, m_Health{ health }
	, m_WindowHeight{ winHeight }
{

}

void Player::Draw() const
{
	m_pTexture->DrawC(m_Pos, m_Width, m_Height);
	utils::DrawPolygon(GetCollider());
}

void Player::Update(float dT)
{
	int x, y;
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);

	int mouseState = SDL_GetMouseState( &x, &y);
	m_Pos.x = float(x);
	m_Pos.y = float(m_WindowHeight - y);

	switch (mouseState)
	{
	case SDL_BUTTON_LEFT:
		//std::cout << "Yeeted that left click" << std::endl;
		GameObjectManager::Get()->Add(new Bullet{ "player", m_Pos});
		break;
	case SDL_BUTTON_RIGHT:
		std::cout << "Yeeted that Right Click" << std::endl;
		break;
		//sssssss
	}
}