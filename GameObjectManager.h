#pragma once
#include "GameObject.h"	
#include <vector>
class GameObject;
class Player;
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

	// Workers
	void Update(float dT);
	void Draw() const;

	// Getters
	std::vector<GameObject*>* GetGameObjects() ;
	Player* GetPlayer() const;
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

	Player* m_pPlayer;

	/// Member Functions
	//Internal Item Manipulation
	void HandleAdd();
	void HandleRemoval();
	void HandleDeletion();	
};

