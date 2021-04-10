#pragma once
#include "Core/GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(const Vector2f& pos, float width, float height, Sprite* pSprite, float launchAngle, float baseSpeed, GameObject* pSender, int level, float baseDamage);
	void Draw() const override;
	void Update(float dT) override;
	void HitLevel(const Vector2f& dMove) override;
	GameObject* GetSender() const { return m_pSender; }

	static const float m_Lifespan; // todo: actually use this
protected:
	void HandleCollision(float dT) override final;

	GameObject* m_pSender;
	float m_BaseSpeed;
	int m_Level;
	float m_BaseDamage;

private:
	/// Data Members

	/// Member functions
};
