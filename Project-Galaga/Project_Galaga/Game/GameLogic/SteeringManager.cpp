#include "GameLogic/SteeringManager.h"
#include "Core/GameObject.h"
#include "Math/Vector2f.h"
#include "Helpers/utils.h"
#include <chrono>
#include <map>
SteeringManager::SteeringManager(GameObject* host)
	: m_pHost{ host }
	, m_Steering{ Vector2f{ 0, 0 } }
	, m_WanderAngle{ utils::g_Pi / 6.f }
	, m_NextWanderDecision(0)
	, m_CurrentWanderTarget{ host->GetPos() + host->GetVelocity() }
	, m_RotationAngle{ 0 }
{
}

void SteeringManager::Update(float dT)
{
	Vector2f velocity{ m_pHost->GetVelocity() };
	Vector2f pos{ m_pHost->GetPos() };
	float maxForce = m_pHost->GetMass() * (velocity.Length() / dT);
	//std::cout << maxForce << std::endl;

	if (maxForce > 0)
		m_Steering = utils::Truncate(m_Steering, maxForce);
	m_Steering *= 1.f / m_pHost->GetMass();

	velocity += m_Steering;
	velocity = utils::Truncate(velocity, m_pHost->GetMaxSpeed());

	m_pHost->SetVelocity(velocity);
	m_pHost->SetAngle(atan2(velocity.y, velocity.x));
	m_pHost->ChangePos(velocity.Normalized() * m_pHost->GetMaxSpeed() * dT);
}

void SteeringManager::Reset()
{
	m_Steering = Vector2f(0, 0);
}

#pragma region PublicSteeringFunctionality

void SteeringManager::Seek(GameObject* pTarget, float slowingRadius)
{
	if (pTarget != nullptr)
	{
		m_Steering += DoSeek(pTarget, slowingRadius);
	}
}
void SteeringManager::Pursuit(GameObject* pTarget)
{
	if (pTarget != nullptr)
	{
		m_Steering += DoPursuit(pTarget);
	}
}

void SteeringManager::Flee(GameObject* pTarget)
{
	if (pTarget != nullptr)
	{
		m_Steering += DoFlee(pTarget);
	}
}
void SteeringManager::Evade(GameObject* pTarget)
{
	if (pTarget != nullptr)
	{
		m_Steering += DoEvade(pTarget);
	}
}

void SteeringManager::Wander(float dT)
{
	m_Steering += DoWander(dT);
}

void SteeringManager::CollisionEvade(const std::vector<std::vector<Point2f>>& vertices)
{
	m_Steering += DoCollisionEvade(vertices);
}

void SteeringManager::Goto(const Vector2f& destPoint)
{
	m_Steering += DoSeek(destPoint);
}

void SteeringManager::Spin(const Vector2f& rotCenter, float radius)
{
	m_Steering += DoSpin(rotCenter, radius);
}
#pragma endregion PublicSteeringFunctionality


#pragma region InternalSteeringFunctionality

Vector2f SteeringManager::DoSeek(GameObject* pTarget, float slowingRadius)
{
	return DoSeek(pTarget->GetPos(), slowingRadius);
}

Vector2f SteeringManager::DoSeek(const Vector2f& targetPos, float slowingRadius)
{
	Vector2f vForce{ 0, 0 };
	Vector2f vDesired{ 0, 0 };
	float distance{  };

	vDesired = targetPos - m_pHost->GetPos();
	distance = vDesired.Length();
	vDesired = vDesired.Normalized();

	if (distance <= slowingRadius && slowingRadius > 0)
	{
		vDesired *= (m_pHost->GetMaxSpeed() * distance / slowingRadius);
	}
	else
	{
		vDesired *= m_pHost->GetMaxSpeed();
	}

	vForce = vDesired - m_pHost->GetVelocity();

	return vForce;
}

Vector2f SteeringManager::DoPursuit(GameObject* pTarget)
{
	float distance{  };
	float updatesNeeded{  };
	Vector2f targetFuturePos{ 0, 0 };

	distance = utils::DistPointPoint(pTarget->GetPos(), m_pHost->GetPos());

	updatesNeeded = distance / m_pHost->GetMaxSpeed();

	targetFuturePos = pTarget->GetPos() + pTarget->GetVelocity() * updatesNeeded;

	return DoSeek(targetFuturePos);
}


Vector2f SteeringManager::DoFlee(GameObject* pTarget)
{
	return DoFlee(pTarget->GetPos());
}

Vector2f SteeringManager::DoFlee(const Vector2f& targetPos)
{
	Vector2f vForce{ 0, 0 };
	Vector2f vDesired{ 0, 0 };

	vDesired = m_pHost->GetPos() - targetPos;
	vDesired = vDesired.Normalized();
	vDesired *= m_pHost->GetMaxSpeed();

	vForce = vDesired - m_pHost->GetVelocity();

	return vForce;
}

Vector2f SteeringManager::DoEvade(GameObject* pTarget)
{
	float distance{  };
	float updatesNeeded{  };
	Vector2f targetFuturePos{ 0, 0 };

	distance = utils::DistPointPoint(pTarget->GetPos(), m_pHost->GetPos());

	updatesNeeded = distance / m_pHost->GetMaxSpeed();

	targetFuturePos = pTarget->GetPos() + pTarget->GetVelocity() * updatesNeeded;

	return DoFlee(targetFuturePos);
}


