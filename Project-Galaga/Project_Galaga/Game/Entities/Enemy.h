#pragma once
#include "Core/GameObject.h"
#include "Math/Vector2f.h"
#include "Resources/ResourceManager.h"
#include "Items/Weapon.h"

class Player;
class Enemy : public GameObject
{
public:
	Enemy(const Vector2f& pos, float width, float height, Sprite* pSprite, int level, float baseHealth);
	~Enemy() override;
	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;
	Enemy(Enemy&&) = delete;
	Enemy& operator=(Enemy&&) = delete;

	void Draw() const override;
	void Update(float dT) override;
	bool IsShooting() override;
	void ToggleShoot() override;
	void Hit(float damage);
	void HitLevel(const Vector2f& dMove) override;

protected:
	// Data Members
	GameObject* m_pPlayer;
	const float m_Friction;
	const float m_BaseHealth;
	float m_CurrentHealth;

	std::vector<Weapon*> m_pWeapons;
	bool m_IsShooting;
	Sprite* m_pExhaustSprite;
	//Member Functions 
	void HandleCollision(float dT) override;
	void HandleLogic(float dT) override;
};
