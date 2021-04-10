#pragma once
#include "Helpers/structs.h"
#include "GameLogic/UIElement.h"
#include "GameLogic/HUD.h"
enum class GameState;
class UIElement;
class UIManager
{
public:
	~UIManager();
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;
	UIManager(UIManager&&) = delete;
	UIManager& operator=(UIManager&&) = delete;

	// Singleton Functionality
	static UIManager* Get();
	static void Destroy();

	// Workers
	void Draw() const;
	void Update(float dT);

	// Item creation / manipulation
	void Add(UIElement* pUIElement);
	void Delete(UIElement* pUIElement);


	void Click(bool state);

	// Getters

	size_t Size() const;
	Vector2f GetWindowSize() const;
	GameState* GetGameState() const;
	bool GetClick() const;
	// Setters

	void SetGameState(GameState* pGameState);
	void SetWindowSize(const Vector2f& window);
	void LoadManager(const Vector2f& window);
	void SetClick(bool isClick);
	// Changers
	void ChangeGameState(const GameState& GameState) const;

private:

	UIManager();

	/// Data Members
	static UIManager* m_pUIManager;
	std::vector<UIElement*> m_UIElements;

	bool m_Click;
	GameState* m_pGameState;
	Vector2f m_WindowSize;

	// Special Screens
	Texture* m_pEndScreen;
	HUD* m_pHud;
	Texture* m_pStartScreen;
	Texture* m_pPauseScreen;

	// Buffers
	Buffer<UIElement*> m_AddBuffer;
	Buffer<UIElement*> m_DeleteBuffer;

	/// Member Functions
	// Internal Item Manipulation
	void HandleAdd();
	void HandleDeletion();
};
