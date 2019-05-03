#include "pch.h"
#include "Weapon.h"
#include "utils.h"
#include "Player.h"
#include "Projectile.h"
#include "GameObjectManager.h"
#include "Matrix2x3.h"

Weapon::Weapon(GameObject* pOwner, float width, float height, Slot slot, Texture* pTexture)
	: GameObject(Vector2f{ 0,0 }, width, height, pTexture)
	, m_Slot{ slot }
	, m_pOwner{ pOwner }
	, m_IsShooting{ m_pGameObjectMananger->GetPlayer()->IsShooting() }
{
	switch (m_Slot)
	{
	case Slot::front:
		m_BaseOffset.y += m_pOwner->GetHeight() / 2.f;
		break;
	case Slot::middle:
		break;
	case Slot::left:
		m_BaseOffset.x -= m_pOwner->GetWidth() / 2.f;
		break;
	case Slot::right:
		m_BaseOffset.x += m_pOwner->GetWidth() / 2.f;
		break;
	case Slot::rear:
		m_BaseOffset.y -= m_pOwner->GetHeight() / 2.f;
		break;
	}
	m_Pos = GetAbsPos();
}

void Weapon::Draw() const
{
	//m_pTexture->DrawC(Point2f{}, m_Width, m_Height);
	utils::DrawPolygon(m_BaseCollider);
}

void Weapon::Update(float dT)
{

	if (m_IsShooting)
	{
		m_pGameObjectMananger->Add(new Projectile{ m_pOwner, GetAbsPos(), GetAngle() });
	}
	//switch (InputHandling::Get()->MouseState())
	//{
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Yeeted that left click" << std::endl;
	//	GameObjectManager::Get()->Add(new Projectile{ this, GameObjectManager::Get()->GetPlayer()->GetPos(), GetAngle() });
	//	break;
	//}

}

float Weapon::GetAngle() const
{
	Vector2f v{};
	switch (m_Slot)
	{
	case Slot::front:
		return m_pOwner->GetAngle();

		break;

	case Slot::middle:
		v = Vector2f(GetAbsPos(), InputHandling::Get()->AbsMousePos());
		return atan2(v.y, v.x);
		break;

	case Slot::left:
		return m_pOwner->GetAngle() + utils::g_Pi / 6;
		break;

	case Slot::right:
		v = Vector2f(GetAbsPos(), InputHandling::Get()->AbsMousePos());
		/*if ( ( atan2(v.y, v.x) - m_pOwner->GetAngle() < utils::g_Pi / 3.f && atan2(v.y,v.x) - m_pOwner->GetAngle() > 0 ) ||
			atan2(v.y, v.x) + m_pOwner->GetAngle() > 5 * utils::g_Pi && atan2(v.y, v.x) < 2 * utils::g_Pi)
		{
			return atan2(v.y, v.x);
		}
		else if (atan2(v.y, v.x) - m_pOwner->GetAngle() > 4 * utils::g_Pi / 3.f && atan2(v.y, v.x) - m_pOwner->GetAngle() < 2 * utils::g_Pi)
		{
			return atan2(v.y, v.x) - utils::g_Pi;
		}
		else
			return m_pOwner->GetAngle() + utils::g_Pi / 2.f;*/

		return m_pOwner->GetAngle() + 11 * utils::g_Pi / 6;
		break;

	case Slot::rear:
		return m_pOwner->GetAngle() - utils::g_Pi;
		break;
	}

	v = Vector2f(GetAbsPos(), InputHandling::Get()->AbsMousePos());
	return atan2(v.y, v.x);
}

void Weapon::ToggleIsShooting()
{
	m_IsShooting = !m_IsShooting;
}

Vector2f Weapon::GetAbsPos() const
{
	Matrix2x3 tMat{ Matrix2x3::CreateTranslationMatrix(m_pOwner->GetPos()) };
	Matrix2x3 rMat{ Matrix2x3::CreateRotationMatrix(utils::ToDeg(m_pOwner->GetAngle() - utils::g_Pi / 2.f)) };
	return Vector2f(tMat.Transform(rMat.Transform(m_BaseOffset.ToPoint2f())));
}

std::vector<Vector2f> Weapon::GetCollider() const
{
	Matrix2x3 tMat{ Matrix2x3::CreateTranslationMatrix(GetAbsPos()) };
	Matrix2x3 rMat{ Matrix2x3::CreateRotationMatrix(utils::ToDeg(GetAngle())) };
	return (tMat*rMat).Transform(m_BaseCollider);
}
