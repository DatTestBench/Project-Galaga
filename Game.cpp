#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Rusher.h"
#include "Rocketeer.h"
#include "Gunner.h"
#include "utils.h"
Game::Game(const Window& window)
	:m_Window{ window }
	, m_Camera{ window.width, window.height }
	, m_Level{  }
	, m_Hud{  }
	, m_EndTexture{ "YOU DIED ", "./Resources/Fonts/Font.otf", 80, Color4f{ 1,0,0,1 } }
	, m_GameStart{ false }
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

	GameObjectManager::Get()->SetLevel(m_Level);


	// adding player
	Player* pPlayer{ new Player { Vector2f(787.5, 787.5), 50, 50, ResourceManager::Get()->GetSpritep("SpritePlayer"), 200.f } };
	GameObjectManager::Get()->Add(pPlayer);


	m_Hud.SetLock(pPlayer);

	// adding enemy

	m_SpawnLocations.push_back(Vector2f{ m_Window.width / 3.f , m_Window.height / 3.f });
	m_SpawnLocations.push_back(Vector2f{ 2 * m_Window.width / 3.f , m_Window.height / 3.f });
	m_SpawnLocations.push_back(Vector2f{ 2 * m_Window.width / 3.f , 2 * m_Window.height / 3.f });
	m_SpawnLocations.push_back(Vector2f{ m_Window.width / 3.f , 2 * m_Window.height / 3.f });
}

void Game::Cleanup()
{
	ResourceManager::Get()->Destroy();
	GameObjectManager::Get()->Destroy();
	InputHandling::Get()->Destroy();
	Scoreboard::Get()->Destroy();
}

void Game::Update(float elapsedSec)
{
	if (static_cast<Player*>(GameObjectManager::Get()->GetPlayer())->GetLives() > 0)
	{
		GameObjectManager::Get()->Update(elapsedSec);
		InputHandling::Get()->UpdateRelMousePos(m_Camera.GetOffset(GameObjectManager::Get()->GetPlayer()));
		m_Level.HandleCollision();
		SpawnEnemies(elapsedSec);


	}
}

void Game::Draw() const
{
	ClearBackground();

	if (static_cast<Player*>(GameObjectManager::Get()->GetPlayer())->GetLives() > 0)
	{
		glPushMatrix();
		m_Camera.Transform(GameObjectManager::Get()->GetPlayer());
		m_Level.Draw();
		utils::SetColor(Color4f{ 1,0,0,1 });
		GameObjectManager::Get()->Draw();
		glPopMatrix();

		m_Hud.Draw();
	}
	else
	{
		utils::SetColor(Color4f{ 128.f, 128.f, 128, 1 });
		utils::DrawRect(0, 0, m_Window.width, m_Window.height);
		m_EndTexture.DrawC(Point2f{ m_Window.width / 2.f, m_Window.height / 2.f });


	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{

}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		if (!GameObjectManager::Get()->GetPlayer()->IsShooting())
			GameObjectManager::Get()->GetPlayer()->ToggleShoot();
		break;
	default:
		break;
	}
	//std::cout << "MOUSEBUTTONDOWN event: ";
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

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		if (GameObjectManager::Get()->GetPlayer()->IsShooting())
			GameObjectManager::Get()->GetPlayer()->ToggleShoot();
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

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::SpawnEnemies(float dT)
{
	m_dT += dT;

	if (!m_GameStart)
	{
		m_GameStart = true;
		Scoreboard::Get()->AddWave();
		std::cout << "spawn";
		for (int idx{}; idx < 3; idx++)
		{
			int spawnSelector{ rand() % 3 };
			int type{ rand() % 3 };
			std::cout << type << ' ' << spawnSelector << std::endl;
			switch (type)
			{
			case 0:
				GameObjectManager::Get()->Add(new Gunner{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteEnemy"), 1, 100 });
				std::cout << "spawn gunner" << std::endl;
				break;
			case 1:
				GameObjectManager::Get()->Add(new Rusher{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteRusher"), 1, 100 });
				std::cout << "spawn rusher" << std::endl;
				break;
			case 2:
				GameObjectManager::Get()->Add(new Rocketeer{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteEnemy"), 1, 100 });
				std::cout << "spawn rocketeer" << std::endl;
				break;
			default:
				break;
			}
		}
	}


	if (m_dT > 30.f)
	{
		Scoreboard::Get()->AddWave();
		std::cout << "spawn";
		for (int idx{}; idx < 4; idx++)
		{
			int spawnSelector{ rand() % 3 };
			int type{ rand() % 3 };
			std::cout << type << ' ' << spawnSelector << std::endl;
			switch (type)
			{
			case 0:
				GameObjectManager::Get()->Add(new Gunner{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteEnemy"), 1, 100 });
				std::cout << "spawn gunner" << std::endl;
				break;
			case 1:
				GameObjectManager::Get()->Add(new Rusher{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteRusher"), 1, 100 });
				std::cout << "spawn rusher" << std::endl;
				break;
			case 2:
				GameObjectManager::Get()->Add(new Rocketeer{ m_SpawnLocations[spawnSelector], 50, 50, ResourceManager::Get()->GetSpritep("SpriteEnemy"), 1, 100 });
				std::cout << "spawn rocketeer" << std::endl;
				break;
			default:
				break;
			}

		}




		m_dT = 0;
	}
}
