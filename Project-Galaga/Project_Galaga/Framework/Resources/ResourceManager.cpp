#include "Resources/ResourceManager.h"
#include "Resources/Texture.h"
#include "Resources/Sprite.h"
#include <iostream>
#include <ranges>

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
	for (auto texture : m_TextureMap | std::views::values)
	{
		if (texture != nullptr)
			delete texture;
	}

	// Sprites
	for (auto sprite : m_SpriteMap | std::views::values)
	{
		if (sprite != nullptr)
			delete sprite;
	}

	// SoundEffect

	for (auto soundEffect : m_SoundEffectMap | std::views::values)
	{
		if (soundEffect != nullptr)
			delete soundEffect;
	}

	//SoundStream
	for (auto soundStream : m_SoundStreamMap | std::views::values)
	{
		if (soundStream != nullptr)
			delete soundStream;
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
Texture* ResourceManager::GetTexture(const std::string& key)
{
	const std::map<std::string, Texture*>::const_iterator cit = m_TextureMap.find(key);

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
Sprite* ResourceManager::GetSprite(const std::string& key)
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

SoundEffect* ResourceManager::GetSoundEffect(const std::string& key)
{
	const std::map<std::string, SoundEffect*>::const_iterator cit = m_SoundEffectMap.find(key);
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

SoundStream* ResourceManager::GetSoundStream(const std::string& key)
{
	const std::map<std::string, SoundStream*>::const_iterator cit = m_SoundStreamMap.find(key);
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
void ResourceManager::PlaySoundEffect(const std::string& key, const int loops, const int volume)
{
	GetSoundEffect(key)->SetVolume(volume);
	if (!GetSoundEffect(key)->Play(loops))
		std::cout << "Play Failed\n";
}

void ResourceManager::PlaySoundStream(const std::string& key, const bool repeat, const int volume)
{
	GetSoundStream(key)->SetVolume(volume);
	if (GetSoundStream(key)->Play(repeat))
		std::cout << "Play Failed\n";
}
#pragma endregion Players



#pragma region Loaders

void ResourceManager::LoadTextures()
{
	// Syntax: pair<std::string, Texture*>("key", new Texture{ "Path" })
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextPlayer", new Texture{ "../Resources/Textures/TexturePlayer.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextEnemy", new Texture{ "../Resources/Textures/TextureEnemy.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextLevel", new Texture{ "../Resources/Textures/TextureLevel.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextHud", new Texture{ "../Resources/Textures/TextureHud.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextHealthBar", new Texture{ "../Resources/Textures/TextureHealthBar.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextBTNStart", new Texture{ "../Resources/Textures/TextureButtonStart.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextBTNPause", new Texture{ "../Resources/Textures/TextureButtonPause.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextStartScreen", new Texture{ "../Resources/Textures/TextureStartScreen.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextEndScreen", new Texture{ "../Resources/Textures/TextureEndScreen.png" }));
	m_TextureMap.insert(std::make_pair<std::string, Texture*>("TextPauseScreen", new Texture{ "../Resources/Textures/TexturePauseScreen.png "}));
	std::cout << "Loaded Textures" << std::endl;

}

void ResourceManager::LoadSprites()
{
	// Syntax: pair<std::string, Sprite*>("key", new Sprite{ new Texture{ "Path", nrCols, nrRows, nrZones, fps } })
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpritePlayer", new Sprite{ new Texture {"../Resources/Sprites/SpritePlayer.png"}, 4, 2, 2, 4.f }));
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpriteEnemy", new Sprite{ new Texture { "../Resources/Sprites/SpriteEnemy.png"}, 1, 1, 1, 1.f }));
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpriteRusher", new Sprite{ new Texture{ "../Resources/Sprites/SpriteRusher.png" }, 4,3,1, 4.f }));
	m_SpriteMap.insert(std::make_pair<std::string, Sprite*>("SpriteExhaust", new Sprite{ new Texture{ "../Resources/Sprites/SpriteExhaust.png"}, 5, 1, 1, 4.f}));

	std::cout << "Loaded Sprites" << std::endl;
}

void ResourceManager::LoadSoundEffects()
{
	// Syntax: pair<std::string, SoundEffect*>("key", new SoundEffect{ "Path" })
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SERocket", new SoundEffect{ "../Resources/Sounds/SoundEffectRocket.mp3" }));
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SEBullet", new SoundEffect{ "../Resources/Sounds/SoundEffectBullet.mp3" }));
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SEPellet", new SoundEffect{ "../Resources/Sounds/SoundEffectPellet.mp3" }));
	m_SoundEffectMap.insert(std::make_pair<std::string, SoundEffect*>("SEButton", new SoundEffect{ "../Resources/Sounds/SoundEffectButton.mp3" }));
	std::cout << "Loaded SoundEffects" << std::endl;
}

void ResourceManager::LoadSoundStream()
{
	// Syntax: pair<std::string, SoundStream*>("key", new SoundStream{ "Path" })
	m_SoundStreamMap.insert(std::make_pair<std::string, SoundStream*>("SSBackground", new SoundStream{ "../Resources/Sounds/SoundStreamBackground.wav" }));
}
#pragma endregion Loaders