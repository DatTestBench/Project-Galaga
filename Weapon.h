#pragma once
#include "GameObject.h"
#include "GameObjectManager.h"
class Weapon : public GameObject
{
public:
	Weapon(float width, float height, Texture* pTexture = {nullptr});
	void Draw() const override;
	void Update(float dT) override;
	float GetAngle() const override;
protected:

private:
	
};

