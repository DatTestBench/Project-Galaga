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
	Weapon(GameObject* pOwner, float width, float height, Slot slot, Texture* pTexture = {nullptr});
	void Draw() const override;
	void Update(float dT) override;
	float GetAngle() const override;
	void ToggleIsShooting();
	Vector2f GetAbsPos() const;
	std::vector<Vector2f> GetCollider() const override;
protected:
	bool m_IsShooting;
	Slot m_Slot;
	Vector2f m_BaseOffset;
	GameObject* m_pOwner;
private:
	
};

