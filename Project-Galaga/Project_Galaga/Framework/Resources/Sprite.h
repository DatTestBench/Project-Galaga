#pragma once
#include <string>

#include "Helpers/structs.h"

class Texture;

class Sprite
{
public:
	Sprite(Texture* pTexture, int nrCols, int nrRows, int nrZones, float frameSec);
	~Sprite();
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	Sprite(Sprite&&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	void Update(float elapsedSec);
	void Draw(const Point2f& pos, float offset, float scale = 1.f);
	void DrawC(const Point2f& pos, float width, float height, float offset, float scale = 1.f);
	float GetFrameWidth() const;
	float GetFrameHeight() const;

private:
	Texture* m_pTexture;
	int m_Cols;
	int m_Rows;
	int m_Zones; // Amount of different zones on the spritesheet, what is drawn is defined by the offset
	float m_FramesPerSec;
	float m_AccuSec;
	int m_ActFrame;

	void CreateTexture(const std::string& filename);
};
