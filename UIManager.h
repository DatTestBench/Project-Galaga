#pragma once
#include "structs.h"
#include "UIElement.h"

class UIElement;
class UIManager
{
public:
	~UIManager();
	UIManager(const UIManager&) = delete;
	UIManager& operator= (const UIManager&) = delete;
	UIManager(UIManager&&) = delete;
	UIManager& operator=(UIManager&&) = delete;

	// Singleton Functionality
	static UIManager* Get();
	void Destroy();

	// Workers
	void Draw() const;
	void Update(float dT);

	// Item creation / manipulation
	void Add (UIElement* pUIElement);
	void Delete(UIElement* pUIElement);


	void Click(bool state);

	// Getters

	size_t Size() const;
private:
	
	UIManager();

	/// Data Members
	static UIManager* m_pUIManager;
	std::vector<UIElement*> m_UIElements;

	bool m_Click;

	// Buffers
	Buffer<UIElement*> m_AddBuffer;
	Buffer<UIElement*> m_DeleteBuffer;

	/// Member Functions
	// Internal Item Manipulation
	void HandleAdd();
	void HandleDeletion();
};

