#pragma once
#include "GameObject.h"	
#include <vector>
class GameObject;
class Player;
class Level;
class GameObjectManager
{
public:
	~GameObjectManager();
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator= (const GameObjectManager&) = delete;
	GameObjectManager(GameObjectManager&&) = delete;
	GameObjectManager& operator= (GameObjectManager&&) = delete;

	//Singleton Functionality
	static GameObjectManager* Get(); 
	void Destroy();

	// External Item Manipulation
	void Add(GameObject* pGameObject);
	void Remove(GameObject* pGameObject);
	void Delete(GameObject* pGameObject);

	void SetLevel(Level& level);
	// Workers
	void Update(float dT);
	void Draw() const;

	// Getters

	std::vector<GameObject*>* GetGameObjects();

	std::vector<GameObject*> GetEnemies();
	std::vector<GameObject*> GetRushers();
	std::vector<GameObject*> GetGunners();
	std::vector<GameObject*> GetRocketeers();

	std::vector<GameObject*> GetProjectiles();
	std::vector<GameObject*> GetPlayerProjectiles();
	std::vector<GameObject*> GetEnemyProjectiles();
	std::vector<GameObject*> GetRockets();
	std::vector<GameObject*> GetBullets();
	std::vector<GameObject*> GetPellets();
	GameObject* GetPlayer() const;
	Level* GetLevel() const;
	size_t Size() const;

private:

	GameObjectManager();
	
	/// Data Members
	static GameObjectManager* m_pGameObjectManager;
	std::vector<GameObject*> m_GameObjects;

	// Buffers
	Buffer<GameObject*> m_AddBuffer;
	Buffer<GameObject*> m_RemoveBuffer;
	Buffer<GameObject*> m_DeleteBuffer;

	// Important objects
	GameObject* m_pPlayer;
	Level* m_pLevel;

	/// Member Functions
	// Internal Item Manipulation
	void HandleAdd();
	void HandleRemoval();
	void HandleDeletion();	
};

