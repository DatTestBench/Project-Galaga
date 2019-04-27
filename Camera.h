#pragma once
#include "GameObject.h"
class Camera
{
public:
	Camera(float width, float height);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const GameObject* pGameObject) const;
	Vector2f GetOffset(const GameObject* pGameObject) const;
private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;

	Vector2f Track(const GameObject* pGameObject) const;
	void Clamp(Vector2f& bottomLeftPos) const;

};

