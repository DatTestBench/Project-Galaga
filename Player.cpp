#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include <iostream>
#include "utils.h"
#include "Bullet.h"
#include <string>
#include"Game.h"
#include "InputHandling.h"


Player::Player(int health, const Point2f& pos, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture}
	, m_Health{ health }
{

}

void Player::Draw() const
{
	m_pTexture->DrawC(m_Pos, m_Width, m_Height);
	utils::DrawPolygon(GetCollider());
}

void Player::Update(float dT)
{
	m_Pos = InputHandling::Get()->MousePos();
	


	switch (InputHandling::Get()->MouseState())
	{
	case SDL_BUTTON_LEFT:
		//std::cout << "Yeeted that left click" << std::endl;
		GameObjectManager::Get()->Add(new Bullet{ "player", m_Pos });
		break;
	}

	//m_Pos += m_MoveV * dT;
}