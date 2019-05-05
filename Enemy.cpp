#include "pch.h"
#include "Enemy.h"
#include "Vector2f.h"
#include "utils.h" 
#include "Player.h"
#include "SAT.h"
#include "Matrix2x3.h"
Enemy::Enemy(const Vector2f& pos, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture }
	, m_pPlayer{ m_pGameObjectManager->GetPlayer() }
	, m_MaxSpeed{ 100 }
	, m_Acceleration{  }
	, m_Friction{  }

{
	
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

void Enemy::HandleCollision(float dT)
{
	PolygonCollisionResult result;

	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		//if (typeid (*pGameObject) == typeid(Enemy) && pGameObject != this)
		if (pGameObject != this)
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