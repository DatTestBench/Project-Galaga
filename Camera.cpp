#include "pch.h"
#include "Camera.h"
#include "utils.h"
#include <vector>
#include <cmath>

Camera::Camera(float width, float height)
	:m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{0,0,width,height }
{
}

void Camera::SetLevelBoundaries(const Rectf & levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const GameObject* pGameObject) const
{
	
	Point2f cameraPos{ Track(pGameObject) };
	Clamp(cameraPos);
	glTranslatef(-cameraPos.x, -cameraPos.y,0.f);
}

Point2f Camera::Track(const GameObject* pGameObject) const
{
	/*Point2f center{};

	for (size_t idx{}; idx < collider.size(); idx++)
	{
		center.x += collider[idx].x;
		center.y += collider[idx].y;
	}
	center.x /= collider.size();
	center.y /= collider.size();

	center.x -= m_Width / 2.f;
	center.y -= m_Height / 2.f;
	return center;*/
	return Point2f {pGameObject->GetPos().x - m_Width / 2.f, pGameObject->GetPos().y - m_Height / 2.f};
}

void Camera::Clamp(Point2f & bottomLeftPos) const 
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

