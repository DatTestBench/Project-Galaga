#include "pch.h"
#include "GameObject.h"
#include "Texture.h"
#include "Matrix2x3.h"
#include "structs.h"
#include "Game.h"
#include "utils.h"

GameObject::GameObject(const Vector2f& pos, float width, float height, Texture* pTexture)
	: m_Pos{ pos }
	, m_pTexture{ pTexture }
	, m_Width{ width  }
	, m_Height { height }
	, m_pGameObjectMananger { GameObjectManager::Get() }
{
	m_BaseCollider.push_back(Vector2f{ - m_Width / 2.f,  -m_Height / 2.f });
	m_BaseCollider.push_back(Vector2f{ m_Width / 2.f, -m_Height / 2.f });
	m_BaseCollider.push_back(Vector2f{ m_Width / 2.f, m_Height / 2.f });
	m_BaseCollider.push_back(Vector2f{ - m_Width / 2.f, m_Height / 2.f });
}

GameObject::~GameObject()
{

}

// Deleted Draw
// Deleted Update

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
	return m_pTexture->GetWidth();
}

float GameObject::GetHeight() const
{
	return m_pTexture->GetHeight();
}

bool GameObject::GetFlag() const
{
	return m_DelFlag;
}

float GameObject::GetAngle() const
{
	return m_Angle;
}

float GameObject::GetSpeed() const
{
	return m_Speed;
}

Vector2f GameObject::GetVelocity() const
{
	return Vector2f(m_Speed * cos(m_Angle), m_Speed * sin(m_Angle));
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
#pragma endregion Changers


#pragma region InternalWorkers

void GameObject::HandleCollision(float dT) // Temporary declaration, remove when fully implemented ToDo
{

}

#pragma endregion InternalWorkers


