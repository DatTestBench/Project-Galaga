#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include <iostream>
#include "utils.h"
#include "Projectile.h"
#include <string>
#include"Game.h"
#include "InputHandling.h"
#include "Weapon.h"
#include "SAT.h"
#include "Matrix2x3.h"
#include "Enemy.h"
#include "MachineGun.h"
#include "Shotgun.h"
#include "RocketLauncher.h"

Player::Player(const Vector2f& pos, float width, float height, Texture* pTexture, float baseHealth)
	: GameObject{ pos, width, height, pTexture }
	, m_BaseHealth{ baseHealth }
	, m_BaseSpeed{ 500 }
	, m_Acceleration{ 10000 }
	, m_Friction{ 10 }
{	
	m_CurrentHealth = m_BaseHealth;
}

Player::~Player()
{
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

	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Draw();

	// Close Transform
	glPopMatrix();

	//Debug Draws
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
	//	GameObjectManager::Get()->Add(new Projectile{ this, m_Pos, GetAngle() });
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

void Player::ToggleShoot()
{
	m_IsShooting = !m_IsShooting;

	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->ToggleShoot();
}

void Player::AddWeapon()
{
	if (m_pWeapons.size() < int (Slot::size))
	{
		//Machinegun* pWeapon = new Machinegun { 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) };
		//Shotgun* pWeapon = new Shotgun{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) };
		RocketLauncher* pWeapon = new RocketLauncher{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) };
		m_pWeapons.push_back(pWeapon);
	}
}

void Player::Hit(float damage)
{
	m_CurrentHealth -= damage;
	if (m_CurrentHealth <= 0)
		std::cout << "Dead";
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

	m_Angle = m_Angle < 0 ? m_Angle + 2 * utils::g_Pi : m_Angle;
	m_Angle = m_Angle > 2 * utils::g_Pi ? m_Angle - 2 * utils::g_Pi : m_Angle;
	
	if (!(m_Speed < DBL_EPSILON))
	{
		m_Speed = utils::lerp(m_Speed, 0.f, dT, m_Friction);
	}

	if (m_Speed > m_BaseSpeed)
		m_Speed = m_BaseSpeed;



	HandleCollision(dT);
	m_Pos += (GetVelocity() * dT);
}

void Player::HandleCollision(float dT)
{
	PolygonCollisionResult result;
	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		if (typeid (*pGameObject) == typeid(Enemy))
		{
			result = sat::PolygonCollision(this, pGameObject);
			if (result.Intersect)
			{
				m_Pos += result.MinimumTranslationVector;
			}
		}

	}
}



