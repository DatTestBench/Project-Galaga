#include "pch.h"
#include "Weapon.h"
#include "utils.h"
#include "Player.h"
#include "Bullet.h"
#include "GameObjectManager.h"
#include "Matrix2x3.h"

Weapon::Weapon(float width, float height, Slot slot, Texture* pTexture)
	:GameObject(Vector2f{ 0,0 }, width, height, pTexture)
	, m_Slot{ slot }
{
	switch (m_Slot)
	{
	case Slot::front:
		m_BaseOffset.y += GameObjectManager::Get()->GetPlayer()->GetHeight() / 2.f;
		break;
	case Slot::middle:
		break;
	case Slot::left:
		m_BaseOffset.x -= GameObjectManager::Get()->GetPlayer()->GetWidth() / 2.f;
		break;
	case Slot::right:
		m_BaseOffset.x += GameObjectManager::Get()->GetPlayer()->GetWidth() / 2.f;
		break;
	case Slot::rear:
		m_BaseOffset.y -= GameObjectManager::Get()->GetPlayer()->GetHeight() / 2.f;
		break;
	}
	m_Pos = GetAbsPos();
}

void Weapon::Draw() const
{
	//m_pTexture->DrawC(Point2f{}, m_Width, m_Height);
	//utils::DrawPolygon(GetCollider());
	utils::DrawEllipse(GetAbsPos(), 5, 5);
}

void Weapon::Update(float dT)
{

	if (m_IsShooting)
	{
		GameObjectManager::Get()->Add(new Bullet{ this, GetAbsPos(), GetAngle() });
	}
	//switch (InputHandling::Get()->MouseState())
	//{
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Yeeted that left click" << std::endl;
	//	GameObjectManager::Get()->Add(new Bullet{ this, GameObjectManager::Get()->GetPlayer()->GetPos(), GetAngle() });
	//	break;
	//}
	
}

float Weapon::GetAngle() const
{
	Vector2f v{ GetAbsPos(), InputHandling::Get()->AbsMousePos() };
	//std::cout << "x: " << GameObjectManager::Get()->GetPlayer()->GetPos().x << " y: " << GameObjectManager::Get()->GetPlayer()->GetPos().y << " x: " << InputHandling::Get()->RelMousePos().x << " y: " << InputHandling::Get()->RelMousePos().y << std::endl;
	//std::cout << GetAbsPos() << std::endl;;
	return atan2(v.y, v.x);
}

void Weapon::ToggleIsShooting()
{
	m_IsShooting = !m_IsShooting;
}

Vector2f Weapon::GetAbsPos() const
{
	//std::cout << GameObjectManager::Get()->GetPlayer()->GetPos() << std::endl;
	Matrix2x3 tMat { Matrix2x3::CreateTranslationMatrix(GameObjectManager::Get()->GetPlayer()->GetPos()) };
	Matrix2x3 rMat{ Matrix2x3::CreateRotationMatrix(utils::ToDeg(GameObjectManager::Get()->GetPlayer()->GetAngle() - utils::g_Pi/ 2.f)) };
	std::cout << tMat << std::endl;
	return Vector2f(tMat.Transform(rMat.Transform(m_BaseOffset.ToPoint2f())));
}

std::vector<Vector2f> Weapon::GetCollider() const
{
	Matrix2x3 tMat { Matrix2x3::CreateTranslationMatrix(GetAbsPos()) };
	Matrix2x3 rMat{ Matrix2x3::CreateRotationMatrix(utils::ToDeg(GetAngle())) };
	return tMat.Transform(rMat.Transform(m_BaseCollider));
}
