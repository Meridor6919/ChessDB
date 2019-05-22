#pragma once
#include "Sprite.h"
#include "Mouse.h"

class Object
{
	bool dragable;
	bool draging;
	static bool s_draging;
	Graphics::Sprite *sprite;

public:
	Object(Graphics::Sprite *sprite, bool dragable);
	bool Update(DirectX::Mouse::ButtonStateTracker* mouse_info, DirectX::Mouse * mouse);
	void Draw();
};

