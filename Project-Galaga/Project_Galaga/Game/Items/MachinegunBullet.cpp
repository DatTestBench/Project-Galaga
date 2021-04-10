#include "Items/MachineGunBullet.h"

MachinegunBullet::MachinegunBullet(const Vector2f& pos, const float width, const float height, Sprite* pSprite, const float launchAngle, GameObject* pSender, const int level)
	: Projectile{ pos, width, height, pSprite, launchAngle, 1000 /*baseSpeed*/, pSender, level, 10.f /*baseDamage*/ }
{
}
