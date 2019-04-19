#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
	enum class Owner 
	{
		enemy
		,player
	};


public:
	Bullet(GameObject* senderPointer, const Point2f& pos, float launchAngle, float width = {3}, float height = {3}, Texture* pTexture = {nullptr});
	void Draw() const override;
	void Update(float dT) override;

	
private:
	GameObject* m_Owner;
	float m_MaxSpeed;
};

