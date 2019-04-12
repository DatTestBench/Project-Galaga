#pragma once
class Camera
{
public:
	Camera(float width, float height);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const std::vector<Point2f>& collider) const;

private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;

	Point2f Track(const std::vector<Point2f>& collider) const;
	void Clamp(Point2f& bottomLeftPos) const;

};

