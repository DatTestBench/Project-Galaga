#pragma once
#include <SDL.h>
#include "Helpers/structs.h"
#include "Math/Vector2f.h"
 

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
	static void Destroy();

	//Input
	void ProcessInput(const SDL_Event& e);
	void InitWindow(const Window& window);
	void UpdateRelMousePos(const Vector2f& offset);

	//Getters
	SDL_Keycode KeyDown() const { return m_KeyDown; }
	SDL_Keycode KeyUp() const { return m_KeyUp; }
	Vector2f MousePos() const { return m_MousePos; }
	Vector2f RelMousePos() const { return m_RelMousePos; }
	Uint8 MouseDown() const { return m_MouseDown; }
	Uint8 MouseUp() const { return m_MouseUp; }
	static const Uint8* KeyState() { return SDL_GetKeyboardState(nullptr); } 
	Uint32 MouseState(int &x, int &y) const;
	static Uint32 MouseState() { return SDL_GetMouseState(nullptr, nullptr); }
	SDL_Event Event() const { return m_Event; }
	SDL_EventType Type() const { return m_Type; }
private:
	InputHandling();
	static InputHandling* m_pInputHandling;

	/// Data Members
	Window m_Window;

	// Keycode
	SDL_Keycode m_KeyDown;
	SDL_Keycode m_KeyUp;
	Vector2f m_MousePos;
	Vector2f m_RelMousePos;
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

