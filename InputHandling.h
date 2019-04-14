#pragma once
#include <SDL.h>
class InputHandling
{
public:
	~InputHandling();
	InputHandling(const InputHandling&) = delete;
	InputHandling& operator= (const InputHandling&) = delete;
	InputHandling(InputHandling&&) = delete;
	InputHandling& operator= (InputHandling&&) = delete;

	//Singleton Functionality
	static InputHandling* Get();
	void Destroy();

	//Input
	void ProcessInput(const SDL_Event& e);
	void InitWindow(const Window& window);
	//Getters
	SDL_Keycode KeyDown();
	SDL_Keycode KeyUp();
	Point2f MousePos();
	Uint8 MouseDown();
	Uint8 MouseUp();
	Uint8 KeyState();
	Uint32 MouseState();

	SDL_Keycode Key();
private:
	InputHandling();
	static InputHandling* m_pInputHandling;

	/// Data Members
	Window m_Window;
	SDL_Keycode m_KeyDown;
	SDL_Keycode m_KeyUp;
	Point2f m_MousePos;
	Uint8 m_MouseDown;
	Uint8 m_MouseUp;

	SDL_Event m_Event;
	/// Member Functions

	// Internal Workers
	void ProcessKeyDownEvent(const SDL_KeyboardEvent & e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
};

