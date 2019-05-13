#include "pch.h"
#include "Rocket.h"
#include "utils.h"
#include "Projectile.h"
#include "utils.h"
Rocket::Rocket(const Vector2f& pos, float width, float height, Texture* pTexture, float launchAngle, GameObject* pSender, int level)
	: Projectile{ pos, width, height, pTexture, launchAngle, 500 /*baseSpeed*/, pSender, level, 50.f /*baseDamage*/ }
	, m_Lifespan{ 50.f }
{
}

void Rocket::Update(float dT)
{
	
	HandleCollision(dT);
	HandleLogic(dT);
	m_Pos += GetVelocity() * dT;
}

void Rocket::HandleLogic(float dT)
{

	GameObject* pClosestObj{ nullptr };
	float closestDist{ std::numeric_limits<float>::infinity() };
	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		if (pGameObject != nullptr)
		{
			if (utils::DistPointPoint(m_Pos, pGameObject->GetPos()) < closestDist && typeid(*pGameObject) != typeid(Projectile) && typeid(*pGameObject) != typeid(*this) && typeid(*pGameObject) != typeid(*m_pSender))
			{
				pClosestObj = pGameObject;
				closestDist = utils::DistPointPoint(m_Pos, pGameObject->GetPos());
			}
		}
	}

	if (pClosestObj == nullptr)
		return;


	
	Vector2f v{ m_Pos, pClosestObj->GetPos() };

	if ((atan2(v.y, v.x) > m_Angle && atan2(v.y, v.x) < m_Angle + utils::g_Pi) || (atan2(v.y, v.x) < m_Angle && atan2(v.y, v.x) > m_Angle - utils::g_Pi))
		m_Angle = utils::lerp(m_Angle, atan2(v.y, v.x), dT, 4);
	else if (atan2(v.y, v.x) > m_Angle)
		m_Angle = utils::lerp(m_Angle, atan2(v.y, v.x) - 2 * utils::g_Pi, dT, 4);
	else
		m_Angle = utils::lerp(m_Angle, atan2(v.y, v.x) + 2 * utils::g_Pi, dT, 4);
		

	m_Angle = m_Angle < 0 ? m_Angle + 2 * utils::g_Pi : m_Angle;
	m_Angle = m_Angle > 2 * utils::g_Pi ? m_Angle - 2 * utils::g_Pi : m_Angle;
}