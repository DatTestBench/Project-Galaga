#include "pch.h"
#include "Enemy.h"
#include "Vector2f.h"
#include "utils.h" 
#include "Player.h"
#include "SAT.h"
#include "Matrix2x3.h"
Enemy::Enemy(const Vector2f& pos, float width, float height, Texture* pTexture, int level, float baseHealth)
	: GameObject{ pos, width, height, pTexture }
	, m_pPlayer{ m_pGameObjectManager->GetPlayer() }
	, m_MaxSpeed{ 100 }
	, m_Acceleration{  }
	, m_Friction{  }
	, m_BaseHealth { baseHealth }

{
	m_CurrentHealth = m_BaseHealth;
}

void Enemy::Draw() const
{
	// Open Transform
	glPushMatrix();

	// Transforms
	glTranslatef(m_Pos.x, m_Pos.y, 0.f);
	glRotatef(utils::ToDeg(GetAngle() + utils::g_Pi / 2.f), 0.f, 0.f, 1.f);

	// Drawcode needing transform
	m_pTexture->DrawC(Point2f{}, m_Width, m_Height); //Enemy Draw

	// Close Transform
	glPopMatrix();

	//Debug Draws
	utils::DrawPolygon(GetCollider());
	
}

void Enemy::Update(float dT)
{
	m_Speed = m_MaxSpeed;
	Vector2f eToPVector(m_Pos, m_pPlayer->GetPos());
	m_Angle = atan2(eToPVector.y, eToPVector.x);
	HandleCollision(dT);

	m_Pos += (GetVelocity() * dT);

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

void Enemy::HandleCollision(float dT)
{
	PolygonCollisionResult result;

	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		if ( (typeid (*pGameObject) == typeid(Enemy) || typeid (*pGameObject) == typeid(Player)) && pGameObject != this)
		{
			result = sat::PolygonCollision(this, pGameObject);
			if (result.Intersect)
			{
				// What happens when hit
				m_Pos += result.MinimumTranslationVector;
			} 
		}

	}
}