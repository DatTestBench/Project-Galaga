#pragma once
#include "GameObject.h"
#include "Weapon.h"
class Player : public GameObject
{
public:
	Player(int health, const Point2f& pos, float width = {50}, float height = {50}, Texture* pTexture = { new Texture {"./Resources/Textures/player.png"}});
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
};