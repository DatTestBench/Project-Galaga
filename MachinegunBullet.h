#pragma once
#include "Projectile.h"

class MachinegunBullet : public Projectile
{
public:
	MachinegunBullet(GameObject* pSender, const Vector2f& pos, float launchAngle, float width = { 3 }, float height = { 3 }, Texture* pTexture = { nullptr });



};

