#include "pch.h"
#include "Enemy.h"
#include "Vector2f.h"
#include "utils.h" 
#include "Player.h"
#include "SAT.h"
Enemy::Enemy(const Point2f& pos, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture }
	, m_pPlayer{ GameObjectManager::Get()->GetPlayer() }

{
}

void Enemy::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 0.f);
	glRotatef(atan2(m_MoveV.y, m_MoveV.x) * (180 / utils::g_Pi) + 90, 0.f, 0.f, 1.f);
	m_pTexture->DrawC(Point2f{}, m_Width, m_Height);
	glPopMatrix();
	utils::DrawPolygon(GetCollider());
}

void Enemy::Update(float dT)
{
	float maxspeed{ 100 };
	m_MoveV = Vector2f{ m_Pos, m_pPlayer->GetPos() }.Normalized();
	m_Pos += m_MoveV * maxspeed * dT;
	HandleCollision();
}

void Enemy::HandleCollision()
{
	PolygonCollisionResult result;


	for (GameObject* pGameObject : *GameObjectManager::Get()->GetGameObjects())
	{
		//if (typeid (*pGameObject) == typeid(Enemy) && pGameObject != this)
		if (pGameObject != this)
		{
			result = sat::PolygonCollision(this, pGameObject);
			if (result.Intersect)
			{
				std::cout << "hit";
				m_Pos += result.MinimumTranslationVector;
				std::cout << result.MinimumTranslationVector;
			}
		}

	}




	//utils::HitInfo hitInfo;
	//utils::HitInfo hitInfoPlayer;
	//utils::HitInfo hitInfoEnemy1;
	//utils::HitInfo hitInfoEnemy2;
	//m_MoveV = Vector2f{ m_Pos, m_pPlayer->GetPos() };

	//// Collision between enemies
	//for (GameObject* pGameObject : *GameObjectManager::Get()->GetGameObjects())
	//{
	//	if (typeid (*pGameObject) == typeid(Enemy))
	//	{
	//		utils::Raycast(pGameObject->GetCollider(), pGameObject->GetPos(), m_Pos, hitInfoEnemy1);
	//		utils::Raycast(GetCollider(), m_Pos, pGameObject->GetPos(), hitInfoEnemy2);

	//		if (utils::Raycast(pGameObject->GetCollider(), m_Pos, pGameObject->GetPos(), hitInfo)
	//			&& utils::DistPointPoint(m_Pos, pGameObject->GetPos())
	//			< utils::DistPointPoint(m_Pos, hitInfoEnemy2.intersectPoint)
	//			+ utils::DistPointPoint(pGameObject->GetPos(), hitInfoEnemy1.intersectPoint))
	//		{
	//			m_Pos.x += hitInfoEnemy1.intersectPoint.x - hitInfoEnemy2.intersectPoint.x;
	//			m_Pos.y += hitInfoEnemy1.intersectPoint.y - hitInfoEnemy2.intersectPoint.y;
	//		}
	//	}
	//}

	//utils::Raycast(m_pPlayer->GetCollider(), m_pPlayer->GetPos(), m_Pos, hitInfoPlayer);
	//utils::Raycast(GetCollider(), m_Pos, m_pPlayer->GetPos(), hitInfoEnemy1);

	//// If the colliders are overlapping, move the enemy outside of the player's collider
	//if (utils::Raycast(m_pPlayer->GetCollider(), m_Pos, m_pPlayer->GetPos(), hitInfo)
	//	&& utils::DistPointPoint(m_Pos, m_pPlayer->GetPos())
	//	< utils::DistPointPoint(m_Pos, hitInfoEnemy1.intersectPoint)
	//	+ utils::DistPointPoint(m_pPlayer->GetPos(), hitInfoPlayer.intersectPoint))
	//{
	//	m_Pos.x += hitInfoPlayer.intersectPoint.x - hitInfoEnemy1.intersectPoint.x;
	//	m_Pos.y += hitInfoPlayer.intersectPoint.y - hitInfoEnemy1.intersectPoint.y;
	//}

	//// Check if the enemy has a line of sight on the player, and move the player accordingly, as long as their colliders aren't overlapping
	//if (utils::Raycast(m_pPlayer->GetCollider(), m_Pos, m_pPlayer->GetPos(), hitInfo)
	//	&& utils::DistPointPoint(m_Pos, m_pPlayer->GetPos())
	//	> utils::DistPointPoint(m_Pos, hitInfoEnemy1.intersectPoint)
	//	+ utils::DistPointPoint(m_pPlayer->GetPos(), hitInfoPlayer.intersectPoint))
	//{
	//	m_Pos += m_MoveV * dT;
	//	return;
	//}
}