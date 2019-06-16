#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include <iostream>
ResourceManager* ResourceManager::m_pResourceManager = nullptr;

ResourceManager::ResourceManager()
{
	LoadTextures();
	LoadSprites();
	LoadSoundEffects();
	LoadSoundStream();
}

ResourceManager::~ResourceManager()
{
	// Textures
	for (const std::pair<std::string, Texture*>& textPair : m_TextureMap)
	{
		if (textPair.second != nullptr)
			delete textPair.second;
	}

	// Sprites
	for (const std::pair<std::string, Sprite*>& spritePair : m_SpriteMap)
	{
		if (spritePair.second != nullptr)
			delete spritePair.second;
	}

	// SoundEffect

	for (const std::pair<std::string, SoundEffect*>& soundEffectPair : m_SoundEffectMap)
	{
		if (soundEffectPair.second != nullptr)
			delete soundEffectPair.second;
	}

	//SoundStream
	for (const std::pair<std::string, SoundStream*>& soundStreamPair : m_SoundStreamMap)
	{
		if (soundStreamPair.second != nullptr)
			delete soundStreamPair.second;
	}

}

#pragma region SingletonFunctionality
ResourceManager* ResourceManager::Get()
{
	if (m_pResourceManager == nullptr)
	{
		m_pResourceManager = new ResourceManager();
		std::cout << "ResourceManager loaded" << std::endl;
	}
	return m_pResourceManager;
}

void ResourceManager::Destroy()
{
	delete ResourceManager::Get();
}
#pragma endregion SingletonFunctionality

#pragma region Getters
// Textures
Texture* ResourceManager::GetTexturep(const std::string& key)
{
	std::map<std::string, Texture*>::const_iterator cit = m_TextureMap.find(key);

	if (cit != m_TextureMap.cend())
	{
		std::cout << "Texture: " << key << " loaded" << std::endl;
		return cit->second;
	}
	else
	{
		std::cout << "Texture: " << key << " was not found" << std::endl;
	}
	return nullptr;
}

// Sprites
Sprite* ResourceManager::GetSpritep(const std::string& key)
{
	std::map<std::string, Sprite*>::const_iterator cit = m_SpriteMap.find(key);

	if (cit != m_SpriteMap.cend())
	{
		std::cout << "Sprite: " << key << " loaded" << std::endl;
		return cit->second;
	}
	else
	{
		std::cout << "Sprite: " << key << " was not found" << std::endl;
	}
	return nullptr;
}

// SoundEffect

SoundEffect* ResourceManager::GetSoundEffectp(const std::string& key)
{
	std::map<std::string, SoundEffect*>::const_iterator cit = m_SoundEffectMap.find(key);
	if (cit != m_SoundEffectMap.cend())
	{
		std::cout << "SoundEffect: " << key << " loaded" << std::endl;
		return cit->second;
	}
	else
	{
		std::cout << "SoundEffect: " << key << " was not found" << std::endl;
	}
	return nullptr;
}

// SoundStream


#pragma endregion Getters

#pragma region Loaders

void ResourceManager::LoadTextures()
{
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextPlayer", new Texture{ "./Resources/Textures/TexturePlayer.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextEnemy", new Texture{ "./Resources/Textures/TextureEnemy.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextLevel", new Texture{ "./Resources/Textures/TextureLevel.png" }));


	std::cout << "Loaded Textures" << std::endl;

}

void ResourceManager::LoadSprites()
{
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpritePlayer", new Sprite{ new Texture {"./Resources/Sprites/SpritePlayer.png"}, 4, 4 ,4.f }));
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpriteEnemy", new Sprite{ new Texture { "./Resources/Sprites/SpriteEnemy.png"}, 1, 1, 1.f }));

	
	std::cout << "Loaded Sprites" << std::endl;
}

void ResourceManager::LoadSoundEffects()
{
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SERocket", new SoundEffect{ "./Resources/Sounds/SoundEffectRocket.mp3" }));
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SEGun", new SoundEffect{ "./Resources/Sounds/SoundEffectGun.mp3" }));
}

void ResourceManager::LoadSoundStream()
{

}

#pragma endregion Loaders