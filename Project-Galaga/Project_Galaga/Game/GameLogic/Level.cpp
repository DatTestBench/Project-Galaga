#include "GameLogic/Level.h"
#include "Core/GameObjectManager.h"
#include "Helpers/SAT.h"
#include "Helpers/SVGParser.h"
#include "Helpers/utils.h"
#include "Resources/ResourceManager.h"
Level::Level()
	: m_pBackgroundTexture{ ResourceManager::Get()->GetTexture("TextLevel") }
	, m_Boundaries{ 0, 0,  ResourceManager::Get()->GetTexture("TextLevel")->GetWidth(), ResourceManager::Get()->GetTexture("TextLevel")->GetHeight() }
	, m_pGameObjectManager{ GameObjectManager::Get() }
{
	InitializeVertices();
}

void Level::Draw() const
{
	m_pBackgroundTexture->Draw(Rectf{ 0.f, 0.f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight() });

	/*for (std::vector<Vector2f> subCollider : m_Vertices)
		utils::DrawPolygon(subCollider);*/
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


const std::vector<std::vector<Point2f>>& Level::GetPoint2fVertices() const
{
	return m_Point2fVertices;
}
const std::vector<std::vector<Vector2f>>& Level::GetVertices() const
{
	return m_Vertices;
}

// Convert Point2f extracted from level SVG to Vector2f for collision detection
void Level::InitializeVertices()
{
	std::string filePath{ "../Resources/level.svg" };
	SVGParser::GetVerticesFromSvgFile(filePath, m_Point2fVertices);

	for (std::vector<Point2f> subCollider : m_Point2fVertices)
	{
		std::vector<Vector2f> tempVector;
		for (Point2f point : subCollider)
		{
			tempVector.push_back(Vector2f(point));
		}
		m_Vertices.push_back(tempVector);
	}
}
