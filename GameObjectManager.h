#pragma once
#include "GameObject.h"	
#include <vector>

class Player;
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
	

	// Getter Functions
	GameObject* GetPlayer() const;

	size_t Size() const;

private:

	// Data Members
	GameObjectManager();
	static GameObjectManager* m_pGameObjectManager;
	std::vector<GameObject*> m_GameObjects;
	Buffer<GameObject*> m_AddBuffer;
	Buffer<GameObject*> m_RemoveBuffer;
	Buffer<GameObject*> m_DeleteBuffer;
	GameObject* m_pPlayer;

	// Member Functions
	void HandleAdd();
	void HandleRemoval();
	void HandleDeletion();	
};

