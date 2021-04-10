#pragma once
#include "Core/GameObject.h"


class GameObject;

// SteeringManager

class SteeringManager
{
public:
	explicit SteeringManager(GameObject* host);

	// Public steering functionality
	void Seek(GameObject* pTarget, float slowingRadius = 0);
	void Pursuit(GameObject* pTarget);
	void Flee(GameObject* pTarget);
	void Evade(GameObject* pTarget);
	void Wander(float dT);
	void CollisionEvade(const std::vector<std::vector<Point2f>>& vertices);
	void Goto(const Vector2f& destPoint);

	void Spin(const Vector2f& rotCenter, float radius);
	// Update, call after all steering has been done
	void Update(float dT);

	// Reset steering forces
	void Reset();

private:
	/// Member variables

	GameObject* m_pHost;
	Vector2f m_Steering;
	float m_WanderAngle;
	time_t m_NextWanderDecision;
	Vector2f m_CurrentWanderTarget;
	Vector2f m_LerpWanderTarget;
	Vector2f m_RotationCenter;
	float m_RotationAngle;

	/// Member functions

	// Internal steering functionality

	Vector2f DoSeek(GameObject* pTarget, float slowingRadius = 0);
	Vector2f DoSeek(const Vector2f& targetPos, float slowingRadius = 0);
	Vector2f DoPursuit(GameObject* pTarget);
	Vector2f DoFlee(GameObject* pTarget);
	Vector2f DoFlee(const Vector2f& targetPos);
	Vector2f DoEvade(GameObject* pTarget);
	Vector2f DoWander(float dT);
	Vector2f DoCollisionEvade(const std::vector<std::vector<Point2f>>& vertices);
	Vector2f DoSpin(const Vector2f& rotCenter, float radius);
	// Helper Functions
	void SetAngle(Vector2f& v, float number) const;
	std::pair<std::vector<Point2f>, Point2f> FindMostThreateningObstacle(const std::vector<std::vector<Point2f>>& vertices, const Vector2f& ahead) const;
};
