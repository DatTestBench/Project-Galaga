#pragma once
#include "GameObject.h"
#include "Vector2f.h"
#include "ResourceManager.h"
#include "Weapon.h"

class Player;
class Enemy : public GameObject
{
public:
	Enemy(const Vector2f& pos, float width, float height, Sprite* pSprite, int level, float baseHealth);
	~Enemy() override;
	void Draw() const override;
	void Update(float dT) override;
	bool IsShooting() override;
	void ToggleShoot() override;
	void Hit(float damage);
	void HitLevel(const Vector2f& dMove);
private:
	
	// Data Members
	GameObject* m_pPlayer;
	const float m_Friction;
	const float m_BaseHealth;
	float m_CurrentHealth;
	
	std::vector<Weapon*> m_pWeapons;
	bool m_IsShooting;
	//Member Functions 
	void HandleCollision(float dT) override;


};