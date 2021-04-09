#include "pch.h"
#include "GameObject.h"
#include "Texture.h"
#include "Matrix2x3.h"
#include "structs.h"
#include "Game.h"
#include "utils.h"
#include "SteeringManager.h"
GameObject::GameObject(const Vector2f& pos, float width, float height, Sprite* pSprite)
	: m_Pos{ pos }
	, m_pSprite { pSprite }
	, m_Width{ width  }
	, m_Height{ height }
	, m_pGameObjectManager { GameObjectManager::Get() }
	, m_pSteeringManager { new SteeringManager { this } }
	, m_pResourceManager { ResourceManager::Get() }
	, m_pLevel{ GameObjectManager::Get()->GetLevel() }
	, m_pScoreboard{ Scoreboard::Get() }
{
	m_BaseCollider.push_back(Vector2f{ - m_Width / 2.f,  -m_Height / 2.f });
	m_BaseCollider.push_back(Vector2f{ m_Width / 2.f, -m_Height / 2.f });
	m_BaseCollider.push_back(Vector2f{ m_Width / 2.f, m_Height / 2.f });
	m_BaseCollider.push_back(Vector2f{ - m_Width / 2.f, m_Height / 2.f });
}

GameObject::~GameObject()
{
	delete m_pSteeringManager;	
}

#pragma region Workers
// Deleted Draw
// Deleted Update

void GameObject::DoAction(float dT)
{}

void GameObject::ToggleAction()
{}

void GameObject::DoShoot(float dT)
{}

void GameObject::ToggleShoot()
{}

bool GameObject::IsShooting()
{
	return false;
}

void GameObject::HitLevel(const Vector2f& dMove)
{}
#pragma endregion Workers

#pragma region Getters
Vector2f GameObject::GetPos() const
{
	return m_Pos;
}

Texture* GameObject::GetpTexture() const
{
	return m_pTexture;
}

std::vector<Vector2f> GameObject::GetCollider() const
{
	Matrix2x3 tMat { Matrix2x3::CreateTranslationMatrix(m_Pos) };
	Matrix2x3 rMat{ Matrix2x3::CreateRotationMatrix(utils::ToDeg(GetAngle())) };
	return (tMat*rMat).Transform(m_BaseCollider);
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
{}

void GameObject::SetVelocity(const Vector2f& vNew)
{
	m_Velocity = vNew;
}

void GameObject::SetAngle(float angleNew)
{
	m_Angle = angleNew;
}

void GameObject::SetSpeed(float speedNew)
{
	m_Speed = speedNew;
}

#pragma endregion Changers


#pragma region InternalWorkers

void GameObject::HandleCollision(float dT)
{}

void GameObject::HandleLogic(float dT)
{}

#pragma endregion InternalWorkers


