#pragma once
#include <vector>
#include "Texture.h"
#include "Vector2f.h"
#include "utils.h"
class Texture;
class GameObject;
class GameObjectManager;
class Level
{
public:
	Level();
	~Level();

	void Draw() const;
	Rectf GetBoundaries() const;
	void HandleCollision() const;
private:

	// Data Members
	std::vector<std::vector<Vector2f>> m_Vertices;
	Rectf m_Boundaries;
	Texture* m_pBackgroundTexture;
	GameObjectManager* m_pGameObjectManager;
	// Memeber Functions
	void InitializeVertices();
};
