#include "pch.h"
#include "Bullet.h"
#include "utils.h"
#include "GameObjectManager.h"
#include "Enemy.h"

Bullet::Bullet(GameObject* senderPointer, const Point2f& pos, float launchAngle, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture }
	, m_Owner{ senderPointer }
	, m_MaxSpeed{ 1000 }

{
	m_MoveV = Vector2f{ m_MaxSpeed * cos(launchAngle), m_MaxSpeed *sin(launchAngle) };
}

void Bullet::Update(float dT)
{

	for (GameObject* pGameObject : *GameObjectManager::Get()->GetGameObjects())
	{
		//if (static_cast<Bullet*>(pGameObject) == nullptr)
		{
			//if (m_Owner != pGameObject && typeid(*pGameObject) != typeid(Bullet))
			if (typeid (*pGameObject) == typeid(Enemy))
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

	if (m_Pos.x > 2000 || m_Pos.x < 0 || m_Pos.y > 2000 || m_Pos.x < 0)
		Delete();

	m_Pos += m_MoveV * dT;
}

void Bullet::Draw() const
{
	utils::DrawPolygon(GetCollider());
}