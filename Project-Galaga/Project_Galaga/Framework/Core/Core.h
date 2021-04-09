#pragma once
#include <ctime>
#include <ratio>
#include <chrono>
#include <SDL_video.h>


#include "Helpers/structs.h"

/*// SDL and OpenGL Includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>*/ 


class Core
{
public:
	explicit Core( const Window& window );
	Core( const Core& other ) = delete;
	Core& operator=( const Core& other ) = delete;
	Core(Core&& other) = delete;
	Core& operator=(Core&& other) = delete;
	~Core( );

	void Run( );

private:
	// DATA MEMBERS
	// The window properties
	const Window m_Window;
	// The window we render to
	SDL_Window* m_pWindow;
	// OpenGL context
	SDL_GLContext m_pContext;
	// Init info
	bool m_Initialized;
	// Prevent timing jumps when debugging
	const float m_MaxElapsedSeconds;
	
	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
};
