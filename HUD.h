#pragma once
#include "Player.h"
#include "Texture.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scoreboard.h"
#include "Player.h"
class HUD
{
public:
	HUD(float width, float height);
	void Draw() const;
	void SetLock(GameObject* pObjectToFollow);
private:

	/// Data Members
	// Window size
	float m_Width;
	float m_Height;


	// Pointers
	ResourceManager* m_pResourceManager;
	GameObject* m_pObjectToFollow;
	Scoreboard* m_pScoreboard;
	GameObjectManager* m_pGameObjectManager;
	/// Member Functions
	void DrawBase() const;

	void DrawLives() const;
	void DrawHealth() const;
	void DrawScore() const;
	void DrawActivePowerups() const;


	
};

