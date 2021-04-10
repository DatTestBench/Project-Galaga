#include "Items/ShotgunPellet.h"

ShotgunPellet::ShotgunPellet(const Vector2f& pos, const float width, const float height, Sprite* pSprite, const float launchAngle, GameObject* pSender, const int level)
	: Projectile{ pos, width, height, pSprite, launchAngle, 1000 /*baseSpeed*/, pSender, level, 30.f /*baseDamage*/ }
{
}
