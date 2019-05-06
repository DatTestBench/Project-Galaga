#include "pch.h"
#include "Projectile.h"
#include "utils.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SAT.h"
#include "MachineGunBullet.h"
#include "ShotgunPellet.h"
#include "Player.h"

Projectile::Projectile(const Vector2f& pos, float width, float height, Texture* pTexture, float launchAngle, float baseSpeed, GameObject* pSender, int level, float baseDamage)
	: GameObject{ pos, width, height, pTexture }
	, m_pSender{ pSender }
	, m_BaseSpeed{ baseSpeed }
	, m_Level { level }
	, m_BaseDamage { baseDamage }

{
	m_Velocity = Vector2f(m_BaseSpeed * cos(launchAngle), m_BaseSpeed * sin(launchAngle));
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
	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		if (pGameObject != m_pSender && pGameObject != this && typeid(*pGameObject) != typeid (MachinegunBullet) && typeid (*pGameObject) != typeid (ShotgunPellet))
		{
			result = sat::PolygonCollision(this, pGameObject);

			if (result.Intersect)
			{
				//ToDo: Change delete to discrete damage values
				if (typeid(*pGameObject) == typeid(Player))
					static_cast<Player*>(pGameObject)->Hit(m_BaseDamage);
				else
				{
					static_cast<Enemy*>(pGameObject)->Hit(m_BaseDamage);
				}
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