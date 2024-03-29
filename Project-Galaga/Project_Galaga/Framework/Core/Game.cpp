#include "Game.h"

#include "InputHandling.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "Entities/Rusher.h"
#include "Entities/Rocketeer.h"
#include "Entities/Gunner.h"
#include "Helpers/utils.h"
Game::Game(const Window& window)
	: m_Window{ window }
	, m_GameState{ GameState::menu }
	, m_Camera{ window.width, window.height }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_Camera.SetLevelBoundaries(m_Level.GetBoundaries());
	GameObjectManager::Get();
	ResourceManager::Get();
	UIManager::Get()->SetGameState(&m_GameState);
	GameObjectManager::Get()->SetLevel(m_Level);
	Scoreboard::Get();

	// adding player
	const auto pPlayer{ new Player{ Vector2f(787.5, 787.5), 50, 50, ResourceManager::Get()->GetSprite("SpritePlayer"), 2000.f } };
	GameObjectManager::Get()->Add(pPlayer);

	// create UI
	UIManager::Get()->LoadManager(Vector2f{ m_Window.width, m_Window.height });
	UIManager::Get()->Add(new UIElement{ "BTNStart", Vector2f{ m_Window.width / 2.f, m_Window.height / 2.f }, 256, 64 });


	ResourceManager::Get()->PlaySoundStream("SSBackground", true, 5);

	// adding enemy

	m_SpawnLocations.emplace_back(m_Window.width / 3.f, m_Window.height / 3.f);
	m_SpawnLocations.emplace_back(2 * m_Window.width / 3.f, m_Window.height / 3.f);
	m_SpawnLocations.emplace_back(2 * m_Window.width / 3.f, 2 * m_Window.height / 3.f);
	m_SpawnLocations.emplace_back(m_Window.width / 3.f, 2 * m_Window.height / 3.f);


	//GameObjectManager::Get()->Update(0);
}

void Game::Cleanup()
{
	ResourceManager::Destroy();
	GameObjectManager::Destroy();
	InputHandling::Destroy();
	Scoreboard::Destroy();
	UIManager::Destroy();
}

void Game::Update(const float elapsedSec)
{
	UIManager::Get()->Update(elapsedSec);

	if (m_GameState != GameState::paused && m_GameState != GameState::menu && m_GameState != GameState::death)
	{
		if (GameObjectManager::Get()->GetPlayer()->GetLives() >= 0)
		{
			GameObjectManager::Get()->Update(elapsedSec);
			InputHandling::Get()->UpdateRelMousePos(m_Camera.GetOffset(GameObjectManager::Get()->GetPlayer()));
			m_Level.HandleCollision();
			SpawnEnemies(elapsedSec);
		}
	}
	else
		// To prevent memory leaks
		GameObjectManager::Get()->Update(0);
}

void Game::Draw() const
{
	ClearBackground();


	//if (m_GameState != GameState::paused && m_GameState != GameState::menu)

	glPushMatrix();
	m_Camera.Transform(GameObjectManager::Get()->GetPlayer());
	m_Level.Draw();
	utils::SetColor(Color4f{ 1, 0, 0, 1 });
	GameObjectManager::Draw();
	glPopMatrix();

	UIManager::Get()->Draw();


	if (GameObjectManager::Get()->GetPlayer()->GetLives() <= 0)
	{
		utils::SetColor(Color4f{ 128.f, 128.f, 128, 1 });
		utils::DrawRect(0, 0, m_Window.width, m_Window.height);
	}
}

#pragma region EventHandling
void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_i:
		std::cout << std::endl;
		std::cout << "Game Controls:" << std::endl;
		std::cout << "Use WASD to move, press left mouse button to shoot" << std::endl;
		std::cout << "Fight endless waves of enemies and get a high score" << std::endl;
		break;
	default:
		break;
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent&)
{
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_MousePos = Vector2f{ static_cast<float>(e.x), (m_Window.height - e.y) };
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) const
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		if (!GameObjectManager::Get()->GetPlayer()->IsShooting() && m_GameState == GameState::playing)
			GameObjectManager::Get()->GetPlayer()->ToggleShoot();
		UIManager::Get()->SetClick(true);
		break;
	default:
		break;
	}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) const
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		if (GameObjectManager::Get()->GetPlayer()->IsShooting() && m_GameState == GameState::playing)
			GameObjectManager::Get()->GetPlayer()->ToggleShoot();
		UIManager::Get()->SetClick(false);
		break;
	default:
		break;
	}
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

#pragma endregion EventHandling

#pragma region GameStateLogic
void Game::StartGame()
{
	m_GameState = GameState::playing;
}

void Game::PauseGame()
{
	m_GameState = GameState::paused;
}

void Game::ResumeGame()
{
	StartGame();
}
#pragma endregion GameStateLogic


void Game::ClearBackground()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Game::SpawnEnemies(const float dT)
{
	// Spawn locations


	// Enemy selector


	// Old code
	m_DT += dT;
	Scoreboard::Get()->AddWave();
	//std::cout << "spawn";
	//for (int idx{}; idx < 3; idx++)
	//{
	//	int spawnSelector{ rand() % 3 };
	//	int type{ rand() % 3 };
	//	//std::cout << type << ' ' << spawnSelector << std::endl;
	//	switch (type)
	//	{
	//	case 0:
	//		GameObjectManager::Get()->Add(new Gunner{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteEnemy"), 1, 100 });
	//		//std::cout << "spawn gunner" << std::endl;
	//		break;
	//	case 1:
	//		GameObjectManager::Get()->Add(new Rusher{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteRusher"), 1, 100 });
	//		//std::cout << "spawn rusher" << std::endl;
	//		break;
	//	case 2:
	//		GameObjectManager::Get()->Add(new Rocketeer{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteEnemy"), 1, 100 });
	//		//std::cout << "spawn rocketeer" << std::endl;
	//		break;
	//	default:
	//		break;
	//	}
	//}


	if (m_DT > 5)
	{
		Scoreboard::Get()->AddWave();
		//std::cout << "spawn";
		for (int idx{}; idx < 2; idx++)
		{
			const int spawnSelector{ rand() % 3 };
			const int type{ rand() % 3 };
			//std::cout << type << ' ' << spawnSelector << std::endl;
			switch (type)
			{
			case 0:
				GameObjectManager::Get()->Add(new Gunner{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSprite("SpriteEnemy"), 1, 100 });
				//std::cout << "spawn gunner" << std::endl;
				break;
			case 1:
				GameObjectManager::Get()->Add(new Rusher{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSprite("SpriteRusher"), 1, 100 });
				//std::cout << "spawn rusher" << std::endl;
				break;
			case 2:
				GameObjectManager::Get()->Add(new Rocketeer{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSprite("SpriteEnemy"), 1, 100 });
				//std::cout << "spawn rocketeer" << std::endl;
				break;
			default:
				break;
			}
		}
		m_DT = 0;
	}
}
