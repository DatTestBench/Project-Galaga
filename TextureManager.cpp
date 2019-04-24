#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

TextureManager* TextureManager::m_pTextureManager = nullptr;

TextureManager::TextureManager()
	: m_pPlayerText{ new Texture{ "./Resources/Textures/player.png" } }
	, m_pEnemyText{ new Texture { "./Resources/Textures/enemy.png" } }
{
}

TextureManager::~TextureManager()
{
	if (m_pPlayerText != nullptr)
		delete m_pPlayerText;
	if (m_pEnemyText != nullptr)
		delete m_pEnemyText;
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
#pragma endregion Getters