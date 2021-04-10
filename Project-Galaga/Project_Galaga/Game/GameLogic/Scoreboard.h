#pragma once
#include "Resources/Texture.h"
class Scoreboard
{
public:
	~Scoreboard();
	Scoreboard(const Scoreboard&) = delete;
	Scoreboard& operator=(const Scoreboard&) = delete;
	Scoreboard(Scoreboard&&) = delete;
	Scoreboard& operator=(Scoreboard&&) = delete;

	// Singleton Functionality
	static Scoreboard* Get();
	static void Destroy();

	// Workers
	void Draw() const;
	void AddScore(int points);
	void AddWave();

	// Getters
	int GetScore() const { return m_Score; }
	int GetWave() const { return m_Wave; }

private:
	Scoreboard();

	// Data Members
	static Scoreboard* m_pScoreboard;
	int m_Score;
	Texture m_ScoreTex;
	int m_Wave;


	// Member Functions
};
