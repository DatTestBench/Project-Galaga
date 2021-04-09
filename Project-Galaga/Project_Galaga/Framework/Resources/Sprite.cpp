#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(Texture* pTexture, int nrCols, int nrRows, int nrZones, float framesPerSec)
	: m_Cols{nrCols}
	, m_Rows{nrRows}
	, m_Zones{nrZones}
	, m_FramesPerSec{framesPerSec}
	, m_AccuSec{ 0.f }	
	, m_ActFrame{ 0 }
	, m_pTexture{ pTexture }
{
	
}

Sprite::~Sprite()
{
	if (m_pTexture != nullptr)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void Sprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= 1.f/m_FramesPerSec)
	{
		++m_ActFrame %= (m_Cols  * m_Rows); // m_Cols * m_Rows = number of frames
		m_AccuSec -= 1.f/m_FramesPerSec;
	}
}

void Sprite::Draw(const Point2f& pos, float offset, float scale)
{
	Rectf destRect{};
	Rectf srcRect{};
	srcRect.width = GetFrameWidth();
	srcRect.height = GetFrameHeight();
	destRect.left = pos.x;
	destRect.bottom = pos.y;
	destRect.width = srcRect.width * scale;
	destRect.height = srcRect.height * scale;
	srcRect.left = srcRect.width * (m_ActFrame % m_Cols); // = width * current col
	srcRect.bottom = srcRect.height * ((m_ActFrame / m_Cols) + offset - 1); // height * current row
	m_pTexture->Draw(destRect, srcRect);
}

void Sprite::DrawC(const Point2f& pos, float width, float height, float offset, float scale)
{
	Rectf srcRect{};
	srcRect.width = GetFrameWidth();
	srcRect.height = GetFrameHeight();
	width *= scale;
	height *= scale;
	srcRect.left = srcRect.width * (m_ActFrame % m_Cols); // = width * current col
	srcRect.bottom = srcRect.height * ((m_ActFrame / m_Cols) + offset - 1); // height * current row
	m_pTexture->DrawC(pos, width, height, srcRect);
}

float Sprite::GetFrameWidth()
{
	return m_pTexture->GetWidth() / m_Cols;
}

float Sprite::GetFrameHeight()
{
	return (m_pTexture->GetHeight() / m_Zones) / m_Rows;
}

void Sprite::CreateTexture(const std::string& filename)
{
	m_pTexture = new Texture(filename);
}
