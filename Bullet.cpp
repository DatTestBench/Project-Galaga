#include "pch.h"
#include "Bullet.h"
#include "utils.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SAT.h"

Bullet::Bullet(GameObject* pSender, const Vector2f& pos, float launchAngle, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture }
	, m_Owner{ pSender }
	, m_MaxSpeed{ 1000 }

{
	m_Velocity = Vector2f(m_MaxSpeed * cos(launchAngle), m_MaxSpeed *sin(launchAngle));
}

void Bullet::Update(float dT)
{

	HandleCollision(dT);

	m_Pos += m_Velocity * dT;
}

void Bullet::Draw() const
{
	utils::DrawPolygon(GetCollider());
}

void Bullet::HandleCollision(float dT)
{
	PolygonCollisionResult result;
	for (GameObject* pGameObject : *m_pGameObjectMananger->GetGameObjects())
	{
		if (typeid (*pGameObject) == typeid(Enemy))
		{
			result = sat::PolygonCollision(this, pGameObject);

			if (result.Intersect)
			{
				pGameObject->Delete();
				Delete();
				return;
			}
		}
	}

	if (m_Pos.x > 2000 || m_Pos.x < 0 || m_Pos.y > 2000 || m_Pos.x < 0)
	{
		Delete();
		return;
	}


}