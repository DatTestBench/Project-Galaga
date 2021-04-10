#pragma once
#include "Core/GameObject.h"
#include "Core/GameObjectManager.h"

enum class Slot
{
	front = 0,
	middle = 1,
	left = 2,
	right = 3,
	rear = 4,
	size = 5 // Used to return the max amount of slots
};

class Weapon : public GameObject
{
public:
	Weapon(float width, float height, Sprite* pSprite, GameObject* pOwner, int level, /*float baseDamage, */const Slot& slot, float baseFireRate);

	void Draw() const override;
	void Update(float dT) override;
	float GetAngle() const override;
	void ToggleShoot() override;
	Vector2f GetAbsPos() const;
	std::vector<Vector2f> GetCollider() const override;

protected:
	bool m_IsShooting;
	Slot m_Slot;
	int m_Level;
	Vector2f m_BaseOffset;
	GameObject* m_pOwner;
	float m_BaseFireRate; // Fire-rate in shots / second
	float m_TimeSinceLastShot; // Time in seconds since the last shot was fired, used to prevent players abusing spam-clicking to improve fire-rate
	float m_Cooldown; // Time it takes for m_TimeSinceLastShot to reset

	void DoShoot(float dT) override;
	float GetFireRate() const;
};
