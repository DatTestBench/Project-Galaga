#pragma once
#include <string>
#include "SDL_ttf.h"
#include "Helpers/structs.h"
#include <SDL_opengl.h>

class Texture
{
public:
	explicit Texture(const std::string& imagePath);
	explicit Texture(const std::string& text, TTF_Font* pFont, const Color4f& textColor);
	explicit Texture(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor);
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;
	~Texture();

	void Draw(const Point2f& destBottomLeft = {}, const Rectf& srcRect = {}) const;
	void DrawC(const Point2f& center = {}, const Rectf& srcRect = {}) const; // Manually added texture draw using the middle of the object, not the bottom left
	void DrawC(const Point2f& center, float width, float height, const Rectf& srcRect = {}) const; // Manually added texture draw using the middle of the object, not the bottom left
	void Draw(const Rectf& destRect, const Rectf& srcRect = {}) const;

	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }
	bool IsCreationOk() const { return m_CreationOk; }

private:
	//DATA MEMBERS
	GLuint m_Id;
	float m_Width;
	float m_Height;
	bool m_CreationOk;

	// FUNCTIONS
	void CreateFromImage(const std::string& path);
	void CreateFromString(const std::string& text, TTF_Font* pFont, const Color4f& color);
	void CreateFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor);
	void CreateFromSurface(const SDL_Surface* pSurface);
	static void DrawFilledRect(const Rectf& destRect);
};
