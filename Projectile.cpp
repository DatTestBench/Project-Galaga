#include "pch.h"
#include "Projectile.h"
#include "utils.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SAT.h"

Projectile::Projectile(GameObject* pSender, const Vector2f& pos, float launchAngle, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture }
	, m_pSender{ pSender }
	, m_MaxSpeed{ 1000 }

{
	m_Velocity = Vector2f(m_MaxSpeed * cos(launchAngle), m_MaxSpeed *sin(launchAngle));
}

void Projectile::Update(float dT)
{

	HandleCollision(dT);

	m_Pos += m_Velocity * dT;
}

void Projectile::Draw() const
{
	utils::DrawPolygon(GetCollider());
}

void Projectile::HandleCollision(float dT)
{
	PolygonCollisionResult result;
	for (GameObject* pGameObject : *m_pGameObjectMananger->GetGameObjects())
	{
		if (pGameObject != m_pSender && pGameObject != this && typeid(*pGameObject) != typeid (Projectile))
		{
			result = sat::PolygonCollision(this, pGameObject);

			if (result.Intersect)
			{
				//ToDo: Change delete to discrete damage values
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