Vector2f SteeringManager::DoWander(float dT)
{
	time_t now = time(nullptr);


	if (now >= m_NextWanderDecision)
	{
		// Get random target position
		//float targetAngle{ utils::RandFloat(m_pHost->GetAngle() - utils::g_Pi / 4.f, m_pHost->GetAngle() + utils::g_Pi / 4.f) };
		float targetAngle{ utils::RandFloat(0, utils::g_Pi * 2) };
		//std::cout << targetAngle << std::endl;
		//float targetDist{ utils::RandFloat(m_pHost->GetVelocity().Length() / 2.f, m_pHost->GetVelocity().Length() * 2) };
		float targetDist{ 500 };
		Vector2f dTargetPos{ targetDist * cos(targetAngle), targetDist * sin(targetAngle) };

		m_CurrentWanderTarget = m_pHost->GetPos() + dTargetPos;

		m_NextWanderDecision = now + 1;
	}

	m_LerpWanderTarget = utils::lerp(m_LerpWanderTarget, m_CurrentWanderTarget, dT, 1);



	return DoSeek(m_LerpWanderTarget);

	/// Alternative wander implementation, needs a lot of work to function properly
	/*
	const float circleDistance { 50 };
	const float circleRadius { 25 };
	// Calculate the circle center
	Vector2f circleCenter { 0, 0 };
	circleCenter = m_pHost->GetVelocity();
	circleCenter = circleCenter.Normalized();
	circleCenter *= circleDistance;

	// Calculate the displacement force
	Vector2f dMove { 0, -1 };
	dMove *= circleRadius;

	// Randomly change vector direction by changing angle
	SetAngle(dMove, m_WanderAngle);

	// Change wander angle so the value won't be the same the next frame
	m_WanderAngle += utils::RandFloat(-1, 1);

	// Calculate and return the wander force
	Vector2f wanderForce { 0, 0 };
	wanderForce = circleCenter + dMove;
	return wanderForce;
	*/
}

Vector2f SteeringManager::DoCollisionEvade(const std::vector<std::vector<Point2f>>& vertices)
{
	Vector2f ahead{ m_pHost->GetVelocity() * 3};
	Vector2f vAvoidance{ 0, 0 };

	std::pair<std::vector<Point2f>, Point2f> mostThreateningObstacle{ FindMostThreateningObstacle(vertices, ahead) };

	if (mostThreateningObstacle.first.size() > 0)
	{
		//vAvoidance = DoFlee(Vector2f(mostThreateningObstacle.second));
		vAvoidance.x = m_pHost->GetPos().x - mostThreateningObstacle.second.x;
		vAvoidance.y = m_pHost->GetPos().y - mostThreateningObstacle.second.y;

		//vAvoidance = Vector2f(vAvoidance.Normalized() * 50 * cos(utils::g_Pi / 2.f), vAvoidance.Normalized() * 50 * sin(utils::g_Pi / 2.f));
		//std::cout << vAvoidance << std::endl;
		
	}
	return vAvoidance;
}

Vector2f SteeringManager::DoSpin(const Vector2f& rotCenter, float radius)
{

	Vector2f v{ rotCenter, m_pHost->GetPos() };
	SetAngle(v, m_RotationAngle);

	m_RotationAngle += utils::g_Pi / 24;

	m_RotationAngle = m_RotationAngle < 0 ? m_RotationAngle + 2 * utils::g_Pi : m_RotationAngle;
	m_RotationAngle = m_RotationAngle > 2 * utils::g_Pi ? m_RotationAngle - 2 * utils::g_Pi : m_RotationAngle;

	//std::cout << (v.Normalized() * radius).Length() << std::endl;
	return DoSeek(v.Normalized() * radius + rotCenter);
	
	//return DoSeek(v + rotCenter);
}
#pragma endregion InternalSteeringFunctionality

#pragma region HelperFunctions
void SteeringManager::SetAngle(Vector2f& v, float number)
{
	float len = v.Length();
	v.x = cos(number) * len;
	v.y = sin(number) * len;
}

std::pair<std::vector<Point2f>, Point2f> SteeringManager::FindMostThreateningObstacle(const std::vector<std::vector<Point2f>>& vertices, const Vector2f& ahead)
{
	utils::HitInfo hitInfo;
	std::vector<Point2f> mostThreateningObstacle{  };
	float closestObstacleIntersectDist{ std::numeric_limits<float>::infinity() };
	for (const std::vector<Point2f>& vertexSet : vertices)
	{
		if (utils::Raycast(vertexSet, m_pHost->GetPos().ToPoint2f(), (m_pHost->GetPos() + ahead).ToPoint2f(), hitInfo) && closestObstacleIntersectDist > utils::DistPointPoint(m_pHost->GetPos(), Vector2f(hitInfo.intersectPoint)))
		{
			//std::cout << "hit" << std::endl;
			mostThreateningObstacle = vertexSet;
			closestObstacleIntersectDist = utils::DistPointPoint(m_pHost->GetPos(), Vector2f(hitInfo.intersectPoint));
		}
	}
	return std::pair<std::vector<Point2f>, Point2f> {mostThreateningObstacle, hitInfo.intersectPoint};
}
#pragma endregion HelperFunctions 