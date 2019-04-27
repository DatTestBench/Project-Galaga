#pragma once
#include "GameObject.h"
#include "Vector2f.h"
#include "TextureManager.h"
class Player;
class Enemy : public GameObject
{
public:
	Enemy(const Point2f& pos, float width = {50}, float height = {50}, Texture* pTexture = {TextureManager::Get()->GetEnemyTextp()});
	
	void Draw() const override;
	void Update(float dT) override;

private:
	
	// Data Members
	Player* m_pPlayer;
	Vector2f m_MoveV;

	//Member Functions 
	void HandleCollision() override;


};