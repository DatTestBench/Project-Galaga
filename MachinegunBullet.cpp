#include "pch.h"
#include "MachineGunBullet.h"

MachinegunBullet::MachinegunBullet(const Vector2f& pos, float width, float height, Texture* pTexture, float launchAngle, GameObject* pSender, int level)
	:Projectile{ pos, width, height, pTexture, launchAngle, 1000 /*baseSpeed*/, pSender, level, 2.f /*baseDamage*/}
{
}

