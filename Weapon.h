#pragma once
#include "GameObject.h"
#include "GameObjectManager.h"

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
	Weapon(GameObject* pOwner, float width, float height, const Slot& slot, float fireRate, Texture* pTexture = {nullptr});
	void Draw() const override;
	virtual void Update(float dT) override;
	float GetAngle() const override;
	void ToggleIsShooting();
	Vector2f GetAbsPos() const;
	std::vector<Vector2f> GetCollider() const override;

protected:
	bool m_IsShooting;
	Slot m_Slot;
	Vector2f m_BaseOffset;
	GameObject* m_pOwner;
	float m_FireRate; // Firerate in shots / second
	float m_TimeSinceLastShot; // Time in seconds since the last shot was fired, used to prevent players abusing spamclicking to improve firerate
	float m_Cooldown; // Time it takes for m_TimeSinceLastShot to reset

	virtual void DoShoot(float dT) = 0;
private:
	
};

