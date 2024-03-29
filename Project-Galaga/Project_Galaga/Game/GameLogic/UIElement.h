#pragma once
#include "Math/Vector2f.h"
#include "Resources/Sprite.h"
#include <map>
#include <functional>
enum class GameState;
class Texture;
class UIManager;
class UIElement
{
public:
	UIElement(const std::string& tag, const Vector2f& pos, float width, float height, bool hasLogic = true);

	// Workers

	void Draw() const;
	void Update(float dT);
	void HandleInput(const Vector2f& inputPos);


	// Getters
	bool GetFlag() const { return m_DelFlag; }

private:
	/// Data Members

	// Element location/shape
	std::string m_Tag; // defines the type of object, loads the correct function pointer
	Vector2f m_Pos;
	float m_Width;
	float m_Height;
	Texture* m_pTexture;
	std::vector<Vector2f> m_Hitbox;
	Sprite* m_pSprite; // Goes for both sprites and textures, if textures are used, collumn and row = 1
	std::map<std::string, std::function<void()>> m_FunctionMap; // Used to store functions
	bool m_DelFlag;
	bool m_IsActive;
	UIManager* m_pUIManager;
	Vector2f m_Window;
	bool m_HasLogic;
	bool m_IsClicked;
	/// Member Functions
	// Type specific action functions
	std::function<void()> GetActionFunction(const std::string& key);
	void LoadFunctionMap();
};
