#pragma once
#include "GameObject.h"


class GameObject;

// SteeringManager

class SteeringManager
{
public:
	SteeringManager(GameObject* host);

	// Public steering functionality
	void Seek(GameObject* pTarget, float slowingRadius = 0);
	void Flee(GameObject* pTarget);
	void Wander(float dT);
	void Evade(GameObject* pTarget);
	void Pursuit(GameObject* pTarget);

	// Update, call after all steering has been done
	void Update(float dT);

	// Reset steering forces
	void Reset();

private:
	/// Member functions
	
	// Internal steering functionality
	
	Vector2f DoSeek(GameObject* pTarget, float slowingRadius = 0);
	Vector2f DoSeek(const Vector2f& targetPos, float slowingRadius = 0);
	Vector2f DoPursuit(GameObject* pTarget);
	Vector2f DoFlee(GameObject* pTarget);
	Vector2f DoFlee(const Vector2f& targetPos);
	Vector2f DoEvade(GameObject* pTarget);
	Vector2f DoWander(float dT);

	// Helper Functions
	void SetAngle(Vector2f& v, float number);
	/// Member variables
	
	GameObject* m_pHost;
	Vector2f m_Steering;
	float m_WanderAngle;
	time_t m_NextWanderDecision;
	Vector2f m_CurrentWanderTarget;
	Vector2f m_LerpWanderTarget;


};