#include "pch.h"
#include "ShotgunPellet.h"


ShotgunPellet::ShotgunPellet(GameObject* pSender, const Vector2f& pos, float launchAngle, float width, float height, Texture* pTexture)
	: Projectile { pSender, pos, launchAngle, width, height, pTexture }
{
}

