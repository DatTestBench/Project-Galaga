#pragma once
#include "Projectile.h"

class ShotgunPellet : public Projectile
{
public:
	ShotgunPellet(const Vector2f& pos, float width, float height, Texture* pTexture, float launchAngle, GameObject* pSender, int level);
};

