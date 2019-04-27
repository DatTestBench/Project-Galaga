#include "pch.h"
#include "Bullet.h"
#include "utils.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SAT.h"

Bullet::Bullet(GameObject* senderPointer, const Vector2f& pos, float launchAngle, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture }
	, m_Owner{ senderPointer }
	, m_MaxSpeed{ 1000 }

{
	m_MoveV = Vector2f(m_MaxSpeed * cos(launchAngle), m_MaxSpeed *sin(launchAngle));
}

void Bullet::Update(float dT)
{

	HandleCollision();

	m_Pos += m_MoveV * dT;
}

void Bullet::Draw() const
{
	utils::DrawPolygon(GetCollider());
}

void Bullet::HandleCollision()
{
	PolygonCollisionResult result;
	for (GameObject* pGameObject : *GameObjectManager::Get()->GetGameObjects())
	{
		if (typeid (*pGameObject) == typeid(Enemy))
		{
			result = sat::PolygonCollision(this, pGameObject);

			if (result.Intersect)
			{
				//pGameObject->Delete();
				Delete();
				return;
			}
		}
	}

	if (m_Pos.x > 2000 || m_Pos.x < 0 || m_Pos.y > 2000 || m_Pos.x < 0)
	{
		//Delete();
		return;
	}


}