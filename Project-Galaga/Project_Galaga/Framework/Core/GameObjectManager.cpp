#include "Core/GameObjectManager.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <typeinfo>
#include <vector>
#include "Core/GameObject.h"
#include "Entities/Gunner.h"
#include "Entities/Player.h"
#include "Entities/Rocketeer.h"
#include "Entities/Rusher.h"
#include "Items/MachinegunBullet.h"
#include "Items/Projectile.h"
#include "Items/Rocket.h"
#include "Items/ShotgunPellet.h"

GameObjectManager* GameObjectManager::m_pGameObjectManager = nullptr;

GameObjectManager::GameObjectManager()
	: m_pPlayer(nullptr)
	, m_pLevel(nullptr)
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
		m_pPlayer = static_cast<Player*>(pGameObject);
}

// WIP
void GameObjectManager::Remove(GameObject* pGameObject)
{
	m_RemoveBuffer.Add(pGameObject);
}

void GameObjectManager::Delete(GameObject* pGameObject)
{
	m_DeleteBuffer.Add(pGameObject);
}

void GameObjectManager::SetLevel(Level& level)
{
	m_pLevel = &level;
}

void GameObjectManager::SetPlayer(Player* pGameObject)
{
	m_pPlayer = pGameObject;
}

#pragma endregion ExternalItemManipulation

#pragma region Workers
void GameObjectManager::Update(float dT)
{
	HandleDeletion();
	HandleAdd();


	for (GameObject *pGameObject : *Get()->GetGameObjects())
	{
		pGameObject->Update(dT);
	}
}

void GameObjectManager::Draw()
{
	for (GameObject *pGameObject : *Get()->GetGameObjects())
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

std::vector<GameObject*> GameObjectManager::GetEnemies()
{
	std::vector<GameObject*> enemies;
	std::ranges::for_each(m_GameObjects, [&enemies](GameObject* a) mutable
	{
		if ((typeid (*a) == typeid (Rusher) || typeid (*a) == typeid (Gunner) || typeid (*a) == typeid (Rocketeer)) && (a->GetFlag() == false))
		{
			enemies.push_back(a);
		}
	});
	return enemies;
}
std::vector<GameObject*> GameObjectManager::GetRushers()
{
	std::vector<GameObject*> rushers;
	std::ranges::for_each(m_GameObjects, [&rushers](GameObject* a) mutable
	{
		if (typeid (*a) == typeid (Rusher) && a->GetFlag() == false)
		{
			rushers.push_back(a);
		}
	});
	return rushers;
}
std::vector<GameObject*> GameObjectManager::GetGunners()
{
	std::vector<GameObject*> gunners;
	std::ranges::for_each(m_GameObjects, [&gunners](GameObject* a) mutable
	{
		if (typeid (*a) == typeid (Gunner) && a->GetFlag() == false)
		{
			gunners.push_back(a);
		}
	});
	return gunners;
}
std::vector<GameObject*> GameObjectManager::GetRocketeers()
{
	std::vector<GameObject*> rocketeers;
	std::ranges::for_each(m_GameObjects, [&rocketeers](GameObject* a) mutable
	{
		if (typeid (*a) == typeid (Rocketeer) && a->GetFlag() == false)
		{
			rocketeers.push_back(a);
		}
	});
	return rocketeers;
}

std::vector<GameObject*> GameObjectManager::GetProjectiles()
{
	std::vector<GameObject*> projectiles;
	std::ranges::for_each(m_GameObjects, [&projectiles](GameObject* a) mutable
	{
		if ((typeid (*a) == typeid (MachinegunBullet) || typeid (*a) == typeid (ShotgunPellet) || typeid (*a) == typeid (Rocket)) && (a->GetFlag() == false))
		{
			projectiles.push_back(a);
		}
	});
	return projectiles;
}
std::vector<GameObject*> GameObjectManager::GetPlayerProjectiles()
{
	std::vector<GameObject*> playerProjectiles;
	std::ranges::for_each(m_GameObjects, [&playerProjectiles](GameObject* a) mutable
	{
		if ((typeid (*a) == typeid (MachinegunBullet) || typeid (*a) == typeid (ShotgunPellet) || typeid (*a) == typeid (Rocket)) && (a->GetFlag() == false))
		{
			if (typeid(*static_cast<Projectile*>(a)->GetSender()) == typeid(Player))
			{
				playerProjectiles.push_back(a);
			}
		}
	});
	return playerProjectiles;
}
std::vector<GameObject*> GameObjectManager::GetEnemyProjectiles()
{
	std::vector<GameObject*> enemyProjectiles;
	std::ranges::for_each(m_GameObjects, [&enemyProjectiles](GameObject* a) mutable
	{
		if ((typeid (*a) == typeid (MachinegunBullet) || typeid (*a) == typeid (ShotgunPellet) || typeid (*a) == typeid (Rocket)) && (a->GetFlag() == false))
		{
			if (typeid(*static_cast<Projectile*>(a)->GetSender()) != typeid(Player))
			{
				enemyProjectiles.push_back(a);
			}
		}
	});
	return enemyProjectiles;
}
std::vector<GameObject*> GameObjectManager::GetRockets()
{
	std::vector<GameObject*> rockets;
	std::ranges::for_each(m_GameObjects, [&rockets](GameObject* a) mutable
	{
		if (typeid (*a) == typeid (Rocket) && a->GetFlag() == false)
		{
			rockets.push_back(a);
		}
	});
	return rockets;
}
std::vector<GameObject*> GameObjectManager::GetBullets()
{
	std::vector<GameObject*> bullets;
	std::ranges::for_each(m_GameObjects, [&bullets](GameObject* a) mutable
	{
		if (typeid (*a) == typeid (MachinegunBullet) && a->GetFlag() == false)
		{
			bullets.push_back(a);
		}
	});
	return bullets;
}
std::vector<GameObject*> GameObjectManager::GetPellets()
{
	std::vector<GameObject*> pellets;
	std::ranges::for_each(m_GameObjects, [&pellets](GameObject* a) mutable
	{
		if (typeid (*a) == typeid (ShotgunPellet) && a->GetFlag() == false)
		{
			pellets.push_back(a);
		}
	});
	return pellets;
}

Player* GameObjectManager::GetPlayer() const
{
	return m_pPlayer;
}

Level* GameObjectManager::GetLevel() const
{
	return m_pLevel;
}
size_t GameObjectManager::Size() const
{
	return m_GameObjects.size();
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
	std::ranges::sort(m_GameObjects, [](GameObject* a, GameObject* b)
	{
		return a->GetFlag() < b->GetFlag();
	});
	for (size_t idx{}; idx < m_DeleteBuffer.buffer.size(); idx++)
	{
		delete m_GameObjects.back();
		m_GameObjects.back() = nullptr;
		m_GameObjects.pop_back();
	}
	m_DeleteBuffer.Reset();
}
#pragma endregion InternalItemManipulation

