#include "Entities/Player.h"
#include "Core/Game.h"
#include "Core/InputHandling.h"
#include "Helpers/LinkedList.h"
#include "Helpers/SAT.h"
#include "Helpers/utils.h"
#include "Items/Machinegun.h"
#include "Items/RocketLauncher.h"
#include "Items/Shotgun.h"
#include "Items/Weapon.h"
#include "Resources/Texture.h"

Player::Player(const Vector2f& pos, float width, float height, Sprite* pSprite, float baseHealth)
	: GameObject{ pos, width, height, pSprite }
	, m_Friction{ 10 }
	, m_BaseHealth{ baseHealth }
	, m_Lives{ 1 }
{
	m_pExhaustSprite = ResourceManager::Get()->GetSprite("SpriteExhaust");
	m_MaxSpeed = 600;
	m_Acceleration = 10000;
	m_CurrentHealth = m_BaseHealth;
	RocketLauncher* pWeapon = new RocketLauncher{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) };
	m_pWeapons.push_back(pWeapon);
}

Player::~Player()
{
	for (Weapon* pWeapon : m_pWeapons)
		delete pWeapon;
}

void Player::Draw() const
{
	DrawTrail();

	// Open Transform
	glPushMatrix();

	// Transforms
	glTranslatef(m_Pos.x, m_Pos.y, 0.f);
	glRotatef(utils::ToDeg(GetAngle() - utils::g_Pi / 2.f), 0.f, 0.f, 1.f);
	m_pExhaustSprite->DrawC(Point2f{ 0, - m_Height / 2.f - 20 }, 20, 40, 1);

	// Drawcode needing transform
	m_pSprite->DrawC(Point2f{}, m_Width, m_Height, 10); //Player Draw
	
	/*for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Draw();*/

	// Close Transform
	glPopMatrix();

	//Debug Draws
	//utils::DrawPolygon(GetCollider());
	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->Draw();
}

void Player::Update(float dT)
{
	//m_Pos = InputHandling::Get()->MousePos();


	//switch (InputHandling::Get()->MouseState())
	//{
	//case SDL_BUTTON_LEFT:
	//	//std::cout << "Yeeted that left click" << std::endl;
	//	GameObjectManager::Get()->Add(new Projectile{ this, m_Pos, GetAngle() });
	//	break;
	//}
	m_pSprite->Update(dT);
	m_pExhaustSprite->Update(dT);

	if (*UIManager::Get()->GetGameState() == GameState::playing)
	{
		for (Weapon* pWeapon : m_pWeapons)
		{
			pWeapon->Update(dT);
		}
	}

	DoTrail(dT);
	HandleMovement(dT);
	HandleCollision(dT);
}

bool Player::IsShooting()
{
	return m_IsShooting;
}

void Player::ToggleShoot()
{
	m_IsShooting = !m_IsShooting;

	for (Weapon* pWeapon : m_pWeapons)
		pWeapon->ToggleShoot();
}

void Player::AddWeapon()
{
	if (m_pWeapons.size() < int(Slot::size))
	{
		if (m_pWeapons.size() == int(Slot::middle))
		{
			m_pWeapons.push_back(new Machinegun{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) });
			return;
		}
		if (m_pWeapons.size() == int(Slot::left))
		{
			m_pWeapons.push_back(new Shotgun{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) });
			return;
		}
		if (m_pWeapons.size() == int(Slot::right))
		{
			m_pWeapons.push_back(new Shotgun{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) });
			return;
		}
		if (m_pWeapons.size() == int(Slot::rear))
		{
			m_pWeapons.push_back(new RocketLauncher{ 10, 10, nullptr, this, 1, Slot(m_pWeapons.size()) });
			return;
		}
	}
}

void Player::Hit(float damage)
{
	m_CurrentHealth -= damage;
	if (m_CurrentHealth <= 0)
	{
		if (m_Lives > 0)
		{
			m_Pos = Point2f{ 787.5f, 787.5f };
			m_CurrentHealth = m_BaseHealth;
			m_Lives -= 1;
		}
		else
		{
			UIManager::Get()->ChangeGameState(GameState::death);
		}
		//std::cout << "Dead";
	}
}

