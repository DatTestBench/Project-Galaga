#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{

public:
	Projectile(const Vector2f& pos, float width, float height, Texture* pTexture, float launchAngle, float baseSpeed, GameObject* pSender /*int level, float baseDamage*/);
	void Draw() const override;
	void Update(float dT) override;


private:
	/// Data Members

	GameObject* m_pSender;
	float m_BaseSpeed;

	/// Memeber functions
	void HandleCollision(float dT) override;
};

