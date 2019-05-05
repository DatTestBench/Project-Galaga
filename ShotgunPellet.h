#pragma once
#include "Projectile.h"

class ShotgunPellet : public Projectile
{
public:
	ShotgunPellet(GameObject* pSender, const Vector2f& pos, float launchAngle, float width = { 2 }, float height = { 2 }, Texture* pTexture = { nullptr });
};

