#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Sprite.h"

TextureManager* TextureManager::m_pTextureManager = nullptr;

TextureManager::TextureManager()
	: m_pPlayerText{ new Texture{ "./Resources/Textures/player.png" } }
	, m_pEnemyText{ new Texture { "./Resources/Textures/enemy.png" } }
	, m_pPlayerSprite{ new Sprite { new Texture {"./Resources/Textures/player.png"}, 4, 4 ,4.f } }
	, m_pEnemySprite{ new Sprite { new Texture { "./Resources/Textures/enemy.png"}, 1, 1, 1.f } }
{
}

TextureManager::~TextureManager()
{
	if (m_pPlayerText != nullptr)
		delete m_pPlayerText;
	if (m_pEnemyText != nullptr)
		delete m_pEnemyText;
	if (m_pPlayerSprite != nullptr)
		delete m_pPlayerSprite;
	if (m_pEnemySprite != nullptr)
		delete m_pEnemySprite;
}

#pragma region SingletonFunctionality
TextureManager* TextureManager::Get()
{
	if (m_pTextureManager == nullptr)
		m_pTextureManager = new TextureManager();
	return m_pTextureManager;
}

void TextureManager::Destroy()
{
	delete TextureManager::Get();
}
#pragma endregion SingletonFunctionality

#pragma region Getters
Texture* TextureManager::GetPlayerTextp()
{

	return m_pPlayerText;
}

Texture* TextureManager::GetEnemyTextp()
{
	return m_pEnemyText;
}

Sprite* TextureManager::GetPlayerSpritep()
{
	return m_pPlayerSprite;
}

Sprite* TextureManager::GetEnemySpritep()
{
	return m_pEnemySprite;
}

#pragma endregion Getters