	#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "utils.h"
Game::Game(const Window& window)
	:m_Window{ window }
	,m_Camera{window.width, window.height}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_Camera.SetLevelBoundaries(Rectf{ 0,0,30000,30000 });
	GameObjectManager::Get();
	// adding player
	//Texture* pPlayerText{ new Texture {"./Resources/Textures/player.png"} };
	Player* pPlayer{ new Player {10, Point2f{m_Window.width / 2.f, m_Window.height / 2.f}} };
	GameObjectManager::Get()->Add(pPlayer);

	// adding enemy
	//Texture* pEnemyText{ new Texture{"./Resources/Textures/enemy.png"} };
	Enemy* pEnemy{ new Enemy {pPlayer, Point2f{}} };
	GameObjectManager::Get()->Add(pEnemy);
}

void Game::Cleanup()
{
	GameObjectManager::Get()->Destroy();
	InputHandling::Get()->Destroy();
}

void Game::Update(float elapsedSec)
{
	GameObjectManager::Get()->Update(elapsedSec);

	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	
	//std::cout << elapsedSec << std::endl;
}

void Game::Draw() const
{
	ClearBackground();

	//glPushMatrix();

	//m_Camera.Transform(GameObjectManager::Get()->GetPlayer());
	GameObjectManager::Get()->Draw();

	//glPopMatrix();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
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
