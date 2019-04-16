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
	: GameObject{ pos, width, height, pTexture }
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
	//m_Pos = InputHandling::Get()->MousePos();
	float maxSpeed{ 1000 };
	float accleration{ 10000 };
	float friction{ 0.9 };

	switch (InputHandling::Get()->MouseState())
	{
	case SDL_BUTTON_LEFT:
		//std::cout << "Yeeted that left click" << std::endl;
		GameObjectManager::Get()->Add(new Bullet{ "player", m_Pos });
		break;
	}

	const Uint8* state = InputHandling::Get()->KeyState();
	
	if (state[SDL_SCANCODE_W])
		m_MoveV.y += accleration * dT;
	if (state[SDL_SCANCODE_S])
		m_MoveV.y -= accleration * dT;
	if (state[SDL_SCANCODE_D])
		m_MoveV.x += accleration * dT;
	if (state[SDL_SCANCODE_A])
		m_MoveV.x -= accleration * dT;

	m_MoveV.x *= friction;
	m_MoveV.y *= friction;

	if (m_MoveV.x > maxSpeed)
		m_MoveV.x = maxSpeed;
	if (m_MoveV.x < -maxSpeed)
		m_MoveV.x = -maxSpeed;
	if (m_MoveV.y > maxSpeed)
		m_MoveV.y = maxSpeed;
	if (m_MoveV.y < -maxSpeed)
		m_MoveV.y = -maxSpeed;

	std::cout << m_MoveV.x << ' ' << m_MoveV.y << std::endl;

	m_Pos += m_MoveV * dT;
}