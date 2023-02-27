#pragma once
#include "Resources/Texture.h"
#include "Resources/Sprite.h"
#include "Resources/SoundEffect.h"
#include "Resources/SoundStream.h"
#include <map>

class ResourceManager
{
public:
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	// Singleton Functionality
	static ResourceManager* Get();
	static void Destroy();

	// Getters
	// Textures
	Texture* GetTexture(const std::string& key) const;

	// Sprites
	Sprite* GetSprite(const std::string& key) const;

	// SoundEffect
	SoundEffect* GetSoundEffect(const std::string& key) const;

	// SoundStream
	SoundStream* GetSoundStream(const std::string& key) const;

	// Players
	// SoundEffect
	void PlaySoundEffect(const std::string& key, int loops, int volume) const;
	//SoundStream
	void PlaySoundStream(const std::string& key, bool repeat, int volume) const;

private:
	ResourceManager();

	/// Data Members
	static ResourceManager* m_pResourceManager;

	// Textures
	std::map<std::string, Texture*> m_TextureMap;

	// Sprites
	std::map<std::string, Sprite*> m_SpriteMap;

	// SoundEffect
	std::map<std::string, SoundEffect*> m_SoundEffectMap;

	// SoundStream
	std::map<std::string, SoundStream*> m_SoundStreamMap;

	/// Member Functions

	//Loaders
	void LoadTextures();
	void LoadSprites();
	void LoadSoundEffects();
	void LoadSoundStream();
};
