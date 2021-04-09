#include "pch.h"
#include "HUD.h"
#include "utils.h"
#include "Texture.h"
HUD::HUD(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_pResourceManager{ ResourceManager::Get() }
	, m_pScoreboard{ Scoreboard::Get() }
	, m_pGameObjectManager{ GameObjectManager::Get() }
{
}

void HUD::Draw() const
{
	DrawBase();
	DrawLives();
	DrawScore();
	DrawActivePowerups();
	DrawHealth();
}

void HUD::SetLock(GameObject* pObjectToFollow)
{
	m_pObjectToFollow = pObjectToFollow;
}


// Main HUD background, includes all static elements
void HUD::DrawBase() const
{
	m_pResourceManager->GetTexturep("TextHud")->Draw(Rectf{ 0, 0, m_Width, m_Height });
}


void HUD::DrawLives() const
{
	if (m_pObjectToFollow == m_pGameObjectManager->GetPlayer())
	{
		for (float idx{}; idx < static_cast<Player*>(m_pObjectToFollow)->GetLives(); idx++)
		{
			//m_pResourceManager->GetTexturep("TextPlayer")->Draw(Rectf{ 20 + 70 * idx  , 20, 50, 50 });
		}
	}
}

void HUD::DrawHealth() const
{
	if (m_pObjectToFollow == m_pGameObjectManager->GetPlayer())
	{
		m_pResourceManager->GetTexturep("TextHealthBar")->Draw(
			Rectf{ m_Width * (1.2f/48.f), 
				m_Height * (1.5f/48.f),  
				m_Width * (45.6f / 48.f) * (static_cast<Player*>(m_pObjectToFollow)->GetHealth() / static_cast<Player*>(m_pObjectToFollow)->GetBaseHealth()), 
				m_Height * (2.f / 48.f) } , 
			Rectf{ 0, 
				0, 
				m_pResourceManager->GetTexturep("TextHealthBar")->GetWidth() * (static_cast<Player*>(m_pObjectToFollow)->GetHealth() /
				 static_cast<Player*>(m_pObjectToFollow)->GetBaseHealth()), 
				m_pResourceManager->GetTexturep("TextHealthBar")->GetHeight() });
	}


	/*utils::SetColor(Color4f{ 1, 0, 0, 1 });
	utils::FillRect(Rectf{ 320, 20, 640, 50 });
	utils::SetColor(Color4f{ 0, 1, 0 , 1 });


	utils::FillRect(Rectf{ 320, 20, 640 * (m_pObjectToFollow->GetHealth() / m_pObjectToFollow->GetBaseHealth()), 50 });*/
}

void HUD::DrawScore() const
{
	m_pScoreboard->Draw();
}

void HUD::DrawActivePowerups() const
{

}