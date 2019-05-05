#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{

public:
	Projectile(GameObject* pSender, const Vector2f& pos, float launchAngle, float width, float height, Texture* pTexture = { nullptr });
	void Draw() const override;
	void Update(float dT) override;


private:
	/// Data Members

	GameObject* m_pSender;
	float m_MaxSpeed;

	/// Memeber functions
	void HandleCollision(float dT) override;
};

