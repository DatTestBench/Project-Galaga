#pragma once
#include "Texture.h"
#include <vector>
#include "Vector2f.h"
class GameObject
{
public:
	GameObject(const Point2f& pos, float width = {10}, float height = {10}, Texture* pTexture = {nullptr} );
	~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator= (const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator= (GameObject&&) = delete;



	virtual void Draw() const = 0;
	virtual void Update(float dT) = 0;
	bool IsOnscreen() const;
	Point2f GetPos() const;
	void ChangePos(const Vector2f& dMove);
	float GetWidth() const;
	float GetHeight() const;
	std::vector<Point2f> GetCollider() const;
	Texture* GetpTexture();
	bool IsDeleted() const;
	void Delete();
protected:

	// Data Members
	Point2f m_Pos;
	Texture* m_pTexture;
	bool m_Onscreen;
	bool m_Deleted {false}; 
	std::vector<Point2f> m_BaseCollider;
	std::vector<Point2f> m_Collider;
	float m_Width;
	float m_Height;
	Vector2f m_MoveV;


};

