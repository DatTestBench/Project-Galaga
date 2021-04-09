#pragma once
#include "GameObjectManager.h"
#include "GameLogic/UIManager.h"
#include "Core/Camera.h"
#include "GameLogic/Level.h"
#include "GameLogic/HUD.h"

enum class GameState
{
	menu,
	playing,
	paused,
	death,
};

class Game
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

	// Game State Logic
	void StartGame();
	void PauseGame();
	void ResumeGame();

private:
	// DATA MEMBERS
	const Window m_Window;
	Vector2f m_MousePos;
	
	GameState m_GameState;

	Camera m_Camera;
	Level m_Level;
	float m_Frames;
	float m_DT;
	std::vector<Vector2f> m_SpawnLocations;
	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void SpawnEnemies(float dT);
};