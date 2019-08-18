#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "SoundEffect.h"
#include "SoundStream.h"
#include <map>

class ResourceManager
{
public:
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	// Singleton Functionality
	static ResourceManager* Get();
	void Destroy();

	// Getters
	// Textures
	Texture* GetTexturep(const std::string& key);

	// Sprites
	Sprite* GetSpritep(const std::string& key);

	// SoundEffect
	SoundEffect* GetSoundEffectp(const std::string& key);

	// SoundStream
	SoundStream* GetSoundStreamp(const std::string& key);

	// Players
	// SoundEffect
	void PlaySoundEffect(const std::string& key, int loops, int volume);
	//SoundStream
	void PlaySoundStream(const std::string& key, bool repeat, int volume);

private:
	ResourceManager();

	/// Data Members
	static ResourceManager* m_pResourceManager;

	// Textures
	std::map <std::string, Texture*> m_TextureMap;

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

