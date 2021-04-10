#include "Core/Camera.h"

Camera::Camera(const float width, const float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{0,0,width,height }
{
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const GameObject* pGameObject) const
{
	Vector2f cameraPos{ Track(pGameObject) };
	Clamp(cameraPos);
	glTranslatef(-cameraPos.x, -cameraPos.y,0.f);
}

Vector2f Camera::GetOffset(const GameObject* pGameObject) const
{
	Vector2f cameraPos{ Track(pGameObject) };
	Clamp(cameraPos);
	return Vector2f {cameraPos};
}

 
Vector2f Camera::Track(const GameObject* pGameObject) const
{
	return Vector2f {pGameObject->GetPos().x - m_Width / 2.f, pGameObject->GetPos().y - m_Height / 2.f};
}

void Camera::Clamp(Vector2f& bottomLeftPos) const 
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
	}
	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
	if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
	}
}

