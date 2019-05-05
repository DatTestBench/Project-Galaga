#pragma once
#include "Projectile.h"

class MachinegunBullet : public Projectile
{
public:
	MachinegunBullet(const Vector2f& pos, float width, float height, Texture* pTexture, float launchAngle, GameObject* pSender/*, int level*/);



};

