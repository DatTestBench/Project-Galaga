#pragma once
#include "GameObject.h"
#include "GameObjectManager.h"

enum class Slot
	{
		front = 1,
		middle = 2,
		left = 3,
		right = 4,
		rear = 5
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

