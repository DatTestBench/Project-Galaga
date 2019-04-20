#include "pch.h"
#include "Weapon.h"
#include "utils.h"
#include "Player.h"
#include "Bullet.h"
#include "GameObjectManager.h"

Weapon::Weapon(float width, float height, Slot slot, Texture* pTexture)
	:GameObject(Point2f{ 0,0 }, width, height, pTexture)
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
	m_Pos = GameObjectManager::Get()->GetPlayer()->GetPos() + m_BaseOffset;
}

void Weapon::Draw() const
{
	//m_pTexture->DrawC(Point2f{}, m_Width, m_Height);
	utils::DrawPolygon(GetCollider());
}

void Weapon::Update(float dT)
{
	m_Pos = GameObjectManager::Get()->GetPlayer()->GetPos() + Offset();
	if (m_IsShooting)
	{
		GameObjectManager::Get()->Add(new Bullet{ this, m_Pos, GetAngle() });
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
	Vector2f v{ m_Pos, InputHandling::Get()->RelMousePos() };
	//std::cout << "x: " << GameObjectManager::Get()->GetPlayer()->GetPos().x << " y: " << GameObjectManager::Get()->GetPlayer()->GetPos().y << " x: " << InputHandling::Get()->RelMousePos().x << " y: " << InputHandling::Get()->RelMousePos().y << std::endl;
	return atan2(v.y, v.x);
}

void Weapon::ToggleIsShooting()
{
	m_IsShooting = !m_IsShooting;
}

Vector2f Weapon::Offset()  
{
	return Vector2f{ m_BaseOffset.x * cos(GameObjectManager::Get()->GetPlayer()->GetAngle()), m_BaseOffset.y * sin(GameObjectManager::Get()->GetPlayer()->GetAngle()) };
}
