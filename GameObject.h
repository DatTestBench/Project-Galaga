#pragma once
#include "Texture.h"
#include <vector>
#include "Vector2f.h"
#include "InputHandling.h"
#include "GameObjectManager.h"

class GameObjectManager;
class GameObject
{
public:
	GameObject(const Vector2f& pos, float width, float height, Texture* pTexture);
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator= (const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator= (GameObject&&) = delete;


	// Workers
	virtual void Draw() const = 0;
	virtual void Update(float dT) = 0;

	// Getters
	Vector2f GetPos() const;
	Texture* GetpTexture() const;
	virtual std::vector<Vector2f> GetCollider() const;
	float GetWidth() const;
	float GetHeight() const;
	bool GetFlag() const;
	virtual float GetAngle() const; 
	float GetSpeed() const;
	Vector2f GetVelocity() const;

	// Changers
	void ChangePos(const Vector2f& dMove);
	void Delete();
	
protected:

	/// Data Members
	Vector2f m_Pos;
	Texture* m_pTexture;
	std::vector<Vector2f> m_BaseCollider;
	float m_Width;
	float m_Height;
	bool m_DelFlag;
	float m_Angle;
	float m_Speed;
	
	Vector2f m_Velocity;
	GameObjectManager* m_pGameObjectManager;

	/// Member Functions
	// Internal Workers
	virtual void HandleCollision(float dT); // = 0 when fully implemented ToDo



};

