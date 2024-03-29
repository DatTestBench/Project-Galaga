#include "Core/GameObject.h"
#include "Resources/Texture.h"
#include "Math/Matrix2x3.h"
#include "Core/Game.h"
#include "Helpers/utils.h"
#include "GameLogic/SteeringManager.h"

GameObject::GameObject(const Vector2f& pos, const float width, const float height, Sprite* pSprite)
	: m_Pos{ pos }
	, m_pTexture(nullptr)
	, m_pSprite{ pSprite }
	, m_Width{ width }
	, m_Height{ height }
	, m_DelFlag(false)
	, m_Angle(0)
	, m_Speed(0)
	, m_Acceleration(0)
	, m_MaxSpeed(0)
	, m_Mass(0)
	, m_pGameObjectManager{ GameObjectManager::Get() }
	, m_pSteeringManager{ new SteeringManager{ this } }
	, m_pResourceManager{ ResourceManager::Get() }
	, m_pLevel{ GameObjectManager::Get()->GetLevel() }
	, m_pScoreboard{ Scoreboard::Get() }
{
	m_BaseCollider.emplace_back(- m_Width / 2.f, -m_Height / 2.f);
	m_BaseCollider.emplace_back(m_Width / 2.f, -m_Height / 2.f);
	m_BaseCollider.emplace_back(m_Width / 2.f, m_Height / 2.f);
	m_BaseCollider.emplace_back(- m_Width / 2.f, m_Height / 2.f);
}

GameObject::~GameObject()
{
	delete m_pSteeringManager;
}

#pragma region Workers
// Deleted Draw
// Deleted Update

void GameObject::DoAction(float /*dT*/)
{
}

void GameObject::ToggleAction()
{
}

void GameObject::DoShoot(float /*dT*/)
{
}

void GameObject::ToggleShoot()
{
}

bool GameObject::IsShooting()
{
	return false;
}

void GameObject::HitLevel(const Vector2f& /*dMove*/)
{
}
#pragma endregion Workers

#pragma region Getters
Vector2f GameObject::GetPos() const
{
	return m_Pos;
}

Texture* GameObject::GetTexture() const
{
	return m_pTexture;
}

std::vector<Vector2f> GameObject::GetCollider() const
{
	const Matrix2x3 tMat{ Matrix2x3::CreateTranslationMatrix(m_Pos) };
	const Matrix2x3 rMat{ Matrix2x3::CreateRotationMatrix(utils::ToDeg(GetAngle())) };
	return (tMat * rMat).Transform(m_BaseCollider);
}

float GameObject::GetWidth() const
{
	return m_Width;
}

float GameObject::GetHeight() const
{
	return m_Width;
}

bool GameObject::GetFlag() const
{
	return m_DelFlag;
}

// Possibly deprecated, only used for draw methods, calculate on the fly if neccesairy
float GameObject::GetAngle() const
{
	return m_Angle;
}

float GameObject::GetSpeed() const
{
	//return m_Speed;
	return m_Velocity.Length();
}

float GameObject::GetMaxSpeed() const
{
	return m_MaxSpeed;
}

Vector2f GameObject::GetVelocity() const
{
	//return Vector2f(m_Speed * cos(m_Angle), m_Speed * sin(m_Angle));
	return m_Velocity;
}

float GameObject::GetMass() const
{
	return m_Mass;
}

#pragma endregion Getters

#pragma region Changers
void GameObject::ChangePos(const Vector2f& dMove)
{
	m_Pos += dMove;
}

void GameObject::Delete()
{
	GameObjectManager::Get()->Delete(this);
	m_DelFlag = true;
}

void GameObject::AddWeapon()
{
}

void GameObject::SetVelocity(const Vector2f& vNew)
{
	m_Velocity = vNew;
}

void GameObject::SetAngle(const float angleNew)
{
	m_Angle = angleNew;
}

void GameObject::SetSpeed(const float speedNew)
{
	m_Speed = speedNew;
}

#pragma endregion Changers


#pragma region InternalWorkers

void GameObject::HandleCollision(float /*dT*/)
{
}

void GameObject::HandleLogic(float /*dT*/)
{
}

#pragma endregion InternalWorkers
