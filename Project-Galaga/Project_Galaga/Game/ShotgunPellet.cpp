#include "pch.h"
#include "ShotgunPellet.h"

ShotgunPellet::ShotgunPellet(const Vector2f& pos, float width, float height, Sprite* pSprite, float launchAngle, GameObject* pSender, int level)
	: Projectile{ pos, width, height, pSprite, launchAngle, 1000 /*baseSpeed*/, pSender , level, 30.f /*baseDamage*/}
{
}