void Player::HitLevel(const Vector2f& dMove)
{
	ChangePos(dMove);
}

float Player::GetBaseHealth() const
{
	return m_BaseHealth;
}

float Player::GetHealth() const
{
	return m_CurrentHealth;
}

float Player::GetLives() const
{
	return m_Lives;
}


#pragma region Behaviour



void Player::HandleMovement(float dT)
{
	const Uint8* state = InputHandling::Get()->KeyState();

	if (state[SDL_SCANCODE_W])
	{
		if (m_Angle > 3.f * utils::g_Pi / 2.f)
			m_Angle = utils::lerp(m_Angle, 5.f * utils::g_Pi / 2.f, dT, 10);
		else
			m_Angle = utils::lerp(m_Angle, utils::g_Pi / 2.f, dT, 10);

		m_Speed += m_Acceleration * dT;
	}
	if (state[SDL_SCANCODE_S])
	{
		if (m_Angle < utils::g_Pi / 2.f)
			m_Angle = utils::lerp(m_Angle, -utils::g_Pi / 2.f, dT, 10);
		else
			m_Angle = utils::lerp(m_Angle, 3.f * utils::g_Pi / 2.f, dT, 10);

		m_Speed += m_Acceleration * dT;
	}
	if (state[SDL_SCANCODE_D])
	{
		if (m_Angle < utils::g_Pi)
			m_Angle = utils::lerp(m_Angle, 0.f, dT, 10);
		else
			m_Angle = utils::lerp(m_Angle, 2 * utils::g_Pi, dT, 10);
		m_Speed += m_Acceleration * dT;
	}
	if (state[SDL_SCANCODE_A])
	{
		m_Angle = utils::lerp(m_Angle, utils::g_Pi, dT, 10);

		m_Speed += m_Acceleration * dT;
	}

	m_Angle = m_Angle < 0 ? m_Angle + 2 * utils::g_Pi : m_Angle;
	m_Angle = m_Angle > 2 * utils::g_Pi ? m_Angle - 2 * utils::g_Pi : m_Angle;

	if (!(m_Speed < DBL_EPSILON))
	{
		m_Speed = utils::lerp(m_Speed, 0.f, dT, m_Friction);
	}

	if (m_Speed > m_MaxSpeed)
		m_Speed = m_MaxSpeed;



	
	m_Pos += (Vector2f(m_Speed * cos(m_Angle), m_Speed * sin(m_Angle)) * dT);
}

void Player::HandleCollision(float /*dT*/)
{
	PolygonCollisionResult result;
	for (GameObject* pGameObject : m_pGameObjectManager->GetEnemies())
	{
			result = sat::PolygonCollision(this, pGameObject);
			if (result.intersect)
			{
				//m_Pos += result.minimumTranslationVector;
			}
	}
}

void Player::DoTrail(float dT)
{
	m_TrailTimer += dT;

	if (m_TrailTimer > 0.1f)
	{
		m_TrailList.PushFront(Circlef{ m_Pos.ToPoint2f(), 5});
		m_TrailTimer = 0;
	}
	if(m_TrailList.Size() > 5)
	{
		m_TrailList.PopBack();
	}
}

void Player::DrawTrail() const
{
	Node<Circlef>* currentNode{ m_TrailList.Begin() };
	for (size_t i{}; i < m_TrailList.Size(); i++)
	{
		utils::SetColor(Color4f{ 133.f, 133.f, 133.f, 1.f });
		Node<Circlef>* pNextNode{ m_TrailList.Begin()->pNext };
		utils::FillEllipse(currentNode->element.center, currentNode->element.radius / (i+1) , currentNode->element.radius / (i+1));
		currentNode = pNextNode;
	}
}

#pragma endregion Behaviour


 

