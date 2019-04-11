#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "utils.h"

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

void GameObjectManager::Add(GameObject* pGameObject)
{
	m_AddBuffer.Add(pGameObject);
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

std::vector<GameObject*>* GameObjectManager::GetGameObjects()
{
	return  &m_GameObjects;
}

size_t GameObjectManager::Size() const
{
	return size_t(m_GameObjects.size());
}


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

	std::cout << m_GameObjects.size() << std::endl;
}

