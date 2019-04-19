#include "pch.h"
#include "Weapon.h"
#include "utils.h"
#include "Player.h"
#include "Bullet.h"
#include "GameObjectManager.h"

Weapon::Weapon(float width, float height, Texture* pTexture )
	:GameObject(Point2f{0,0}, width, height, pTexture )
{

}

void Weapon::Draw() const
{
	//m_pTexture->DrawC(Point2f{}, m_Width, m_Height);
	utils::DrawPolygon(GetCollider());
}

void Weapon::Update(float dT)
{
	switch (InputHandling::Get()->MouseState())
	{
	case SDL_BUTTON_MIDDLE:
		//std::cout << "Yeeted that left click" << std::endl;
		GameObjectManager::Get()->Add(new Bullet{ this, GameObjectManager::Get()->GetPlayer()->GetPos(), GetAngle() });
		break;
	}
}

float Weapon::GetAngle() const
{
	Vector2f v{ GameObjectManager::Get()->GetPlayer()->GetPos(),InputHandling::Get()->RelMousePos() };
	std::cout << "x: " << GameObjectManager::Get()->GetPlayer()->GetPos().x << " y: " << GameObjectManager::Get()->GetPlayer()->GetPos().y << " x: " << InputHandling::Get()->RelMousePos().x << " y: " << InputHandling::Get()->RelMousePos().y << std::endl;
	return atan2(v.y, v.x);
}
