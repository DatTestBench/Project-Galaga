#include "pch.h"
#include "Enemy.h"
#include "Vector2f.h"
#include "utils.h" 
#include "Player.h"
#include "SAT.h"
#include "Matrix2x3.h"
#include "RocketLauncher.h"
#include "Shotgun.h"
#include "utils.h"
#include "SteeringManager.h"
Enemy::Enemy(const Vector2f& pos, float width, float height, Sprite* pSprite, int level, float baseHealth)
	: GameObject{ pos, width, height, pSprite }
	, m_pPlayer{ m_pGameObjectManager->GetPlayer() }
	, m_Friction{  }
	, m_BaseHealth{ baseHealth }

{
	m_MaxSpeed = 100;
	m_Mass = 10;
	m_CurrentHealth = m_BaseHealth;
	RocketLauncher* pWeapon = new RocketLauncher{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) };
	m_pWeapons.push_back(pWeapon);
}

Enemy::~Enemy()
{
	for (Weapon* pWeapon : m_pWeapons)
		delete pWeapon;
}

void Enemy::Draw() const
{
	// Open Transform
	glPushMatrix();

	// Transforms
	glTranslatef(m_Pos.x, m_Pos.y, 0.f);
	glRotatef(utils::ToDeg(GetAngle() + utils::g_Pi / 2.f), 0.f, 0.f, 1.f);

	// Drawcode needing transform
	m_pSprite->DrawC(Point2f{}, m_Width, m_Height, 1); //Enemy Draw

	/*for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Draw();*/

		// Close Transform
	glPopMatrix();

	//Debug Draws
	utils::DrawPolygon(GetCollider());
	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Draw();

}

#include <vector>
void Enemy::Update(float dT)
{
	Vector2f eToPVector(m_Pos, m_pPlayer->GetPos());
	//m_Angle = atan2(eToPVector.y, eToPVector.x);
	HandleCollision(dT);

	if (!IsShooting())
	{
		if (utils::DistPointPoint(m_pGameObjectManager->GetPlayer()->GetPos(), m_Pos) < 500)
		{
			ToggleShoot();
			std::cout << "Shoot" << std::endl;
		}
	}
	else
	{
		if (utils::DistPointPoint(m_pGameObjectManager->GetPlayer()->GetPos(), m_Pos) > 500)
		{
			ToggleShoot();
			std::cout << "No Shoot" << std::endl;
		}
	}

	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Update(dT);

	/*if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) < 300)
	{
		m_pSteeringManager->Evade(m_pPlayer);
	}
	else
	{
		m_pSteeringManager->Seek(m_pPlayer);
	}*/
	if (utils::DistPointPoint(m_pPlayer->GetPos(), m_Pos) < 100)
	{
		m_pSteeringManager->Pursuit(m_pPlayer);

	}
	else
	{
		m_pSteeringManager->Wander(dT);

	}
	m_pSteeringManager->Update(dT);
	m_pSteeringManager->Reset();

}

bool Enemy::IsShooting()
{
	return m_IsShooting;
}

void Enemy::ToggleShoot()
{
	m_IsShooting = !m_IsShooting;

	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->ToggleShoot();
}

void Enemy::Hit(float damage)
{
	std::cout << "Enemy hit" << std::endl;
	m_CurrentHealth -= damage;
	if (m_CurrentHealth <= 0)
	{
		Delete();
		std::cout << "Enemy died" << std::endl;

	}
}

void Enemy::HitLevel(const Vector2f& dMove)
{
	ChangePos(dMove);
}

void Enemy::HandleCollision(float dT)
{
	PolygonCollisionResult result;

	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		if ((typeid (*pGameObject) == typeid(Enemy) || typeid (*pGameObject) == typeid(Player)) && pGameObject != this)
		{
			result = sat::PolygonCollision(this, pGameObject);
			if (result.intersect)
			{
				// What happens when hit
				m_Pos += result.minimumTranslationVector;
			}
		}

	}
}