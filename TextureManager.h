#pragma once
#include "Texture.h"
#include "Sprite.h"
class TextureManager
{
public:
	~TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator= (const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

	// Singleton Functionality
	static TextureManager* Get();
	void Destroy();

	// Getters
	Texture* GetPlayerTextp();
	Texture* GetEnemyTextp();
	Sprite* GetPlayerSpritep();
	Sprite* GetEnemySpritep();

private:
	TextureManager();

	/// Data Members
	static TextureManager* m_pTextureManager;

	// Textures
	Texture* m_pPlayerText;
	Texture* m_pEnemyText;

	// Sprites
	Sprite* m_pPlayerSprite;
	Sprite* m_pEnemySprite;


};

