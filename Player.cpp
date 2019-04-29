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

Player::Player(int health, const Vector2f& pos, float width, float height, Texture* pTexture)
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
	glRotatef(utils::ToDeg(GetAngle() - utils::g_Pi / 2.f), 0.f, 0.f, 1.f);

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
	std::cout << m_MoveV << ' ' << GetAngle() << ' ' << atan2(m_MoveV.y, m_MoveV.x) << std::endl;
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
	{
		if (m_Angle > 3.f * utils::g_Pi / 2.f)
			m_Angle = utils::lerp(m_Angle, 5.f * utils::g_Pi / 2.f, dT, 10);
		else
			m_Angle = utils::lerp(m_Angle, utils::g_Pi / 2.f, dT, 10);

		m_Speed += m_Acceleration * dT;
	}
	if (state[SDL_SCANCODE_S])
	{
		if (m_Angle < utils::g_Pi / 2.f)
			m_Angle = utils::lerp(m_Angle, -utils::g_Pi / 2.f, dT, 10);
		else
			m_Angle = utils::lerp(m_Angle, 3.f * utils::g_Pi / 2.f, dT, 10);

		m_Speed += m_Acceleration * dT;
	}
	if (state[SDL_SCANCODE_D])
	{
		if (m_Angle < utils::g_Pi) 
			m_Angle = utils::lerp(m_Angle, 0.f, dT, 10);
		else
			m_Angle = utils::lerp(m_Angle, 2 * utils::g_Pi, dT, 10);
		m_Speed += m_Acceleration * dT;
	}
	if (state[SDL_SCANCODE_A])
	{
		m_Angle = utils::lerp(m_Angle, utils::g_Pi, dT, 10);

		m_Speed += m_Acceleration * dT;
	}

	m_Angle = m_Angle < 0 ? m_Angle + 2*utils::g_Pi : m_Angle;
	m_Angle = m_Angle > 2 * utils::g_Pi ? m_Angle - 2*utils::g_Pi : m_Angle;
	
	if (!(m_Speed < DBL_EPSILON))
	{
		m_Speed = utils::lerp(m_Speed, 0.f, dT, m_Friction);
	}

	if (m_Speed > m_MaxSpeed)
		m_Speed = m_MaxSpeed;

	//std::cout << m_MoveV.x << ' ' << m_MoveV.y << std::endl;

	m_Pos += Vector2f (m_Speed * cos(m_Angle), m_Speed * sin (m_Angle)) *dT;
}