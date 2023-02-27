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
	[[nodiscard]] Rectf GetBoundaries() const;
	void HandleCollision() const;

	[[nodiscard]] const std::vector<std::vector<Point2f>>& GetPoint2fVertices() const { return m_Point2fVertices; }
	[[nodiscard]] const std::vector<std::vector<Vector2f>>& GetVertices() const { return m_Vertices; }
private:

	// Data Members
	Texture* m_pBackgroundTexture;
	std::vector<std::vector<Vector2f>> m_Vertices;
	std::vector<std::vector<Point2f>> m_Point2fVertices;
	Rectf m_Boundaries;
	GameObjectManager* m_pGameObjectManager;
	// Member Functions
	void InitializeVertices();
};
