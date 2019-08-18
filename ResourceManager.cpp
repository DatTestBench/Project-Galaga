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
		//std::cout << "Texture: " << key << " loaded" << std::endl;
		return cit->second;
	}
	else
	{
		//std::cout << "Texture: " << key << " was not found" << std::endl;
	}
	return nullptr;
}


// Sprites
Sprite* ResourceManager::GetSpritep(const std::string& key)
{
	std::map<std::string, Sprite*>::const_iterator cit = m_SpriteMap.find(key);

	if (cit != m_SpriteMap.cend())
	{
		//std::cout << "Sprite: " << key << " loaded" << std::endl;
		return cit->second;
	}
	else
	{
		//std::cout << "Sprite: " << key << " was not found" << std::endl;
	}
	return nullptr;
}

// SoundEffect

SoundEffect* ResourceManager::GetSoundEffectp(const std::string& key)
{
	std::map<std::string, SoundEffect*>::const_iterator cit = m_SoundEffectMap.find(key);
	if (cit != m_SoundEffectMap.cend())
	{
		//std::cout << "SoundEffect: " << key << " loaded" << std::endl;
		return cit->second;
	}
	else
	{
		//std::cout << "SoundEffect: " << key << " was not found" << std::endl;
		return nullptr;
	}
}

// SoundStream

SoundStream* ResourceManager::GetSoundStreamp(const std::string& key)
{
	std::map<std::string, SoundStream*>::const_iterator cit = m_SoundStreamMap.find(key);
	if (cit != m_SoundStreamMap.cend())
	{
		//std::cout << "SoundEffect: " << key << " loaded" << std::endl;
		return cit->second;
	}
	else
	{
		//std::cout << "SoundEffect: " << key << " was not found" << std::endl;
		return nullptr;
	}
}

#pragma endregion Getters

#pragma region Players
// SoundEffect
void ResourceManager::PlaySoundEffect(const std::string& key, int loops, int volume)
{
	GetSoundEffectp(key)->SetVolume(volume);
	GetSoundEffectp(key)->Play(loops);
}

void ResourceManager::PlaySoundStream(const std::string& key, bool repeat, int volume)
{
	GetSoundStreamp(key)->SetVolume(volume);
	GetSoundStreamp(key)->Play(repeat);
}
#pragma endregion Players



#pragma region Loaders

void ResourceManager::LoadTextures()
{
	// Syntax: pair<std::string, Texture*>("key", new Texture{ "Path" })
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextPlayer", new Texture{ "./Resources/Textures/TexturePlayer.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextEnemy", new Texture{ "./Resources/Textures/TextureEnemy.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextLevel", new Texture{ "./Resources/Textures/TextureLevel.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextHud", new Texture{ "./Resources/Textures/TextureHud.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextHealthBar", new Texture{ "./Resources/Textures/TextureHealthBar.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextBTNStart", new Texture{ "./Resources/Textures/TextureButtonStart.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextBTNPause", new Texture{ "./Resources/Textures/TextureButtonPause.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextStartScreen", new Texture{ "./Resources/Textures/TextureStartScreen.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextEndScreen", new Texture{ "./Resources/Textures/TextureEndScreen.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextPauseScreen", new Texture{ "./Resources/Textures/TexturePauseScreen.png "}));
	std::cout << "Loaded Textures" << std::endl;

}

void ResourceManager::LoadSprites()
{
	// Syntax: pair<std::string, Sprite*>("key", new Sprite{ new Texture{ "Path", nrCols, nrRows, nrZones, fps } })
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpritePlayer", new Sprite{ new Texture {"./Resources/Sprites/SpritePlayer.png"}, 4, 2, 2, 4.f }));
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpriteEnemy", new Sprite{ new Texture { "./Resources/Sprites/SpriteEnemy.png"}, 1, 1, 1, 1.f }));
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpriteRusher", new Sprite{ new Texture{ "./Resources/Sprites/SpriteRusher.png" }, 4,3,1, 4.f }));
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpriteExhaust", new Sprite{ new Texture{ "./Resources/Sprites/SpriteExhaust.png"}, 5, 1, 1, 4.f}));

	std::cout << "Loaded Sprites" << std::endl;
}

void ResourceManager::LoadSoundEffects()
{
	// Syntax: pair<std::string, SoundEffect*>("key", new SoundEffect{ "Path" })
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SERocket", new SoundEffect{ "./Resources/Sounds/SoundEffectRocket.mp3" }));
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SEBullet", new SoundEffect{ "./Resources/Sounds/SoundEffectBullet.mp3" }));
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SEPellet", new SoundEffect{ "./Resources/Sounds/SoundEffectPellet.mp3" }));
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SEButton", new SoundEffect{ "./Resources/Sounds/SoundEffectButton.mp3" }));
	std::cout << "Loaded SoundEffects" << std::endl;
}

void ResourceManager::LoadSoundStream()
{
	// Syntax: pair<std::string, SoundStream*>("key", new SoundStream{ "Path" })
	m_SoundStreamMap.insert(std::make_pair<std::string, SoundStream*>("SSBackground", new SoundStream{ "./Resources/Sounds/SoundStreamBackground.wav" }));
}
#pragma endregion Loaders