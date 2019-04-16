#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(int health, const Point2f& pos, float width = {50}, float height = {50}, Texture* pTexture = { new Texture {"./Resources/Textures/player.png"}});
	void Draw() const override;
	void Update(float dT) override;
private:
	/// Data Members
	int m_Health;
	const float m_MaxSpeed;
	const float m_Acceleration;
	const float m_Friction;
	/// Member Functions
	void HandleMovement(float dT);
};