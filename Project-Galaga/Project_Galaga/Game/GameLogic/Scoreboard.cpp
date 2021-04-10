#include "GameLogic/Scoreboard.h"
#include "Core/Game.h"
#include "Core/GameObjectManager.h"
#include "Entities/Player.h"
#include "GameLogic/UIManager.h"
#include "Resources/Texture.h"

Scoreboard* Scoreboard::m_pScoreboard = nullptr;

Scoreboard::Scoreboard()
	: m_Score{ 0 }
	, m_ScoreTex{ Texture{ std::to_string(0), "../Resources/Fonts/Font.ttf", 50, Color4f{ 1, 1, 1, 1 } } }
	, m_Wave(0)
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
	delete Get();
}
#pragma endregion SingletonFunctionality

#pragma region Workers
void Scoreboard::AddScore(const int points)
{
	m_Score += points;
	m_ScoreTex = Texture{ std::to_string(m_Score), "../Resources/Fonts/Font.ttf", 50, Color4f{ 1, 1, 1, 1 } };

	if (m_Score == 2)
		GameObjectManager::Get()->GetPlayer()->AddWeapon();

	if (m_Score == 5)
		GameObjectManager::Get()->GetPlayer()->AddWeapon();


	if (m_Score == 7)
		GameObjectManager::Get()->GetPlayer()->AddWeapon();


	if (m_Score == 11)
		GameObjectManager::Get()->GetPlayer()->AddWeapon();
}

void Scoreboard::AddWave()
{
	m_Wave += 1;
}

void Scoreboard::Draw() const
{
	m_ScoreTex.DrawC(Point2f(UIManager::Get()->GetWindowSize().x / 2, 22 * UIManager::Get()->GetWindowSize().y / 24));
	if (*UIManager::Get()->GetGameState() == GameState::death)
		m_ScoreTex.DrawC(Point2f(UIManager::Get()->GetWindowSize().x / 2, UIManager::Get()->GetWindowSize().y / 2));
}
#pragma endregion Workers
