#include "pch.h"
#include "Scoreboard.h"
#include "utils.h"
#include "Texture.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "UIManager.h"
#include "Game.h"
Scoreboard* Scoreboard::m_pScoreboard = nullptr;

Scoreboard::Scoreboard()
	: m_ScoreTex{ Texture{ std::to_string(0), "./Resources/Fonts/Font.ttf", 50, Color4f{ 1, 1, 1, 1 } } }
	, m_Score{ 0 }
{
}

Scoreboard::~Scoreboard()
{
}

#pragma region SingletonFunctionality
Scoreboard* Scoreboard::Get()
{
	if (m_pScoreboard == nullptr)
		m_pScoreboard = new Scoreboard();
	return m_pScoreboard;
}

void Scoreboard::Destroy()
{
	delete Scoreboard::Get();
}
#pragma endregion SingletonFunctionality


#pragma region Workers
void Scoreboard::AddScore(int points)
{
	m_Score += points;
	m_ScoreTex = Texture{ std::to_string(m_Score), "./Resources/Fonts/Font.ttf", 50, Color4f{ 1, 1, 1, 1 } };

	if (m_Score == 2)
	{
		static_cast<Player*>(GameObjectManager::Get()->GetPlayer())->AddWeapon();
	}

	if (m_Score == 5)
	{
		static_cast<Player*>(GameObjectManager::Get()->GetPlayer())->AddWeapon();
	}


	if (m_Score == 7)
	{
		static_cast<Player*>(GameObjectManager::Get()->GetPlayer())->AddWeapon();
	}


	if (m_Score == 11)
	{
		static_cast<Player*>(GameObjectManager::Get()->GetPlayer())->AddWeapon();
	}
}

void Scoreboard::AddWave()
{
	m_Wave += 1;
}

void Scoreboard::Draw() const
{
	m_ScoreTex.DrawC(Point2f(  UIManager::Get()->GetWindowSize().x / 2, 22 * UIManager::Get()->GetWindowSize().y / 24));
	if (*UIManager::Get()->GetGameState() == GameState::death)
	{
		m_ScoreTex.DrawC(Point2f(UIManager::Get()->GetWindowSize().x / 2, UIManager::Get()->GetWindowSize().y / 2 ));
	}
}
#pragma endregion Workers

#pragma region Getters
int Scoreboard::GetScore() const
{
	return m_Score;
}

int Scoreboard::GetWave() const
{
	return m_Wave;
}
#pragma endregion Getters
