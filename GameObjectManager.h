#pragma once
#include "GameObject.h"	
#include <vector>

class GameObjectManager
{
public:
	~GameObjectManager();
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator= (const GameObjectManager&) = delete;
	GameObjectManager(GameObjectManager&&) = delete;
	GameObjectManager& operator= (GameObjectManager&&) = delete;

	static GameObjectManager* Get(); 
	void Destroy();

	void Add(GameObject* pGameObject);
	void Remove(GameObject* pGameObject);
	void Delete(GameObject* pGameObject);
	void Update(float dT);
	void Draw() const;
	std::vector<GameObject*>* GetGameObjects() ;
	//void HandleCollision();

	// Getter Functions
	//Rectf GetPlayerRect() const;

	size_t Size() const;

private:

	// Data Members
	GameObjectManager();
	static GameObjectManager* m_pGameObjectManager;
	std::vector<GameObject*> m_pGameObjects;
	Buffer<GameObject*> m_AddBuffer;
	Buffer<GameObject*> m_RemoveBuffer;
	Buffer<GameObject*> m_DeleteBuffer;

	// Member Functions
	void HandleAdd();
	void HandleRemoval();
	void HandleDeletion();	
};

