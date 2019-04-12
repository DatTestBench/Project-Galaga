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

void Camera::Transform(const std::vector<Point2f>& collider) const
{
	
	Point2f cameraPos{ Track(collider) };
	Clamp(cameraPos);
	glTranslatef(-cameraPos.x, -cameraPos.y,0.f);
	//Rectf drawRect{ cameraPos.x, cameraPos.y , m_Width, m_Height };
	//utils::SetColor(Color4f{ 0, 0, 1, 1 });
	//utils::DrawRect(drawRect);
	
}

Point2f Camera::Track(const std::vector<Point2f>& collider) const
{
	Point2f center{};

	for (size_t idx{}; idx < collider.size(); idx++)
	{
		center.x += collider[idx].x;
		center.y += collider[idx].y;
	}
	center.x /= collider.size();
	center.y /= collider.size();

	center.x -= m_Width / 2.f;
	center.y -= m_Height / 2.f;
	return center;
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

