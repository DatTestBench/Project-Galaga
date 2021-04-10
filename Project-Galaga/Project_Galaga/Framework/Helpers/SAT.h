#pragma once
#include "Math/Vector2f.h"
#include "Core/GameObject.h"

//Adapted from : https://www.codeproject.com/Articles/15573/2D-Polygon-Collision-Detection
//				 http://www.dyn4j.org/2010/01/sat/
// Structure that stores the results of the PolygonCollision function
struct PolygonCollisionResult
{
	// Are the polygons going to intersect forward in time?
	bool willIntersect;
	// Are the polygons currently intersecting?
	bool intersect;
	// The translation to apply to the first polygon to push the polygons apart.
	Vector2f minimumTranslationVector;
};

namespace sat
{
	PolygonCollisionResult PolygonCollision(GameObject* pGameObjectA, GameObject* pGameObjectB);
	PolygonCollisionResult PolygonCollision(GameObject* pGameObjectA, const std::vector<Vector2f>& staticPoly);
	void ProjectPolygon(const Vector2f& axis, const std::vector<Vector2f>& vertexSet, float& min, float& max);
	float IntervalDistance(float minA, float maxA, float minB, float maxB);
	Vector2f MakeAxis(const Vector2f& vertexA, const Vector2f& vertexB);
}


