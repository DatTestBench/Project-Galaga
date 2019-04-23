#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include <iostream>
#include "utils.h"
#include "Bullet.h"
#include <string>
#include"Game.h"
#include "InputHandling.h"
#include "Weapon.h"

Player::Player(int health, const Point2f& pos, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture }
	, m_Health{ health }
	, m_MaxSpeed{ 1000 }
	, m_Acceleration{ 10000 }
	, m_Friction{ 10 }
{	
}

Player::~Player()
{
	/*if (m_pTexture != nullptr)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}*/

	for (Weapon* pWeapon : m_pWeapons)
		delete pWeapon;
}

void Player::Draw() const
{
	// Open Transform
	glPushMatrix();

	// Transforms
	glTranslatef(m_Pos.x, m_Pos.y, 0.f);
	glRotatef(utils::ToDeg(atan2(m_MoveV.y, m_MoveV.x) - utils::g_Pi / 2.f), 0.f, 0.f, 1.f);

	// Drawcode needing transform
	m_pTexture->DrawC(Point2f{}, m_Width, m_Height); //Player Draw

	/*for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Draw();*/

	// Close Transform
	glPopMatrix();

	//Debug Player Draws
	utils::DrawPolygon(GetCollider());
	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Draw();
}

void Player::Update(float dT)
{
	//m_Pos = InputHandling::Get()->MousePos();


	//switch (InputHandling::Get()->MouseState())
	//{
	//case SDL_BUTTON_LEFT:
	//	//std::cout << "Yeeted that left click" << std::endl;
	//	GameObjectManager::Get()->Add(new Bullet{ this, m_Pos, GetAngle() });
	//	break;
	//}
	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Update(dT);

	HandleMovement(dT);

}

bool Player::IsShooting()
{
	return m_IsShooting;
}

void Player::ToggleIsShooting()
{
	m_IsShooting = !m_IsShooting;

	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->ToggleIsShooting();
}

void Player::AddWeapon()
{
	Weapon* pWeapon = new Weapon { 10, 10, Slot(m_pWeapons.size() + 1) };
	m_pWeapons.push_back(pWeapon);
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

	//std::cout << m_MoveV.x << ' ' << m_MoveV.y << std::endl;

	m_Pos += m_MoveV * dT;
}