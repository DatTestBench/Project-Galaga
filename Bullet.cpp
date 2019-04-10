#include "pch.h"
#include "Bullet.h"
#include "utils.h"
#include "GameObjectManager.h"
#include "Enemy.h"

Bullet::Bullet(const std::string& ownerTag, const Point2f& pos, float width, float height, Texture* pTexture)
	:GameObject{ pos, width, height, pTexture}

{
	m_MoveV = Vector2f{ 0, 10 };
}

void Bullet::Update(float dT)
{
	
	m_MoveV.y += 1;
	
	m_Pos.x += m_MoveV.ToPoint2f().x;
	m_Pos.y += m_MoveV.ToPoint2f().y;

	utils::HitInfo hitInfo;
	utils::HitInfo hitInfoBullet;
	utils::HitInfo hitInfoGameObject;

	for (GameObject *pGameObject : *GameObjectManager::Get()->GetGameObjects())
	{
		if (typeid (*pGameObject) == typeid (Enemy))
		{
			/*utils::Raycast(GetCollider(), m_Pos, pGameObject->GetPos(), hitInfoBullet);
			utils::Raycast(pGameObject->GetCollider(), pGameObject->GetPos(), m_Pos, hitInfoGameObject);
			std::cout << "hit" <<std::endl;
			if (utils::Raycast(pGameObject->GetCollider(), m_Pos, pGameObject->GetPos(), hitInfo)
				&& utils::DistPointPoint(m_Pos, pGameObject->GetPos())
				< utils::DistPointPoint(m_Pos, hitInfoBullet.intersectPoint)
				+ utils::DistPointPoint(pGameObject->GetPos(), hitInfoGameObject.intersectPoint))
			{
				m_Pos.x += hitInfoGameObject.intersectPoint.x - hitInfoBullet.intersectPoint.x;
				m_Pos.y += hitInfoGameObject.intersectPoint.y - hitInfoBullet.intersectPoint.y;
			}*/

			if (utils::IsPointInPolygon(m_Pos, pGameObject->GetCollider()))
			{
				pGameObject->ChangePos(m_MoveV);
				Delete();
				//m_MoveV.x += pGameObject->GetPos().x - m_Pos.x;
				//m_MoveV.y += pGameObject->GetPos().y - m_Pos.y;
				//std::cout << "hit" << std::endl;

			}

		}
	}
}

void Bullet::Draw() const
{
	utils::DrawPolygon(GetCollider());
}