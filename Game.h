#pragma once
#include "GameObjectManager.h"
#include "Camera.h"
#include "Level.h"
#include "HUD.h"
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

private:
	// DATA MEMBERS
	const Window m_Window;
	Camera m_Camera;
	Level m_Level;
	HUD m_Hud;
	float m_Frames;
	float m_dT;
	std::vector<Vector2f> m_SpawnLocations;
	Texture m_EndTexture;
	bool m_GameStart;
	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void SpawnEnemies(float dT);
};