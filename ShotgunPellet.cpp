#include "pch.h"
#include "ShotgunPellet.h"


ShotgunPellet::ShotgunPellet(const Vector2f& pos, float width, float height, Texture* pTexture, float launchAngle, GameObject* pSender /*int level*/)
	: Projectile{ pos, width, height, pTexture, launchAngle, 1000 /*baseSpeed*/, pSender /*, level, baseDamage*/}
{
}

