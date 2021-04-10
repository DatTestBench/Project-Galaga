#pragma once
#include "Items/Projectile.h"

#include "Core/GameObject.h"
#include "Math/Vector2f.h"
#include "Resources/Sprite.h"

class MachinegunBullet final : public Projectile
{
public:
	MachinegunBullet(const Vector2f& pos, float width, float height, Sprite* pSprite, float launchAngle, GameObject* pSender, int level);
};
