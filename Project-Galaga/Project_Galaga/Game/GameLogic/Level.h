#pragma once
#include <vector>
#include "Math/Vector2f.h"
#include "Resources/Texture.h"
class Texture;
class GameObject;
class GameObjectManager;
class Level
{
public:
	Level();

	void Draw() const;
	Rectf GetBoundaries() const;
	void HandleCollision() const;

	const std::vector<std::vector<Point2f>>& GetPoint2fVertices() const;
	const std::vector<std::vector<Vector2f>>& GetVertices() const;
private:

	// Data Members
	Texture* m_pBackgroundTexture;
	std::vector<std::vector<Vector2f>> m_Vertices;
	std::vector<std::vector<Point2f>> m_Point2fVertices;
	Rectf m_Boundaries;
	GameObjectManager* m_pGameObjectManager;
	// Memeber Functions
	void InitializeVertices();
};

