#pragma once
#include "GameObject.h"
#include "Vector2f.h"
class Player;
class Enemy : public GameObject
{
public:
	Enemy(Player* pPlayer, const Point2f& pos, float width = {50}, float height = {50}, Texture* pTexture = {new Texture { "./Resources/Textures/enemy.png"}});
	
	void Draw() const override;
	void Update(float dT) override;

private:
	
	// Data Members
	Player* m_pPlayer;
	Vector2f m_MoveV;

	//Member Functions 
	void HandleCollision(float dT);


};