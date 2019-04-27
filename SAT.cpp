#include "pch.h"
#include "SAT.h"
#include <vector>
#include "GameObject.h"
#include "utils.h"

/// SAT V2
PolygonCollisionResult sat::PolygonCollision(GameObject* pGameObjectA, GameObject* pGameObjectB)
{
	Vector2f dVelocity{ pGameObjectA->GetVelocity() - pGameObjectB->GetVelocity() };

	PolygonCollisionResult result{};
	result.Intersect = true;
	result.WillIntersect = true;

	std::vector<Point2f>vertexSetA{ pGameObjectA->GetCollider() };
	std::vector<Point2f>vertexSetB{ pGameObjectB->GetCollider() };
	size_t vertexCountA{ vertexSetA.size() };
	size_t vertexCountB{ vertexSetB.size() };
	float minIntervalDistance{ std::numeric_limits<float>::infinity() };
	Vector2f translationAxis{};
	Point2f vertex{};
	Point2f nextVertex{};

	// Loop through all the vertecis of both polygons
	for (size_t vertexIndex = 0; vertexIndex < vertexCountA + vertexCountB; vertexIndex++) 
	{
		if (vertexIndex < vertexCountA)
		{
			vertex = Point2f{ vertexSetA[vertexIndex] };
			nextVertex = Point2f{vertexSetA[vertexIndex + 1 == vertexCountA ? 0 : vertexIndex + 1] };
		}
		else
		{
			vertex = Point2f{ vertexSetB[vertexIndex - vertexCountA] };
			nextVertex = Point2f{ vertexSetB[vertexIndex - vertexCountA + 1 == vertexCountA ? 0 : vertexIndex - vertexCountA + 1] };
		}

		// ===== 1. Find if the polygons are currently intersecting =====

		// Find the axis perpendicular to the current edge
		Vector2f axis = MakeAxis(vertex, nextVertex);

		// Find the projection of the polygon on the current axis
		float minA{ 0 }, minB{ 0 }, maxA{ 0 }, maxB{ 0 };
		ProjectPolygon(axis, vertexSetA, minA, maxA);
		ProjectPolygon(axis, vertexSetB, minB, maxB);

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
			result.Intersect = false;

		// ===== 2. Now find if the polygons *will* intersect =====

		// Project the velocity on the current axis
		float velocityProjection{ axis.DotProduct(dVelocity) };

		// Get the projection of polygon A during the movement
		if (velocityProjection < 0)
		{
			minA += velocityProjection;
		}
		else
		{
			maxA += velocityProjection;
		}

		// Do the same test as above for the new projection
		float intervalDistance = IntervalDistance(minA, maxA, minB, maxB);
		if (intervalDistance > 0)
			result.WillIntersect = false;

		// If the polygons are not intersecting and won't intersect, exit the loop
		if (!result.Intersect && !result.WillIntersect)
			break;

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		intervalDistance = abs(intervalDistance);
		if (intervalDistance < minIntervalDistance)
		{
			minIntervalDistance = intervalDistance;
			translationAxis = axis;

			Vector2f d = pGameObjectA->GetPos() - pGameObjectB->GetPos();
			if (d.DotProduct(translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons appart.
	if (result.WillIntersect)
		result.MinimumTranslationVector = translationAxis * minIntervalDistance;

	return result;
}

void sat::ProjectPolygon(Vector2f axis, const std::vector<Point2f>& vertexSet, float& min, float& max)
{
	// To project a point on an axis use the dot product
	float dotProduct = axis.DotProduct(Vector2f(vertexSet[0]));
	min = dotProduct;
	max = dotProduct;
	for (int i = 0; i < vertexSet.size(); i++)
	{
		dotProduct = Vector2f(vertexSet[i]).DotProduct(axis);
		//dotProduct = axis.DotProduct(Vector2f(pGameObject->GetCollider()[i]));
		if (dotProduct < min)
			min = dotProduct;
		else if (dotProduct > max)
			max = dotProduct;
	}
}

float sat::IntervalDistance(float minA, float maxA, float minB, float maxB)
{
	if (minA < minB)
		return minB - maxA;
	else
		return minA - maxB;
}

Vector2f sat::MakeAxis(Point2f vertexA, Point2f vertexB)
{
	// Get edge
	Vector2f edge{ vertexA, vertexB };
	// get either perpendicular vector
	Vector2f normal{ edge.Orthogonal() };
	//return normalized
	return normal.Normalized();
}
