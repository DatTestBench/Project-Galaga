#include "pch.h"
#include "Enemy.h"
#include "Vector2f.h"
#include "utils.h" 
#include "Player.h"
Enemy::Enemy(Player* pPlayer, const Point2f& pos, float width, float height, Texture* pTexture)
	: GameObject{ pos, width, height, pTexture }
	, m_pPlayer{ pPlayer }

{
}

void Enemy::Draw() const
{
	m_pTexture->DrawC(m_Pos, m_Width, m_Height);
	utils::DrawPolygon(GetCollider());
}

void Enemy::Update(float dT)
{
	HandleCollision(dT);
}

void Enemy::HandleCollision(float dT)
{
	utils::HitInfo hitInfo;
	utils::HitInfo hitInfoPlayer;
	utils::HitInfo hitInfoEnemy;
	m_MoveV = Vector2f{ m_Pos, m_pPlayer->GetPos() };

	utils::Raycast(m_pPlayer->GetCollider(), m_pPlayer->GetPos(), m_Pos, hitInfoPlayer);
	utils::Raycast(GetCollider(), m_Pos, m_pPlayer->GetPos(), hitInfoEnemy);

	// Check if the enemy has a line of sight on the player, and move the player accordingly, as long as their colliders aren't overlapping
	if (utils::Raycast(m_pPlayer->GetCollider(), m_Pos, m_pPlayer->GetPos(), hitInfo)
		&& utils::DistPointPoint(m_Pos, m_pPlayer->GetPos())
		> utils::DistPointPoint(m_Pos, hitInfoEnemy.intersectPoint)
		+ utils::DistPointPoint(m_pPlayer->GetPos(), hitInfoPlayer.intersectPoint))
	{
		m_Pos += m_MoveV * dT;
		return;
	}

	// If the colliders are overlapping, move the enemy outside of the player's collider
	if (utils::Raycast(m_pPlayer->GetCollider(), m_Pos, m_pPlayer->GetPos(), hitInfo)
		&& utils::DistPointPoint(m_Pos, m_pPlayer->GetPos())
		< utils::DistPointPoint(m_Pos, hitInfoEnemy.intersectPoint)
		+ utils::DistPointPoint(m_pPlayer->GetPos(), hitInfoPlayer.intersectPoint))
	{
		m_Pos.x += hitInfoPlayer.intersectPoint.x - hitInfoEnemy.intersectPoint.x;
		m_Pos.y += hitInfoPlayer.intersectPoint.y - hitInfoEnemy.intersectPoint.y;
	}
}