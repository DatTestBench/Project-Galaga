#pragma once
#include <vector>
#include "Math/Vector2f.h"
#include "Core/GameObjectManager.h"
#include "Framework/Resources/Sprite.h"
#include "Game/GameLogic/SteeringManager.h"
#include "Resources/ResourceManager.h"
#include "Game/GameLogic/Scoreboard.h"

class Texture;
class GameObjectManager;
class SteeringManager;
class ResourceManager;
class Level;
class Scoreboard;
class GameObject
{
public:
	GameObject(const Vector2f& pos, float width, float height, Sprite* pSprite);
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator= (const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator= (GameObject&&) = delete;


	// Workers
	virtual void Draw() const = 0;
	virtual void Update(float dT) = 0;
	
	virtual void DoAction(float dT);
	virtual void ToggleAction();

	virtual void DoShoot(float dT);
	virtual void ToggleShoot();
	virtual bool IsShooting();
	virtual void HitLevel(const Vector2f& dMove);
	
	// Getters
	Vector2f GetPos() const;
	Texture* GetTexture() const;
	virtual std::vector<Vector2f> GetCollider() const;
	float GetWidth() const;
	float GetHeight() const;
	bool GetFlag() const;
	virtual float GetAngle() const; 
	float GetSpeed() const;
	float GetMaxSpeed() const;
	Vector2f GetVelocity() const;
	float GetMass() const;


	// Changers
	void ChangePos(const Vector2f& dMove);
	void Delete();
	virtual void AddWeapon();
	void SetVelocity(const Vector2f& vNew);
	void SetAngle(float angleNew);
	void SetSpeed(float speedNew);
	

protected:

	/// Data Members
	Vector2f m_Pos;
	Texture* m_pTexture;
	Sprite* m_pSprite;
	std::vector<Vector2f> m_BaseCollider;
	float m_Width;
	float m_Height;
	bool m_DelFlag;
	float m_Angle;
	float m_Speed;
	float m_Acceleration;
	float m_MaxSpeed;
	float m_Mass;
	
	Vector2f m_Velocity;

	GameObjectManager* m_pGameObjectManager;
	SteeringManager* m_pSteeringManager;
	ResourceManager* m_pResourceManager;
	Level* m_pLevel;
	Scoreboard* m_pScoreboard;

	/// Member Functions
	// Internal Workers
	virtual void HandleCollision(float dT); 
	virtual void HandleLogic(float dT); // Handles enemy movement, steering, ect. All enemy actions

};

