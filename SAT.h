#pragma once
#include "Vector2f.h"
#include "GameObject.h"


/// SAT V2
//Adapted from : https://www.codeproject.com/Articles/15573/2D-Polygon-Collision-Detection
//				 http://www.dyn4j.org/2010/01/sat/
// Structure that stores the results of the PolygonCollision function
struct PolygonCollisionResult
{
	// Are the polygons going to intersect forward in time?
	bool WillIntersect;
	// Are the polygons currently intersecting?
	bool Intersect;
	// The translation to apply to the first polygon to push the polygons apart.
	Vector2f MinimumTranslationVector;
};
namespace sat
{

	PolygonCollisionResult PolygonCollision(GameObject* pGameObjectA, GameObject* pGameObjectB);
	void ProjectPolygon(Vector2f axis, const std::vector<Point2f>& vertexSet, float& min, float& max);
	float IntervalDistance(float minA, float maxA, float minB, float maxB);
	Vector2f MakeAxis(Point2f vertexA, Point2f vertexB);
}


