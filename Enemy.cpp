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
#include "Rocketeer.h"
#include "Gunner.h"
#include "Rusher.h"
Enemy::Enemy(const Vector2f& pos, float width, float height, Sprite* pSprite, int level, float baseHealth)
	: GameObject{ pos, width, height, pSprite }
	, m_pPlayer{ m_pGameObjectManager->GetPlayer() }
	, m_Friction{  }
	, m_BaseHealth{ baseHealth }

{
	
	m_Mass = 10;
	m_CurrentHealth = m_BaseHealth;

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
	//utils::DrawPolygon(GetCollider());
	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Draw();

}


void Enemy::Update(float dT)
{
	

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
	//std::cout << "Enemy hit" << std::endl;
	m_CurrentHealth -= damage;
	if (m_CurrentHealth <= 0)
	{
		Delete();
		m_pScoreboard->AddScore(1);
		//std::cout << "Enemy died" << std::endl;

	}
}

void Enemy::HitLevel(const Vector2f& dMove)
{
	ChangePos(dMove);
}

void Enemy::HandleCollision(float dT)
{
	PolygonCollisionResult result;

	for (GameObject* pGameObject : m_pGameObjectManager->GetEnemies())
	{
		if (pGameObject != this)
		{
			result = sat::PolygonCollision(this, pGameObject);
			if (result.intersect)
			{
				// What happens when hit
				m_Pos += result.minimumTranslationVector;
			}
		}
	}

	result = sat::PolygonCollision(this, m_pGameObjectManager->GetPlayer());
	if (result.intersect)
	{
		m_Pos += result.minimumTranslationVector;
	}
}

void Enemy::HandleLogic(float dT)
{}