#pragma once
#include "Texture.h"
#include <vector>
#include "Vector2f.h"
#include "InputHandling.h"
class GameObject
{
public:
	GameObject(const Point2f& pos, float width, float height, Texture* pTexture = {nullptr} );
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator= (const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator= (GameObject&&) = delete;


	// Workers
	virtual void Draw() const = 0;
	virtual void Update(float dT) = 0;

	// Getters
	Point2f GetPos() const;
	Texture* GetpTexture() const;
	virtual std::vector<Point2f> GetCollider() const;
	float GetWidth() const;
	float GetHeight() const;
	bool GetFlag() const;
	virtual float GetAngle() const; 

	// Changers
	void ChangePos(const Vector2f& dMove);
	void Delete();
	
protected:

	/// Data Members
	Point2f m_Pos;
	Texture* m_pTexture;
	std::vector<Point2f> m_BaseCollider;
	float m_Width;
	float m_Height;
	bool m_DelFlag;
	Vector2f m_MoveV;

	/// Member Functions



};

