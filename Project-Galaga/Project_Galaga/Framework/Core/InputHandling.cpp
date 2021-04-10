#include "InputHandling.h"
#include "Helpers/structs.h"
#include "Math/Vector2f.h"
#include <iostream>

InputHandling* InputHandling::m_pInputHandling = nullptr;

InputHandling::InputHandling()
	: m_KeyDown(0)
	, m_KeyUp(0)
	, m_MouseDown(0)
	, m_MouseUp(0)
	, m_Event()
	, m_Type()
{
}

InputHandling::~InputHandling()
{

}

#pragma region SingletonFunctionality
InputHandling* InputHandling::Get()
{
	if (m_pInputHandling == nullptr)
		m_pInputHandling = new InputHandling();
	return m_pInputHandling;
}

void InputHandling::Destroy()
{
	delete InputHandling::Get();
}
#pragma endregion SingletonFunctionality

#pragma region Input
void InputHandling::ProcessInput(const SDL_Event& e)
{
	m_Event = e;

	switch (e.type)
	{
	case SDL_QUIT:
		break;
	case SDL_KEYDOWN:
		ProcessKeyDownEvent(e.key);
		m_Type = static_cast<SDL_EventType>(e.type);
		break;
	case SDL_KEYUP:
		ProcessKeyUpEvent(e.key);
		m_Type = static_cast<SDL_EventType>(e.type);
		break;
	case SDL_MOUSEMOTION:
		ProcessMouseMotionEvent(e.motion);
		m_Type = static_cast<SDL_EventType>(e.type);
		break;
	case SDL_MOUSEBUTTONDOWN:
		ProcessMouseDownEvent(e.button);
		m_Type = static_cast<SDL_EventType>(e.type);
		break;
	case SDL_MOUSEBUTTONUP:
		ProcessMouseUpEvent(e.button);
		m_Type = static_cast<SDL_EventType>(e.type);
		break;
	default:
		break;
	}
}

void InputHandling::InitWindow(const Window& window)
{
	m_Window.height = window.height;
	m_Window.isVSyncOn = window.isVSyncOn;
	m_Window.title = window.title;
	m_Window.width = window.width;
}

void InputHandling::UpdateRelMousePos(const Vector2f& offset)
{
	m_RelMousePos = m_MousePos + offset;
}
#pragma endregion Input


#pragma region Getters


Uint32 InputHandling::MouseState(int &x, int &y) const
{
	const Uint32 state{ SDL_GetMouseState(&x, &y) };
	y = static_cast<int>(m_Window.height) - y;
	return state;
}

#pragma endregion Getters


#pragma region InternalWorkers
void InputHandling::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
	m_KeyDown = e.keysym.sym;
}

void InputHandling::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	m_KeyUp = e.keysym.sym;
}

void InputHandling::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_MousePos.x = static_cast<float>(e.x);
	m_MousePos.y = m_Window.height - e.y;
}

void InputHandling::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	m_MouseDown = e.button;
}

void InputHandling::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	m_MouseUp = e.button;

}
#pragma endregion InternalWorkers