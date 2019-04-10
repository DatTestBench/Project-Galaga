#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

GameObjectManager* GameObjectManager::m_pGameObjectManager = nullptr;

GameObjectManager::GameObjectManager()
	:m_pGameObjects{}
{
}

GameObjectManager::~GameObjectManager()
{
	for (size_t idx{}; idx < Size(); idx++)
	{
		delete m_pGameObjects[idx];
		m_pGameObjects[idx] = nullptr;
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
	pGameObject = nullptr;
	std::cout << "added to deletebuffer ";
}

void GameObjectManager::Update(float dT)
{
	HandleDeletion();
	HandleAdd();


	for (size_t idx{}; idx < m_pGameObjects.size(); idx++)
	{
		m_pGameObjects[idx]->Update(dT);
	}
}

void GameObjectManager::Draw() const
{
	for (size_t idx{}; idx < m_pGameObjects.size(); idx++)
	{
		m_pGameObjects[idx]->Draw();
	}
}

std::vector<GameObject*>* GameObjectManager::GetGameObjects()
{
	return  &m_pGameObjects;
}

size_t GameObjectManager::Size() const
{
	return size_t(m_pGameObjects.size());
}


void GameObjectManager::HandleAdd()
{
	m_pGameObjects.insert(std::end(m_pGameObjects), std::begin(m_AddBuffer.buffer), std::end(m_AddBuffer.buffer));
	m_AddBuffer.Reset();
}

// WIP
void GameObjectManager::HandleRemoval()
{

}

void GameObjectManager::HandleDeletion()
{
	
	/*if (m_DeleteBuffer.buffer.size() > 0)
	{
		m_pGameObjects.erase(std::remove(std::begin(m_pGameObjects), std::end(m_pGameObjects), nullptr));
		std::cout << m_DeleteBuffer.buffer.size() << std::endl;
		m_DeleteBuffer.Reset();
	}*/

	size_t deleteC{};
	for (size_t idx{}; idx < m_pGameObjects.size(); idx++)
	{
		if (m_pGameObjects[idx] == nullptr)
		{
			m_pGameObjects.erase(std::begin(m_pGameObjects) + idx - deleteC);
			deleteC++;
		}
	}
}
//Rectf GameObjectManager::GetPlayerRect() const 
//{
//	for (GameObject* pGameObject : m_pGameObjects)
//	{
//		if (typeid(*pGameObject) == typeid(Player))
//		{
//			return Rectf{ pGameObject->GetPos().x, pGameObject->GetPos().y,pGameObject->GetWidth(), pGameObject->GetHeight() };
//		}
//	}
//	return Rectf{};
//}


