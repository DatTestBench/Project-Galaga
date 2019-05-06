#pragma once
#include "GameObject.h"
#include "Vector2f.h"
#include "TextureManager.h"
class Player;
class Enemy : public GameObject
{
public:
	Enemy(const Vector2f& pos, float width, float height, Texture* pTexture, int level, float baseHealth);
	
	void Draw() const override;
	void Update(float dT) override;
	void Hit(float damage);
private:
	
	// Data Members
	Player* m_pPlayer;
	const float m_MaxSpeed;
	const float m_Acceleration;
	const float m_Friction;
	const float m_BaseHealth;
	float m_CurrentHealth;
	//Member Functions 
	void HandleCollision(float dT) override;


};