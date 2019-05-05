#include "pch.h"
#include "MachineGunBullet.h"


MachinegunBullet::MachinegunBullet(GameObject* pSender, const Vector2f& pos, float launchAngle, float width, float height, Texture* pTexture)
	:Projectile { pSender, pos, launchAngle, width, height, pTexture }
{
}

