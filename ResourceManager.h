#pragma once
#include "Texture.h"
#include "Sprite.h"
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
	Texture* GetPlayerTextp();
	Texture* GetEnemyTextp();
	Texture* GetLevelTextp();

		// Sprites
	Sprite* GetPlayerSpritep();
	Sprite* GetEnemySpritep();

private:
	ResourceManager();

	/// Data Members
	static ResourceManager* m_pResourceManager;

	// Textures
	Texture* m_pPlayerText;
	Texture* m_pEnemyText;
	Texture* m_pLevelText;

	// Sprites
	Sprite* m_pPlayerSprite;
	Sprite* m_pEnemySprite;


};

