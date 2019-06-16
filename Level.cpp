#include "pch.h"
#include "Level.h"
#include "utils.h"
#include "SVGParser.h"
#include "ResourceManager.h"
#include "SAT.h"
#include "GameObjectManager.h"
Level::Level()
	: m_pBackgroundTexture{ ResourceManager::Get()->GetTexturep("TextLevel") }
	, m_Boundaries{ 0, 0,  ResourceManager::Get()->GetTexturep("TextLevel")->GetWidth(), ResourceManager::Get()->GetTexturep("TextLevel")->GetHeight() }
	, m_pGameObjectManager{ GameObjectManager::Get() }
{
	InitializeVertices();
}


Level::~Level()
{
}

void Level::Draw() const
{
	m_pBackgroundTexture->Draw(Rectf{ 0.f, 0.f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight() });

	for (std::vector<Vector2f> subCollider : m_Vertices)
		utils::DrawPolygon(subCollider);
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

void Level::HandleCollision() const
{
	PolygonCollisionResult result;
	for (GameObject* pGameObject : *m_pGameObjectManager->GetGameObjects())
	{
		for (std::vector<Vector2f> subCollider : m_Vertices)
		{
			result = sat::PolygonCollision(pGameObject, subCollider);
			if (result.intersect)
			{
				pGameObject->HitLevel(result.minimumTranslationVector);
				//pGameObject->ChangePos(result.minimumTranslationVector);
			}
		}
	}
}

// Convert Point2f extracted from level SVG to Vector2f for collision detection
void Level::InitializeVertices()
{
	std::vector<std::vector<Point2f>> vertices;

	std::string filePath{ "./Resources/level.svg" };
	SVGParser::GetVerticesFromSvgFile(filePath, vertices);

	for (std::vector<Point2f> subCollider : vertices)
	{
		std::vector<Vector2f> tempVector;
		for (Point2f point : subCollider)
		{
			tempVector.push_back(Vector2f(point));
		}
		m_Vertices.push_back(tempVector);
	}
}
