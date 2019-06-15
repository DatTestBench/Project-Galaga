#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"

ResourceManager* ResourceManager::m_pResourceManager = nullptr;

ResourceManager::ResourceManager()
	: m_pPlayerText{ new Texture{ "./Resources/Textures/player.png" } }
	, m_pEnemyText{ new Texture { "./Resources/Textures/enemy.png" } }
	, m_pLevelText{ new Texture { "./Resources/Textures/level.png" } }
	, m_pPlayerSprite{ new Sprite { new Texture {"./Resources/Textures/player.png"}, 4, 4 ,4.f } }
	, m_pEnemySprite{ new Sprite { new Texture { "./Resources/Textures/enemy.png"}, 1, 1, 1.f } }

{
}

ResourceManager::~ResourceManager()
{
	// Textures
	if (m_pPlayerText != nullptr)
		delete m_pPlayerText;
	if (m_pEnemyText != nullptr)
		delete m_pEnemyText;
	if (m_pLevelText != nullptr)
		delete m_pLevelText;

	// Sprites
	if (m_pPlayerSprite != nullptr)
		delete m_pPlayerSprite;
	if (m_pEnemySprite != nullptr)
		delete m_pEnemySprite;
}

#pragma region SingletonFunctionality
ResourceManager* ResourceManager::Get()
{
	if (m_pResourceManager == nullptr)
		m_pResourceManager = new ResourceManager();
	return m_pResourceManager;
}

void ResourceManager::Destroy()
{
	delete ResourceManager::Get();
}
#pragma endregion SingletonFunctionality

#pragma region Getters
// Textures
Texture* ResourceManager::GetPlayerTextp()
{

	return m_pPlayerText;
}

Texture* ResourceManager::GetEnemyTextp()
{
	return m_pEnemyText;
}

Texture* ResourceManager::GetLevelTextp()
{
	return m_pLevelText;
}
// Sprites
Sprite* ResourceManager::GetPlayerSpritep()
{
	return m_pPlayerSprite;
}

Sprite* ResourceManager::GetEnemySpritep()
{
	return m_pEnemySprite;
}

#pragma endregion Getters