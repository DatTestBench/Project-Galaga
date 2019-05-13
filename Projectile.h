#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{

public:
	Projectile(const Vector2f& pos, float width, float height, Texture* pTexture, float launchAngle, float baseSpeed, GameObject* pSender, int level, float baseDamage);
	void Draw() const override;
	void Update(float dT) override;
protected:
	void HandleCollision(float dT) override final;
	
	GameObject* m_pSender;
	float m_BaseSpeed;
	int m_Level;
	float m_BaseDamage;
private:
	/// Data Members

	

	/// Memeber functions
};

