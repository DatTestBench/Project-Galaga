#include "pch.h"
#include "HUD.h"
#include "utils.h"
#include "Texture.h"
HUD::HUD()
	: m_pResourceManager{ ResourceManager::Get() }
	, m_pScoreboard{ Scoreboard::Get() }
{
}

void HUD::Draw() const
{
	for (float idx{}; idx < m_pObjectToFollow->GetLives(); idx++)
	{
		m_pResourceManager->GetTexturep("TextPlayer")->Draw(Rectf{ 20 + 70 * idx  , 20, 50, 50 });

	}

	m_pScoreboard->Draw();
	utils::SetColor(Color4f{ 1, 0, 0, 1 });
	utils::FillRect(Rectf{ 320, 20, 640, 50 });
	utils::SetColor(Color4f{ 0, 1, 0 , 1 });
	utils::FillRect(Rectf{ 320, 20, 640 * (m_pObjectToFollow->GetHealth() / m_pObjectToFollow->GetBaseHealth()), 50 });
	
}

void HUD::SetLock(Player* pObjectToFollow)
{
	m_pObjectToFollow = pObjectToFollow;
}
