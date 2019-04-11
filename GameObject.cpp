#include "pch.h"
#include "GameObject.h"
#include "Texture.h"
#include "Matrix2x3.h"
#include "structs.h"
#include "Game.h"

GameObject::GameObject(const Point2f& pos, float width, float height, Texture* pTexture)
	: m_Pos{ pos }
	, m_pTexture{ pTexture }
	, m_Width{ width  }
	, m_Height { height }
{
	
	m_BaseCollider.push_back(Point2f{ - m_Width / 2.f,  -m_Height / 2.f });
	m_BaseCollider.push_back(Point2f{ m_Width / 2.f, -m_Height / 2.f });
	m_BaseCollider.push_back(Point2f{ m_Width / 2.f, m_Height / 2.f });
	m_BaseCollider.push_back(Point2f{ - m_Width / 2.f, m_Height / 2.f });
	
	m_Collider.resize(m_BaseCollider.size());
}

GameObject::~GameObject()
{
	if (m_pTexture != nullptr)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

bool GameObject::IsOnscreen() const
{
	return m_Onscreen;
}

Point2f GameObject::GetPos() const
{
	return m_Pos;
}

void GameObject::ChangePos(const Vector2f& dMove)
{
	m_Pos += dMove;
}


float GameObject::GetWidth() const
{
	return m_pTexture->GetWidth();
}

float GameObject::GetHeight() const
{
	return m_pTexture->GetHeight();
}

std::vector<Point2f> GameObject::GetCollider() const
{
	Matrix2x3 tMat{ Matrix2x3::CreateTranslationMatrix(m_Pos.x, m_Pos.y) };
	return std::vector<Point2f>{tMat.Transform(m_BaseCollider)};
}

Texture* GameObject::GetpTexture()
{
	return m_pTexture;
}

bool GameObject::IsDeleted() const
{
	return m_Deleted;
}

void GameObject::Delete()
{
	GameObjectManager::Get()->Delete(this);
	m_DelFlag = true;
}

bool GameObject::GetFlag()
{
	return m_DelFlag;
}