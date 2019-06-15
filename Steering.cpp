#include "pch.h"
#include "Steering.h"
#include "GameObject.h"
#include "Vector2f.h"
#include "utils.h"
#include <chrono>
SteeringManager::SteeringManager(GameObject* host)
	: m_pHost{ host }
	, m_Steering{ Vector2f { 0, 0 } }
	, m_WanderAngle{ utils::g_Pi / 6.f }
	, m_CurrentWanderTarget { host->GetPos() + host->GetVelocity()}
{}

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

	/*
		Vector2f velocity{ m_pHost->GetVelocity().Normalized() };
		std::cout << "v1 " << velocity << ' ';
		velocity += m_Steering.Normalized();
		std::cout << "steer " << m_Steering << ' ';

		velocity = utils::lerp(velocity, velocity * m_pHost->GetMaxSpeed(), dT, m_pHost->GetMass());
		//velocity *= m_pHost->GetMaxSpeed();
		std::cout << "v2 " << velocity << std::endl;

		m_pHost->SetVelocity(velocity);
		m_pHost->ChangePos(velocity * dT);*/
}

void SteeringManager::Reset()
{
	m_Steering = Vector2f(0, 0);
}

#pragma region PublicSteeringFunctionality

void SteeringManager::Seek(GameObject* pTarget, float slowingRadius)
{
	if (pTarget != nullptr)
		m_Steering += DoSeek(pTarget, slowingRadius);
}
void SteeringManager::Flee(GameObject* pTarget)
{
	if (pTarget != nullptr)
		m_Steering += DoFlee(pTarget);
}
void SteeringManager::Wander(float dT)
{
	m_Steering += DoWander(dT);
}
void SteeringManager::Evade(GameObject* pTarget)
{
	if (pTarget != nullptr)
		m_Steering += DoEvade(pTarget);
}
void SteeringManager::Pursuit(GameObject* pTarget)
{
	if (pTarget != nullptr)
		m_Steering += DoPursuit(pTarget);
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
		float targetAngle{ utils::RandFloat(0, 2 * utils::g_Pi) };
		std::cout << targetAngle << std::endl;
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
#pragma endregion InternalSteeringFunctionality

#pragma region HelperFunctions
void SteeringManager::SetAngle(Vector2f& v, float number)
{
	float len = v.Length();
	v.x = cos(number) * len;
	v.y = sin(number) * len;
}

#pragma endregion HelperFunctions 