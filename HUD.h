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
	HUD();
	void Draw() const;
	void SetLock(Player* pObjectToFollow);
private:

	ResourceManager* m_pResourceManager;
	Player* m_pObjectToFollow;
	Scoreboard* m_pScoreboard;
	
};

