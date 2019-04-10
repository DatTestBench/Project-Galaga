#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(int health, float winHeight, const Point2f& pos, float width = {50}, float height = {50}, Texture* pTexture = { new Texture {"./Resources/Textures/player.png"}});
	void Draw() const override;
	void Update(float dT) override;
private:
	// Data Members
	float m_WindowHeight;
	int m_Health;
};