#pragma once
#include "GameObject.h"
#include "Weapon.h"
#include "ResourceManager.h"
class Player : public GameObject
{
public:
	Player(const Vector2f& pos, float width, float height, Sprite* pSprite, float baseHealth);
	~Player() override;
	void Draw() const override;
	void Update(float dT) override;
	bool IsShooting() override;
	void ToggleShoot() override;
	void AddWeapon();
	void Hit(float damage);

	void HitLevel(const Vector2f& dMove) override;
	float GetBaseHealth() const;
	float GetHealth() const;
	float GetLives() const;
private:
	/// Data Members
	const float m_Friction;
	const float m_BaseHealth;
	float m_CurrentHealth;
	float m_Lives;
	std::vector<Weapon*> m_pWeapons;
	bool m_IsShooting;
		
	/// Member Functions
	// Player behaviour 
	void Fire(float dT);
	void HandleMovement(float dT);
	void HandleCollision(float dT) override;

};