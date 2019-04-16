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
	, m_MaxSpeed{ 1000 }
	, m_Acceleration{ 10000 }
	, m_Friction{ 10 }
{

}

void Player::Draw() const
{
	glPushMatrix();
	glTranslatef( m_Pos.x, m_Pos.y, 0.f );
	glRotatef(atan2(m_MoveV.y, m_MoveV.x) * (180 / utils::g_Pi) - 90, 0.f, 0.f, 1.f);
	m_pTexture->DrawC(Point2f{}, m_Width, m_Height);
	glPopMatrix();
	utils::DrawPolygon(GetCollider());
}

void Player::Update(float dT)
{
	//m_Pos = InputHandling::Get()->MousePos();


	switch (InputHandling::Get()->MouseState())
	{
	case SDL_BUTTON_LEFT:
		//std::cout << "Yeeted that left click" << std::endl;
		GameObjectManager::Get()->Add(new Bullet{ "player", m_Pos });
		break;
	}

	HandleMovement(dT);
}


void Player::HandleMovement(float dT)
{
	const Uint8* state = InputHandling::Get()->KeyState();

	if (state[SDL_SCANCODE_W])
		m_MoveV.y += m_Acceleration * dT;
	if (state[SDL_SCANCODE_S])
		m_MoveV.y -= m_Acceleration * dT;
	if (state[SDL_SCANCODE_D])
		m_MoveV.x += m_Acceleration * dT;
	if (state[SDL_SCANCODE_A])
		m_MoveV.x -= m_Acceleration * dT;

	//if ((abs(m_MoveV.x) > DBL_EPSILON && abs(m_MoveV.y) > DBL_EPSILON) && (abs(m_MoveV.x) < DBL_EPSILON*2 && abs(m_MoveV.y) < DBL_EPSILON*2))
	if (!(m_MoveV.Length() < DBL_EPSILON))
	{
		m_MoveV = utils::lerp(m_MoveV, Vector2f{}, dT, m_Friction);
	}

	if (m_MoveV.x > m_MaxSpeed)
		m_MoveV.x = m_MaxSpeed;
	if (m_MoveV.x < -m_MaxSpeed)
		m_MoveV.x = -m_MaxSpeed;
	if (m_MoveV.y > m_MaxSpeed)
		m_MoveV.y = m_MaxSpeed;
	if (m_MoveV.y < -m_MaxSpeed)
		m_MoveV.y = -m_MaxSpeed;

	std::cout << m_MoveV.x << ' ' << m_MoveV.y << std::endl;

	m_Pos += m_MoveV * dT;
}