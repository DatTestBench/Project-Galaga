#pragma once
#include "GameObject.h"
#include "Weapon.h"
#include "TextureManager.h"
class Player : public GameObject
{
public:
	Player(const Vector2f& pos, float width, float height, Texture* pTexture, int health);
	~Player() override;
	void Draw() const override;
	void Update(float dT) override;
	bool IsShooting();
	void ToggleIsShooting();
	void AddWeapon();
private:
	/// Data Members
	int m_Health;
	const float m_MaxSpeed;
	const float m_Acceleration;
	const float m_Friction;

	std::vector<Weapon*> m_pWeapons;
	bool m_IsShooting;
	
	/// Member Functions
	void HandleMovement(float dT);
	void HandleCollision(float dT) override;
};