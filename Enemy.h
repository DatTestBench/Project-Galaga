#pragma once
#include "GameObject.h"
#include "Vector2f.h"
#include "TextureManager.h"
class Player;
class Enemy : public GameObject
{
public:
	Enemy(const Vector2f& pos, float width = {50}, float height = {50}, Texture* pTexture = {TextureManager::Get()->GetEnemyTextp()});
	
	void Draw() const override;
	void Update(float dT) override;

private:
	
	// Data Members
	Player* m_pPlayer;
	const float m_MaxSpeed;
	const float m_Acceleration;
	const float m_Friction;
	//Member Functions 
	void HandleCollision(float dT) override;


};