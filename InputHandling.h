#pragma once
#include <SDL.h>
#include "structs.h"
#include "Vector2f.h"
 

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
	void UpdateRelMousePos(const Vector2f& offset);

	//Getters
	SDL_Keycode KeyDown();
	SDL_Keycode KeyUp();
	Vector2f MousePos();
	Vector2f AbsMousePos();
	Uint8 MouseDown();
	Uint8 MouseUp();
	const Uint8* KeyState();
	Uint32 MouseState(int &x, int &y);
	Uint32 MouseState();
	SDL_Event Event();
	SDL_EventType Type();
private:
	InputHandling();
	static InputHandling* m_pInputHandling;

	/// Data Members
	Window m_Window;

	// Keycode
	SDL_Keycode m_KeyDown;
	SDL_Keycode m_KeyUp;
	Vector2f m_MousePos;
	Vector2f m_AbsMousePos;
	Uint8 m_MouseDown;
	Uint8 m_MouseUp;

	SDL_Event m_Event;
	SDL_EventType m_Type;
	/// Member Functions

	// Internal Workers
	void ProcessKeyDownEvent(const SDL_KeyboardEvent & e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
};

