#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "utils.h"
#include <typeinfo>

GameObjectManager* GameObjectManager::m_pGameObjectManager = nullptr;

GameObjectManager::GameObjectManager()
	:m_GameObjects{}
{
}

GameObjectManager::~GameObjectManager()
{
	for (size_t idx{}; idx < Size(); idx++)
	{
		delete m_GameObjects[idx];
		m_GameObjects[idx] = nullptr;
	}
	
}

#pragma region SingletonFunctionality
GameObjectManager* GameObjectManager::Get()
{
	if (m_pGameObjectManager == nullptr)
		m_pGameObjectManager = new GameObjectManager();
	return m_pGameObjectManager;
}

void GameObjectManager::Destroy()
{
	delete GameObjectManager::Get();
}
#pragma endregion SingletonFunctionality

#pragma region ExternalItemManipulation
void GameObjectManager::Add(GameObject* pGameObject)
{
	m_AddBuffer.Add(pGameObject);
	if (typeid(*pGameObject) == typeid (Player))
		m_pPlayer = pGameObject;
}

// WIP
void GameObjectManager::Remove(GameObject* pGameObject)
{
	m_RemoveBuffer.Add(pGameObject);
}

void GameObjectManager::Delete(GameObject* pGameObject)
{
	m_DeleteBuffer.Add(pGameObject);


	//std::cout << "added to deletebuffer ";
}
#pragma endregion ExternalItemManipulation

#pragma region Workers
void GameObjectManager::Update(float dT)
{
	HandleDeletion();
	HandleAdd();


	for (GameObject *pGameObject : *GameObjectManager::Get()->GetGameObjects())
	{
		pGameObject->Update(dT);
	}
}

void GameObjectManager::Draw() const
{
	for (GameObject *pGameObject : *GameObjectManager::Get()->GetGameObjects())
	{
		pGameObject->Draw();
	}
}
#pragma endregion Workers

#pragma region Getters
std::vector<GameObject*>* GameObjectManager::GetGameObjects()
{
	return  &m_GameObjects;
}

GameObject* GameObjectManager::GetPlayer() const
{
	return m_pPlayer;
}

size_t GameObjectManager::Size() const
{
	return size_t(m_GameObjects.size());
}
#pragma endregion Getters

#pragma region InternalItemManipulation
void GameObjectManager::HandleAdd()
{
	m_GameObjects.insert(std::end(m_GameObjects), std::begin(m_AddBuffer.buffer), std::end(m_AddBuffer.buffer));
	m_AddBuffer.Reset();
}

// WIP
void GameObjectManager::HandleRemoval()
{

}

void GameObjectManager::HandleDeletion()
{
	std::sort(m_GameObjects.begin(), m_GameObjects.end(), [](GameObject* a, GameObject* b)
	{
		return a->GetFlag() < b->GetFlag();
	});
	for (size_t idx{}; idx < m_DeleteBuffer.buffer.size(); idx++)
	{
		delete m_GameObjects.back();
		m_GameObjects.pop_back();
	}
	m_DeleteBuffer.Reset();
}
#pragma endregion InternalItemManipulation

